#ifndef QPDF_LOADER_INTERFACE_H
#define QPDF_LOADER_INTERFACE_H

#include <QObject>
#include <QImage>
#include <QSizeF>
#include <QSize>
#include <QString>

#include <functional>

#include "interfaces/easy_desktop_class.h"

class QPdf_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual void *createDocument(QObject *parent = nullptr) = 0;
    virtual void destroyDocument(void *doc) = 0;
    virtual bool documentLoad(void *doc, const QString &fileName) = 0;
    virtual int documentPageCount(const void *doc) = 0;
    virtual QSizeF documentPageSize(const void *doc, int page) = 0;
    virtual int documentPageRotation(const void *doc, int page) = 0;
    virtual void documentClose(void *doc) = 0;
    virtual QImage documentRender(const void *doc, int page, const QSize &size) = 0;
    virtual QImage documentRenderClipped(const void *doc, int page, const QSize &fullSize, const QRect &scaledClipRect) = 0;

    virtual void *createPageNavigation(QObject *parent = nullptr) = 0;
    virtual void destroyPageNavigation(void *nav) = 0;
    virtual void navigationSetDocument(void *nav, void *doc) = 0;
    virtual int navigationCurrentPage(void *nav) = 0;
    virtual void navigationSetCurrentPage(void *nav, int page) = 0;
    virtual void navigationGoToPreviousPage(void *nav) = 0;
    virtual void navigationGoToNextPage(void *nav) = 0;

    virtual void setCurrentPageChangedCallback(void *nav, std::function<void()> callback) = 0;
    virtual void removeCurrentPageChangedCallback(void *nav) = 0;

protected:
    virtual ~QPdf_Loader_Interface() = default;
};

#endif // QPDF_LOADER_INTERFACE_H
