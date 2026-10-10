#include "wallpaper_plugin.h"

#include <QFont>
Ext_Wallpaper_PluginInterface::~Ext_Wallpaper_PluginInterface() {}

void Ext_Wallpaper_PluginInterface::init(const Path_Info &info, P_Sender *send_position_sender)
{
    (void) info;
    (void) send_position_sender;
}
void Ext_Wallpaper_PluginInterface::update_style(QColor theme_color, QColor theme_background_color, QColor theme_text_color, QColor select_text_color, QColor disabled_text_color, const QString &checked_icon_path)
{
    (void) theme_color;
    (void) theme_background_color;
    (void) theme_text_color;
    (void) select_text_color;
    (void) disabled_text_color;
    (void) checked_icon_path;
}
void Ext_Wallpaper_PluginInterface::mouseMoveEvent(int mouse_x, int mouse_y)
{
    (void) mouse_x;
    (void) mouse_y;
}
void Ext_Wallpaper_PluginInterface::play()
{}
void Ext_Wallpaper_PluginInterface::pause()
{}
void Ext_Wallpaper_PluginInterface::setPosition(int value)
{
    (void) value;
}
void Ext_Wallpaper_PluginInterface::setVolume(int value)
{
    (void) value;
}
void Ext_Wallpaper_PluginInterface::setSpeed(int value)
{
    (void) value;
}
void Ext_Wallpaper_PluginInterface::sizeChange(QSize size)
{
    (void) size;
}
void Ext_Wallpaper_PluginInterface::settingsEvent()
{}
void Ext_Wallpaper_PluginInterface::Trans_Update()
{}
void Ext_Wallpaper_PluginInterface::update_style_V2(QColor m_theme_color, QColor m_theme_background_color, QColor m_theme_text_color, QColor m_select_text_color, QColor m_disabled_text_color, const QString &m_checked_icon_path, const QString &m_checked_and_selected_icon_path, int m_radius, int m_icon_size, QColor m_separator_color, int m_min_width, int m_on_blurring_type, QFont m_text_font, QColor m_menu_outline_color, int m_menu_outline_width, int m_blur_radius, QColor m_highlight_color)
{
    (void) m_theme_color;
    (void) m_theme_background_color;
    (void) m_theme_text_color;
    (void) m_select_text_color;
    (void) m_disabled_text_color;
    (void) m_checked_icon_path;
    (void) m_checked_and_selected_icon_path;
    (void) m_radius;
    (void) m_icon_size;
    (void) m_separator_color;
    (void) m_min_width;
    (void) m_on_blurring_type;
    (void) m_text_font;
    (void) m_menu_outline_color;
    (void) m_menu_outline_width;
    (void) m_blur_radius;
    (void) m_highlight_color;
}
void Ext_Wallpaper_PluginInterface::init_V_0_0_3(const Ext_Path_Info_V_0_0_1 &info, const QStringList &loaderNames, const P_Sender *seek_loader_sender, const P_Sender *recive_loader_sender)
{
    (void) info;
    (void) loaderNames;
    (void) seek_loader_sender;
    (void) recive_loader_sender;
}
void Ext_Wallpaper_PluginInterface::call_plugin_save()
{}
void Ext_Wallpaper_PluginInterface::setPitch(int value)
{
    (void) value;
}
void Ext_Wallpaper_PluginInterface::setPosition_qint64(qint64 value)
{
    (void) value;
}
void Ext_Wallpaper_PluginInterface::get_qint64_pos_and_dur_sender(qint64 &position, qint64 &duration)
{
    (void) position;
    (void) duration;
}

void Ext_Wallpaper_PluginInterface::easy_desktop_version(const P_Version &Easy_Desktop_Version, const QString &AKA_name)
{
    (void) Easy_Desktop_Version;
    (void) AKA_name;
}
