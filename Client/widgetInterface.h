/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp ../com.deepin.dbus.usrdata.xml -p ../Client/widgetInterface
 *
 * qdbusxml2cpp is Copyright (C) 2017 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef WIDGETINTERFACE_H
#define WIDGETINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.deepin.dbus.usrdata
 */
class ComDeepinDbusUsrdataInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.deepin.dbus.usrdata"; }

public:
    ComDeepinDbusUsrdataInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);

    ~ComDeepinDbusUsrdataInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<int> ReceiveUsrData(const QString &name, int age, const QString &phone, const QString &id, const QString &address, double temp)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(name) << QVariant::fromValue(age) << QVariant::fromValue(phone) << QVariant::fromValue(id) << QVariant::fromValue(address) << QVariant::fromValue(temp);
        return asyncCallWithArgumentList(QStringLiteral("ReceiveUsrData"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace com {
  namespace deepin {
    namespace dbus {
      typedef ::ComDeepinDbusUsrdataInterface usrdata;
    }
  }
}
#endif
