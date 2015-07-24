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
