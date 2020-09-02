#include "mainwindow.h"
#include<QStyle>
#include<QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    //设置窗口
    this->setWindowTitle("通行界面");
    this->resize(800,680);

    m_thermometer=new CThermometer;
    m_thermometer->setPrecision(CThermometer::E_ONE);
    m_thermometer->setMaxValue(50);
    m_thermometer->setMinValue(20);
    m_thermometer->setValue(37.2);

    //label
    m_label=new QLabel();
    m_label->setText("是否放行：是");

    //设置水平布局
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_label);
    layout->addWidget(m_thermometer);

    this->setLayout(layout);

}

void MainWindow::setValue(qreal value)
{
    m_thermometer->setValue(value);
}

void MainWindow::setValueColor(QColor color)
{
    m_thermometer->setValueColor(color);
}

void MainWindow::showCanPass(bool state)
{
    if(state)
    {
        m_label->setText("能否通行：否");
        m_label->setStyleSheet("color:red;");
    }
    else {
        m_label->setText("能否通行：能");
        m_label->setStyleSheet("color:green;");
    }
    m_label->update();
}

MainWindow::~MainWindow()
{

}
