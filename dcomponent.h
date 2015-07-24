#ifndef DCOMPONENT_H
#define DCOMPONENT_H

#include "common.h"

#define MARGIN_IMAGE_BOUND 20

class DComponent :  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    DComponent();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void boundImageToPress(QString imagePath);

    void boundImageToRelease(QString imagePath);

    void boundImageToHover(QString imagePath);

    void setBounds(int x, int y, int w, int h)
    {
        x_axis = x;
        y_axis = y;
        width = w;
        height = h;
    }

    void setPressBackgroundColor(const QColor &color)
    {
        pressBackgroundColor = color;
    }

    void setReleaseBackgroundColor(const QColor &color)
    {
        releaseBackgroundColor = color;
    }

    void setHoverBackgroundColor(const QColor &color)
    {
        hoverBackgroundColor = color;
    }

    void setHoverEnableFlag(bool flag)
    {
         setAcceptHoverEvents(flag);
    }

    void setAdjust(qreal value)
    {
        adjust = value;
    }

    bool isPressed()
    {
        return pressed;
    }

    bool isHovered()
    {
        return hovered;
    }

    void setBackgroundEnable(bool flag)
    {
        backgroundEnabled = flag;
    }

    int boundX()
    {
        return x_axis;
    }

    int boundY()
    {
        return y_axis;
    }

    int boundWidth()
    {
        return width;
    }

    int boundHeight()
    {
        return height;
    }

    void setText(const QString & text)
    {
        textContent = text;
    }

    QString text()
    {
        return textContent;
    }

    void setTextColor(const QColor &color)
    {
        textColor = color;
    }

    QColor getTextColor()
    {
        return textColor;
    }

    void setBackgroundColor(const QColor &color)
    {
        backGroundColor = color;
    }

    QColor getBackgroundColor()
    {
        return backGroundColor;
    }

    void setPress(bool b)
    {
        pressed = b;
    }

    void setDraggable(bool b);

    bool pressed;
    bool hovered;
    bool backgroundEnabled;

    QColor hoverBackgroundColor;
    QColor releaseBackgroundColor;
    QColor pressBackgroundColor;

    QColor textColor;
    QColor backGroundColor;

    int x_axis, y_axis, width, height;
    int text_x, text_y;
    qreal adjust;
    QPixmap pressImage;
    QPixmap releaseImage;
    QPixmap hoverImage;

    QString textContent;

signals:

    void clicked();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    int m_xOffset, m_yOffset;
    int m_xPos, m_yPos;
    int m_xPress, m_yPress;
    bool m_isDraggable;

};

#endif // DCOMPONENT_H
