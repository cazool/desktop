#ifndef DCOMPONENT_H
#define DCOMPONENT_H

#include "common.h"

#define MARGIN_IMAGE_BOUND 20

class DComponent :  public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES ( QGraphicsItem )

public:
    DComponent();
    
    enum Alignment
    {
        center = 0,
        left = 1,
        right = 2,
        top = 3,
        bottom = 4,
        topRight = 5,
        topLeft = 6,
        bottomLeft = 7,
        bottomRight = 8
    };
    
    enum ImageRatioMode
    {
        IgnoreImageRatio,
        KeepImageRatio,
        KeepImageRatioByExpanding
    };
    
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void boundImageToPress(QString imagePath);
    void boundImageToRelease(QString imagePath);
    void boundImageToHover(QString imagePath);
    void setDraggable(bool b);

    bool m_pressed;
    bool m_hovered;
    bool m_backgroundEnabled;

    QColor m_hoverBackgroundColor;
    QColor m_releaseBackgroundColor;
    QColor m_pressBackgroundColor;

    QColor m_textColor;
    QColor m_backGroundColor;

    int m_x_axis;
    int m_y_axis;
    int m_width;
    int m_height;
    int m_text_x;
    int m_text_y;
    qreal m_adjust;
    QPixmap m_pressImage;
    QPixmap m_releaseImage;
    QPixmap m_hoverImage;

    QString m_textContent;


    void setBounds(int x, int y, int w, int h);
    void setPressBackgroundColor(const QColor &color);
    void setReleaseBackgroundColor(const QColor &color);
    void setHoverBackgroundColor(const QColor &color);
    void setHoverEnableFlag(bool flag);
    void setAdjust(qreal value);
    bool isPressed();
    bool isHovered();
    void setBackgroundEnable(bool flag);
    int boundX();
    int boundY();
    int boundWidth();
    int boundHeight();
    void setText(const QString & text);
    QString text();
    void setTextColor(const QColor &color);
    QColor getTextColor();
    void setPress(bool b);
    void setPressBackgroundEnable(bool b); 
    void setReleaseBackgroundEnable(bool b);    
    void setHoverBackgroundEnable(bool b);
    void setImageRatioMode(ImageRatioMode mode);   
    void setImageAlignment(Alignment align);
    void setImageScale(int w, int h);

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
    int m_xOffsetImage, m_yOffsetImage;
    
    bool m_isDraggable;
    bool m_pressBackgroundEnabled;
    bool m_releaseBackgroundEnabled;
    bool m_hoverBackgroundEnabled;

};

#endif // DCOMPONENT_H
