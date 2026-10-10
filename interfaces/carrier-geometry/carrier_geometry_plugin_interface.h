#ifndef CARRIER_GEOMETRY_PLUGIN_INTERFACE_H
#define CARRIER_GEOMETRY_PLUGIN_INTERFACE_H

#include "interfaces/easy_desktop_class.h"
#include "carrier_geometry_types.h"

#include <QColor>
#include <QFont>
#include <QPluginLoader>
#include <QString>
#include <QWidget>

class Basic_Widget;
class Carrier_Geometry_Interface;


// 插件元数据要求:
//   {
//       "Ext_Carrier_Geometry_Plugin": ""
//   }
// 注意: 元数据文件里不要写 "MetaData" 外层, Q_PLUGIN_METADATA 会自动加
// 注意: 元数据不要求 "api" 字段, 版本通过 Plugin_Version 字段暴露
//
// 生命周期:
//   1. 宿主加载 .so
//   2. 校验元数据与版本
//   3. 调用 init()
//   4. 若 tick_interval_ms() > 0, 宿主按该间隔调用 on_tick()
//   5. 用户操作时宿主调用 on_widget_* / on_page_changed / on_container_resized
//   6. 用户保存时宿主调用 on_host_save()
//   7. 插件被移除或可载体销毁时宿主调用 RemovePlugin()
//
// 约束:
//   - 插件只能操作当前挂载的可载体, 不能越级到父/子/兄弟载体
//   - 直接子项若是可载体, 也当普通 Basic_Widget 处理
//   - 插件必须在 on_widget_removed() 中清空对该 widget 的所有引用
//   - 插件乱用指针导致崩溃, 由插件自身负责
//
// 实现约定:
//   - 只有 RemovePlugin / Plugin_Name / init 是纯虚函数, 必须实现
//   - 其余接口都有默认空实现, 插件按需 override
//   - 不需要的通知可以不 override, 宿主调用默认实现不会有副作用
/// Easy_Desktop 载体几何插件接口
class Ext_Carrier_Geometry_PluginInterface
{
public:
    /// 扩展名, 宿主用于识别插件类型
    const QString Ext_Name = "Easy_Desktop_Carrier_Geometry";

    /// 扩展规格, 保留
    const QString Ext_Spec = "";

    /// 插件版本, 宿主读取并判断是否满足最低要求
    /// 当前最低要求: 0.0.1
    P_Version Plugin_Version{0, 0, 1};

    /// 是否已初始化, 由宿主维护, 插件不要修改
    bool inited = false;

    /// 插件加载器指针, 由宿主维护, 插件不要修改
    QPluginLoader *your_plugin_loader = nullptr;

    /// 插件路径, 由宿主维护, 插件不要修改
    QString plugin_path = "";

    // ============================================================
    // 生命周期
    // ============================================================

    /// 析构函数
    virtual ~Ext_Carrier_Geometry_PluginInterface();

    /// 移除插件
    /// 插件需要在这里停止所有动画, 释放所有资源, 清空所有缓存
    /// 此函数返回后, 宿主会立即断绝对插件的所有引用
    /// [必须实现]
    virtual void RemovePlugin() = 0;

    /// 插件名称, 用于界面显示
    /// [必须实现]
    virtual QString Plugin_Name() = 0;

    /// 初始化
    /// ptr: 宿主提供的控制接口, 插件保存该指针, 之后所有操作走它
    /// 注意: ptr 的生命周期与当前可载体实例一致
    /// [必须实现]
    virtual void init(Carrier_Geometry_Interface *ptr) = 0;

    /// 清理
    /// 当插件被禁用或可载体即将销毁时调用
    /// 与 RemovePlugin 的区别: clear() 可能被多次调用, RemovePlugin 只调一次
    /// 默认空实现
    virtual void clear();

    // ============================================================
    // 帧循环
    // ============================================================

    /// 返回 tick 间隔, 单位毫秒
    /// 返回 0 表示不需要 tick, 宿主不会启动定时器
    /// 默认返回 0
    virtual int tick_interval_ms() const;

    /// 每次 tick 回调
    /// elapsed_ms: 距离上一次 tick 的实际毫秒数, 至少为 1
    /// 插件应在此实现重力, 平铺动画, 弹性等效果
    /// 默认空实现
    virtual void on_tick(qint64 elapsed_ms);

    // ============================================================
    // 控件通知
    // ============================================================

    /// 当有 Basic_Widget 被添加到当前可载体时调用
    /// widget: 被添加的控件
    /// page: 所在页索引, 从 0 开始
    /// 注意: 如果直接子项本身也是可载体, 例如 Self_Carrier,
    ///       也走这个回调, 插件只能当普通 Basic_Widget 操作
    /// 默认空实现
    virtual void on_widget_added(Basic_Widget *widget, int page);

