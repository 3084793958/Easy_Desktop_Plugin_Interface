#ifndef PULSE_LOADER_INTERFACE_H
#define PULSE_LOADER_INTERFACE_H

#include <cstddef>
#include <cstdint>

#include "interfaces/easy_desktop_class.h"

#include <cstdint>
#include <cstddef>

struct pa_mainloop;
struct pa_mainloop_api;
struct pa_context;
struct pa_stream;
struct pa_operation;
struct pa_proplist;
struct pa_format_info;
struct pa_simple;

typedef uint64_t pa_usec_t;
typedef uint32_t pa_volume_t;
#define PA_CHANNELS_MAX 32U

typedef enum pa_sample_format
{
    PA_SAMPLE_U8,
    PA_SAMPLE_ALAW,
    PA_SAMPLE_ULAW,
    PA_SAMPLE_S16LE,
    PA_SAMPLE_S16BE,
    PA_SAMPLE_FLOAT32LE,
    PA_SAMPLE_FLOAT32BE,
    PA_SAMPLE_S32LE,
    PA_SAMPLE_S32BE,
    PA_SAMPLE_S24LE,
    PA_SAMPLE_S24BE,
    PA_SAMPLE_S24_32LE,
    PA_SAMPLE_S24_32BE,
    PA_SAMPLE_MAX,
    PA_SAMPLE_INVALID = -1
} pa_sample_format_t;

typedef struct pa_sample_spec
{
    pa_sample_format_t format;
    uint32_t rate;
    uint8_t channels;
} pa_sample_spec;

typedef enum pa_channel_position
{
    PA_CHANNEL_POSITION_INVALID = -1,
    PA_CHANNEL_POSITION_MONO = 0,
    PA_CHANNEL_POSITION_FRONT_LEFT,
    PA_CHANNEL_POSITION_FRONT_RIGHT,
    PA_CHANNEL_POSITION_FRONT_CENTER,
    PA_CHANNEL_POSITION_LEFT = PA_CHANNEL_POSITION_FRONT_LEFT,
    PA_CHANNEL_POSITION_RIGHT = PA_CHANNEL_POSITION_FRONT_RIGHT,
    PA_CHANNEL_POSITION_CENTER = PA_CHANNEL_POSITION_FRONT_CENTER,
    PA_CHANNEL_POSITION_REAR_CENTER,
    PA_CHANNEL_POSITION_REAR_LEFT,
    PA_CHANNEL_POSITION_REAR_RIGHT,
    PA_CHANNEL_POSITION_LFE,
    PA_CHANNEL_POSITION_SUBWOOFER = PA_CHANNEL_POSITION_LFE,
    PA_CHANNEL_POSITION_FRONT_LEFT_OF_CENTER,
    PA_CHANNEL_POSITION_FRONT_RIGHT_OF_CENTER,
    PA_CHANNEL_POSITION_SIDE_LEFT,
    PA_CHANNEL_POSITION_SIDE_RIGHT,
    PA_CHANNEL_POSITION_AUX0,
    PA_CHANNEL_POSITION_AUX1,
    PA_CHANNEL_POSITION_AUX2,
    PA_CHANNEL_POSITION_AUX3,
    PA_CHANNEL_POSITION_AUX4,
    PA_CHANNEL_POSITION_AUX5,
    PA_CHANNEL_POSITION_AUX6,
    PA_CHANNEL_POSITION_AUX7,
    PA_CHANNEL_POSITION_AUX8,
    PA_CHANNEL_POSITION_AUX9,
    PA_CHANNEL_POSITION_AUX10,
    PA_CHANNEL_POSITION_AUX11,
    PA_CHANNEL_POSITION_AUX12,
    PA_CHANNEL_POSITION_AUX13,
    PA_CHANNEL_POSITION_AUX14,
    PA_CHANNEL_POSITION_AUX15,
    PA_CHANNEL_POSITION_AUX16,
    PA_CHANNEL_POSITION_AUX17,
    PA_CHANNEL_POSITION_AUX18,
    PA_CHANNEL_POSITION_AUX19,
    PA_CHANNEL_POSITION_AUX20,
    PA_CHANNEL_POSITION_AUX21,
    PA_CHANNEL_POSITION_AUX22,
    PA_CHANNEL_POSITION_AUX23,
    PA_CHANNEL_POSITION_AUX24,
    PA_CHANNEL_POSITION_AUX25,
    PA_CHANNEL_POSITION_AUX26,
    PA_CHANNEL_POSITION_AUX27,
    PA_CHANNEL_POSITION_AUX28,
    PA_CHANNEL_POSITION_AUX29,
    PA_CHANNEL_POSITION_AUX30,
    PA_CHANNEL_POSITION_AUX31,
    PA_CHANNEL_POSITION_TOP_CENTER,
    PA_CHANNEL_POSITION_TOP_FRONT_LEFT,
    PA_CHANNEL_POSITION_TOP_FRONT_RIGHT,
    PA_CHANNEL_POSITION_TOP_FRONT_CENTER,
    PA_CHANNEL_POSITION_TOP_REAR_LEFT,
    PA_CHANNEL_POSITION_TOP_REAR_RIGHT,
    PA_CHANNEL_POSITION_TOP_REAR_CENTER,
    PA_CHANNEL_POSITION_MAX
} pa_channel_position_t;

