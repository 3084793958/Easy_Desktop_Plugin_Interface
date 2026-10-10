#ifndef MEDIA_WIDGETACTION_INTERFACE_H
#define MEDIA_WIDGETACTION_INTERFACE_H

class QString;
class QColor;

#include <qglobal.h>

class Media_WidgetAction_Interface
{
public:
    virtual ~Media_WidgetAction_Interface();
    virtual void set_value(int m_volume, int m_speed) = 0;
    virtual void set_second(int value, QString text) = 0;
    virtual void slider_set_volume(int value) = 0;
    virtual void slider_set_position(int value) = 0;
    virtual void slider_set_speed(int value) = 0;
    virtual void set_color(QColor color) = 0;
};

class Media_WidgetAction_Interface_V_0_0_2
{
public:
    virtual ~Media_WidgetAction_Interface_V_0_0_2();
    virtual void slider_set_pitch(int value) = 0;
    virtual void slider_set_position_qint64(qint64 value) = 0;
    virtual void set_dialog_using_qint64(qint64 m_dialog_using_position, qint64 m_dialog_using_duration) = 0;
};

#endif // MEDIA_WIDGETACTION_INTERFACE_H
