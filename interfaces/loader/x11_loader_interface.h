#ifndef X11_LOADER_INTERFACE_H
#define X11_LOADER_INTERFACE_H

#include <QObject>
#include <QString>
#include <QWidget>
#include <QPixmap>
#include <QRect>
#include <QSize>
#include <QByteArray>

#include <functional>
#include <sys/types.h>

#include "interfaces/easy_desktop_class.h"

struct _XRectangle;
typedef struct _XRectangle XRectangle;

class X11_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual QString getWindowPropertyString(unsigned long id,
                                            const QString &propertyName,
                                            unsigned long type = 31UL) const = 0;

    virtual bool getWindowPropertyRaw(unsigned long window,
                                      const QString &propertyName,
                                      unsigned long reqType,
                                      QByteArray &data,
                                      unsigned long *actualType = nullptr,
                                      int *actualFormat = nullptr) const = 0;

    virtual QString getAtomName(unsigned long atom) const = 0;
    virtual pid_t getWindowPid(unsigned long window) = 0;
    virtual bool isWindowValid(unsigned long id) const = 0;
    virtual void raiseWindow(unsigned long window) = 0;
    virtual void lowerWindow(unsigned long window) = 0;
    virtual void setInputFocus(unsigned long window) = 0;
    virtual void flush() = 0;
    virtual QWidget* mergeWindow(unsigned long window, QWidget *container) = 0;
    virtual void breakWindow(unsigned long window, QWidget *targetWidget, QWidget *container) = 0;
    virtual void setRectangularShape(unsigned long window, int radius, QSize size) = 0;
    virtual void clearRectangularShape(unsigned long window) = 0;
    virtual void intersectRegion(unsigned long window, const XRectangle *rects, int count) = 0;
    virtual void selectWindowFromUser(std::function<void(bool, unsigned long)> callback) = 0;
    virtual void moveToWorkspace(int &human_index, bool &workspace_donotshow, QWidget *widget, QRect &screen_geometry) = 0;
    virtual void setAsDesktop(QWidget *widget) = 0;
    virtual QPixmap grabWindow(unsigned long window, int x = 0, int y = 0, int w = -1, int h = -1) = 0;
    virtual unsigned long rootWindow(int screen = -1) const = 0;
    virtual int defaultScreen() const = 0;
    virtual int connectionNumber() const = 0;

protected:
    virtual ~X11_Loader_Interface() = default;
};

#endif // X11_LOADER_INTERFACE_H
