#include "carrier_geometry_plugin_interface.h"

Ext_Carrier_Geometry_PluginInterface::~Ext_Carrier_Geometry_PluginInterface()
{}
void Ext_Carrier_Geometry_PluginInterface::clear()
{}
int Ext_Carrier_Geometry_PluginInterface::tick_interval_ms() const
{
    return 0;
}
void Ext_Carrier_Geometry_PluginInterface::on_tick(qint64 elapsed_ms)
{
    (void) elapsed_ms;
}
void Ext_Carrier_Geometry_PluginInterface::on_widget_added(Basic_Widget *widget, int page)
{
    (void) widget;
    (void) page;
}
void Ext_Carrier_Geometry_PluginInterface::on_widget_removed(Basic_Widget *widget, int page)
{
    (void) widget;
    (void) page;
}
void Ext_Carrier_Geometry_PluginInterface::on_widget_page_changed(Basic_Widget *widget,
                                                                   int old_page,
                                                                   int new_page)
{
    (void) widget;
    (void) old_page;
    (void) new_page;
}
void Ext_Carrier_Geometry_PluginInterface::on_widget_geometry_changed(Basic_Widget *widget,
                                                                       const QRect &old_rect,
                                                                       const QRect &new_rect)
{
    (void) widget;
    (void) old_rect;
    (void) new_rect;
}
void Ext_Carrier_Geometry_PluginInterface::on_widget_selected_changed(Basic_Widget *widget,
                                                                       bool selected)
{
    (void) widget;
    (void) selected;
}
void Ext_Carrier_Geometry_PluginInterface::on_widget_z_changed(Basic_Widget *widget,
                                                                int old_z,
                                                                int new_z)
{
    (void) widget;
    (void) old_z;
    (void) new_z;
}
void Ext_Carrier_Geometry_PluginInterface::on_widget_pressed(Basic_Widget *widget)
{
    (void) widget;
}
void Ext_Carrier_Geometry_PluginInterface::on_widget_released(Basic_Widget *widget)
{
    (void) widget;
}
void Ext_Carrier_Geometry_PluginInterface::on_page_changed(int old_page, int new_page)
{
    (void) old_page;
    (void) new_page;
}
void Ext_Carrier_Geometry_PluginInterface::on_container_resized(const QSize &old_size,
                                                                 const QSize &new_size)
{
    (void) old_size;
    (void) new_size;
}
void Ext_Carrier_Geometry_PluginInterface::on_host_save()
{}
void Ext_Carrier_Geometry_PluginInterface::call_settings_widget()
{}
void Ext_Carrier_Geometry_PluginInterface::update_style(QColor theme_color,
                                                         QColor theme_background_color,
                                                         QColor theme_text_color,
                                                         QColor select_text_color,
                                                         QColor disabled_text_color,
                                                         const QString &checked_icon_path,
                                                         const QString &checked_and_selected_icon_path,
                                                         int radius,
                                                         int icon_size,
                                                         QColor separator_color,
                                                         int min_width,
                                                         int on_blurring_type,
                                                         QFont text_font,
                                                         QColor menu_outline_color,
                                                         int menu_outline_width,
                                                         int blur_radius,
                                                         QColor highlight_color)
{
    (void) theme_color;
    (void) theme_background_color;
    (void) theme_text_color;
    (void) select_text_color;
    (void) disabled_text_color;
    (void) checked_icon_path;
    (void) checked_and_selected_icon_path;
    (void) radius;
    (void) icon_size;
    (void) separator_color;
    (void) min_width;
    (void) on_blurring_type;
    (void) text_font;
    (void) menu_outline_color;
    (void) menu_outline_width;
    (void) blur_radius;
    (void) highlight_color;
}
void Ext_Carrier_Geometry_PluginInterface::Trans_Update()
{}

void Ext_Carrier_Geometry_PluginInterface::Get_Loader(const QStringList &loaderNames, const P_Sender *seek_loader_sender, const P_Sender *recive_loader_sender)
{
    (void) loaderNames;
    (void) seek_loader_sender;
    (void) recive_loader_sender;
}

void Ext_Carrier_Geometry_PluginInterface::easy_desktop_version(const P_Version &Easy_Desktop_Version, const QString &AKA_name)
{
    (void) Easy_Desktop_Version;
    (void) AKA_name;
}
