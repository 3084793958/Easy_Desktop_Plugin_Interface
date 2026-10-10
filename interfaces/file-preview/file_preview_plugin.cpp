#include "file_preview_plugin.h"

#include <QFont>

Ext_Preview_PluginInterface::~Ext_Preview_PluginInterface()
{}
void Ext_Preview_PluginInterface::init(Preview_File_Interface *ptr, QWidget *carrier)
{
    (void) ptr;
    (void) carrier;
}
void Ext_Preview_PluginInterface::update_style(QColor theme_color, QColor theme_background_color, QColor theme_text_color, QColor select_text_color, QColor disabled_text_color, const QString &checked_icon_path)
{
    (void) theme_color;
    (void) theme_background_color;
    (void) theme_text_color;
    (void) select_text_color;
    (void) disabled_text_color;
    (void) checked_icon_path;
}
QWidget *Ext_Preview_PluginInterface::previewItem()
{
    return nullptr;
}

bool Ext_Preview_PluginInterface::willThrowFileToNextPreview()
{
    return false;
}
void Ext_Preview_PluginInterface::resetZoom()
{}
void Ext_Preview_PluginInterface::init_V_0_0_2(Preview_File_Interface_V_0_0_2 *ptr)
{
    (void) ptr;
}
void Ext_Preview_PluginInterface::init_V_0_0_3(Preview_File_Interface_V_0_0_3 *ptr)
{
    (void) ptr;
}
void Ext_Preview_PluginInterface::Trans_Update()
{}
void Ext_Preview_PluginInterface::init_V_0_0_4(Preview_File_Interface_V_0_0_4 *ptr, const QStringList &loaderNames, const P_Sender *seek_loader_sender, const P_Sender *recive_loader_sender)
{
    (void) ptr;
    (void) loaderNames;
    (void) seek_loader_sender;
    (void) recive_loader_sender;
}
void Ext_Preview_PluginInterface::update_style_V2(QColor m_theme_color, QColor m_theme_background_color, QColor m_theme_text_color, QColor m_select_text_color, QColor m_disabled_text_color, const QString &m_checked_icon_path, const QString &m_checked_and_selected_icon_path, int m_radius, int m_icon_size, QColor m_separator_color, int m_min_width, int m_on_blurring_type, QFont m_text_font, QColor m_menu_outline_color, int m_menu_outline_width, int m_blur_radius, QColor m_highlight_color)
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
void Ext_Preview_PluginInterface::call_plugin_save()
{}

void Ext_Preview_PluginInterface::easy_desktop_version(const P_Version &Easy_Desktop_Version, const QString &AKA_name)
{
    (void) Easy_Desktop_Version;
    (void) AKA_name;
}