typedef struct pa_channel_map
{
    uint8_t channels;
    pa_channel_position_t map[PA_CHANNELS_MAX];
} pa_channel_map;

typedef struct pa_cvolume
{
    uint8_t channels;
    pa_volume_t values[PA_CHANNELS_MAX];
} pa_cvolume;

typedef enum pa_context_state
{
    PA_CONTEXT_UNCONNECTED,
    PA_CONTEXT_CONNECTING,
    PA_CONTEXT_AUTHORIZING,
    PA_CONTEXT_SETTING_NAME,
    PA_CONTEXT_READY,
    PA_CONTEXT_FAILED,
    PA_CONTEXT_TERMINATED
} pa_context_state_t;

typedef enum pa_stream_state
{
    PA_STREAM_UNCONNECTED,
    PA_STREAM_CREATING,
    PA_STREAM_READY,
    PA_STREAM_FAILED,
    PA_STREAM_TERMINATED
} pa_stream_state_t;

typedef enum pa_sink_state
{
    PA_SINK_INVALID_STATE = -1,
    PA_SINK_RUNNING = 0,
    PA_SINK_IDLE = 1,
    PA_SINK_SUSPENDED = 2
} pa_sink_state_t;

typedef enum pa_source_state
{
    PA_SOURCE_INVALID_STATE = -1,
    PA_SOURCE_RUNNING = 0,
    PA_SOURCE_IDLE = 1,
    PA_SOURCE_SUSPENDED = 2
} pa_source_state_t;

typedef enum pa_context_flags
{
    PA_CONTEXT_NOFLAGS = 0x0000U,
    PA_CONTEXT_NOAUTOSPAWN = 0x0001U,
    PA_CONTEXT_NOFAIL = 0x0002U
} pa_context_flags_t;

typedef enum pa_stream_flags
{
    PA_STREAM_NOFLAGS = 0x0000U,
    PA_STREAM_START_CORKED = 0x0001U,
    PA_STREAM_INTERPOLATE_TIMING = 0x0002U,
    PA_STREAM_NOT_MONOTONIC = 0x0004U,
    PA_STREAM_AUTO_TIMING_UPDATE = 0x0008U,
    PA_STREAM_NO_REMAP_CHANNELS = 0x0010U,
    PA_STREAM_NO_REMIX_CHANNELS = 0x0020U,
    PA_STREAM_FIX_FORMAT = 0x0040U,
    PA_STREAM_FIX_RATE = 0x0080U,
    PA_STREAM_FIX_CHANNELS = 0x0100,
    PA_STREAM_DONT_MOVE = 0x0200U,
    PA_STREAM_VARIABLE_RATE = 0x0400U,
    PA_STREAM_PEAK_DETECT = 0x0800U,
    PA_STREAM_START_MUTED = 0x1000U,
    PA_STREAM_ADJUST_LATENCY = 0x2000U,
    PA_STREAM_EARLY_REQUESTS = 0x4000U,
    PA_STREAM_DONT_INHIBIT_AUTO_SUSPEND = 0x8000U,
    PA_STREAM_START_UNMUTED = 0x10000U,
    PA_STREAM_FAIL_ON_SUSPEND = 0x20000U,
    PA_STREAM_RELATIVE_VOLUME = 0x40000U,
    PA_STREAM_PASSTHROUGH = 0x80000U
} pa_stream_flags_t;

