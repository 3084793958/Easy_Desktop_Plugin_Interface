# Easy_Desktop 载体几何插件开发文档

本文档面向前来开发 Easy_Desktop 载体几何插件的开发者。内容包括接口说明、开发流程、常见坑与注意事项。

---

## 一、概述

载体几何插件（Carrier Geometry Plugin）是 Easy_Desktop 提供的一类扩展插件，运行在可载体（Container）内部，用于对可载体内的 `Basic_Widget` 施加动画、几何变换、布局控制、视觉效果等。

插件与宿主之间通过两套接口通信：

- `Ext_Carrier_Geometry_PluginInterface`：插件实现，宿主调用。
- `Carrier_Geometry_Interface`：宿主实现，插件调用。

插件通过 `QPluginLoader` 动态加载，通过 `Q_DECLARE_INTERFACE` 做接口识别。

Easy_Desktop 提供三个可载体：

- `Desktop_Main`（桌面主载体）
- `My_Process_Carrier`（进程/文件按钮载体）
- `Self_Carrier`（自载体）

每个可载体实例只能挂载一个几何插件。

---

## 二、设计原则

### 2.1 单向所有权

宿主是 `Basic_Widget` 的唯一所有者，生命周期由 Qt 父子树管理。

插件只能借用 `Basic_Widget *`，不能 `delete`，不能 `setParent` 到非宿主期望的容器。插件对控件的所有修改必须通过 `Carrier_Geometry_Interface`。

### 2.2 接口隔离

插件不 include 宿主内部头文件，如 `basic_widget.h`、`desktop_main.h`。插件头文件里 `Basic_Widget` 是前置声明的不完整类型。

插件工程只依赖 `interfaces/carrier-geometry/` 和 `interfaces/easy_desktop_class.h`。

### 2.3 生命周期显式

插件必须在 `on_widget_removed` 里清空对该控件的所有引用。控件析构函数会调用宿主 `unregister_widget`，宿主再调用插件 `on_widget_removed`，此时对象完整，插件可以安全访问。

### 2.4 效果与命中分离

视觉变换（旋转、倾斜、缩放、透明度、伪透视）只影响渲染，不影响命中。宿主在鼠标靠近时会把控件的变换临时重置为 identity，保证点击命中正确。

### 2.5 帧循环统一

插件不自己 `new QTimer` 做动画。所有周期性任务通过 `tick_interval_ms()` 和 `on_tick()` 由宿主统一调度。

### 2.6 嵌套不递归

插件只能操作当前挂载的可载体。当前页的直接子项如果是另一个可载体（`Self_Carrier` / `My_Process_Carrier`），插件只能当普通 `Basic_Widget` 处理，不能进入它内部。

### 2.7 保存分离

宿主只保存插件 `.so` 路径。插件内部状态由插件自己保存，宿主通过 `on_host_save()` 通知。插件通常用 `QStandardPaths::AppDataLocation` 或固定的 `~/.local/lib/easy_desktop_geometry_plugins/` 存到自己的路径。

### 2.8 崩溃自负

插件可以拿裸指针做黑魔法，比如 `reinterpret_cast`、直接访问宿主内部。宿主不拦，但崩了是插件自己的问题。

---

## 三、加载与元数据

### 3.1 元数据

插件 `.json` 文件：

```json
{
    "Ext_Carrier_Geometry_Plugin": ""
}
```

注意事项：

1. 不要写 `MetaData` 外层，`Q_PLUGIN_METADATA` 会自动加。
2. 不要求 `api` 字段，版本通过 `Plugin_Version` 字段暴露。
3. 元数据缺失时宿主会询问用户是否强制加载。

### 3.2 版本

插件类里：

```cpp
P_Version Plugin_Version{0, 0, 1};
```

宿主检查 `Plugin_Version >= P_Version{0, 0, 1}`，不满足则拒绝加载。

### 3.3 IID

插件类里：

```cpp
Q_PLUGIN_METADATA(IID "com.Easy.Desktop.Ext_Carrier_Geometry_PluginInterface"
                  FILE "xxx.json")
Q_INTERFACES(Ext_Carrier_Geometry_PluginInterface)
```