    /// 当有 Basic_Widget 从当前可载体移除时调用
    /// widget: 被移除的控件, 析构函数入口调用, 对象完整
    /// page: 移除前所在的页
    /// 插件应在此函数中删除对该 widget 的所有引用
    /// 默认空实现, 但插件若有缓存必须 override
    virtual void on_widget_removed(Basic_Widget *widget, int page);

    /// 当 Basic_Widget 所在的页发生变化时调用
    /// old_page: 旧页索引
    /// new_page: 新页索引
    /// 默认空实现
    virtual void on_widget_page_changed(Basic_Widget *widget,
                                        int old_page,
                                        int new_page);

    /// 当 Basic_Widget 的几何信息变化时调用
    /// old_rect: 变化前的几何
    /// new_rect: 变化后的几何
    /// 注意: 插件自己通过接口 set_geometry 也会触发这个回调
    /// 默认空实现
    virtual void on_widget_geometry_changed(Basic_Widget *widget,
                                            const QRect &old_rect,
                                            const QRect &new_rect);

    /// 当 Basic_Widget 的选中状态变化时调用
    /// 默认空实现
    virtual void on_widget_selected_changed(Basic_Widget *widget,
                                            bool selected);

    /// 当 Basic_Widget 的 z-index 变化时调用
    /// 默认空实现
    virtual void on_widget_z_changed(Basic_Widget *widget,
                                     int old_z,
                                     int new_z);

    /// 当 Basic_Widget 被鼠标按下时调用
    /// 只统计左键, 右键不算
    /// 只统计 Basic_Widget 本身被按下, 内部子控件被按下不算
    /// 默认空实现
    virtual void on_widget_pressed(Basic_Widget *widget);

    /// 当 Basic_Widget 被鼠标松开时调用
    /// 与 on_widget_pressed 配对
    /// 如果控件在按下状态下被移除, 宿主会先调用 on_widget_released
    /// 再调用 on_widget_removed
    /// 默认空实现
    virtual void on_widget_released(Basic_Widget *widget);

    // ============================================================
    // 容器通知
    // ============================================================

    /// 当当前页变化时调用
    /// 默认空实现
    virtual void on_page_changed(int old_page, int new_page);

    /// 当可载体尺寸变化时调用
    /// 默认空实现
    virtual void on_container_resized(const QSize &old_size,
                                      const QSize &new_size);

    // ============================================================
    // 持久化
    // ============================================================

    /// 当 Easy_Desktop 执行保存时调用
    /// 无参数, 插件自己决定保存什么, 怎么保存
    /// 插件可以使用 QSettings 保存到自己的路径
    /// 默认空实现
    virtual void on_host_save();

    // ============================================================
    // 设置窗口
    // ============================================================

    /// 打开插件设置界面
    /// 宿主菜单 "几何插件设置" 点击后调用
    /// 窗口的生命周期完全由插件管理
    /// 宿主不参与创建, 显示, 销毁
    /// 插件应在内部处理父窗口, 单例窗口, 保存等逻辑
    /// 默认空实现
    virtual void call_settings_widget();

    // ============================================================
    // 主题与翻译
    // ============================================================

    /// 主题样式更新
    /// 参数与其它插件样式接口一致
    /// 默认空实现
    virtual void update_style(QColor theme_color,
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
                              QColor highlight_color);

    /// 翻译更新通知
    /// 插件在此重新设置自己界面上的文字
    /// 默认空实现
    virtual void Trans_Update();

    /// 提供Easy_Desktop的Loader
    /// loaderNames会为你提供当前Easy_Desktop拥有的loader的QString.
    /// ,seek_loader_sender用于请求loader指针, recive_loader_sender用于获取loader指针.无论怎样都会返回,若没有这个loader,会给nullptr.
    /// 注意:seek_loader_sender只走Send_Data路线,请发送一个QString(这里是全匹配,没有模糊匹配),
    /// recive_loader_sender只走Send_Ptr路线,给出void *,需要自行转化.Easy_Desktop不会负责除这两条线外的其他路线
    virtual void Get_Loader(const QStringList &loaderNames, const P_Sender *seek_loader_sender, const P_Sender *recive_loader_sender);

    ///
    /// \brief easy_desktop_version
    /// 宿主调用, 告知插件当前 Easy_Desktop 的版本信息与 AKA 名称
    /// 插件可通过此回调做兼容性判断
    ///
    virtual void easy_desktop_version(const P_Version &Easy_Desktop_Version, const QString &AKA_name);
};

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(Ext_Carrier_Geometry_PluginInterface,
                    "com.Easy.Desktop.Ext_Carrier_Geometry_PluginInterface")

QT_END_NAMESPACE

#endif // CARRIER_GEOMETRY_PLUGIN_INTERFACE_H