typedef enum pa_sink_flags
{
    PA_SINK_NOFLAGS = 0x0000U,
    PA_SINK_HW_VOLUME_CTRL = 0x0001U,
    PA_SINK_LATENCY = 0x0002U,
    PA_SINK_HARDWARE = 0x0004U,
    PA_SINK_NETWORK = 0x0008U,
    PA_SINK_HW_MUTE_CTRL = 0x0010U,
    PA_SINK_DECIBEL_VOLUME = 0x0020U,
    PA_SINK_FLAT_VOLUME = 0x0040U,
    PA_SINK_DYNAMIC_LATENCY = 0x0080U,
    PA_SINK_SET_FORMATS = 0x0100U
} pa_sink_flags_t;

typedef enum pa_source_flags
{
    PA_SOURCE_NOFLAGS = 0x0000U,
    PA_SOURCE_HW_VOLUME_CTRL = 0x0001U,
    PA_SOURCE_LATENCY = 0x0002U,
    PA_SOURCE_HARDWARE = 0x0004U,
    PA_SOURCE_NETWORK = 0x0008U,
    PA_SOURCE_HW_MUTE_CTRL = 0x0010U,
    PA_SOURCE_DECIBEL_VOLUME = 0x0020U,
    PA_SOURCE_DYNAMIC_LATENCY = 0x0040U,
    PA_SOURCE_FLAT_VOLUME = 0x0080U
} pa_source_flags_t;

typedef enum pa_stream_direction
{
    PA_STREAM_NODIRECTION,
    PA_STREAM_PLAYBACK,
    PA_STREAM_RECORD,
    PA_STREAM_UPLOAD
} pa_stream_direction_t;

typedef struct pa_sink_port_info
{
    const char *name;
    const char *description;
    uint32_t priority;
    int available;
    const char *availability_group;
    uint32_t type;
} pa_sink_port_info;

typedef struct pa_source_port_info
{
    const char *name;
    const char *description;
    uint32_t priority;
    int available;
    const char *availability_group;
    uint32_t type;
} pa_source_port_info;

typedef struct pa_server_info
{
    const char *user_name;
    const char *host_name;
    const char *server_version;
    const char *server_name;
    pa_sample_spec sample_spec;
    const char *default_sink_name;
    const char *default_source_name;
    uint32_t cookie;
    pa_channel_map channel_map;
} pa_server_info;

typedef struct pa_sink_info
{
    const char *name;
    uint32_t index;
    const char *description;
    pa_sample_spec sample_spec;
    pa_channel_map channel_map;
    uint32_t owner_module;
    pa_cvolume volume;
    int mute;
    uint32_t monitor_source;
    const char *monitor_source_name;
    pa_usec_t latency;
    const char *driver;
    pa_sink_flags_t flags;
    pa_proplist *proplist;
    pa_usec_t configured_latency;
    pa_volume_t base_volume;
    pa_sink_state_t state;
    uint32_t n_volume_steps;
    uint32_t card;
    uint32_t n_ports;
    pa_sink_port_info **ports;
    pa_sink_port_info *active_port;
    uint8_t n_formats;
    pa_format_info **formats;
} pa_sink_info;

typedef struct pa_source_info
{
    const char *name;
    uint32_t index;
    const char *description;
    pa_sample_spec sample_spec;
    pa_channel_map channel_map;
    uint32_t owner_module;
    pa_cvolume volume;
    int mute;
    uint32_t monitor_of_sink;
    const char *monitor_of_sink_name;
    pa_usec_t latency;
    const char *driver;
    pa_source_flags_t flags;
    pa_proplist *proplist;
    pa_usec_t configured_latency;
    pa_volume_t base_volume;
    pa_source_state_t state;
    uint32_t n_volume_steps;
    uint32_t card;
    uint32_t n_ports;
    pa_source_port_info **ports;
    pa_source_port_info *active_port;
    uint8_t n_formats;
    pa_format_info **formats;
} pa_source_info;

