#ifndef CARRIER_GEOMETRY_TYPES_H
#define CARRIER_GEOMETRY_TYPES_H

#include <QMetaType>
#include <QRect>
#include <QSize>
#include <QString>

/// 视觉变换参数
/// 仅描述视觉层效果, 不改变真实 geometry
/// 真实命中区域仍由 QRect 控制
struct Carrier_Transform
{
    /// 平面旋转角度, 单位度, 顺时针为正
    qreal rotation = 0.0;
    /// 绕 X 轴倾斜角度, 单位度, 上下翻转
    /// 正值表示上边远离观察者, 视觉上上边收窄
    qreal tilt_x = 0.0;
    /// 绕 Y 轴倾斜角度, 单位度, 左右翻转
    /// 正值表示右边远离观察者, 视觉上右边收窄
    qreal tilt_y = 0.0;
    /// X 轴缩放, 1.0 为原始大小
    qreal scale_x = 1.0;
    /// Y 轴缩放, 1.0 为原始大小
    qreal scale_y = 1.0;
    /// 透明度, 0.0 全透明, 1.0 不透明
    qreal opacity = 1.0;
    /// 伪透视强度, 0.0 无透视, 越大透视越强
    qreal perspective = 0.0;
    /// 是否启用变换
    /// false 时宿主会把控件恢复为 identity
    bool enabled = false;
    /// 是否允许宿主在鼠标靠近时抑制本变换
    /// true  宿主会临时把控件变换设为 identity, 保证点击命中
    /// false 宿主不抑制, 变换始终生效, 但可能影响点击命中
    bool allow_suppress = true;
};

/// 能力位
/// 宿主通过 capabilities() 告诉插件支持哪些
enum Carrier_Geometry_Capability
{
    Cap_None          = 0,
    Cap_Move          = 1 << 0,
    Cap_Resize        = 1 << 1,
    Cap_Rotate        = 1 << 2,
    Cap_Scale         = 1 << 3,
    Cap_Opacity       = 1 << 4,
    Cap_Perspective   = 1 << 5,
    Cap_ZIndex        = 1 << 6,
    Cap_PageControl   = 1 << 7,
    Cap_MouseSuppress = 1 << 8,
    Cap_TakeInOut     = 1 << 9,
    Cap_SendSignal    = 1 << 10,
    Cap_PressState    = 1 << 11
};

/// 单个控件的描述信息
struct Carrier_Widget_Info
{
    /// 控件类名, 例如 "My_Clock"
    QString class_name;
    /// 所在页, 从 0 开始
    int page = -1;
    /// 所属可载体 id
    int owner_carrier_id = -1;
    /// 是否是可载体
    /// 例如 Self_Carrier 会是 true
    /// 插件仍只能当普通 Basic_Widget 操作
    bool is_carrier = false;
    /// 是否在载体内部
    bool in_carrier = false;
    /// 是否被选中
    bool selected = false;
    /// 是否可见
    bool visible = false;
    /// 是否被鼠标按下
    bool pressed = false;
    /// 真实几何
    QRect geometry;
    /// 内容尺寸, 不含关闭按钮外扩
    QSize content_size;
};

Q_DECLARE_METATYPE(Carrier_Transform)

#endif // CARRIER_GEOMETRY_TYPES_H
