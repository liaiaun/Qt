#ifndef COLLECTEDATAWIN_H
#define COLLECTEDATAWIN_H

#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QString>
#include<QGSettings/QGSettings>
#include<QMap>
#include<QRegExp>
#include<QRegExpValidator>

class QueryInfoWin;

class CollecteDataWin : public QWidget
{
    Q_OBJECT

public:
    explicit CollecteDataWin(QWidget *parent = nullptr);
private:
    QLabel *m_nameLabel;         //姓名
    QLabel *m_ageLabel;          //年龄
    QLabel *m_phoneLabel;        //电话
    QLabel *m_idLabel;               //身份证
    QLabel *m_addressLabel;       //地址
    QLabel *m_temperatrueLabel;  //体温

    QLineEdit *m_nameEdit;
    QLineEdit *m_ageEdit;
    QLineEdit *m_phoneEdit;
    QLineEdit *m_idEdit;
    QLineEdit *m_addressEdit;
    QLineEdit *m_temperatureEdit;

    QPushButton *m_veriyButton; //确定按钮

    QGSettings* m_settings;

    //提示信息
    QLabel* m_tips;

    //弹出用户信息界面
    QueryInfoWin *m_qwin;


signals:

public slots:
};

#endif // COLLECTEDATAWIN_H