IID 必须与宿主头文件里的 `Q_DECLARE_INTERFACE` 字符串一致，否则 `qobject_cast` 失败。

---

## 四、接口说明

### 4.1 必须实现的三个接口

以下三个方法是纯虚函数，插件必须实现，否则链接失败：

- `void RemovePlugin()`：插件卸载时由宿主调用，释放所有资源。
- `QString Plugin_Name()`：返回插件名称。
- `void init(Carrier_Geometry_Interface *ptr)`：宿主绑定插件时调用，保存 `ptr`。

### 4.2 按需 override 的接口

以下方法都有默认空实现，插件按需 override：

- `void clear()`
- `int tick_interval_ms() const`
- `void on_tick(qint64 elapsed_ms)`
- `void on_widget_added(Basic_Widget *widget, int page)`
- `void on_widget_removed(Basic_Widget *widget, int page)`
- `void on_widget_page_changed(Basic_Widget *widget, int old_page, int new_page)`
- `void on_widget_geometry_changed(Basic_Widget *widget, const QRect &old_rect, const QRect &new_rect)`
- `void on_widget_selected_changed(Basic_Widget *widget, bool selected)`
- `void on_widget_z_changed(Basic_Widget *widget, int old_z, int new_z)`
- `void on_widget_pressed(Basic_Widget *widget)`
- `void on_widget_released(Basic_Widget *widget)`
- `void on_page_changed(int old_page, int new_page)`
- `void on_container_resized(const QSize &old_size, const QSize &new_size)`
- `void on_host_save()`
- `void call_settings_widget()`
- `void update_style(...)`
- `void Trans_Update()`
- `void Get_Loader(const QStringList &loaderNames, const P_Sender *seek_loader_sender, const P_Sender *recive_loader_sender)`
- `void easy_desktop_version(const P_Version &Easy_Desktop_Version, const QString &AKA_name)`

### 4.3 宿主控制接口

插件通过 `Carrier_Geometry_Interface` 操作可载体内的控件：

| 分类 | 接口 | 说明 |
|---|---|---|
| 容器信息 | `container_widget` | 容器 `QWidget *` |
| 容器信息 | `container_rect` | `QRect(0, 0, w, h)` |
| 容器信息 | `carrier_id` | 唯一 id |
| 页管理 | `page_count` | 当前可载体的页数 |
| 页管理 | `current_page` | 当前页索引 |
| 页管理 | `set_current_page` | 切页，触发 `on_page_changed` |
| 页管理 | `list_widgets(page)` | 指定页的直接子 Basic_Widget |
| 页管理 | `list_all_widgets` | 所有页的直接子 Basic_Widget |
| 页管理 | `widget_page` | 某控件在哪页，返回 -1 表示不属于本载体 |
| 控件信息 | `get_widget_info` | 查控件信息 |
| 控件信息 | `is_widget_pressed` | 查某控件是否被鼠标按下 |
| 控件信息 | `any_widget_pressed` | 是否有控件被按下 |
| 控件信息 | `pressed_widgets` | 列出所有被按下的控件 |
| 几何操作 | `get_geometry` | 读控件当前 `QRect` |
| 几何操作 | `set_geometry` | 写控件几何，触发 `on_widget_geometry_changed` |
| 几何操作 | `move_by` | 等价于 `set_geometry(widget, rect.translated(delta))` |
| 视觉变换 | `set_transform` | 写视觉变换 |
| 视觉变换 | `get_transform` | 读视觉变换 |
| 可见与层级 | `set_visible` | 显示 / 隐藏控件 |
| 可见与层级 | `set_selected` / `is_selected` | 选中状态 |
| 可见与层级 | `set_z_index` / `get_z_index` | 同父兄弟排序 |
| 信号 | `send_signal` | 走 `Basic_Widget::dispatch_signal` |
| 拖入拖出 | `take_in` | 把控件移入当前可载体 |
| 拖入拖出 | `take_out` | 把控件移出当前可载体 |
| 鼠标与能力 | `mouse_global_pos` | 全局鼠标位置 |
| 鼠标与能力 | `mouse_in_container` | 鼠标是否在容器内 |
| 鼠标与能力 | `capabilities` | 宿主支持哪些功能 |

---

## 五、生命周期

