#include "widget.h"
#include <QApplication>

#include"widgetAdaptor.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
    w.show();

    //ValueAdaptor是qdbusxml2cpp生成的Adaptor类
    UsrdataAdaptor usrAd(&w);

    //建立与DBus的连接
    QDBusConnection connection = QDBusConnection::sessionBus();
    //注册Dbus服务
    if (!connection.registerService("com.deepin.dbus.usrdata")) {
        qDebug() << "error:" << connection.lastError().message();
        exit(-1);
    }
    //注册Dbus对象
    connection.registerObject("/com/deepin/dbus/usrdata", &w);
    return a.exec();
}
