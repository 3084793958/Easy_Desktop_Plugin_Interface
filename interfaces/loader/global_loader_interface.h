#ifndef GLOBAL_LOADER_INTERFACE_H
#define GLOBAL_LOADER_INTERFACE_H

#include <QHash>
#include <QList>
#include <QPair>
#include <QString>
#include <QStringList>

#include "interfaces/easy_desktop_class.h"

class Global_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;

    //返回:0-全部符号有效,1-部分符号有效,-1-加载失败且指针清空,-2-加载失败但保留旧指针
    virtual int loadLibrary(const QStringList &fileNames,
                            const QList<QPair<void**, QStringList>> &symbolGroups,
                            const QString &loadName,
                            bool forceReload = false) = 0;

    virtual void *resolve(const QString &loadName, const QString &symbol) const = 0;
    virtual bool isLoaded(const QString &loadName) const = 0;
    virtual const QHash<QString, QHash<QString, void *>> &getSymbolsHash() = 0;

protected:
    virtual ~Global_Loader_Interface() = default;
};

#endif // GLOBAL_LOADER_INTERFACE_H
