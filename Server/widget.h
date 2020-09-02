#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTableView>
#include<QStandardItemModel>
#include<QLayout>
#include<QtDBus>
#include<QCloseEvent>

#define NORMAL_TEMP   37.2  //正常温度值


class Widget : public QWidget
{
    Q_OBJECT
    //定义Interface名称为com.scorpio.test.value
    Q_CLASSINFO("D-Bus Interface", "com.deepin.dbus.usrdata")


protected:
    //窗口关闭事件
    void closeEvent(QCloseEvent *event);
    //保存数据到xml
    void WriteUsrDataToXML();
    //从XML读取数据
    void ReadUsrDataFromXML();

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    //存储客户端发过来的数据
    QTableView *m_table;
    QStandardItemModel* m_model;

public slots:
    int ReceiveUsrData(QString name,int age,QString phone,QString id,QString address,double temp);
};

#endif // WIDGET_H
