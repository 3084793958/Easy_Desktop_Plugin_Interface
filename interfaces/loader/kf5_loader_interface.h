#ifndef KF5_LOADER_INTERFACE_H
#define KF5_LOADER_INTERFACE_H

#include <QRegion>
#include <QWidget>

#include "interfaces/easy_desktop_class.h"

class KF5_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual bool isBlurAvailable() const = 0;
    virtual void enableBlurBehind(WId window, bool enable, const QRegion &region = QRegion()) = 0;

protected:
    virtual ~KF5_Loader_Interface() = default;
};

#endif // KF5_LOADER_INTERFACE_H
