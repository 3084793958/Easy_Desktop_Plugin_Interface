# Easy_Desktop_Plugin_Interface
适用于Easy_Desktop插件的接口,包含所有Easy_Desktop能接入的接口.licenses:LGPL3.0

## 支持范围

该接口包含Ext_Plugin_Interface接口(基于dde-dock插件改造的接口,使Easy_Desktop能导入dde-dock插件)([旧版本接口](https://github.com/3084793958/Ext_Plugin_Interface.git))

同时包含Ext_Preview_PluginInterface的接口(预览控件(Preview_File_Widget)的插件)

## 许可证
LGPL3.0

## Tips
Ext_Preview_PluginInterface已经提供注释了

由于在写Ext_Plugin_Interface时没考虑过接入其他插件,故旧版本的文件结构设置得不易拓展(主要是那样放太乱了).虽然Easy_Desktop仍然兼容[旧版本接口](https://github.com/3084793958/Ext_Plugin_Interface.git),但旧版本接口应该不会更新了,全部转移到这里

Easy_Desktop仍然兼容 由旧版本接口:[https://github.com/3084793958/Ext_Plugin_Interface.git](https://github.com/3084793958/Ext_Plugin_Interface.git)开发的插件

这次更新在Ext_Plugin_Interface中为V2.0.0的dde-dock插件留了个接口,但没有插件去测试,不一定有效.

Easy_Desktop中的QMake有一个宏定义USE_DTK,只有开启这项时,才会把dde-dockV2.0.0插件接口打开.
