#include "cthermometer.h"
#include <QPainter>
#include<QDebug>

CThermometer::CThermometer(QWidget *parent) : QWidget(parent)
{
    initData();

    m_valueAnimation = new QPropertyAnimation(this,"value",this);
    m_valueAnimation->setDuration(1000); //动画时间1秒
    m_valueAnimation->setEasingCurve(QEasingCurve::OutCubic); //动画效果
}

void CThermometer::setValue(qreal value)
{
    m_value = value;

    update();
}

qreal CThermometer::getValue()
{
    return m_value;
}

void CThermometer::setValueWithAnimation(qreal value)
{
    m_valueAnimation->setStartValue(m_value);
    m_valueAnimation->setEndValue(value);
    m_valueAnimation->start();
}

void CThermometer::setMaxValue(int maxValue)
{
    m_maxValue = maxValue - maxValue%10;

    update();
}

void CThermometer::setMinValue(int minValue)
{
    m_minValue = minValue - minValue%10;

    update();
}

void CThermometer::setCenterWidth(int nWidth)
{
    m_width = nWidth;
    update();
}

void CThermometer::setPrecision(PRECISION p)
{
    m_precision = p;
    update();
}

void CThermometer::setTopPadding(int nPad)
{
    m_nPadTop = nPad;
    update();
}

void CThermometer::setBottomPadding(int nPad)
{
    m_nPadBottom = nPad;
    update();
}

void CThermometer::setBackGroundFlag(int nFlag)
{
    m_backGroundFlag = nFlag;
    update();
}

void CThermometer::setScaleColor(QColor color)
{
    m_scaleColor = color;
    update();
}

void CThermometer::setValueColor(QColor color)
{
    m_valueColor=color;
    update();
}

void CThermometer::setBackGroundColor(QColor color)
{
    m_backGroundColor = color;
    update();
}

void CThermometer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    m_value>NORMAL_TEMP?m_valueColor=Qt::red:m_valueColor=Qt::green;
    //背景
    if(m_backGroundFlag == 1)
        paintBackground1(painter);
    else
        paintBackground2(painter);

    //中心柱子底色
    painter.fillRect(m_rect,QColor(168,200,225));

    //圆
    painter.save();
    QRectF tmpRect = QRectF(m_rect.bottomLeft(),QSizeF(m_width,m_width*CIRCLE_RADIUS));
    painter.fillRect(tmpRect,m_valueColor);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_valueColor);
    painter.drawEllipse(tmpRect.bottomLeft() + QPointF(tmpRect.width()/2,0),m_width*CIRCLE_RADIUS,m_width*CIRCLE_RADIUS);
    painter.restore();

    //画刻度
    painter.save();
    painter.setPen(m_scaleColor);
    int nYcount = (m_maxValue - m_minValue)/10 + 1; //分为几个大刻度(预留1个十度上下各0.5个)
    qreal perHeight = m_rect.height()/nYcount;
    int nPrecisionCount = 10/(int)m_precision;
    qreal precisionHeight = perHeight/nPrecisionCount; //最小刻度

    QFontMetricsF fMetrics(painter.font());

    for(int i = 0; i < nYcount; ++i)
    {
        //左侧刻度
        QPointF basePoint = m_rect.bottomLeft() + QPointF(0,-perHeight/2) + QPointF(-2,-perHeight*i);
        painter.drawLine(basePoint,basePoint + QPointF(-8,0)); //左侧大刻度

        if(i != nYcount - 1)
        {
            for(int j = 1; j < nPrecisionCount; ++j)
            {
                painter.drawLine(basePoint + QPointF(0,-precisionHeight*j),basePoint + QPointF(-5,-precisionHeight*j)); //左侧小刻度
            }
        }

        //刻度值
        QString text = QString::number(m_minValue + 10*i);
        QRectF textRect(basePoint + QPointF(-8,0),QSizeF(fMetrics.width(text),fMetrics.height()));
        textRect.adjust(-textRect.width() - 5,-textRect.height()/2,-textRect.width() - 5,-textRect.height()/2);
        painter.drawText(textRect,Qt::AlignCenter,text);


        //右侧刻度
        basePoint = m_rect.bottomRight() + QPointF(0,-perHeight/2) + QPointF(2,-perHeight*i);
        painter.drawLine(basePoint,basePoint + QPointF(8,0));

        if(i != nYcount - 1)
        {
            for(int j = 1; j < nPrecisionCount; ++j)
            {
                painter.drawLine(basePoint + QPointF(0,-precisionHeight*j),basePoint + QPointF(5,-precisionHeight*j)); //左侧小刻度
            }
        }

    }

    painter.restore();

    //值
    qreal h = (m_value - m_minValue + 5)/(m_maxValue - m_minValue + 10)*m_rect.height();

    if(h < 0)
        h = 0;

    if(h > m_rect.height())
        h = m_rect.height();

    painter.fillRect(m_rect.adjusted(0,m_rect.height() - h,0,0),m_valueColor);


    //标识℃
    painter.save();
    painter.setPen(m_scaleColor);
    painter.setFont(QFont("微软雅黑",12,QFont::Bold));
    QRectF flagRect = QRectF(m_rect.topLeft(),QSizeF(fMetrics.width(QString("°C")),fMetrics.height()));
    flagRect.adjust(-flagRect.width() - 20,-flagRect.height(),-flagRect.width() - 20,-flagRect.height());
    painter.drawText(flagRect,Qt::AlignCenter,QString("°C"));
    painter.restore();

}

void CThermometer::paintBackground1(QPainter& painter)
{
    painter.fillRect(rect(),m_backGroundColor);
}

void CThermometer::paintBackground2(QPainter& painter)
{
    painter.save();
    painter.setBrush(m_backGroundColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(),10,10);

    QPen p;
    p.setColor(QColor(61,34,19));
    p.setWidth(4);
    painter.setPen(p);
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(rect(),10,10);
    painter.restore();
}

void CThermometer::resizeEvent(QResizeEvent *e)
{
    updateRect();

    QWidget::resizeEvent(e);
}

void CThermometer::initData()
{
    m_maxValue = 70;
    m_minValue = -30;
    m_value = 37.0;
    m_precision = E_TWO;

    m_width = 8;
    m_nPadTop = 25;
    m_nPadBottom = 40;
    m_backGroundColor = Qt::transparent;
    m_backGroundFlag = 1;
    m_scaleColor = QColor(124,160,180);

    m_valueColor=Qt::green;
}

void CThermometer::updateRect()
{
    m_rect.setX((this->width() - m_width)/2);
    m_rect.setY(m_nPadTop);
    m_rect.setWidth(m_width);
    m_rect.setHeight(this->height() - m_nPadTop - m_nPadBottom - CIRCLE_RADIUS*m_width);
}
