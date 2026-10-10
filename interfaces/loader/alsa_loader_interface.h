#ifndef ALSA_LOADER_INTERFACE_H
#define ALSA_LOADER_INTERFACE_H

#include <cstddef>
#include <cstdint>
#include "interfaces/easy_desktop_class.h"

typedef struct _snd_pcm snd_pcm_t;
typedef struct _snd_pcm_hw_params snd_pcm_hw_params_t;

typedef int snd_pcm_sframes_t;

enum _snd_pcm_stream
{
    SND_PCM_STREAM_PLAYBACK = 0,
    SND_PCM_STREAM_CAPTURE  = 1
};

enum _snd_pcm_access
{
    SND_PCM_ACCESS_RW_INTERLEAVED = 3
};

enum _snd_pcm_format
{
    SND_PCM_FORMAT_UNKNOWN     = -1,
    SND_PCM_FORMAT_S8          = 0,
    SND_PCM_FORMAT_U8          = 1,
    SND_PCM_FORMAT_S16_LE      = 2,
    SND_PCM_FORMAT_S16_BE      = 3,
    SND_PCM_FORMAT_U16_LE      = 4,
    SND_PCM_FORMAT_U16_BE      = 5,
    SND_PCM_FORMAT_S24_LE      = 6,
    SND_PCM_FORMAT_S24_BE      = 7,
    SND_PCM_FORMAT_U24_LE      = 8,
    SND_PCM_FORMAT_U24_BE      = 9,
    SND_PCM_FORMAT_S32_LE      = 10,
    SND_PCM_FORMAT_S32_BE      = 11,
    SND_PCM_FORMAT_U32_LE      = 12,
    SND_PCM_FORMAT_U32_BE      = 13,
    SND_PCM_FORMAT_FLOAT_LE    = 14,
    SND_PCM_FORMAT_FLOAT_BE    = 15,
    SND_PCM_FORMAT_FLOAT64_LE  = 16,
    SND_PCM_FORMAT_FLOAT64_BE  = 17,
    SND_PCM_FORMAT_IEC958_SUBFRAME_LE = 18,
    SND_PCM_FORMAT_IEC958_SUBFRAME_BE = 19,
    SND_PCM_FORMAT_MU_LAW      = 20,
    SND_PCM_FORMAT_A_LAW       = 21,
    SND_PCM_FORMAT_IMA_ADPCM   = 22,
    SND_PCM_FORMAT_MPEG        = 23,
    SND_PCM_FORMAT_GSM         = 24,
    SND_PCM_FORMAT_SPECIAL     = 31,
    SND_PCM_FORMAT_S24_3LE     = 32,
    SND_PCM_FORMAT_S24_3BE     = 33,
    SND_PCM_FORMAT_U24_3LE     = 34,
    SND_PCM_FORMAT_U24_3BE     = 35,
    SND_PCM_FORMAT_S20_3LE     = 36,
    SND_PCM_FORMAT_S20_3BE     = 37,
    SND_PCM_FORMAT_U20_3LE     = 38,
    SND_PCM_FORMAT_U20_3BE     = 39,
    SND_PCM_FORMAT_S18_3LE     = 40,
    SND_PCM_FORMAT_S18_3BE     = 41,
    SND_PCM_FORMAT_U18_3LE     = 42,
    SND_PCM_FORMAT_U18_3BE     = 43,
    SND_PCM_FORMAT_G723_24     = 44,
    SND_PCM_FORMAT_G723_24_1B  = 45,
    SND_PCM_FORMAT_G723_40     = 46,
    SND_PCM_FORMAT_G723_40_1B  = 47,
    SND_PCM_FORMAT_DSD_U8      = 48,
    SND_PCM_FORMAT_DSD_U16_LE  = 49,
    SND_PCM_FORMAT_DSD_U32_LE  = 50,
    SND_PCM_FORMAT_DSD_U16_BE  = 51,
    SND_PCM_FORMAT_DSD_U32_BE  = 52
};

