#include "dcomponent.h"


DComponent::DComponent()
{
    m_hovered = false;
    m_pressed = false;
    m_backgroundEnabled = false;
    m_isDraggable = false;
    m_adjust = 0;
    m_xPos = 0;
    m_yPos = 0;
    m_xOffsetImage = 0;
    m_yOffsetImage = 0;
    setFlag(QGraphicsItem::ItemIsFocusable);
    setAcceptHoverEvents(false);
    setReleaseBackgroundColor(Qt::white);
    setPressBackgroundColor(QColor(238,232,205,255));
    setHoverBackgroundColor(QColor(238,232,205,255));
    setPressBackgroundEnable(false);
    setReleaseBackgroundEnable(false);
    setHoverBackgroundEnable(false);
    setTextColor(Qt::black);
}

QRectF DComponent::boundingRect() const
{
    return QRectF(m_x_axis - m_adjust,
                  m_y_axis - m_adjust,
                  m_width + m_adjust,
                  m_height + m_adjust);
}

void DComponent::paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_pressed)
    {
        if(m_pressBackgroundEnabled)
        {
            painter->setPen(QColor(0,0,0,0));
            painter->setBrush(m_pressBackgroundColor);
            painter->drawRect(m_x_axis, m_y_axis, m_width, m_height);
        }
        painter->drawPixmap(-m_releaseImage.width()/2 + m_xOffsetImage,
                            -m_releaseImage.height()/2 + m_yOffsetImage,
                            m_releaseImage.width(),
                            m_releaseImage.height(),
                            m_pressImage);
        
    }
    else if(m_hovered)
    {
        if(m_hoverBackgroundEnabled)
        {
            painter->setBrush(m_hoverBackgroundColor);
            painter->setPen(QColor(0,0,0,0));
            painter->drawRect(m_x_axis, m_y_axis, m_width, m_height);
        }
        painter->drawPixmap(-m_releaseImage.width()/2 + m_xOffsetImage,
                            -m_releaseImage.height()/2 + m_yOffsetImage,
                            m_releaseImage.width(),
                            m_releaseImage.height(),
                            m_hoverImage);
    }
    else
    {
        if(m_releaseBackgroundEnabled)
        {
            painter->setPen(QColor(0,0,0,0));
            painter->setBrush(m_releaseBackgroundColor);
            painter->drawRect(m_x_axis, m_y_axis, m_width, m_height);
        }
        painter->drawPixmap(-m_releaseImage.width()/2 + m_xOffsetImage,
                            -m_releaseImage.height()/2 + m_yOffsetImage,
                            m_releaseImage.width(),
                            m_releaseImage.height(),
                            m_releaseImage);
    }
    
    if(!m_textContent.isNull())
    {
        painter->setPen(QColor(255,255,255,255));
        painter->drawText(m_x_axis, m_y_axis+50,m_textContent);
    }
}

void DComponent::setImageRatioMode(ImageRatioMode mode)
{
    switch(mode)
    {
    case IgnoreImageRatio:
        if(!m_pressImage.isNull())
            m_pressImage = m_pressImage.scaled(m_width, m_height, Qt::IgnoreAspectRatio);
        
        if(!m_releaseImage.isNull())
            m_releaseImage = m_releaseImage.scaled(m_width, m_height, Qt::IgnoreAspectRatio);
        
        if(!m_hoverImage.isNull())
            m_hoverImage = m_hoverImage.scaled(m_width, m_height, Qt::IgnoreAspectRatio);
        break;
    case KeepImageRatio:
        if(!m_pressImage.isNull())
            m_pressImage = m_pressImage.scaled(m_width, m_height, Qt::KeepAspectRatio);
        
        if(!m_releaseImage.isNull())
            m_releaseImage = m_releaseImage.scaled(m_width, m_height, Qt::KeepAspectRatio);
        
        if(!m_hoverImage.isNull())
            m_hoverImage = m_hoverImage.scaled(m_width, m_height, Qt::KeepAspectRatio);
        break;
    case KeepImageRatioByExpanding:
        if(!m_pressImage.isNull())
            m_pressImage = m_pressImage.scaled(m_width, m_height, Qt::KeepAspectRatioByExpanding);
        
        if(!m_releaseImage.isNull())
            m_releaseImage = m_releaseImage.scaled(m_width, m_height, Qt::KeepAspectRatioByExpanding);
        
        if(!m_hoverImage.isNull())
            m_hoverImage = m_hoverImage.scaled(m_width, m_height, Qt::KeepAspectRatioByExpanding);
        break;
     default:
        break;
    }
}

void DComponent::boundImageToPress(QString imagePath)
{
    m_pressImage.load(imagePath);
    if(m_pressImage.width() > m_width || m_pressImage.height() > m_height)
        m_pressImage = m_pressImage.scaled(m_width - MARGIN_IMAGE_BOUND,
                                       m_height - MARGIN_IMAGE_BOUND,  Qt::KeepAspectRatio);
}

