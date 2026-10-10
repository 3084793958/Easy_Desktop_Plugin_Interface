#ifndef QDBUS_LOADER_INTERFACE_H
#define QDBUS_LOADER_INTERFACE_H

#include <QObject>
#include <QString>
#include <QVariantList>

#include <functional>

#include "interfaces/easy_desktop_class.h"

class QDbus_Loader_Interface
{
public:
    using SignalCallback = std::function<void(const QVariantList &args)>;

    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual QVariantList callMethod(const QString &service,
                                    const QString &path,
                                    const QString &interface,
                                    const QString &method,
                                    const QVariantList &args = QVariantList()) = 0;

    virtual bool emitSignal(const QString &path,
                            const QString &interface,
                            const QString &name,
                            const QVariantList &args = QVariantList()) = 0;

    virtual bool emitTargetedSignal(const QString &service,
                                    const QString &path,
                                    const QString &interface,
                                    const QString &name,
                                    const QVariantList &args = QVariantList()) = 0;

    virtual bool connectSignal(const QString &service,
                               const QString &path,
                               const QString &interface,
                               const QString &name,
                               SignalCallback callback) = 0;

    virtual bool disconnectSignal(const QString &service,
                                  const QString &path,
                                  const QString &interface,
                                  const QString &name) = 0;

    virtual bool connectSignalToSlot(const QString &service,
                                     const QString &path,
                                     const QString &interface,
                                     const QString &name,
                                     QObject *receiver,
                                     const char *slot) = 0;

    virtual bool disconnectSignalFromSlot(const QString &service,
                                          const QString &path,
                                          const QString &interface,
                                          const QString &name,
                                          QObject *receiver,
                                          const char *slot) = 0;

    virtual QString getGlobalMenuLayoutJson_for_Raw_GlobalMenu_Manager(const QString &service,
                                                                       const QString &path,
                                                                       int parentId = 0) = 0;

    virtual bool connectLayoutUpdatedSignal_for_Raw_GlobalMenu_Manager(const QString &service,
                                                                       const QString &path,
                                                                       QObject *receiver,
                                                                       const char *slot) = 0;

    virtual bool disconnectLayoutUpdatedSignal_for_Raw_GlobalMenu_Manager(const QString &service,
                                                                          const QString &path,
                                                                          QObject *receiver,
                                                                          const char *slot) = 0;

protected:
    virtual ~QDbus_Loader_Interface() = default;
};

#endif // QDBUS_LOADER_INTERFACE_H
