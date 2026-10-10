// Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
// SPDX-FileCopyrightText: 2018 - 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef PLUGINSITEMINTERFACE_V_2_0_0_H
#define PLUGINSITEMINTERFACE_V_2_0_0_H

#include "pluginproxyinterface_v2.0.0.h"

#include <DGuiApplicationHelper>

#include <QIcon>
#include <QtCore>

#include "interfaces/easy_desktop_class.h"

class QMenu;

DGUI_USE_NAMESPACE

// 任务栏的部件位置
enum class DockPart {
    QuickShow = 0,    // 快捷插件显示区域
    QuickPanel,       // 快捷面板区域
    SystemPanel,      // 系统插件显示区域
    DCCSetting        // 显示在控制中心个性化设置的图标
};

enum PluginFlag {
    Type_NoneFlag = 0x1,                 // 插件类型-没有任何的属性，不在任何地方显示
    Type_Common = 0x2,                   // 插件类型-快捷插件区
    Type_Tool = 0x4,                     // 插件类型-工具插件，例如回收站
    Type_System = 0x8,                   // 插件类型-系统插件，例如关机插件
    Type_Tray = 0x10,                    // 插件类型-托盘区，例如U盘插件
    Type_Fixed = 0x20,                   // 插件类型-固定区域,例如多任务视图和显示桌面

    Quick_Single = 0x40,                 // 当插件类型为Common时,快捷插件区域只有一列的那种插件
    Quick_Multi = 0x80,                  // 当插件类型为Common时,快捷插件区占两列的那种插件
    Quick_Full = 0x100,                  // 当插件类型为Common时,快捷插件区占用4列的那种插件，例如声音、亮度设置和音乐等

    Attribute_CanDrag = 0x200,           // 插件属性-是否支持拖动
    Attribute_CanInsert = 0x400,         // 插件属性-是否支持在其前面插入其他的插件，普通的快捷插件是支持的
    Attribute_CanSetting = 0x800,        // 插件属性-是否可以在控制中心设置显示或隐藏
    Attribute_ForceDock = 0x1000,        // 插件属性-强制显示在任务栏上

    FlagMask = 0xffffffff                // 掩码
};

