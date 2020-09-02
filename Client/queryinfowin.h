#ifndef QUERYINFOWIN_H
#define QUERYINFOWIN_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>

#include"widgetInterface.h"
#include"mainwindow.h"

class CollecteDataWin;

class QueryInfoWin : public QWidget
{
    Q_OBJECT
    friend CollecteDataWin;
public:
    explicit QueryInfoWin(QWidget *parent = nullptr);

private:
    QLabel *m_nameLabel;
    QLabel *m_ageLabel;
    QLabel *m_phoneLabel;
    QLabel *m_idLabel;
    QLabel *m_addressLabel;
    QLabel *m_temperatureLabel;

    QLabel *m_nameShow;
    QLabel *m_ageShow;
    QLabel *m_phoneShow;
    QLabel *m_idShow;
    QLabel *m_addressShow;
    QLabel *m_temperatureShow;

    //发送按钮
    QPushButton* m_sendButton;

    //Dbus代理
    ComDeepinDbusUsrdataInterface* m_dbusProxy;

    //温度显示窗口
    MainWindow* m_mainWin;
};

#endif // QUERYINFOWIN_H