```
宿主 QPluginLoader::load()
    ↓
元数据校验 (缺失则询问用户)
    ↓
qobject_cast 到插件接口
    ↓
版本校验
    ↓
宿主调用 plugin->easy_desktop_version(版本, AKA)
    ↓
宿主设置 plugin->your_plugin_loader / plugin_path / inited
    ↓
宿主调用 host->set_plugin(plugin)
    ├─ 调用 plugin->init(interface)
    ├─ 读 plugin->tick_interval_ms(), 启动 tick 定时器
    └─ 遍历已有控件, 调 plugin->on_widget_added
    ↓
宿主调用 plugin->Get_Loader(loaderNames, seek, recv)
    ↓
宿主启动 tick 定时器, 周期调 plugin->on_tick
    ↓
用户操作触发 on_widget_* / on_page_changed / on_container_resized
    ↓
用户保存触发 on_host_save
    ↓
用户点"几何插件设置"触发 call_settings_widget
    ↓
用户卸载插件或可载体销毁
    ↓
宿主调用 plugin->RemovePlugin
    ↓
QPluginLoader::unload()
```

**重要时机说明**：

- `easy_desktop_version()` 是**最早**被调用的回调，早于 `init()`。插件可以在这个回调里做版本兼容判断，但此时还拿不到 `Carrier_Geometry_Interface`。
- `init()` 会在 `Get_Loader()` **之前**被调用。如果 `init()` 里想用 Loader，需要延后到 `on_tick` 或第一次 `on_widget_added`。
- `on_widget_added()` 对**已有控件**的回调会在 `init()` 里同步触发，也在 `Get_Loader()` 之前。
- `Get_Loader()` 是唯一一个可以拿到内部 Loader 指针的入口，之后 `on_tick` / `on_widget_added` 等才会被周期或事件触发。

---

## 六、视觉变换

`Carrier_Transform` 字段：

| 字段 | 类型 | 默认值 | 说明 |
|---|---|---|---|
| `rotation` | `qreal` | `0.0` | 平面旋转角度，单位度，顺时针为正 |
| `tilt_x` | `qreal` | `0.0` | 绕 X 轴倾斜角度，单位度，上下翻转。正值表示上边远离观察者，视觉上上边收窄 |
| `tilt_y` | `qreal` | `0.0` | 绕 Y 轴倾斜角度，单位度，左右翻转。正值表示右边远离观察者，视觉上右边收窄 |
| `scale_x` | `qreal` | `1.0` | X 轴缩放 |
| `scale_y` | `qreal` | `1.0` | Y 轴缩放 |
| `opacity` | `qreal` | `1.0` | 透明度，0.0 全透明，1.0 不透明 |
| `perspective` | `qreal` | `0.0` | 伪透视强度，0.0 无透视，越大透视越强 |
| `enabled` | `bool` | `false` | 是否启用。`false` 时宿主会把控件恢复为 identity |
| `allow_suppress` | `bool` | `true` | 是否允许宿主在鼠标靠近时抑制本变换。`true` 宿主会临时把控件变换设为 identity，保证点击命中；`false` 宿主不抑制，变换始终生效，但可能影响点击命中 |

通过 `set_transform(widget, transform)` 设置，通过 `get_transform(widget, &t)` 读取。

`enabled = false` 时，宿主会移除该控件的视觉效果，控件恢复默认绘制。

---

## 七、能力位

宿主通过 `capabilities()` 返回支持的功能位。插件应根据能力位降级：

```cpp
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
```

插件：

```cpp
quint64 caps = m_interface->capabilities();
if (caps & Cap_Rotate)
{
    // 支持旋转
}
```

---

## 八、Z-Index 实现

`QWidget` 没有 `setZValue`。宿主在 `Basic_Widget` 里实现：

1. `Basic_Widget` 持有 `int m_z_index`。
2. `set_z_index(int)` 修改后调用 `update_z_order()`。
3. `update_z_order()` 对同一父对象下的兄弟 `Basic_Widget` 按 z 值稳定排序，然后依次 `raise()`。
4. `save` / `load` 里存 z 值，加载后延迟调用 `update_z_order()`。

跨页、跨载体的控件不参与排序，因为不在同一父对象下。

---

## 九、通知机制

### 9.1 通知类型

