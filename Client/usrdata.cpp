#include"usrdata.h"

// 将MyStructure 数据编码到 D-Bus argument中
QDBusArgument &operator<<(QDBusArgument &argument, const usrdata &usr)
{
    argument.beginStructure();
    argument << usr.name << usr.age << usr.phone << usr.id << usr.address << usr.temperature;
    argument.endStructure();
    return argument;
}

// 从D-Bus argumentj解码数据到MyStructure data 中
const QDBusArgument &operator>>(const QDBusArgument &argument, usrdata &usr)
{
    argument.beginStructure();
    argument >> usr.name >> usr.age >> usr.phone >> usr.id >> usr.address >> usr.temperature;
    argument.endStructure();
    return argument;
}





void usrdata::registerMetaType()
{
    qDBusRegisterMetaType<usrdata>();
}
