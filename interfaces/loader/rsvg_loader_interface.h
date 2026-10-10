#ifndef RSVG_LOADER_INTERFACE_H
#define RSVG_LOADER_INTERFACE_H

#include "interfaces/easy_desktop_class.h"

typedef struct _RsvgHandle RsvgHandle;
typedef struct _GError GError;
typedef struct _cairo cairo_t;

struct RsvgDimensionData
{
    int width;
    int height;
};

class Rsvg_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual RsvgHandle *rsvg_handle_new_from_file(const char *file_name, GError **error) = 0;
    virtual void rsvg_handle_get_dimensions(RsvgHandle *handle, RsvgDimensionData *dimension_data) = 0;
    virtual void rsvg_handle_render_cairo(RsvgHandle *handle, cairo_t *cr) = 0;
    virtual void g_object_unref(void *object) = 0;

protected:
    virtual ~Rsvg_Loader_Interface() = default;
};

#endif // RSVG_LOADER_INTERFACE_H
