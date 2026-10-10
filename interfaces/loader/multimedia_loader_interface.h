#ifndef MULTIMEDIA_LOADER_INTERFACE_H
#define MULTIMEDIA_LOADER_INTERFACE_H

#include <QObject>
#include <QUrl>
#include <QList>
#include <QString>
#include <QByteArray>
#include <QImage>
#include <QSizeF>
#include <Qt>

#include <functional>

#include "interfaces/easy_desktop_class.h"

class Multimedia_Loader_Interface
{
public:
    virtual P_Version loader_version() = 0;
    virtual int loadLibrary(bool force = false) = 0;
    virtual bool isLoaded() const = 0;

    virtual void *createMediaPlayer(QObject *parent = nullptr) = 0;
    virtual void destroyMediaPlayer(void *player) = 0;

    virtual void playerSetMedia(void *player, const QUrl &url) = 0;
    virtual void playerSetPlaylist(void *player, const QList<QUrl> &urls, int startIndex = 0) = 0;

    virtual void playerPlay(void *player) = 0;
    virtual void playerPause(void *player) = 0;
    virtual void playerStop(void *player) = 0;
    virtual void playerSetPosition(void *player, qint64 pos) = 0;
    virtual void playerSetVolume(void *player, int volume) = 0;
    virtual void playerSetPlaybackRate(void *player, qreal rate) = 0;
    virtual void playerSetPitch(void *player, qreal pitch) = 0;

    virtual void playerSetPlaybackOption(void *player, int option) = 0;
    virtual void playerSetNextIndexController(void *player, std::function<int(int)> controller) = 0;

    virtual int playerCurrentIndex(void *player) = 0;
    virtual int playerPlaylistSize(void *player) = 0;
    virtual int playerPlaybackOption(void *player) = 0;

    virtual qint64 playerDuration(void *player) = 0;
    virtual int playerState(void *player) = 0;
    virtual int playerMediaStatus(void *player) = 0;
    virtual void playerSetVideoOutput(void *player, void *videoItem) = 0;
    virtual void playerClearMedia(void *player) = 0;
    virtual bool playerHasMedia(void *player) = 0;

    virtual void *createVideoItem() = 0;
    virtual void destroyVideoItem(void *item) = 0;
    virtual QSize videoItemSize(void *item) = 0;
    virtual void videoItemSetSize(void *item, const QSizeF &size) = 0;
    virtual void videoItemSetAspectRatioMode(void *item, Qt::AspectRatioMode mode) = 0;

    virtual void *createAudioDecoder(QObject *parent = nullptr) = 0;
    virtual void destroyAudioDecoder(void *decoder) = 0;
    virtual void decoderSetSourceFilename(void *decoder, const QString &fileName) = 0;
    virtual void decoderStart(void *decoder) = 0;
    virtual void decoderStop(void *decoder) = 0;

    virtual void setPlayerPositionChangedCallback(void *player, std::function<void(qint64)> cb) = 0;
    virtual void setPlayerStateChangedCallback(void *player, std::function<void(int)> cb) = 0;
    virtual void setPlayerMediaStatusChangedCallback(void *player, std::function<void(int)> cb) = 0;
    virtual void setPlayerCurrentIndexChangedCallback(void *player, std::function<void(int)> cb) = 0;
    virtual void setAudioDecoderBufferReadyCallback(void *decoder, std::function<void(const QByteArray &, int, int, int, int)> cb) = 0;
    virtual void setAudioDecoderFinishedCallback(void *decoder, std::function<void()> cb) = 0;
    virtual void setVideoItemNativeSizeChangedCallback(void *item, std::function<void(const QSizeF &)> cb) = 0;

    virtual void removePlayerPositionChangedCallback(void *player) = 0;
    virtual void removePlayerStateChangedCallback(void *player) = 0;
    virtual void removePlayerMediaStatusChangedCallback(void *player) = 0;
    virtual void removePlayerCurrentIndexChangedCallback(void *player) = 0;
    virtual void removeVideoItemNativeSizeChangedCallback(void *item) = 0;
    virtual void removeAudioDecoderBufferReadyCallback(void *decoder) = 0;
    virtual void removeAudioDecoderFinishedCallback(void *decoder) = 0;

protected:
    virtual ~Multimedia_Loader_Interface() = default;
};

#endif // MULTIMEDIA_LOADER_INTERFACE_H