typedef struct pa_buffer_attr
{
    uint32_t maxlength;
    uint32_t tlength;
    uint32_t prebuf;
    uint32_t minreq;
    uint32_t fragsize;
} pa_buffer_attr;

typedef void (*pa_context_notify_cb_t)(pa_context *c, void *userdata);
typedef void (*pa_server_info_cb_t)(pa_context *c, const pa_server_info *i, void *userdata);
typedef void (*pa_sink_info_cb_t)(pa_context *c, const pa_sink_info *i, int eol, void *userdata);
typedef void (*pa_source_info_cb_t)(pa_context *c, const pa_source_info *i, int eol, void *userdata);
typedef void (*pa_stream_notify_cb_t)(pa_stream *s, void *userdata);
typedef void (*pa_stream_request_cb_t)(pa_stream *s, size_t nbytes, void *userdata);

class Pulse_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual pa_mainloop* pa_mainloop_new() = 0;
    virtual pa_mainloop_api* pa_mainloop_get_api(pa_mainloop *m) = 0;
    virtual void pa_mainloop_free(pa_mainloop *m) = 0;
    virtual int pa_mainloop_iterate(pa_mainloop *m, int block, int *ret) = 0;

    virtual pa_context* pa_context_new(pa_mainloop_api *api, const char *name) = 0;
    virtual int pa_context_connect(pa_context *c, const char *server, pa_context_flags flags, const void *api) = 0;
    virtual void pa_context_set_state_callback(pa_context *c, pa_context_notify_cb_t cb, void *userdata) = 0;
    virtual pa_context_state_t pa_context_get_state(pa_context *c) = 0;
    virtual pa_operation* pa_context_get_server_info(pa_context *c, pa_server_info_cb_t cb, void *userdata) = 0;
    virtual pa_operation* pa_context_get_sink_info_by_name(pa_context *c, const char *name, pa_sink_info_cb_t cb, void *userdata) = 0;
    virtual pa_operation* pa_context_get_source_info_by_name(pa_context *c, const char *name, pa_source_info_cb_t cb, void *userdata) = 0;
    virtual void pa_context_disconnect(pa_context *c) = 0;
    virtual void pa_context_unref(pa_context *c) = 0;

    virtual pa_stream* pa_stream_new(pa_context *c, const char *name, const pa_sample_spec *ss, const pa_channel_map *map) = 0;
    virtual void pa_stream_set_state_callback(pa_stream *s, pa_stream_notify_cb_t cb, void *userdata) = 0;
    virtual void pa_stream_set_read_callback(pa_stream *s, pa_stream_request_cb_t cb, void *userdata) = 0;
    virtual int pa_stream_connect_record(pa_stream *s, const char *device, const pa_buffer_attr *attr, pa_stream_flags flags) = 0;
    virtual void pa_stream_disconnect(pa_stream *s) = 0;
    virtual void pa_stream_unref(pa_stream *s) = 0;
    virtual int pa_stream_peek(pa_stream *p, const void **data, size_t *nbytes) = 0;
    virtual void pa_stream_drop(pa_stream *p) = 0;
    virtual pa_stream_state_t pa_stream_get_state(pa_stream *p) = 0;
    virtual const pa_sample_spec* pa_stream_get_sample_spec(pa_stream *p) = 0;
    virtual size_t pa_frame_size(const pa_sample_spec *spec) = 0;

    virtual void pa_operation_unref(pa_operation *o) = 0;

    virtual pa_simple *pa_simple_new(const char *server,
                                     const char *name,
                                     pa_stream_direction_t dir,
                                     const char *dev,
                                     const char *stream_name,
                                     const pa_sample_spec *ss,
                                     const pa_channel_map *map,
                                     const pa_buffer_attr *attr,
                                     int *error) = 0;
    virtual int pa_simple_write(pa_simple *s, const void *data, size_t bytes, int *error) = 0;
    virtual int pa_simple_drain(pa_simple *s, int *error) = 0;
    virtual void pa_simple_free(pa_simple *s) = 0;
    virtual const char *pa_strerror(int error) = 0;

protected:
    virtual ~Pulse_Loader_Interface() = default;
};

#endif // PULSE_LOADER_INTERFACE_H
