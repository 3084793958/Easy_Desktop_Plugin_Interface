#include "pluginsiteminterface_v2.0.0.h"

#include <QFont>

PluginsItemInterface_V_2_0_0::~PluginsItemInterface_V_2_0_0()
{}
const QString PluginsItemInterface_V_2_0_0::pluginDisplayName() const
{
    return QString();
}
QWidget *PluginsItemInterface_V_2_0_0::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return nullptr;
}
QWidget *PluginsItemInterface_V_2_0_0::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return nullptr;
}
const QString PluginsItemInterface_V_2_0_0::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return QString();
}
const QString PluginsItemInterface_V_2_0_0::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return QString();
}
void PluginsItemInterface_V_2_0_0::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey);
    Q_UNUSED(menuId);
    Q_UNUSED(checked);
}
int PluginsItemInterface_V_2_0_0::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return 1;
}
void PluginsItemInterface_V_2_0_0::setSortKey(const QString &itemKey, const int order)
{
    Q_UNUSED(itemKey);
    Q_UNUSED(order);
}
bool PluginsItemInterface_V_2_0_0::itemAllowContainer(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return false;
}
bool PluginsItemInterface_V_2_0_0::itemIsInContainer(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return false;
}
void PluginsItemInterface_V_2_0_0::setItemIsInContainer(const QString &itemKey, const bool container)
{
    Q_UNUSED(itemKey);
    Q_UNUSED(container);
}
bool PluginsItemInterface_V_2_0_0::pluginIsAllowDisable()
{
    return false;
}
bool PluginsItemInterface_V_2_0_0::pluginIsDisable()
{
    return false;
}
void PluginsItemInterface_V_2_0_0::pluginStateSwitched()
{}
void PluginsItemInterface_V_2_0_0::displayModeChanged(const Dock::DisplayMode displayMode)
{
    Q_UNUSED(displayMode);
}
void PluginsItemInterface_V_2_0_0::positionChanged(const Dock::Position position)
{
    Q_UNUSED(position);
}
void PluginsItemInterface_V_2_0_0::refreshIcon(const QString &itemKey)
{
    Q_UNUSED(itemKey);
}
Dock::DisplayMode PluginsItemInterface_V_2_0_0::displayMode() const
{
    return qApp->property(PROP_DISPLAY_MODE).value<Dock::DisplayMode>();
}
Dock::Position PluginsItemInterface_V_2_0_0::position() const
{
    return qApp->property(PROP_POSITION).value<Dock::Position>();
}
void PluginsItemInterface_V_2_0_0::pluginSettingsChanged()
{}
PluginsItemInterface_V_2_0_0::PluginType PluginsItemInterface_V_2_0_0::type()
{
    return Normal;
}
PluginsItemInterface_V_2_0_0::PluginSizePolicy PluginsItemInterface_V_2_0_0::pluginSizePolicy() const
{
    return System;
}
PluginsItemInterface_V_2_0_0::PluginMode PluginsItemInterface_V_2_0_0::status() const
{
    return PluginMode::Deactive;
}
QString PluginsItemInterface_V_2_0_0::description() const
{
    return QString();
}
QIcon PluginsItemInterface_V_2_0_0::icon(const DockPart &dockPart, DGuiApplicationHelper::ColorType themeType)
{
    (void)dockPart;
    (void) themeType;
    return QIcon();
}
PluginFlags PluginsItemInterface_V_2_0_0::flags() const
{
    return PluginFlag::Type_Common | PluginFlag::Quick_Single | PluginFlag::Attribute_CanDrag | PluginFlag::Attribute_CanInsert | PluginFlag::Attribute_CanSetting;
}
bool PluginsItemInterface_V_2_0_0::eventHandler(QEvent *event)
{
    (void)event; return false;
}
bool PluginsItemInterface_V_2_0_0::pluginIsAllowUnload()
{
    return false;
}
void PluginsItemInterface_V_2_0_0::pluginUnload()
{}
void PluginsItemInterface_V_2_0_0::pluginGetSender(P_Sender * const update_sender, P_Sender * const send_data_sender)
{
    (void) update_sender;
    (void) send_data_sender;
}
QPair<int, int> PluginsItemInterface_V_2_0_0::pluginSetCarrierSpacing(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, bool *isValid)
{
    (void) carrier_type;
    *isValid = false;
    return qMakePair(0, 0);
}
void PluginsItemInterface_V_2_0_0::pluginGetCarrierSpacing(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, int distance_width, int distance_height)
{
    (void) carrier_type;
    (void) distance_width;
    (void) distance_height;
}
QPair<int, int> PluginsItemInterface_V_2_0_0::pluginSetCarrierOffset(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, bool *isValid)
{
    (void) carrier_type;
    *isValid = false;
    return qMakePair(0, 0);
}
void PluginsItemInterface_V_2_0_0::pluginGetCarrierOffset(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, int delta_x, int delta_y)
{
    (void) carrier_type;
    (void) delta_x;
    (void) delta_y;
}
QColor PluginsItemInterface_V_2_0_0::pluginSetCarrierColor(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, bool *isValid)
{
    (void) carrier_type;
    *isValid = false;
    return QColor();
}
void PluginsItemInterface_V_2_0_0::pluginGetCarrierColor(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, QColor background_color)
{
    (void) carrier_type;
    (void) background_color;
}
int PluginsItemInterface_V_2_0_0::pluginSetCarrierRadius(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, bool *isValid)
{
    (void) carrier_type;
    *isValid = false;
    return 0;
}
void PluginsItemInterface_V_2_0_0::pluginGetCarrierRadius(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, int radius)
{
    (void) carrier_type;
    (void) radius;
}
QSize PluginsItemInterface_V_2_0_0::pluginSetCarrierSize(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, bool *isValid)
{
    (void) carrier_type;
    *isValid = false;
    return QSize();
}
void PluginsItemInterface_V_2_0_0::pluginGetCarrierQMenu(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, QMenu *menu, P_Sender * const action_sender)
{
    (void) carrier_type;
    (void) menu;
    (void) action_sender;
}
QPair<QMenu *, P_Sender * const> PluginsItemInterface_V_2_0_0::pluginAddToCarrierQMenu(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, bool *isValid)
{
    (void) carrier_type;
    *isValid = false;
    return QPair<QMenu *, P_Sender * const>(nullptr, nullptr);
}
QSize PluginsItemInterface_V_2_0_0::pluginSetWidgetSize(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, bool *isValid)
{
    (void) carrier_type;
    *isValid = false;
    return QSize();
}
QPoint PluginsItemInterface_V_2_0_0::pluginSetCarrierPos(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, QPoint item_pos, QSize item_size, bool *isValid)
{
    (void) carrier_type;
    (void) item_pos;
    (void) item_size;
    *isValid = false;
    return QPoint();
}
int PluginsItemInterface_V_2_0_0::pluginSetCarrierPage(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, int total_page, bool *isValid)
{
    (void) carrier_type;
    (void) total_page;
    *isValid = false;
    return 0;
}
void PluginsItemInterface_V_2_0_0::pluginGetIsMouseInPluginCarrier(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, bool result)//用于给music-island打补丁
{
    (void) carrier_type;
    (void) result;
}
void PluginsItemInterface_V_2_0_0::pluginGetShowCarrierCloseButton(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, bool result)
{
    (void) carrier_type;
    (void) result;
}
bool PluginsItemInterface_V_2_0_0::pluginSetShowCarrierCloseButton(PluginsItemInterface_V_2_0_0::Carrier_Type carrier_type, bool *isValid)
{
    (void) carrier_type;
    *isValid = false;
    return false;
}
void PluginsItemInterface_V_2_0_0::Trans_Update()
{}
void PluginsItemInterface_V_2_0_0::update_style_V2(QColor m_theme_color, QColor m_theme_background_color, QColor m_theme_text_color, QColor m_select_text_color, QColor m_disabled_text_color, const QString &m_checked_icon_path, const QString &m_checked_and_selected_icon_path, int m_radius, int m_icon_size, QColor m_separator_color, int m_min_width, int m_on_blurring_type, QFont m_text_font, QColor m_menu_outline_color, int m_menu_outline_width, int m_blur_radius, QColor m_highlight_color)
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
void PluginsItemInterface_V_2_0_0::call_plugin_save()
{}
void PluginsItemInterface_V_2_0_0::init_V_0_0_3(const QStringList &loaderNames, const P_Sender *seek_loader_sender, const P_Sender *recive_loader_sender)
{
    (void) loaderNames;
    (void) seek_loader_sender;
    (void) recive_loader_sender;
}

void PluginsItemInterface_V_2_0_0::easy_desktop_version(const P_Version &Easy_Desktop_Version, const QString &AKA_name)
{
    (void) Easy_Desktop_Version;
    (void) AKA_name;
}
