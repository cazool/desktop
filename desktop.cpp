
#include "desktop.h"

Desktop::Desktop(QObject *parent)
    : QGraphicsScene(parent)
{

}

Desktop::Desktop(QGraphicsView *view)
{
    m_view = view;
    m_view->setWindowFlags(Qt::CustomizeWindowHint);
    m_view->setStyleSheet( "QGraphicsView { border-style: none; }" );
    m_view->showFullScreen();
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    getScreenDemension();
    setDesktopDemension();
    setBackgroundColor(QColor(255,255,255,255));
    environment();
    getDesktopFiles();
    createIcons();
    setBackgroudImage("/usr/share/backgrounds/desktop.jpg");
    m_panel->setImageRatioMode(DComponent::KeepImageRatioByExpanding);
}

Desktop::~Desktop()
{

}

void Desktop::setBackgroundColor(const QColor &color)
{
    m_view->setBackgroundBrush(color);
}

void Desktop::setBackgroudImage(QString path)
{
    m_panel->boundImageToRelease(path);
}

void Desktop::environment()
{
    m_iconPathList.append("/usr/share/icons/hicolor/48x48/apps/");
    m_iconPathList.append("/usr/share/icons/flattr/apps/scalable/");
    m_iconPathList.append("/usr/share/pixmaps/");
    m_iconPathList.append("/usr/share/icons/hicolor/512x512/apps/");
    m_desktopLocation = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
}

QString Desktop::parseDesktopFile(QString fileName, QString item)
{
    QString name;
    QSettings settings(m_desktopLocation.at(0)+"/"+fileName, QSettings::IniFormat);
    settings.beginGroup("Desktop Entry");
    name = settings.value(item).toString();
    settings.endGroup();
    return name;
}

void Desktop::getScreenDemension()
{
    QDesktopWidget widget;
    QRect rec = widget.availableGeometry(widget.primaryScreen());
    m_screenHeight = rec.height();
    m_screenWidth = rec.width();
    qDebug()<<m_screenHeight<<m_screenWidth;
}

void Desktop::setDesktopDemension()
{
    setSceneRect(-m_screenWidth/2,-m_screenHeight/2,m_screenWidth,m_screenHeight);
    m_view->resize(m_screenWidth,m_screenHeight);
}

void Desktop::getDesktopFiles()
{
    QDirIterator dirIt(m_desktopLocation.at(0),QDirIterator::Subdirectories);
    while (dirIt.hasNext())
    {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile())
        {
            if (QFileInfo(dirIt.filePath()).suffix() == "desktop")
            {
                m_fileList.append(parseDesktopFile(QFileInfo(dirIt.filePath()).fileName(),"Icon"));
                m_fileNameList.append(parseDesktopFile(QFileInfo(dirIt.filePath()).fileName(),"Name"));
            }
        }
    }
}

QString Desktop::getIconFile(QString fileName)
{
    QString arg;
    for(int i=0;i<m_iconPathList.size();i++)
    {
        if(QFileInfo(m_iconPathList.at(i)+fileName+".png").exists())
        {
            arg = m_iconPathList.at(i)+fileName+".png";
            break;
        }
        else if(QFileInfo(m_iconPathList.at(i)+fileName+".svg").exists())
        {
            arg = m_iconPathList.at(i)+fileName+".svg";
            break;
        }
        else if(QFileInfo(m_iconPathList.at(i)+fileName+".xpm").exists())
        {
            arg = m_iconPathList.at(i)+fileName+".xpm";
            break;
        }
    }
    return arg;
}

void Desktop::createIcons()
{
    m_panel = new Panel();
    m_panel->setPos(0, 0);
    m_panel->setBounds(-m_screenWidth/2,-m_screenHeight/2,m_screenWidth,m_screenHeight);
    m_panel->setHoverEnableFlag(false);
    addItem(m_panel);
    for(int i=0;i<m_fileList.size();i++)
    {
        Icon *icon = new Icon();
        icon->setPos(0, i*80);
        icon->setBounds(-40,-40,80,80);
        icon->setHoverEnableFlag(true);
        icon->setPressBackgroundEnable(true);
        icon->setHoverBackgroundEnable(true);
        icon->setPressBackgroundColor(QColor(0,0,0,100));
        icon->setHoverBackgroundColor(QColor(0,0,0,100));
        icon->setDraggable(true);
        
        QString filePath = getIconFile(m_fileList.at(i));
        icon->setText(m_fileNameList.at(i));
        icon->boundImageToPress(filePath);
        icon->boundImageToRelease(filePath);
        icon->boundImageToHover(filePath);
        icon->setImageScale(48,48);
        icon->setImageAlignment(DComponent::top);
        addIcon(icon);
    }
}

void Desktop::addIcon(Icon *icon)
{
    this->addItem(icon);
}

void Desktop::showScene()
{
    m_view->setScene(this);
    m_view->show();
}
