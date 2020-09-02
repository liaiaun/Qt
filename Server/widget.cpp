#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("服务端");
    this->resize(1280,960);

    m_model = new QStandardItemModel();
    /* 设置列数 */
    m_model->setColumnCount(7);
    m_model->setHeaderData(0, Qt::Horizontal, "姓名");
    m_model->setHeaderData(1, Qt::Horizontal, "年龄");
    m_model->setHeaderData(2, Qt::Horizontal, "电话");
    m_model->setHeaderData(3, Qt::Horizontal, "身份证");
    m_model->setHeaderData(4, Qt::Horizontal, "地址");
    m_model->setHeaderData(5, Qt::Horizontal, "体温");
    m_model->setHeaderData(6,Qt::Horizontal, "是否放行");
    //    /* 设置行数 */
    //    m_model->setRowCount(14);
    //    m_model->setHeaderData(0, Qt::Vertical, 1);
    ReadUsrDataFromXML();

    m_table=new QTableView();
    m_table->setModel(m_model);

    //放在后面设置
    //设置列宽
    m_table->setColumnWidth(2,120);
    m_table->setColumnWidth(3,180);
    m_table->setColumnWidth(4,160);

    QLayout* layout=new QHBoxLayout();
    layout->addWidget(m_table);

    this->setLayout(layout);
}

void Widget::closeEvent(QCloseEvent *event)
{
    //保存数据到xml
    WriteUsrDataToXML();

    event->accept();
}

void Widget::WriteUsrDataToXML()
{
    QFile file("usrdata.xml");

    if (!file.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "Error: cannot open file";
        return;
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("items");
    for(int i=0;i<m_model->rowCount();i++){
        writer.writeStartElement("item");
        writer.writeTextElement("name",m_model->item(i,0)->text());
        writer.writeTextElement("age",m_model->item(i,1)->text());
        writer.writeTextElement("phone",m_model->item(i,2)->text());
        writer.writeTextElement("id",m_model->item(i,3)->text());
        writer.writeTextElement("address",m_model->item(i,4)->text());
        writer.writeTextElement("temperature",m_model->item(i,5)->text());
        writer.writeTextElement("passable",m_model->item(i,6)->text());
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();

}

void Widget::ReadUsrDataFromXML()
{
    QFile file("usrdata.xml");
        if (!file.open(QFile::ReadOnly | QFile::Text)){
            qDebug()<<"Error: cannot open file";
            return;
        }
        QXmlStreamReader reader;
        reader.setDevice(&file);
        QVector<QString> data;
        while (!reader.atEnd()){
            QXmlStreamReader::TokenType type = reader.readNext();
            if (type == QXmlStreamReader::Characters&& !reader.isWhitespace()){
                QString temp(reader.text().toUtf8());
                data.append(temp);
            }
        }
        int k=0;
        if(data.size()/7==0)
            return;
        for(int i=0;i<data.size()/7;i++){
            m_model->insertRow(m_model->rowCount());
            for(int j=0;j<7;j++){
                QStandardItem *item=new QStandardItem();
                item->setText(data.at(k++));
                //qDebug()<<newItem->text();
                m_model->setItem(i,j,item);
            }
        }
}


Widget::~Widget()
{

}

int Widget::ReceiveUsrData(QString name,int age,QString phone,QString id,QString address,double temp)
{

    int state=0;
    QString b="是";
    if(temp > NORMAL_TEMP)
    {
        state=1;
        b="否";
    }

    QList<QStandardItem*> list;
    list<<new QStandardItem(name)<<new QStandardItem(QString::number(age))<<new QStandardItem(phone)<<new QStandardItem(id)<<
          new QStandardItem(address)<<new QStandardItem(QString::number(temp))<<new QStandardItem(b);

    //根据身份证号查询记录是否存在
    for(int i=0;i<m_model->rowCount();++i)
    {
        if(m_model->item(i,3)->text()==id)
        {
            //更新
            m_model->removeRow(i);
            m_model->insertRow(i,list);
            return state;
        }
    }

    //否则追加
    m_model->appendRow(list);

    return state;
}
