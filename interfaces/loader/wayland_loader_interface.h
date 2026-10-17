#ifndef WAYLAND_LOADER_INTERFACE_H
#define WAYLAND_LOADER_INTERFACE_H

#include "interfaces/easy_desktop_class.h"

#include <cstdint>

struct wl_display;
struct wl_registry;
struct wl_surface;
struct wl_proxy;

class Wayland_Loader_Interface
{
public:
    virtual ~Wayland_Loader_Interface() = default;

    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual wl_display *display() const = 0;

    virtual wl_registry *get_registry() = 0;
    virtual void registry_add_listener(wl_registry *r,
                                        void (*cb)(void *, wl_registry *, uint32_t, const char *, uint32_t),
                                        void *data) = 0;
    virtual void *registry_bind(wl_registry *r, uint32_t name,
                                const void *iface, uint32_t version) = 0;

    virtual wl_proxy *proxy_marshal_flags(wl_proxy *proxy, uint32_t opcode,
                                          const void *iface, uint32_t version,
                                          uint32_t flags, ...) = 0;
    virtual uint32_t proxy_get_version(wl_proxy *proxy) = 0;
    virtual void proxy_destroy(wl_proxy *proxy) = 0;

    virtual int display_roundtrip(wl_display *d) = 0;
    virtual int display_dispatch(wl_display *d) = 0;
    virtual void display_flush(wl_display *d) = 0;
};

#endif // WAYLAND_LOADER_INTERFACE_H
