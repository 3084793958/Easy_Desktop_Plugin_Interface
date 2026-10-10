# Easy_Desktop_Plugin_Interface

适用于 Easy_Desktop 插件的接口。包含所有 Easy_Desktop 能接入的接口。

**许可证**：LGPL-3.0

---

## 一、支持范围

本仓库包含 Easy_Desktop 目前支持的四类插件接口：

| 接口 | 用途 | 当前版本 | 来源 |
|------|------|----------|------|
| `Ext_Plugin_Interface` | dde-dock 插件（含 V1.2.3 与 V2.0.0 两个变体） | V0.0.3 | 基于 dde-dock 插件改造 |
| `Ext_Preview_PluginInterface` | 预览控件（`Preview_File_Widget`）的插件 | V0.0.4 | 本项目 |
| `Ext_Wallpaper_PluginInterface` | 壁纸插件 | V0.0.3 | 本项目 |
| `Ext_Carrier_Geometry_PluginInterface` | 载体几何插件 | V0.0.1 | 本项目 |

旧版本接口（仅含 `Ext_Plugin_Interface` V0.0.1）：[https://github.com/3084793958/Ext_Plugin_Interface.git](https://github.com/3084793958/Ext_Plugin_Interface.git)

Easy_Desktop **仍然兼容**由旧版本接口开发的插件。旧版本接口将不再更新，所有新接口和功能都迁移到本仓库。

---

## 二、目录结构

```
interfaces/
├── easy_desktop_class.h/.cpp           P_Version / P_Sender（所有接口共用）
│
├── dde-dock/
│   ├── v1.2.3/
│   │   ├── constants.h
│   │   ├── pluginproxyinterface.h
│   │   └── pluginsiteminterface.h/.cpp
│   └── v2.0.0/
│       ├── pluginproxyinterface_v2.0.0.h
│       └── pluginsiteminterface_v2.0.0.h/.cpp
│
├── file-preview/
│   ├── file_preview_plugin.h/.cpp
│   └── preview_file_interface.h/.cpp
│
├── wallpaper/
│   ├── wallpaper_info_def.h/.cpp
│   └── wallpaper_plugin.h/.cpp
│
├── carrier-geometry/
│   ├── carrier_geometry_types.h
│   ├── carrier_geometry_interface.h/.cpp
│   └── carrier_geometry_plugin_interface.h/.cpp
│
├── media-widget-action/
│   └── media_widgetaction_interface.h/.cpp
│
└── loader/
    ├── alsa_loader_interface.h
    ├── archive_loader_interface.h
    ├── cairo_loader_interface.h
    ├── ffmpeg_loader_interface.h
    ├── glib_loader_interface.h
    ├── global_loader_interface.h
    ├── kf5_loader_interface.h
    ├── multimedia_loader_interface.h
    ├── poppler_loader_interface.h
    ├── pulse_loader_interface.h
    ├── qdbus_loader_interface.h
    ├── qnetwork_loader_interface.h
    ├── qpdf_loader_interface.h
    ├── qsvg_loader_interface.h
    ├── rsvg_loader_interface.h
    ├── x11_loader_interface.h
    └── loader_interface_include.hpp
```

---

## 三、通用约定

### 3.1 接口识别

每个插件类必须声明：

```cpp
Q_PLUGIN_METADATA(IID "<对应接口的 IID>" FILE "xxx.json")
Q_INTERFACES(<接口名>)
```

各接口对应的 IID：

| 接口 | IID |
|------|-----|
| `Ext_Plugin_Interface` V1.2.3 | `com.deepin.dock.PluginsItemInterface` |
| `Ext_Plugin_Interface` V2.0.0 | `com.deepin.dock.PluginsItemInterface_2_0_0` |
| `Ext_Preview_PluginInterface` | `com.Easy.Desktop.Ext_Preview_PluginInterface` |
| `Ext_Wallpaper_PluginInterface` | `com.Easy.Desktop.Ext_Wallpaper_PluginInterface` |
| `Ext_Carrier_Geometry_PluginInterface` | `com.Easy.Desktop.Ext_Carrier_Geometry_PluginInterface` |

IID 必须与 Easy_Desktop 内部的 `Q_DECLARE_INTERFACE` 字符串一致，否则 `qobject_cast` 会失败。

### 3.2 版本号

插件通过 `Plugin_Version` 字段向宿主暴露自己的版本：

```cpp
P_Version Plugin_Version{0, 0, 1};
```

`P_Version` 定义在 `interfaces/easy_desktop_class.h` 中，支持比较运算：

```cpp
struct P_Version
{
    uint Major_Version;
    uint Minor_Version;
    uint Patch_Version;

    P_Version(uint Major, uint Minor, uint Patch);
    P_Version(QString Version_Name); // "1.2.0" 格式

    bool operator==(P_Version) const;
    bool operator!=(P_Version) const;
    bool operator>(P_Version) const;
    bool operator>=(P_Version) const;
    bool operator<(P_Version) const;
    bool operator<=(P_Version) const;

    QString VersionName() const;
};
```

宿主会检查插件的最低版本要求，不满足则拒绝加载。

### 3.3 宿主维护的字段

以下字段由宿主读写，**插件不要修改**：

| 字段 | 类型 | 说明 |
|------|------|------|
| `inited` | `bool` | 是否已初始化 |
| `your_plugin_loader` | `QPluginLoader *` | 插件加载器指针 |
| `plugin_path` | `QString` | 插件路径 |

### 3.4 元数据 JSON

插件 `.json` 元数据文件**不要**写 `MetaData` 外层，`Q_PLUGIN_METADATA` 会自动加：

```json
{
    "Ext_Carrier_Geometry_Plugin": ""
}
```

不同接口用不同的键：

| 接口 | 元数据键 |
|------|----------|
| dde-dock V1.2.3 | `"Ext_Plugin": ""` 或 `"api": "1.2.3"` |
| dde-dock V2.0.0 | `"Ext_Plugin": ""` 或 `"api": "2.0.0"` |
| 预览插件 | `"Ext_Preview_Plugin": ""` |
| 壁纸插件 | `"Ext_Wallpaper_Plugin": ""` |
| 载体几何插件 | `"Ext_Carrier_Geometry_Plugin": ""` |

### 3.5 Loader 访问

从 V0.0.3 开始，部分接口支持通过 `P_Sender` 访问 Easy_Desktop 内部的 Loader。写法：

```cpp
plugin_interface->init_V_0_0_3(
    {"Alsa_Loader",
     "Archive_Loader",
     "Cairo_Loader",
     "Ffmpeg_Loader",
     "Glib_Loader",
     "KF5_Loader",
     "Multimedia_Loader",
     "Poppler_Loader",
     "Pulse_Loader",
     "Dbus_Loader",
     "QNetwork_Loader",
     "QPdf_Loader",
     "QSvg_Loader",
     "Rsvg_Loader",
     "X11_Loader"},
    seek_loader_sender,
    recive_loader_sender);
```

- `seek_loader_sender` 只走 `Send_Data` 路线，发送 `QString` 请求 Loader 名（全匹配）
- `recive_loader_sender` 只走 `Send_Ptr` 路线，返回 `void *`，需自行转换
- 无论是否找到，`recive_loader_sender` 都会返回一次（找不到返回 `nullptr`）

### 3.6 Easy_Desktop 版本告知

所有接口都支持：

```cpp
virtual void easy_desktop_version(const P_Version &Easy_Desktop_Version,
                                  const QString &AKA_name);
```

宿主在加载插件后调用，告知当前 Easy_Desktop 的版本号与 AKA 名称。插件可通过此回调做兼容性判断。

### 3.7 翻译热更新

从各接口的 V0.0.2 版本开始，都支持：

```cpp
virtual void Trans_Update();
```

Easy_Desktop 的动态翻译更新时调用，插件应重新设置自己界面上的文字。

---

## 四、四类接口简述

### 4.1 `Ext_Plugin_Interface` —— dde-dock 插件

把 dde-dock 插件嵌入到 Easy_Desktop 的 `Plugin_Widget` 中。

- **V1.2.3** 变体：基于 deepin 20.9 的 dde-dock 接口
- **V2.0.0** 变体：**需要 `DEFINES += USE_DTK`**（即 `dtk` 变体），因为 V2.0.0 接口依赖 `DGuiApplicationHelper`

主要方法：

```cpp
pluginName() / pluginDisplayName()
init(PluginProxyInterface*)
itemWidget(itemKey) / itemTipsWidget(itemKey) / itemPopupApplet(itemKey)
itemCommand(itemKey) / itemContextMenu(itemKey) / invokedMenuItem(...)
pluginIsAllowUnload() / pluginUnload()
pluginGetSender(update_sender, send_data_sender)
pluginSetCarrierSpacing / Offset / Color / Radius / Size / Page
pluginAddToCarrierQMenu(...)
update_style_V2(...)
init_V_0_0_3(loaderNames, seek, recv)
```

**关于 `libtray.so`**：Easy_Desktop 对 dde-tray 做了专门兼容，把它提升为独立顶层窗口。这是为了让它能正常运行，普通插件不受影响。详见 Easy_Desktop 主仓库的 README。

### 4.2 `Ext_Preview_PluginInterface` —— 预览插件

扩展 `Preview_File_Widget` 支持的预览类型。宿主每遇到一个文件会依次询问每个已加载的预览插件。

**当前版本 V0.0.4。** 主要方法：

```cpp
init(Preview_File_Interface*, QWidget*)
init_V_0_0_2(...) / init_V_0_0_3(...) / init_V_0_0_4(...)
previewFile(QFileInfo&) -> bool           是否处理该文件
previewItem() -> QWidget*                 预览控件
willThrowFileToNextPreview() -> bool      是否继续传给下一个预览插件
clear() / resetZoom()
```

### 4.3 `Ext_Wallpaper_PluginInterface` —— 壁纸插件

扩展桌面壁纸类型。一个壁纸插件对应 `Path_Info` 中的一种"插件"壁纸。

**当前版本 V0.0.3。** 主要方法：

```cpp
RemovePlugin()
init(const Path_Info&, P_Sender*)
init_V_0_0_3(const Ext_Path_Info_V_0_0_1&, loaderNames, seek, recv)
wallpaperItem() -> QWidget*
mouseMoveEvent(int, int) / sizeChange(QSize)
play() / pause()
setPosition(int) / setPosition_qint64(qint64)
setVolume(int) / setSpeed(int) / setPitch(int)
settingsEvent()
get_qint64_pos_and_dur_sender(qint64&, qint64&)
```

### 4.4 `Ext_Carrier_Geometry_PluginInterface` —— 载体几何插件

控制载体中控件的布局、视觉变换、tick 动画。

**当前版本 V0.0.1。** 三个必须实现的方法：

```cpp
virtual void RemovePlugin() = 0;
virtual QString Plugin_Name() = 0;
virtual void init(Carrier_Geometry_Interface *ptr) = 0;
```

其余方法都有默认空实现。生命周期、接口细节、开发坑位，见：

- **开发文档**：[Easy_Desktop 载体几何插件开发文档](./Easy_Desktop 载体几何插件设计规则.md)（若有）
- **Easy_Desktop 主仓库** `README.md` 的"插件接口"章节

#### 容器和控件操作

通过 `Carrier_Geometry_Interface` 操作：

- **容器信息**：`carrier_id` / `container_widget` / `container_rect`
- **页管理**：`page_count` / `current_page` / `set_current_page` / `list_widgets` / `list_all_widgets` / `widget_page`
- **控件信息**：`get_widget_info` / `is_widget_pressed` / `any_widget_pressed` / `pressed_widgets`
- **几何操作**：`get_geometry` / `set_geometry` / `move_by`
- **视觉变换**：`set_transform` / `get_transform`
- **可见性与层级**：`set_visible` / `set_selected` / `is_selected` / `set_z_index` / `get_z_index`
- **信号**：`send_signal`
- **拖入拖出**：`take_in` / `take_out`
- **鼠标与能力**：`mouse_global_pos` / `mouse_in_container` / `capabilities`

#### 视觉变换字段

`Carrier_Transform` 是 POD 结构：

| 字段 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `rotation` | `qreal` | `0.0` | 平面旋转角度（度），顺时针为正 |
| `tilt_x` | `qreal` | `0.0` | 绕 X 轴倾斜（度） |
| `tilt_y` | `qreal` | `0.0` | 绕 Y 轴倾斜（度） |
| `scale_x` | `qreal` | `1.0` | X 轴缩放 |
| `scale_y` | `qreal` | `1.0` | Y 轴缩放 |
| `opacity` | `qreal` | `1.0` | 透明度 |
| `perspective` | `qreal` | `0.0` | 伪透视强度 |
| `enabled` | `bool` | `false` | 是否启用 |
| `allow_suppress` | `bool` | `true` | 是否允许鼠标靠近时抑制变换 |

**重要**：`Carrier_Transform` 是 POD 结构，宿主和插件各自编译一份。如果两边版本不同，内存布局不一致会出问题。**宿主和插件的 `interfaces/carrier-geometry/` 目录内容必须完全一致。**

---

## 五、插件工程示例

### 5.1 `.pro` 文件

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

- `CONFIG += debug`：**强制 debug 编译**。release 模式下的 `-O2/-O3/-flto` 会破坏 `Q_PLUGIN_METADATA` 嵌入的元数据、破坏 vtable 布局，导致 `undefined symbol` 或 `qobject_cast` 失败
- 必须编译 `interfaces/*.cpp`，否则链接会缺符号

### 5.2 插件类骨架

```cpp
#include <QObject>
#include "interfaces/carrier-geometry/carrier_geometry_plugin_interface.h"

class My_Plugin : public QObject, public Ext_Carrier_Geometry_PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.Easy.Desktop.Ext_Carrier_Geometry_PluginInterface"
                      FILE "my_plugin.json")
    Q_INTERFACES(Ext_Carrier_Geometry_PluginInterface)

public:
    P_Version Plugin_Version{0, 0, 1};

    void RemovePlugin() override;
    QString Plugin_Name() override;
    void init(Carrier_Geometry_Interface *ptr) override;

    // 按需 override
    int tick_interval_ms() const override;
    void on_tick(qint64 elapsed_ms) override;
    void on_widget_added(Basic_Widget *widget, int page) override;
    void on_widget_removed(Basic_Widget *widget, int page) override;
    // ...

private:
    Carrier_Geometry_Interface *m_interface = nullptr;
};
```

### 5.3 元数据 JSON

```json
{
    "Ext_Carrier_Geometry_Plugin": ""
}
```

### 5.4 编译

```bash
qmake my_plugin.pro
make -j$(nproc)
```

产物：`libmy_plugin.so`

---

## 六、插件实例

| 插件 | 接口 | 说明 |
|------|------|------|
| [music-island](https://github.com/3084793958/music-island-B-QT-P) | `Ext_Plugin_Interface` | music-island |
| [Window_Container](https://github.com/3084793958/Window_Container) | `Ext_Plugin_Interface` | 窗口容器 |
| [PPT_LibreOffice_Previewer](https://github.com/3084793958/PPT_LibreOffice_Previewer) | `Ext_Preview_PluginInterface` | PPT 预览（LibreOffice 后端） |
| [Two_SOI_Previewer](https://github.com/3084793958/Two_SOI_Previewer.git) | `Ext_Preview_PluginInterface` | two-SOI 图像预览 |
| [Metro_Wallpaper](https://github.com/3084793958/Metro_Wallpaper.git) | `Ext_Wallpaper_PluginInterface` | 广州地铁主题壁纸 |

---

## 七、Easy_Desktop 编译变体与接口

Easy_Desktop 目前发布两个变体：

| 变体 | 宏 | 支持的插件接口 |
|------|-----|----------------|
| `empty` | （无） | `Ext_Preview_PluginInterface`、`Ext_Wallpaper_PluginInterface`、`Ext_Carrier_Geometry_PluginInterface`、`Ext_Plugin_Interface` V1.2.3 |
| `dtk` | `USE_DTK` | 上面全部 + `Ext_Plugin_Interface` V2.0.0 |

**`.pro` 中的宏定义**：

```pro
contains(DEFINES, USE_DTK) {
    QT += dtkcore dtkgui dtkwidget
}
```

只有开启 `USE_DTK` 时，才会把 dde-dock V2.0.0 插件接口打开。

V2.0.0 接口已预留，但**目前尚无插件用于实测，不保证完全可用**。

---

## 八、Tips

1. **`Ext_Preview_PluginInterface` 已提供详细注释**，包括接口的生命周期、回调时机、参数含义。
2. **`Ext_Plugin_Interface` 旧版本的文件结构不易扩展**（写时未考虑接入其他类型插件），因此本次将全部接口重新组织到本仓库。Easy_Desktop 仍兼容旧版插件，但**旧版接口不再更新**。
3. **载体几何插件开发有大量坑位**，建议在写之前先阅读 Easy_Desktop 主仓库的 README 中"关于 DTK 插件的 `libtray.so` 特化处理"和"插件接口"章节。
4. **所有接口都在运行时通过 `QPluginLoader` 加载**，接口本身**不 include 任何 Qt 之外的第三方头文件**，因此没有第三方编译依赖。
5. **插件和宿主使用的接口版本必须一致**，尤其是 `Carrier_Transform`、`P_Version`、`P_Sender` 等 POD 结构。修改接口时，宿主和插件要一起改、一起编译。

---

## 九、许可证

LGPL-3.0