| 通知 | 触发时机 | 参数 |
|---|---|---|
| `on_widget_added` | 控件加入可载体 | widget, page |
| `on_widget_removed` | 控件从可载体移除 | widget, page |
| `on_widget_page_changed` | 控件换页 | widget, old_page, new_page |
| `on_widget_geometry_changed` | 控件几何变化 | widget, old_rect, new_rect |
| `on_widget_selected_changed` | 控件选中变化 | widget, selected |
| `on_widget_z_changed` | 控件 z 变化 | widget, old_z, new_z |
| `on_widget_pressed` | 控件被鼠标按下 | widget |
| `on_widget_released` | 控件被鼠标松开 | widget |
| `on_page_changed` | 当前页变化 | old_page, new_page |
| `on_container_resized` | 容器尺寸变化 | old_size, new_size |
| `on_host_save` | 宿主保存 | 无 |

### 9.2 生命周期协议

- 控件创建后，宿主调用 `on_widget_added`。
- 控件析构函数入口调用宿主 `unregister_widget`，宿主再调用 `on_widget_removed`。此时对象完整，插件可以安全访问。
- 控件换页时，宿主通过 `QEvent::ParentChange` 检测，更新页号并调用 `on_widget_page_changed`。
- 跨可载体移动时，旧宿主 `unregister_widget`，新宿主 `register_widget`，幂等。
- 控件在按下状态下被移除时，宿主先调 `on_widget_released`，再调 `on_widget_removed`。

### 9.3 插件侧存储建议

插件推荐用：

```cpp
QHash<Basic_Widget *, QPointer<QObject>> m_widgets;
QHash<Basic_Widget *, int> m_page_map;
QHash<Basic_Widget *, 其它状态> m_states;
```

`Basic_Widget *` 做 key 便于 O(1) 查找，`QPointer<QObject>` 做值兜底对象销毁。

`on_widget_removed` 里三个 map 都要清空对应项。

---

## 十、保存与加载

### 10.1 宿主保存什么

- 插件 `.so` 路径，key 是 `carrier_geometry_plugin_path`。
- 三个可载体各自在自己的 group 里保存，互不冲突。

### 10.2 插件保存什么

插件内部状态由插件自己保存。宿主通过 `on_host_save()` 通知，无参数。

插件通常用：

```cpp
QString dir = QDir::homePath() + "/.local/lib/easy_desktop_geometry_plugins";
QDir().mkpath(dir);
QString path = dir + "/My_Plugin.ini";
QSettings settings(path, QSettings::IniFormat);
settings.setValue("key", value);
```

保存时建议只写与默认值不同的键：

```cpp
if (m_gravity != k_default_gravity) settings.setValue("gravity", m_gravity);
```

### 10.3 加载时机

宿主 `load()` 时：

1. 读 `carrier_geometry_plugin_path`，加载 `.so`。
2. 调 `plugin->init(interface)`。
3. 恢复控件时逐个 `register_widget`，触发 `on_widget_added`。
4. `take_in` 时补充注册。

插件在 `init()` 里自己读参数，不需要宿主通知 `load`。

---

## 十一、设置窗口

### 11.1 入口

宿主菜单"几何插件设置"点击后：

```cpp
void Carrier_Geometry_Plugin_Root::call_plugin_settings()
{
    if (m_plugin == nullptr)
    {
        return;
    }
    m_plugin->call_settings_widget();
}
```

### 11.2 插件实现

```cpp
void My_Plugin::call_settings_widget()
{
    if (m_settings_dialog != nullptr)
    {
        m_settings_dialog->show();
        m_settings_dialog->raise();
        m_settings_dialog->activateWindow();
        return;
    }
    My_Settings_Dialog *dialog = new My_Settings_Dialog(nullptr);
    connect(dialog, &My_Settings_Dialog::settings_changed, this,
            [this](qreal value)
    {
        m_value = value;
        save_settings();
    });
    m_settings_dialog = dialog;
    dialog->show();
}
```

### 11.3 关键点

1. `m_settings_dialog` 用 `QPointer<My_Settings_Dialog>`。
2. 父窗口用 `nullptr`，让窗口成为独立顶层窗口。
3. 已打开时激活，不重建。
4. 用户点关闭时只 `hide`，不删除。
5. 插件卸载时在 `RemovePlugin` 里同步 `delete`。

