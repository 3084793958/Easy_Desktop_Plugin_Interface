#ifndef POPPLER_LOADER_INTERFACE_H
#define POPPLER_LOADER_INTERFACE_H

#include <QObject>
#include <QImage>
#include <QSizeF>
#include <QString>

#include "interfaces/easy_desktop_class.h"

class Poppler_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual void *createDocument(const QString &filePath) = 0;
    virtual void destroyDocument(void *doc) = 0;
    virtual int documentPages(const void *doc) = 0;
    virtual void *documentCreatePage(const void *doc, int index) = 0;

    virtual void destroyPage(void *page) = 0;
    virtual QSizeF pageSize(const void *page) = 0;

    virtual QImage pageRenderToImageEx(const void *page, double dpiX, double dpiY, int cropX, int cropY, int cropW, int cropH, int rotation, bool decodeAlpha) = 0;

protected:
    virtual ~Poppler_Loader_Interface() = default;
};


#endif // POPPLER_LOADER_INTERFACE_H