Q_DECLARE_FLAGS(PluginFlags, PluginFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(PluginFlags)

// 快捷面板详情页面的itemWidget对应的itemKey
#define QUICK_ITEM_KEY "quick_item_key"
///
/// \brief The PluginsItemInterface class
/// the dock plugins item interface, all dock plugins should
/// inheirt this class and override all pure virtual function.
///

class PluginsItemInterface_V_2_0_0
{
public:
    enum PluginType {
        Normal,
        Fixed
    };

    /**
    * @brief Plugin size policy
    */
    enum PluginSizePolicy {
        System = 1 << 0, // Follow the system
        Custom = 1 << 1  // The custom
    };

    enum PluginMode {
        Deactive = 0,
        Active,
        Disabled
    };

    ///
    /// \brief ~PluginsItemInterface
    /// DON'T try to delete m_proxyInter.
    ///
    virtual ~PluginsItemInterface_V_2_0_0();

    ///
    /// \brief pluginName
    /// tell dock the unique plugin id
    /// \return
    ///
    virtual const QString pluginName() const = 0;
    virtual const QString pluginDisplayName() const;

    ///
    /// \brief init
    /// init your plugins, you need to save proxyInter to m_proxyInter
    /// member variable. but you shouldn't free this pointer.
    /// \param proxyInter
    /// DON'T try to delete this pointer.
    ///
    virtual void init(PluginProxyInterface_V_2_0_0 *proxyInter) = 0;
    ///
    /// \brief itemWidget
    /// your plugin item widget, each item should have a unique key.
    /// \param itemKey
    /// your widget' unqiue key.
    /// \return
    ///
    virtual QWidget *itemWidget(const QString &itemKey) = 0;

    ///
    /// \brief itemTipsWidget
    /// override this function if your item want to have a tips.
    /// the tips will shown when user hover your item.
    /// nullptr will be ignored.
    /// \param itemKey
    /// \return
    ///
    virtual QWidget *itemTipsWidget(const QString &itemKey);
    ///
    /// \brief itemPopupApplet
    /// override this function if your item wants to have an popup applet.
    /// the popup applet will shown when user click your item.
    ///
    /// Tips:
    /// dock should receive mouse press/release event to check user mouse operate,
    /// if your item filter mouse event, this function will not be called.
    /// so if you override mouse event and want to use popup applet, you
    /// should pass event to your parent use QWidget::someEvent(e);
    /// \param itemKey
    /// \return
    ///
    virtual QWidget *itemPopupApplet(const QString &itemKey);
    ///
    /// \brief itemCommand
    /// execute spec command when user clicked your item.
    /// ensure your command do not get user input.
    ///
    /// empty string will be ignored.
    /// \param itemKey
    /// \return
    ///
    virtual const QString itemCommand(const QString &itemKey);

    ///
    /// \brief itemContextMenu
    /// context menu is shown when RequestPopupMenu called.
    /// \param itemKey
    /// \return
    ///
    virtual const QString itemContextMenu(const QString &itemKey);
    ///
    /// \brief invokedMenuItem
    /// call if context menu item is clicked
    /// \param itemKey
    /// \param itemId
    /// menu item id
    /// \param checked
    ///
    virtual void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked);

    ///
    /// \brief itemSortKey
    /// tell dock where your item wants to put on.
    ///
    /// this index is start from 1 and
    /// 0 for left side
    /// -1 for right side
    /// \param itemKey
    /// \return
    ///
    virtual int itemSortKey(const QString &itemKey);
    ///
    /// \brief setSortKey
    /// save your item new position
    /// sort key will be changed when plugins order
    /// changed(by user drag-drop)
    /// \param itemKey
    /// \param order
    ///
    virtual void setSortKey(const QString &itemKey, const int order);

    ///
    /// \brief itemAllowContainer
    /// tell dock is your item allow to move into container
    ///
    /// if your item placed into container, popup tips and popup
    /// applet will be disabled.
    /// \param itemKey
    /// \return
    ///
    virtual bool itemAllowContainer(const QString &itemKey);
    ///
    /// \brief itemIsInContainer
    /// tell dock your item is in container, this function
    /// called at item init and if your item enable container.
    /// \param itemKey
    /// \return
    ///
    virtual bool itemIsInContainer(const QString &itemKey);
    ///
    /// \brief setItemIsInContainer
    /// save your item new state.
    /// this function called when user drag out your item from
    /// container or user drop item into container(if your item
    /// allow drop into container).
    /// \param itemKey
    /// \param container
    ///
    virtual void setItemIsInContainer(const QString &itemKey, const bool container);

    virtual bool pluginIsAllowDisable();
    virtual bool pluginIsDisable();
    virtual void pluginStateSwitched();

    ///
    /// \brief displayModeChanged
    /// override this function to receive display mode changed signal
    /// \param displayMode
    ///
    virtual void displayModeChanged(const Dock::DisplayMode displayMode);
    ///
    /// \brief positionChanged
    /// override this function to receive dock position changed signal
    /// \param position
    ///
    virtual void positionChanged(const Dock::Position position);

    ///
    /// \brief refreshIcon
    /// refresh item icon, its triggered when system icon theme changed.
    /// \param itemKey
    /// item key
    ///
    virtual void refreshIcon(const QString &itemKey);

    ///
    /// \brief displayMode
    /// get current dock display mode
    /// \return
    ///
    inline Dock::DisplayMode displayMode() const;

    ///
    /// \brief position
    /// get current dock position
    /// \return
    ///
    inline Dock::Position position() const;

    ///
    /// \brief settingsChanged
    /// override this function to receive plugin settings changed signal(DeepinSync)
    ///
    virtual void pluginSettingsChanged();

    ///
    /// \brief type
    /// default plugin add dock right,fixed plugin add to dock fixed area
    ///
    virtual PluginType type();

    ///
    /// \brief plugin size policy
    /// default plugin size policy
    ///
    virtual PluginSizePolicy pluginSizePolicy() const;

    ///
    /// the plugin status
    ///
    ///
    virtual PluginMode status() const;

    ///
    /// return the detail value, it will display in the center
    ///
    ///
    virtual QString description() const;

    ///
    /// the icon for the plugin
    /// themeType {0:UnknownType 1:LightType 2:DarkType}
    ///
    virtual QIcon icon(const DockPart &dockPart, DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType());

    ///
    /// \brief m_proxyInter
    /// return the falgs for current plugin
    ///
    virtual PluginFlags flags() const;

    ///
    /// \brief m_proxyInter
    ///
    ///
    virtual bool eventHandler(QEvent *event);




    //对于"api": "2.0.0"的解决方案


    //插件需要在json中说明自己支持Ext_Plugin
    //格式:   "Ext_Plugin": ""
    //ADD
    const QString Ext_Name = "Easy_Desktop";
    const QString Ext_Spec = "";
    //ADD

    //for Easy_Desktop
    P_Version Plugin_Version{0, 0, 3};//不使用const,用于欺骗Easy_Desktop

    //最低版本号:0.0.1
    //for Easy_Desktop

    //for Easy_Desktop 0.0.1
    virtual bool pluginIsAllowUnload();
    virtual void pluginUnload();
    //
    enum class Carrier_Type
    {
        Unknown,
        Plugin_Item,
        Plugin_Popup,
        Plugin_Tips
    };
    virtual void pluginGetSender(P_Sender * const update_sender, P_Sender * const send_data_sender);
    virtual QPair<int, int> pluginSetCarrierSpacing(Carrier_Type carrier_type, bool *isValid);
    virtual void pluginGetCarrierSpacing(Carrier_Type carrier_type, int distance_width, int distance_height);
    virtual QPair<int, int> pluginSetCarrierOffset(Carrier_Type carrier_type, bool *isValid);
    virtual void pluginGetCarrierOffset(Carrier_Type carrier_type, int delta_x, int delta_y);
    virtual QColor pluginSetCarrierColor(Carrier_Type carrier_type, bool *isValid);
    virtual void pluginGetCarrierColor(Carrier_Type carrier_type, QColor background_color);
    virtual int pluginSetCarrierRadius(Carrier_Type carrier_type, bool *isValid);
    virtual void pluginGetCarrierRadius(Carrier_Type carrier_type, int radius);
    virtual QSize pluginSetCarrierSize(Carrier_Type carrier_type, bool *isValid);
    virtual void pluginGetCarrierQMenu(Carrier_Type carrier_type, QMenu *menu, P_Sender * const action_sender);
    virtual QPair<QMenu *, P_Sender * const> pluginAddToCarrierQMenu(Carrier_Type carrier_type, bool *isValid);
    virtual QSize pluginSetWidgetSize(Carrier_Type carrier_type, bool *isValid);
    virtual QPoint pluginSetCarrierPos(Carrier_Type carrier_type, QPoint item_pos, QSize item_size, bool *isValid);
    virtual int pluginSetCarrierPage(Carrier_Type carrier_type, int total_page, bool *isValid);
    virtual void pluginGetIsMouseInPluginCarrier(Carrier_Type carrier_type, bool result);
    virtual void pluginGetShowCarrierCloseButton(Carrier_Type carrier_type, bool result);
    virtual bool pluginSetShowCarrierCloseButton(Carrier_Type carrier_type, bool *isValid);
    //for Easy_Desktop 0.0.1
    //不会修改PluginProxyInterface,无法控制插件怎么调用,只能控制Easy_Desktop怎么调用,至于插件主动更新,用P_Sender

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
    /// \brief call_plugin_save
    /// 通知保存
    ///
    virtual void call_plugin_save();

    ///
    /// \brief init_V_0_0_3
    /// loaderNames会为你提供当前Easy_Desktop拥有的loader的QString.
    /// ,seek_loader_sender用于请求loader指针, recive_loader_sender用于获取loader指针.无论怎样都会返回,若没有这个loader,会给nullptr.
    /// 注意:seek_loader_sender只走Send_Data路线,请发送一个QString(这里是全匹配,没有模糊匹配),
    /// recive_loader_sender只走Send_Ptr路线,给出void *,需要自行转化.Easy_Desktop不会负责除这两条线外的其他路线
    /// \param loaderNames
    /// \param seek_loader_sender
    /// \param recive_loader_sender
    ///
    virtual void init_V_0_0_3(const QStringList &loaderNames, const P_Sender *seek_loader_sender, const P_Sender *recive_loader_sender);

    ///
    /// \brief easy_desktop_version
    /// 宿主调用, 告知插件当前 Easy_Desktop 的版本信息与 AKA 名称
    /// 插件可通过此回调做兼容性判断
    ///
    virtual void easy_desktop_version(const P_Version &Easy_Desktop_Version, const QString &AKA_name);
    //V_0.0.3

protected:
    ///
    /// \brief m_proxyInter
    /// NEVER delete this object.
    ///
    PluginProxyInterface_V_2_0_0 *m_proxyInter = nullptr;
};

QT_BEGIN_NAMESPACE

#define ModuleInterface_iid "com.deepin.dock.PluginsItemInterface_2_0_0"

Q_DECLARE_INTERFACE(PluginsItemInterface_V_2_0_0, ModuleInterface_iid)

#undef ModuleInterface_iid

QT_END_NAMESPACE


#endif // PLUGINSITEMINTERFACE_H