---

## 十二、插件工程

### 12.1 `.pro` 文件

```pro
QT = core gui widgets
TEMPLATE = lib
CONFIG += plugin c++11 debug
CONFIG -= qml quick ltcg release

HEADERS += \
    my_plugin.h \
    my_settings_dialog.h \
    interfaces/easy_desktop_class.h \
    interfaces/carrier-geometry/carrier_geometry_types.h \
    interfaces/carrier-geometry/carrier_geometry_interface.h \
    interfaces/carrier-geometry/carrier_geometry_plugin_interface.h

SOURCES += \
    my_plugin.cpp \
    my_settings_dialog.cpp \
    interfaces/easy_desktop_class.cpp \
    interfaces/carrier-geometry/carrier_geometry_interface.cpp \
    interfaces/carrier-geometry/carrier_geometry_plugin_interface.cpp
```

**关键点**：

- `CONFIG += plugin c++11 debug`：强制 debug 模式。
- `CONFIG -= qml quick ltcg release`：移除 release 相关默认配置。
- `.pro` 里直接写明 `debug`，即使用户忘了在 qmake 命令行里传，也能保证是 debug。

### 12.2 编译

```bash
qmake my_plugin.pro
make -j$(nproc)
```

若 `.pro` 里已经写明了 `CONFIG += debug`，则 `qmake` 命令行里可以省去 `CONFIG+=debug`。

产物是 `libmy_plugin.so`（Linux）。

### 12.3 加载

Easy_Desktop 右键可载体 → "载入几何插件" → 选中 `.so`。

---

## 十三、开发中会遇到的坑

### 坑 1：不要用 release 模式编译插件

**症状**：

- 插件加载时报 `undefined symbol`
- `QPluginLoader::metaData()` 返回空
- `qobject_cast` 到接口失败

**原因**：

- 开启 `-O2/-O3` 后，编译器可能把 inline 函数完全展开，丢弃部分符号。
- `Q_PLUGIN_METADATA` 嵌入的 JSON 元数据在高优化下可能被优化掉。
- LTO 会破坏 vtable 布局。

**解法**：在 `.pro` 里写 `CONFIG += debug`，`CONFIG -= release ltcg`。

### 坑 2：元数据不要写 `MetaData` 外层

**症状**：`[Geo] fail: no Ext_Carrier_Geometry_Plugin key`。

**原因**：`Q_PLUGIN_METADATA` 会自动在嵌入的 JSON 外层包一层 `MetaData`。如果 `.json` 里也写了 `MetaData`，变成两层，宿主查不到。

**解法**：

```json
{
    "Ext_Carrier_Geometry_Plugin": ""
}
```

### 坑 3：`Basic_Widget` 在插件侧是不完整类型

**症状**：用 `QPointer<Basic_Widget>` 编译不过。

**原因**：插件头文件里只前置声明 `class Basic_Widget;`，编译器不知道它继承 `QObject`。

**解法**：

- 用 `QPointer<QObject>` 而不是 `QPointer<Basic_Widget>`。
- `Basic_Widget *` 转 `QObject *` 用 `reinterpret_cast`（单继承链，地址一致，安全）。

```cpp
static inline QObject *basic_widget_as_qobject(Basic_Widget *widget)
{
    return reinterpret_cast<QObject *>(widget);
}
```

### 坑 4：`on_widget_removed` 必须清空引用

**症状**：控件被关闭后，插件在下一帧 `on_tick` 里访问悬空指针，崩溃。

**原因**：控件析构时宿主会调 `on_widget_removed`，但插件忘记在这个回调里删除自己的缓存。

**解法**：每个存储了 `Basic_Widget *` 的容器，都要在 `on_widget_removed` 里删除对应项。

```cpp
void My_Plugin::on_widget_removed(Basic_Widget *widget, int page)
{
    (void) page;
    m_widgets.remove(widget);
    m_states.remove(widget);
    m_velocities.remove(widget);
}
```

### 坑 5：`on_tick` 遍历容器时不要直接删除元素

**症状**：`on_tick` 里随机崩溃，或漏处理部分控件。