enum _snd_pcm_state
{
    SND_PCM_STATE_OPEN,
    SND_PCM_STATE_SETUP,
    SND_PCM_STATE_PREPARED,
    SND_PCM_STATE_RUNNING,
    SND_PCM_STATE_XRUN,
    SND_PCM_STATE_DRAINING,
    SND_PCM_STATE_PAUSED,
    SND_PCM_STATE_SUSPENDED,
    SND_PCM_STATE_DISCONNECTED
};

typedef int  (*snd_pcm_open_func)(snd_pcm_t** pcm, const char* name, int stream, int mode);
typedef int  (*snd_pcm_close_func)(snd_pcm_t* pcm);
typedef int  (*snd_pcm_prepare_func)(snd_pcm_t* pcm);
typedef int  (*snd_pcm_drop_func)(snd_pcm_t* pcm);
typedef int  (*snd_pcm_drain_func)(snd_pcm_t* pcm);
typedef snd_pcm_sframes_t (*snd_pcm_readi_func)(snd_pcm_t* pcm, void* buffer, unsigned long size);
typedef snd_pcm_sframes_t (*snd_pcm_writei_func)(snd_pcm_t* pcm, const void* buffer, unsigned long size);
typedef int  (*snd_pcm_hw_params_any_func)(snd_pcm_t* pcm, snd_pcm_hw_params_t* params);
typedef int  (*snd_pcm_hw_params_set_access_func)(snd_pcm_t* pcm, snd_pcm_hw_params_t* params, int access);
typedef int  (*snd_pcm_hw_params_set_format_func)(snd_pcm_t* pcm, snd_pcm_hw_params_t* params, int format);
typedef int  (*snd_pcm_hw_params_set_channels_func)(snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val);
typedef int  (*snd_pcm_hw_params_set_rate_near_func)(snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir);
typedef int  (*snd_pcm_hw_params_func)(snd_pcm_t* pcm, snd_pcm_hw_params_t* params);
typedef void (*snd_pcm_hw_params_free_func)(snd_pcm_hw_params_t* params);
typedef int  (*snd_pcm_hw_params_malloc_func)(snd_pcm_hw_params_t** ptr);
typedef const char* (*snd_strerror_func)(int errnum);

class Alsa_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual int snd_pcm_open(snd_pcm_t** pcm, const char* name, int stream, int mode) = 0;
    virtual int snd_pcm_close(snd_pcm_t* pcm) = 0;
    virtual int snd_pcm_prepare(snd_pcm_t* pcm) = 0;
    virtual int snd_pcm_drop(snd_pcm_t* pcm) = 0;
    virtual int snd_pcm_drain(snd_pcm_t* pcm) = 0;
    virtual snd_pcm_sframes_t snd_pcm_readi(snd_pcm_t* pcm, void* buffer, unsigned long size) = 0;
    virtual snd_pcm_sframes_t snd_pcm_writei(snd_pcm_t* pcm, const void* buffer, unsigned long size) = 0;
    virtual int snd_pcm_hw_params_any(snd_pcm_t* pcm, snd_pcm_hw_params_t* params) = 0;
    virtual int snd_pcm_hw_params_set_access(snd_pcm_t* pcm, snd_pcm_hw_params_t* params, int access) = 0;
    virtual int snd_pcm_hw_params_set_format(snd_pcm_t* pcm, snd_pcm_hw_params_t* params, int format) = 0;
    virtual int snd_pcm_hw_params_set_channels(snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int val) = 0;
    virtual int snd_pcm_hw_params_set_rate_near(snd_pcm_t* pcm, snd_pcm_hw_params_t* params, unsigned int* val, int* dir) = 0;
    virtual int snd_pcm_hw_params(snd_pcm_t* pcm, snd_pcm_hw_params_t* params) = 0;
    virtual void snd_pcm_hw_params_free(snd_pcm_hw_params_t* params) = 0;
    virtual int snd_pcm_hw_params_malloc(snd_pcm_hw_params_t** ptr) = 0;
    virtual const char* snd_strerror(int errnum) = 0;
protected:
    virtual ~Alsa_Loader_Interface() = default;
};

#endif // ALSA_LOADER_INTERFACE_H

