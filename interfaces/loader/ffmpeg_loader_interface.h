#ifndef FFMPEG_LOADER_INTERFACE_H
#define FFMPEG_LOADER_INTERFACE_H

#include "interfaces/easy_desktop_class.h"

//这里不提供函数指针的获取,需要的话从Global_Loader的symbols通过函数符号去获取

class Ffmpeg_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

protected:
    virtual ~Ffmpeg_Loader_Interface() = default;
};

#endif // FFMPEG_LOADER_INTERFACE_H
