#include "dcomponent.h"


DComponent::DComponent()
{
    hovered = false;
    pressed = false;
    backgroundEnabled = false;
    m_isDraggable = false;
    adjust = 0;
    m_xPos = 0;
    m_yPos = 0;
    setFlag(QGraphicsItem::ItemIsFocusable);
    setAcceptHoverEvents(false);
    setReleaseBackgroundColor(Qt::white);
    setPressBackgroundColor(QColor(238,232,205,255));
    setHoverBackgroundColor(QColor(238,232,205,255));
    setTextColor(Qt::black);
    setBackgroundColor(QColor(255,255,255,255));
}

QRectF DComponent::boundingRect() const
{
    return QRectF(x_axis - adjust,
                  y_axis - adjust,
                  width + adjust,
                  height + adjust);
}

void DComponent::paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(pressed)
    {
        if(backgroundEnabled)
        {
            painter->setPen(pressBackgroundColor);
            painter->setBrush(pressBackgroundColor);
            painter->drawRect(x_axis, y_axis, width, height);
        }
        painter->drawPixmap(-releaseImage.width()/2,-releaseImage.height()/2,
                            releaseImage.width(),releaseImage.height(),pressImage);

    }
    else if(hovered)
    {
        if(backgroundEnabled)
        {
            painter->setPen(hoverBackgroundColor);
            painter->setBrush(hoverBackgroundColor);
            painter->drawRect(x_axis, y_axis, width, height);
        }
        painter->drawPixmap(-releaseImage.width()/2,-releaseImage.height()/2,
                            releaseImage.width(),releaseImage.height(),hoverImage);
    }
    else
    {
        if(backgroundEnabled)
        {
            painter->setPen(releaseBackgroundColor);
            painter->setBrush(releaseBackgroundColor);
            painter->drawRect(x_axis, y_axis, width, height);
        }
        painter->drawPixmap(-releaseImage.width()/2,-releaseImage.height()/2,
                            releaseImage.width(),releaseImage.height(),releaseImage);
    }
}

void DComponent::boundImageToPress(QString imagePath)
{
    pressImage.load(imagePath);
    if(pressImage.width()>width||pressImage.height()>height)
        pressImage = pressImage.scaled(width - MARGIN_IMAGE_BOUND,
                                       height - MARGIN_IMAGE_BOUND,  Qt::KeepAspectRatio);
}

void DComponent::boundImageToRelease(QString imagePath)
{
    releaseImage.load(imagePath);
    if(releaseImage.width()>width||releaseImage.height()>height)
        releaseImage = releaseImage.scaled(width - MARGIN_IMAGE_BOUND,
                                           height - MARGIN_IMAGE_BOUND,  Qt::KeepAspectRatio);
}

void DComponent::boundImageToHover(QString imagePath)
{
    hoverImage.load(imagePath);
    if(hoverImage.width()>width||hoverImage.height()>height)
        hoverImage = hoverImage.scaled(width - MARGIN_IMAGE_BOUND,
                                       height - MARGIN_IMAGE_BOUND,  Qt::KeepAspectRatio);
}

void DComponent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_isDraggable)
    {
        m_xPress = event->pos().x();
        m_yPress = event->pos().y();
    }
    pressed = true;
    emit clicked();
    update();
}

void DComponent::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(pressed&&m_isDraggable)
    {
        m_xOffset = event->pos().x() - m_xPress;
        m_xPos += m_xOffset;
        m_xPress = event->pos().x();

        m_yOffset = event->pos().y() - m_yPress;
        m_yPos += m_yOffset;
        m_yPress = event->pos().y();
        moveBy(m_xPos,m_yPos);
        update();
    }
}

void DComponent::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    pressed = false;
    update();
}

void DComponent::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void DComponent::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    hovered = true;
    update();
}

void DComponent::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    hovered = false;
    update();
}

void DComponent::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    Q_UNUSED(event);
}

void DComponent::setDraggable(bool b)
{
    m_isDraggable = b;
}

