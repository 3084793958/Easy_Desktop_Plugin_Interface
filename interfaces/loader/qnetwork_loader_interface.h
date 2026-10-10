#ifndef QNETWORK_LOADER_INTERFACE_H
#define QNETWORK_LOADER_INTERFACE_H

#include <QObject>
#include <QUrl>
#include <QByteArray>
#include <QString>

#include <functional>

#include "interfaces/easy_desktop_class.h"

class QNetwork_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual void get(const QUrl &url,
                     std::function<void(const QByteArray &data, const QString &errorString)> callback) = 0;

protected:
    virtual ~QNetwork_Loader_Interface() = default;
};

#endif // QNETWORK_LOADER_INTERFACE_H
