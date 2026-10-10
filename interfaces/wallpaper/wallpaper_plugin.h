#ifndef WALLPAPER_PLUGIN_H
#define WALLPAPER_PLUGIN_H

#include "interfaces/easy_desktop_class.h"

#include <QColor>
#include <QSize>
#include "interfaces/wallpaper/wallpaper_info_def.h"

class Ext_Wallpaper_PluginInterface
{
public:
    //插件需要在json中说明自己支持Ext_Wallpaper_Plugin
    //格式:   "Ext_Wallpaper_Plugin": ""
    //ADD
    const QString Ext_Name = "Easy_Desktop_Wallpaper";
    const QString Ext_Spec = "";
    //ADD

    P_Version Plugin_Version{0, 0, 3};//不使用const,用于欺骗Easy_Desktop

    ///
    /// \brief inited
    /// Desktop_Background会处理,你不需要管这个变量
    ///
    bool inited = false;

    //0.0.1
    ///
    /// \brief ~Ext_Wallpaper_PluginInterface()
    /// 就是正常的析构函数
    ///
    virtual ~Ext_Wallpaper_PluginInterface();
    ///
    /// \brief RemovePlugin
    /// 移除该插件,你需要做的是停止控件/释放内存[必须实现]
    ///
    virtual void RemovePlugin() = 0;
    ///
    /// \brief init(const Path_Info &info, P_Sender *send_position_sender)
    /// 初始化时传递用户设定的信息,其中,info包含wallpaper信息,send_position_sender为更新进度条的sender,使用Send_Data(QList<QVariant>() << int value << QString text)
    /// \param info
    /// \param send_position_sender
    ///
    virtual void init(const Path_Info &info, P_Sender *send_position_sender);
    ///
    /// \brief update_style(QColor theme_color, QColor theme_background_color, QColor theme_text_color, QColor select_text_color, QColor disabled_text_color, const QString & checked_icon_path)
    /// 设置style
    /// \param theme_color
    /// \param theme_background_color
    /// \param theme_text_color
    /// \param select_text_color
    /// \param disabled_text_color
    /// \param checked_icon_path
    ///
    virtual void update_style(QColor theme_color, QColor theme_background_color, QColor theme_text_color, QColor select_text_color, QColor disabled_text_color, const QString & checked_icon_path);
    ///
    /// \brief mouseMoveEvent(int mouse_x, int mouse_y)
    /// 当鼠标运动时,传递鼠标信息
    /// \param mouse_x
    /// \param mouse_y
    ///
    virtual void mouseMoveEvent(int mouse_x, int mouse_y);
    ///
    /// \brief play
    /// 播放时触发
    ///
    virtual void play();
    ///
    /// \brief pause
    /// 暂停时触发
    ///
    virtual void pause();
    ///
    /// \brief setPosition
    /// 进度条更改时触发,value:0-100
    /// \param value
    ///
    virtual void setPosition(int value);
    ///
    /// \brief setVolume
    /// 音量更改时触发
    /// \param value
    ///
    virtual void setVolume(int value);
    ///
    /// \brief setSpeed
    /// 倍速更改时触发
    /// \param value
    ///
    virtual void setSpeed(int value);
    ///
    /// \brief sizeChange
    /// 大小改变时触发
    /// \param size
    ///
    virtual void sizeChange(QSize size);
    ///
    /// \brief settingsEvent
    /// 呼出插件的设置窗口的
    ///
    virtual void settingsEvent();
    ///
    /// \brief wallpaperItem
    /// 给出一个wallpaper的实现,Easy_Desktop会将其渲染[必须实现]
    /// \return
    ///
    virtual QWidget *wallpaperItem() = 0;

    //V_0.0.2
    ///
    /// \brief Trans_Update
    /// 告诉插件:翻译动态更新了
    ///
    virtual void Trans_Update();
    //V_0.0.2

    //V_0.0.3
    ///
    /// \brief update_style_V2
    /// 主题风格设置V2
    /// \param m_theme_color
    /// \param m_theme_background_color
    /// \param m_theme_text_color
    /// \param m_select_text_color
    /// \param m_disabled_text_color
    /// \param m_checked_icon_path
    /// \param m_checked_and_selected_icon_path
    /// \param m_radius
    /// \param m_icon_size
    /// \param m_separator_color
    /// \param m_min_width
    /// \param m_on_blurring_type
    /// \param m_text_font
    /// \param m_menu_outline_color
    /// \param m_menu_outline_width
    /// \param m_blur_radius
    /// \param m_highlight_color
    ///
    virtual void update_style_V2(QColor  m_theme_color,
                                 QColor  m_theme_background_color,
                                 QColor  m_theme_text_color,
                                 QColor  m_select_text_color,
                                 QColor  m_disabled_text_color,
                                 const QString & m_checked_icon_path,
                                 const QString & m_checked_and_selected_icon_path,
                                 int     m_radius,
                                 int     m_icon_size,
                                 QColor  m_separator_color,
                                 int     m_min_width,
                                 int     m_on_blurring_type,
                                 QFont   m_text_font,
                                 QColor  m_menu_outline_color,
                                 int     m_menu_outline_width,
                                 int     m_blur_radius,
                                 QColor  m_highlight_color);

    ///
    /// \brief init(const Ext_Path_Info_V_0_0_1 &info, const P_Sender *seek_loader_sender, const P_Sender *recive_loader_sender)
    /// 初始化时传递用户设定的信息,其中,info包含wallpaper信息.
    /// loaderNames会为你提供当前Easy_Desktop拥有的loader的QString.
    /// ,seek_loader_sender用于请求loader指针, recive_loader_sender用于获取loader指针.无论怎样都会返回,若没有这个loader,会给nullptr.
    /// 注意:seek_loader_sender只走Send_Data路线,请发送一个QString(这里是全匹配,没有模糊匹配),
    /// recive_loader_sender只走Send_Ptr路线,给出void *,需要自行转化.Easy_Desktop不会负责除这两条线外的其他路线.
    /// \param info
    ///
    virtual void init_V_0_0_3(const Ext_Path_Info_V_0_0_1 &info, const QStringList &loaderNames, const P_Sender *seek_loader_sender, const P_Sender *recive_loader_sender);
    ///
    /// \brief call_plugin_save
    /// 通知保存
    ///
    virtual void call_plugin_save();
    ///
    /// \brief setPitch
    /// 音调更改时触发 V0.0.3+
    ///
    virtual void setPitch(int value);
    ///
    /// \brief setPosition_qint64
    /// 进度条更改时触发,value反映真实帧
    /// \param value
    ///
    virtual void setPosition_qint64(qint64 value);
    ///
    /// \brief get_qint64_pos_and_dur_sender
    /// media_widgetaction的dialog细化设置position需要依靠这两个值,
    /// Easy_Desktop在收到send_position_sender的信号后调用,
    /// 记得提供哦>(O^<)<
    /// \param position
    /// \param duration
    ///
    virtual void get_qint64_pos_and_dur_sender(qint64 &position, qint64 &duration);

    ///
    /// \brief easy_desktop_version
    /// 宿主调用, 告知插件当前 Easy_Desktop 的版本信息与 AKA 名称
    /// 插件可通过此回调做兼容性判断
    ///
    virtual void easy_desktop_version(const P_Version &Easy_Desktop_Version, const QString &AKA_name);
    //V_0.0.3
};

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(Ext_Wallpaper_PluginInterface, "com.Easy.Desktop.Ext_Wallpaper_PluginInterface")

QT_END_NAMESPACE

#endif // WALLPAPER_PLUGIN_H