**原因**：遍历 `QHash<Basic_Widget *, ...>` 时直接 `remove` 会破坏迭代器。

**解法**：先收集要删的，循环外统一删：

```cpp
void My_Plugin::on_tick(qint64 elapsed_ms)
{
    QList<Basic_Widget *> dead;
    for (auto it = m_widgets.begin(); it != m_widgets.end(); ++it)
    {
        if (it.value().isNull())
        {
            dead.append(it.key());
            continue;
        }
        // 正常处理
    }
    for (Basic_Widget *w : dead)
    {
        m_widgets.remove(w);
        m_states.remove(w);
    }
}
```

### 坑 6：`RemovePlugin` 里必须同步删除 dialog

**症状**：移除插件时崩，栈里出现 `sendPostedEvents`、`QObject::event`。

**原因**：dialog 用了 `WA_DeleteOnClose`，`close()` 只是排队了 `DeferredDelete`。`RemovePlugin` 返回后宿主 `m_loader->unload()` 卸载 `.so`，事件循环再处理 `DeferredDelete` 时，dialog 的析构函数在已卸载内存里。

**解法**：`RemovePlugin` 里同步删除：

```cpp
void My_Plugin::RemovePlugin()
{
    if (m_settings_dialog != nullptr)
    {
        m_settings_dialog->disconnect(this);
        // 如果有 QComboBox, 先关掉 popup
        const QList<QComboBox *> combos = m_settings_dialog->findChildren<QComboBox *>();
        for (QComboBox *combo : combos)
        {
            if (combo != nullptr)
            {
                combo->hidePopup();
            }
        }
        m_settings_dialog->hide();
        delete m_settings_dialog;
        m_settings_dialog = nullptr;
    }
    // 清空所有缓存
    m_widgets.clear();
    m_states.clear();
    m_interface = nullptr;
}
```

同时 `call_settings_widget` 里**不要**设 `WA_DeleteOnClose`。

### 坑 7：`QComboBox` popup 是顶层窗口

**症状**：只有带 `QComboBox` 的插件崩溃，纯 `QDoubleSpinBox` 的插件不崩。

**原因**：`QComboBox` 的下拉菜单是一个独立的顶层 `QWidget` popup，不受 dialog 父子树管理。dialog 析构时 popup 被 `deleteLater`，但如果 `.so` 已卸载，popup 的析构函数就跳到了已卸载内存。

**解法**：dialog 析构前显式 `combo->hidePopup()`，让 popup 立即关闭并释放。

### 坑 8：不要在插件里 `dynamic_cast` 到具体控件类型

**症状**：编不过，或运行崩溃。

**原因**：插件侧 `Basic_Widget` 是不完整类型，`qobject_cast<My_Clock *>` 或 `dynamic_cast` 需要完整类型定义。

**解法**：不要这样做。所有操作走 `Carrier_Geometry_Interface`。

### 坑 9：不要在插件里自己 `new QTimer`

**症状**：插件卸载后宿主定时器还在触发，回调打进已卸载内存。

**原因**：插件自己建 timer，卸载时没停。

**解法**：用宿主提供的 `on_tick`。所有周期性任务通过 `tick_interval_ms()` 和 `on_tick()` 由宿主统一调度。

### 坑 10：`on_tick` 不能做重活

**症状**：宿主整体卡顿，甚至主窗口响应迟滞。

**原因**：`on_tick` 在主线程调用，遍历每个控件调 `set_geometry` / `set_transform` 都会触发宿主内部排序、重绘。

**解法**：

- 不要每帧都调 `set_z_index`。设阈值过滤，只有目标 z 与当前 z 差别大于阈值时才调。
- 不要每帧遍历所有页的控件，只遍历当前页。
- 不要每帧都做全量动画计算。

### 坑 11：`call_settings_widget` 不要阻塞

**症状**：调用设置窗口后，宿主所有动画停止。

**原因**：用了 `dialog->exec()` 而不是 `dialog->show()`。`exec()` 会启动一个嵌套事件循环，阻塞当前调用栈。

**解法**：用 `show()`，不要用 `exec()`。

### 坑 12：`send_signal` 的参数类型

**症状**：调 `send_signal(widget, Signal::xxx, data)` 编译报错。

