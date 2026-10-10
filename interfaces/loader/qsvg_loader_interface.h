#ifndef QSVG_LOADER_INTERFACE_H
#define QSVG_LOADER_INTERFACE_H

#include <QString>
#include <QSize>
#include <QRectF>
#include <QPainter>

#include "interfaces/easy_desktop_class.h"

class QSvg_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual void *create(const QString &fileName) = 0;
    virtual void destroy(void *renderer) = 0;

    virtual QSize defaultSize(const void *renderer) = 0;
    virtual void render(const void *renderer, QPainter *painter, const QRectF &bounds) = 0;

    virtual bool isValid(const void *renderer) = 0;

protected:
    virtual ~QSvg_Loader_Interface() = default;
};

#endif // QSVG_LOADER_INTERFACE_H
