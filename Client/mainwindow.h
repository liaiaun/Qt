#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include<QLabel>
#include "cthermometer.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    //设置温度值
    void setValue(qreal value);
    //设置温度值颜色
    void setValueColor(QColor color);
    //显示是否通行
    void showCanPass(bool state);

    ~MainWindow();
private:
    //温度计
    CThermometer *m_thermometer;
    //显示是否放行
    QLabel *m_label;
};

#endif // MAINWINDOW_H
