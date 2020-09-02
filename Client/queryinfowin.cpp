#include "queryinfowin.h"

QueryInfoWin::QueryInfoWin(QWidget *parent) : QWidget(parent)
  ,m_dbusProxy(new ComDeepinDbusUsrdataInterface("com.deepin.dbus.usrdata",
                                                 "/com/deepin/dbus/usrdata",
                                                 QDBusConnection::sessionBus(),this))
{
    //设置窗口标题
    this->setWindowTitle("用户信息");
    this->resize(480,420);

    //构造mainwin
    m_mainWin=new MainWindow();

    m_nameLabel=new QLabel("姓名：");       //姓名
    m_nameShow=new QLabel();
    QHBoxLayout *nameLayout=new QHBoxLayout();
    nameLayout->addWidget(m_nameLabel);
    nameLayout->addWidget(m_nameShow);

    m_ageLabel=new QLabel("年龄：");        //年龄
    m_ageShow=new QLabel();
    QHBoxLayout *ageLayout=new QHBoxLayout();
    ageLayout->addWidget(m_ageLabel);
    ageLayout->addWidget(m_ageShow);

    m_phoneLabel=new QLabel("电话：");      //电话
    m_phoneShow=new QLabel();
    QHBoxLayout *phoneLayout=new QHBoxLayout();
    phoneLayout->addWidget(m_phoneLabel);
    phoneLayout->addWidget(m_phoneShow);

    m_idLabel=new QLabel("身份证：");
    m_idShow=new QLabel();
    QHBoxLayout *idLayout=new QHBoxLayout();
    idLayout->addWidget(m_idLabel);
    idLayout->addWidget(m_idShow);

    m_addressLabel=new QLabel("地址：");           //地址
    m_addressShow=new QLabel();
    QHBoxLayout *addressLayout=new QHBoxLayout();
    addressLayout->addWidget(m_addressLabel);
    addressLayout->addWidget(m_addressShow);

    m_temperatureLabel =new QLabel("体温：");       //体温
    m_temperatureShow=new QLabel();
    QHBoxLayout *tempLayout=new QHBoxLayout();
    tempLayout->addWidget(m_temperatureLabel);
    tempLayout->addWidget(m_temperatureShow);

    //按钮
    m_sendButton=new QPushButton();
    m_sendButton->setText("发送");
    //连接信号
    //点击确定后会发送给服务器使用Dbus通信
    connect(m_sendButton,&QPushButton::pressed,[=]{

        //点击按钮前,先关闭已有的

        bool winIsClose=m_mainWin->close();

        QString name=m_nameShow->text();
        int age=m_ageShow->text().toInt();
        QString phone=m_phoneShow->text();
        QString id=m_idShow->text();
        QString address=m_addressShow->text();
        double temperature=m_temperatureShow->text().toDouble();
        int state =m_dbusProxy->ReceiveUsrData(name,age,phone,id,address,temperature);

        //设置温度值
        m_mainWin->setValue(temperature);
        m_mainWin->showCanPass(state);
        if(state==0) //放行
        {
            m_mainWin->setValueColor(Qt::green);
        }else if(state==1){      //不能放行
            m_mainWin->setValueColor(Qt::red);
        }

        if(winIsClose)
        {
            m_mainWin->show();
        }
    });

    //设置按钮布局
    QHBoxLayout* qbtnLayout =new QHBoxLayout();
    qbtnLayout->addStretch();
    qbtnLayout->addWidget(m_sendButton);
    qbtnLayout->addStretch();

    //
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addLayout(nameLayout);
    layout->addLayout(ageLayout);
    layout->addLayout(phoneLayout);
    layout->addLayout(idLayout);
    layout->addLayout(addressLayout);
    layout->addLayout(tempLayout);
    layout->addLayout(qbtnLayout);
    //添加布局
    this->setLayout(layout);
}
