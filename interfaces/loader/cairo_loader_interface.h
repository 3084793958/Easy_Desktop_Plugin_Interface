#ifndef CAIRO_LOADER_INTERFACE_H
#define CAIRO_LOADER_INTERFACE_H

#include "interfaces/easy_desktop_class.h"

typedef struct _cairo cairo_t;
typedef struct _cairo_surface cairo_surface_t;

class Cairo_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual cairo_surface_t* cairo_image_surface_create_for_data(unsigned char *data,
                                                                 int format,
                                                                 int width,
                                                                 int height,
                                                                 int stride) = 0;
    virtual cairo_t* cairo_create(cairo_surface_t *surface) = 0;
    virtual void cairo_translate(cairo_t *cr, double tx, double ty) = 0;
    virtual void cairo_scale(cairo_t *cr, double sx, double sy) = 0;
    virtual void cairo_destroy(cairo_t *cr) = 0;
    virtual void cairo_surface_destroy(cairo_surface_t *surface) = 0;
    virtual void cairo_set_matrix(cairo_t *cr, double xx, double yx, double xy, double yy, double x0, double y0) = 0;

protected:
    virtual ~Cairo_Loader_Interface() = default;
};

#endif // CAIRO_LOADER_INTERFACE_H
