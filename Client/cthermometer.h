#ifndef CTHERMOMETER_H
#define CTHERMOMETER_H

#include <QWidget>
#include <QPropertyAnimation>

#define CIRCLE_RADIUS 1.5   //圆的半径为是m_width的倍数
#define NORMAL_TEMP   37.2  //正常温度值
//温度计

class CThermometer : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal value READ getValue WRITE setValue)
public:
    enum PRECISION{ //精度(分度值)
        E_ONE = 1,      //一度
        E_TWO,          //两度
        E_FIVE = 5      //五度
    };
    explicit CThermometer(QWidget *parent = 0);

    void setValue(qreal value); //设置值

    qreal getValue(); //获取值

    void setValueWithAnimation(qreal value); //设置值(伴随动画)

    void setMaxValue(int maxValue); //设置最大值(10的倍数)

    void setMinValue(int minValue); //设置最小值(10的倍数)

    void setCenterWidth(int nWidth); //设置中间柱子宽度

    void setPrecision(PRECISION p);  //设置精度

    void setTopPadding(int nPad); //设置顶部空白

    void setBottomPadding(int nPad);//设置底部空白

    void setBackGroundFlag(int nFlag); //背景标志

    void setScaleColor(QColor color); //设置刻度值颜色

    void setValueColor(QColor color); //设置温度值颜色

    void setBackGroundColor(QColor color); //设置背景颜色
protected:
    void paintEvent(QPaintEvent *);     //绘制

    void paintBackground1(QPainter& painter); //绘制背景1,无边框

    void paintBackground2(QPainter& painter); //绘制背景2

    void resizeEvent(QResizeEvent *);

    void initData(); //初始化

    void updateRect(); //计算m_rect值
signals:

public slots:

private:
    int                 m_maxValue;   //最大值(10的倍数)
    int                 m_minValue;   //最小值(10的倍数)
    qreal               m_value;      //值
    PRECISION           m_precision;       //分度值

    QPropertyAnimation* m_valueAnimation;  //动画

    QRectF              m_rect;            //柱子范围
    int                 m_width;           //中间柱状的宽度
    int                 m_nPadTop;         //顶部空白
    int                 m_nPadBottom;      //底部空白

    QColor              m_scaleColor;       //刻度颜色
    int                 m_backGroundFlag;   //背景样式 -- 背景的绘制可根据设计编写
    QColor              m_backGroundColor;  //背景颜色
    
    QColor              m_valueColor;       //温度值颜色；

};

#endif // CTHERMOMETER_H
