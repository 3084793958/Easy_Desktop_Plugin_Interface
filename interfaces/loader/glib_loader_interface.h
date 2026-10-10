#ifndef GLIB_LOADER_INTERFACE_H
#define GLIB_LOADER_INTERFACE_H

#include "interfaces/easy_desktop_class.h"

typedef struct _GError GError;

class Glib_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual void g_error_free(GError *error) = 0;

protected:
    virtual ~Glib_Loader_Interface() = default;
};

#endif // GLIB_LOADER_INTERFACE_H