void DComponent::boundImageToRelease(QString imagePath)
{
    m_releaseImage.load(imagePath);
    if(m_releaseImage.width() > m_width || m_releaseImage.height() > m_height)
        m_releaseImage = m_releaseImage.scaled(m_width - MARGIN_IMAGE_BOUND,
                                           m_height - MARGIN_IMAGE_BOUND,  Qt::KeepAspectRatio);
}

void DComponent::boundImageToHover(QString imagePath)
{
    m_hoverImage.load(imagePath);
    if(m_hoverImage.width() > m_width||m_hoverImage.height() > m_height)
        m_hoverImage = m_hoverImage.scaled(m_width - MARGIN_IMAGE_BOUND,
                                       m_height - MARGIN_IMAGE_BOUND,  Qt::KeepAspectRatio);
}

void DComponent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_isDraggable)
    {
        m_xPress = event->pos().x();
        m_yPress = event->pos().y();
    }
    m_pressed = true;
    emit clicked();
    update();
}

void DComponent::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_pressed&&m_isDraggable)
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
    m_pressed = false;
    update();
}

void DComponent::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void DComponent::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovered = true;
    update();
}

void DComponent::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovered = false;
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

void DComponent::setBounds(int x, int y, int w, int h)
{
    m_x_axis = x;
    m_y_axis = y;
    m_width = w;
    m_height = h;
}

void DComponent::setPressBackgroundColor(const QColor &color)
{
    m_pressBackgroundColor = color;
}

void DComponent::setReleaseBackgroundColor(const QColor &color)
{
   m_releaseBackgroundColor = color;
}

void DComponent::setHoverBackgroundColor(const QColor &color)
{
    m_hoverBackgroundColor = color;
}

void DComponent::setHoverEnableFlag(bool flag)
{
     setAcceptHoverEvents(flag);
}

void DComponent::setAdjust(qreal value)
{
    m_adjust = value;
}

bool DComponent::isPressed()
{
    return m_pressed;
}

bool DComponent::isHovered()
{
    return m_hovered;
}

void DComponent::setBackgroundEnable(bool flag)
{
    m_backgroundEnabled = flag;
}

int DComponent::boundX()
{
    return m_x_axis;
}

int DComponent::boundY()
{
    return m_y_axis;
}

int DComponent::boundWidth()
{
    return m_width;
}

int DComponent::boundHeight()
{
    return m_height;
}

void DComponent::setText(const QString & text)
{
    m_textContent = text;
}

QString DComponent::text()
{
    return m_textContent;
}

void DComponent::setTextColor(const QColor &color)
{
    m_textColor = color;
}

QColor DComponent::getTextColor()
{
    return m_textColor;
}

void DComponent::setPress(bool b)
{
    m_pressed = b;
}

void DComponent::setPressBackgroundEnable(bool b)
{
    m_pressBackgroundEnabled = b;
}

void DComponent::setReleaseBackgroundEnable(bool b)
{
    m_releaseBackgroundEnabled = b;
}

void DComponent::setHoverBackgroundEnable(bool b)
{
    m_hoverBackgroundEnabled = b;
}

void DComponent::setImageAlignment(Alignment align)
{
    switch(align)
    {
    case center:
        m_xOffsetImage = 0;
        m_yOffsetImage = 0;
        break;
    case left:
        m_xOffsetImage = -m_width/4;
        m_yOffsetImage = 0;
        break;
    case right:
        m_xOffsetImage = m_width/4;
        m_yOffsetImage = 0;
        break;
    case top:
        m_xOffsetImage = 0;
        m_yOffsetImage = -m_height/4;
        if(-m_releaseImage.height()/2 + m_yOffsetImage <= -m_height/2)
            m_yOffsetImage = -m_height/2 + m_releaseImage.height()/2 + MARGIN_IMAGE_BOUND;
        break;
    case topLeft:
        m_xOffsetImage = -m_width/4;
        m_yOffsetImage = -m_height/4;
        break;
    case topRight:
        m_xOffsetImage = m_width/4;
        m_yOffsetImage = -m_height/4;
        break;
    case bottom:
        m_xOffsetImage = 0;
        m_yOffsetImage = m_height/4;
        break;
    case bottomLeft:
        m_xOffsetImage = -m_width/4;
        m_yOffsetImage = m_height/4;
        break;
    case bottomRight:
        m_xOffsetImage = m_width/4;
        m_yOffsetImage = -m_height/4;
        break;
    default:
        m_xOffsetImage = 0;
        m_yOffsetImage = 0;
        break;
    }
}

void DComponent::setImageScale(int w, int h)
{
    m_releaseImage = m_releaseImage.scaled(w, h, Qt::KeepAspectRatio);
    m_hoverImage = m_hoverImage.scaled(w, h, Qt::KeepAspectRatio);
    m_pressImage = m_pressImage.scaled(w, h, Qt::KeepAspectRatio);
}
