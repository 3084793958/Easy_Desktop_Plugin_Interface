#ifndef CARRIER_GEOMETRY_INTERFACE_H
#define CARRIER_GEOMETRY_INTERFACE_H

#include "carrier_geometry_types.h"

#include <QList>
#include <QPoint>
#include <QRect>
#include <QVariant>
#include <QWidget>

class Basic_Widget;

/// 宿主控制接口
/// 插件通过这个接口操作当前可载体
/// 插件不能通过这个接口访问父载体, 兄弟载体, 子载体
/// 所有指针参数都是 Basic_Widget *, 由宿主保证生命周期
/// 插件若自行保存裸指针, 必须在 on_widget_removed() 中清除
class Carrier_Geometry_Interface
{
public:
    virtual ~Carrier_Geometry_Interface();

    // ============================================================
    // 容器信息
    // ============================================================

    /// 当前可载体的唯一 id
    virtual int carrier_id() const = 0;

    /// 当前可载体的容器控件
    /// 插件可用于坐标换算, 但不应对其 setParent 或 delete
    virtual QWidget *container_widget() const = 0;

    /// 当前可载体的矩形区域
    virtual QRect container_rect() const = 0;

    // ============================================================
    // 页管理
    // ============================================================

    /// 页总数
    virtual int page_count() const = 0;

    /// 当前页索引
    virtual int current_page() const = 0;

    /// 设置当前页
    /// 返回是否成功
    virtual bool set_current_page(int page) = 0;

    /// 列出指定页的所有直接子 Basic_Widget
    /// 如果子项本身是可载体, 例如 Self_Carrier, 也当普通 Basic_Widget 返回
    /// 不递归
    virtual QList<Basic_Widget *> list_widgets(int page) = 0;

    /// 列出所有页的直接子 Basic_Widget
    /// 不递归
    virtual QList<Basic_Widget *> list_all_widgets() = 0;

    /// 查询某个 Basic_Widget 在哪一页
    /// 返回 -1 表示不属于当前可载体
    virtual int widget_page(Basic_Widget *widget) = 0;

    // ============================================================
    // 控件信息
    // ============================================================

    /// 查询某个 Basic_Widget 的信息
    /// out_info 不可为 nullptr
    virtual bool get_widget_info(Basic_Widget *widget,
                                 Carrier_Widget_Info *out_info) = 0;

    /// 查询某个 Basic_Widget 是否被鼠标按下
    /// 只统计左键按下, 右键不算
    /// 只统计 Basic_Widget 本身被按下, 内部子控件被按下不算
    /// 返回 false 表示未按下或该 widget 不属于当前可载体
    virtual bool is_widget_pressed(Basic_Widget *widget) = 0;

    /// 查询当前是否有任何控件被鼠标按下
    virtual bool any_widget_pressed() const = 0;

    /// 列出当前所有被鼠标按下的控件
    /// 只包含当前页的控件
    virtual QList<Basic_Widget *> pressed_widgets() = 0;

    // ============================================================
    // 几何操作
    // ============================================================

    /// 获取几何信息
    virtual bool get_geometry(Basic_Widget *widget, QRect *out_rect) = 0;

    /// 设置几何信息
    /// 会触发 on_widget_geometry_changed 回调
    virtual bool set_geometry(Basic_Widget *widget, const QRect &rect) = 0;

    /// 相对移动
    /// 等价于 set_geometry(widget, widget->geometry().translated(delta))
    virtual bool move_by(Basic_Widget *widget, const QPoint &delta) = 0;

    // ============================================================
    // 视觉变换
    // ============================================================

    /// 设置视觉变换
    /// 仅影响渲染, 不影响命中
    /// 宿主会在鼠标靠近时临时把该控件的变换设为 identity
    /// 保证点击命中正确
    virtual bool set_transform(Basic_Widget *widget,
                               const Carrier_Transform &transform) = 0;

    /// 获取视觉变换
    virtual bool get_transform(Basic_Widget *widget,
                               Carrier_Transform *out_transform) = 0;

    // ============================================================
    // 可见性与层级
    // ============================================================

    /// 设置可见性
    virtual bool set_visible(Basic_Widget *widget, bool visible) = 0;

    /// 设置选中状态
    /// 会触发 on_widget_selected_changed 回调
    virtual bool set_selected(Basic_Widget *widget, bool selected) = 0;

    /// 查询选中状态
    virtual bool is_selected(Basic_Widget *widget) = 0;

    /// 设置 z-index
    /// 宿主会按同父兄弟的 z-index 排序, 然后依次 raise()
    /// 会触发 on_widget_z_changed 回调
    virtual bool set_z_index(Basic_Widget *widget, int z) = 0;

    /// 获取 z-index
    virtual int get_z_index(Basic_Widget *widget) = 0;

    // ============================================================
    // 信号与载体
    // ============================================================

    /// 发送信号给 Basic_Widget
    /// signal 取值参考 select_signal.h 中的 Signal 枚举
    /// 会走 Basic_Widget::dispatch_signal
    virtual bool send_signal(Basic_Widget *widget,
                             int signal,
                             const QVariant &data) = 0;

    /// 拖入载体
    /// global_pos: 鼠标全局坐标, 用于计算落点
    /// 会走 Container::take_in
    virtual bool take_in(Basic_Widget *widget, const QPoint &global_pos) = 0;

    /// 拖出载体
    /// 会走 Container::take_out
    virtual bool take_out(Basic_Widget *widget) = 0;

    // ============================================================
    // 鼠标与能力
    // ============================================================

    /// 获取当前鼠标全局位置
    virtual QPoint mouse_global_pos() const = 0;

    /// 鼠标是否在可载体内部
    virtual bool mouse_in_container() const = 0;

    /// 获取宿主能力位
    virtual quint64 capabilities() const = 0;
};

#endif // CARRIER_GEOMETRY_INTERFACE_H
