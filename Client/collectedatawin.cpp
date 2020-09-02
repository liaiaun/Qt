#include "collectedatawin.h"
#include"queryinfowin.h"

CollecteDataWin::CollecteDataWin(QWidget *parent) : QWidget(parent)
{
    //设置窗口
    this->setWindowTitle("收集用户信息");
    this->resize(480,420);

    //构造弹出信息框
    m_qwin=new QueryInfoWin();

    //设置Gsettings
    m_settings = new QGSettings("com.deepin.dde.usrdata","/com/deepin/dde/usrdata/");
    //当值发生变化时会发出信号
    connect(m_settings,&QGSettings::changed,[=](const QString key)
    {
        QMap<QString,int> map;
        map.insert("name",1);
        map.insert("age",2);
        map.insert("phone",3);
        map.insert("adress",4);
        map.insert("temperature",5);
        int value=map[key];
        switch (value) {
        case 1:
        {
            QString name=m_settings->get("name").toString();
            m_nameEdit->setText(name);
            break;
        }
        case 2:
        {
            QString age=m_settings->get("age").toString();
            m_ageEdit->setText(age);
            break;
        }
        case 3:
        {
            QString phone=m_settings->get("phone").toString();
            m_phoneEdit->setText(phone);
            break;
        }
        case 4:
        {
            QString adress=m_settings->get("address").toString();
            m_addressEdit->setText(adress);
            break;
        }
        case 5:
        {
            QString temp=m_settings->get("temperature").toString();
            m_temperatureEdit->setText(temp);
            break;
        }
        default:
            break;
        }
    });

    //
    m_nameLabel=new QLabel();
    m_nameLabel->setText("姓    名：");
    m_nameEdit=new QLineEdit();
    QHBoxLayout *nameLayout=new QHBoxLayout();
    nameLayout->addWidget(m_nameLabel);
    nameLayout->addWidget(m_nameEdit);

    m_ageLabel=new QLabel();
    m_ageLabel->setText("年    龄：");
    m_ageEdit=new QLineEdit();
    QHBoxLayout *ageLayout=new QHBoxLayout();
    ageLayout->addWidget(m_ageLabel);
    ageLayout->addWidget(m_ageEdit);

    m_idLabel=new QLabel("身份证：");
    m_idEdit=new QLineEdit();
    QHBoxLayout *idLayout=new QHBoxLayout();
    idLayout->addWidget(m_idLabel);
    idLayout->addWidget(m_idEdit);

    m_addressLabel=new QLabel();
    m_addressLabel->setText("地    址：");
    m_addressEdit=new QLineEdit();
    QHBoxLayout *addressLayout=new QHBoxLayout();
    addressLayout->addWidget(m_addressLabel);
    addressLayout->addWidget(m_addressEdit);

    m_phoneLabel=new QLabel();
    m_phoneLabel->setText("电    话：");
    m_phoneEdit=new QLineEdit();
    QHBoxLayout *phoneLayout=new QHBoxLayout();
    phoneLayout->addWidget(m_phoneLabel);
    phoneLayout->addWidget(m_phoneEdit);

    m_temperatrueLabel=new QLabel();
    m_temperatrueLabel->setText("体    温：");
    m_temperatureEdit=new QLineEdit();
    QHBoxLayout *tempLayout=new QHBoxLayout();
    tempLayout->addWidget(m_temperatrueLabel);
    tempLayout->addWidget(m_temperatureEdit);

    //确定按钮
    m_veriyButton=new QPushButton();
    m_veriyButton->setText("确    定");
    QHBoxLayout *buttonLayout=new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_veriyButton);
    buttonLayout->addStretch();

    m_tips=new QLabel();
    m_tips->setStyleSheet("color:red;");
    QHBoxLayout* tipsLayout=new QHBoxLayout();
    tipsLayout->addStretch();
    tipsLayout->addWidget(m_tips);
    tipsLayout->addStretch();

    //连接按钮点击事件
    connect(m_veriyButton,&QPushButton::pressed,[=]{
        m_tips->setText("");

        bool winIsClose=m_qwin->close();

        //有空行时
        if(m_nameEdit->text().isEmpty()||m_ageEdit->text().isEmpty()||m_phoneEdit->text().isEmpty()||m_idEdit->text().isEmpty()||m_addressEdit->text().isEmpty()||
                m_temperatureEdit->text().isEmpty())
        {
            m_tips->setText("字段不能为空！");
            return;
        }
        //正则表达式判断年龄是否合法
        {
            QRegExp rx("^(?:[1-9][0-9]?|1[01][0-9]|120)$");
            QRegExpValidator v(rx);
            QString text;
            int pos=0;
            QValidator::State state;
            text=m_ageEdit->text();
            state= v.validate(text,pos);
            if(state != QValidator::Acceptable)
            {
                m_tips->setText("请输入1-120之间的整数年龄");
                return;
            }

        }
        //正则表达式判断手机号是否合法
        {
            QRegExp rx("^(13[0-9]|14[5|7]|15[0|1|2|3|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|9]|17[3|9])\\d{8}$");
            QRegExpValidator v(rx);
            QString text;
            int pos=0;
            QValidator::State state;
            text=m_phoneEdit->text();
            state= v.validate(text,pos);
            if(state != QValidator::Acceptable)
            {
                m_tips->setText("手机号输入不合法");
                return;
            }

        }
        //正则表达式判断身份证是否合法
        {
            QRegExp rx("^[1-9]\\d{5}[1-9]\\d{3}((0\\d)|(1[0-2]))(([0|1|2]\\d)|3[0-1])\\d{3}([0-9]|X)$");
            QRegExpValidator v(rx);
            QString text;
            int pos=0;
            QValidator::State state;
            text=m_idEdit->text();
            state= v.validate(text,pos);
            if(state != QValidator::Acceptable)
            {
                m_tips->setText("身份证输入不合法");
                return;
            }

        }
        //正则表达式判断体温是否合法
        {
            QRegExp rx("((3[5-9])|40).\\d$");
            QRegExpValidator v(rx);
            QString text;
            int pos=0;
            QValidator::State state;
            text=m_temperatureEdit->text();
            state= v.validate(text,pos);
            if(state != QValidator::Acceptable)
            {
                m_tips->setText("请输入35.0-40.9之间的温度");
                return;
            }
        }

        //写入dconf
        QString name=m_nameEdit->text();
        m_settings->trySet("name",name);

        int age=m_ageEdit->text().toInt();
        m_settings->trySet("age",age);

        QString phone=m_phoneEdit->text();
        m_settings->trySet("phone",phone);

        QString id=m_idEdit->text();
        m_settings->trySet("id",id);

        QString address=m_addressEdit->text();
        m_settings->trySet("address",address);


        double temperature=m_temperatureEdit->text().toDouble();
        m_settings->trySet("temperature",temperature);

        //设置
        QString txt=m_settings->get("name").toString();
        m_qwin->m_nameShow->setText(txt);

        txt=m_settings->get("age").toString();
        m_qwin->m_ageShow->setText(txt);

        txt=m_settings->get("address").toString();
        m_qwin->m_addressShow->setText(txt);

        txt=m_settings->get("phone").toString();
        m_qwin->m_phoneShow->setText(txt);

        txt=m_settings->get("id").toString();
        m_qwin->m_idShow->setText(txt);

        txt=m_settings->get("temperature").toString();
        m_qwin->m_temperatureShow->setText(txt);

        if(winIsClose)
        {
            m_qwin->show();
        }
    });

    //添加并且设置大小
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addLayout(nameLayout);
    layout->addStretch();
    layout->addLayout(ageLayout);
    layout->addStretch();
    layout->addLayout(phoneLayout);
    layout->addStretch();
    layout->addLayout(idLayout);
    layout->addStretch();
    layout->addLayout(addressLayout);
    layout->addStretch();
    layout->addLayout(tempLayout);
    layout->addStretch();
    layout->addLayout(buttonLayout);
    layout->addStretch();
    layout->addLayout(tipsLayout);

    //布局
    this->setLayout(layout);
}
