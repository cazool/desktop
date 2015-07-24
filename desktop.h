#ifndef DESKTOP_H
#define DESKTOP_H

#include "common.h"
#include "icon.h"
#include "panel.h"

class Desktop : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Desktop(QObject *parent = 0);

    Desktop(QGraphicsView *view);

    void showScene();

    void addIcon(Icon *icon);

    void addGridLayout();

    void setBackgroundColor(const QColor &color);

    void setBackgroudImage(QString path);

    QString parseDesktopFile(QString fileName, QString item);

    QString getIconFile(QString fileName);

    ~Desktop();
private:
    void environment();
    void createIcons();
    void getDesktopFiles();
    void getScreenDemension();
    void setDesktopDemension();

    int m_screenWidth, m_screenHeight;
    QStringList m_fileList;
    QGraphicsView *m_view;
    QStringList m_desktopLocation;
    QStringList m_iconPathList;

    Panel *m_panel;
};

#endif // DESKTOP_H