**原因**：`send_signal` 的参数是 `int signal`，不是 `Signal` 枚举。

**解法**：

```cpp
m_interface->send_signal(widget, static_cast<int>(Signal::Run), QVariant());
```

### 坑 13：`set_z_index` 阈值过滤

**症状**：每帧 `set_z_index` 导致宿主反复排序和 `raise()`，性能下降。

**解法**：

```cpp
int target_z = qRound((1.0 - depth) * 1000.0);
if (qAbs(state.current_z - target_z) > 10)
{
    m_interface->set_z_index(w, target_z);
    state.current_z = target_z;
}
```

### 坑 14：宿主和插件的 `Carrier_Transform` 布局必须一致

**症状**：升级宿主或插件后，变换效果错乱。

**原因**：`Carrier_Transform` 是 POD 结构，宿主和插件各自编译一份。如果两边版本不同，内存布局不一致。

**解法**：宿主和插件的 `interfaces/carrier-geometry/` 目录内容必须完全一致，改的时候两边一起改，一起编译。

### 坑 15：不要在插件里持有宿主的对象指针

**症状**：插件卸载后宿主对象还在用，或宿主对象销毁后插件还在用。

**原因**：插件从宿主那拿了一个 `QObject *` 并长期持有。

**解法**：不要从宿主拿宿主内部的对象指针。所有跨边界的操作走 `Carrier_Geometry_Interface`。

### 坑 16：`update_style` 和 `Trans_Update` 的实现

**症状**：插件界面文字不跟随系统语言，或主题色不更新。

**原因**：没有 override 这两个接口。

**解法**：如果插件有界面，要 override 这两个方法：

```cpp
void My_Plugin::update_style(...)
{
    // 把主题应用到 dialog
}
void My_Plugin::Trans_Update()
{
    // 重新设置界面文字
}
```

---

## 十四、调试方法

### 14.1 日志

宿主侧 `load_plugin` 有 `[Geo]` 前缀的调试日志。加载失败时看控制台会知道卡在哪一步：

- `fail: QPluginLoader::load error = ...` → `.so` 加载失败
- `fail: no Ext_Carrier_Geometry_Plugin key` → 元数据不对
- `fail: qobject_cast to interface failed` → IID 不对或 `Q_INTERFACES` 漏了
- `load_plugin success` → 加载成功

### 14.2 gdb

```
gdb ./Easy_Desktop
(gdb) run
# 复现崩溃
(gdb) bt full
```

看完整调用栈和局部变量。

### 14.3 不要用 `-O2` 编译插件

即使宿主可以开优化，插件也不要。见坑 1。

---

## 十五、检查清单

插件开发完，交付前检查：

- [ ] 元数据 `.json` 只有 `Ext_Carrier_Geometry_Plugin` 一个键，没有 `MetaData` 外层
- [ ] `Q_INTERFACES` 已写，IID 与宿主一致
- [ ] 三个必须实现的接口都实现了
- [ ] `on_widget_removed` 里清空了所有对该 widget 的引用
- [ ] `RemovePlugin` 里同步删除了 dialog，且没有 `WA_DeleteOnClose`
- [ ] dialog 里的 `QComboBox` 在删除前调了 `hidePopup()`
- [ ] 插件用 `CONFIG+=debug` 编译，没用 release
- [ ] 插件工程编译了 `interfaces/*.cpp`
- [ ] `on_tick` 遍历时先收集 dead 再统一清理
- [ ] `set_z_index` 有阈值过滤
- [ ] `Basic_Widget *` 转 `QObject *` 用 `reinterpret_cast`
- [ ] `send_signal` 的 `signal` 参数用 `static_cast<int>` 转换
- [ ] 插件工程不引入 `basic_widget.h`
- [ ] 设置窗口用 `QPointer` 管生命周期

---

## 十六、参考文件

| 文件 | 说明 |
|---|---|
| `interfaces/carrier-geometry/carrier_geometry_plugin_interface.h` | 插件接口 |
| `interfaces/carrier-geometry/carrier_geometry_interface.h` | 宿主控制接口 |
| `interfaces/carrier-geometry/carrier_geometry_types.h` | 类型定义 |
| `interfaces/easy_desktop_class.h` | `P_Version`、`P_Sender` |
