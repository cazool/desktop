#ifndef ICON_H
#define ICON_H


#include "dcomponent.h"

#define ComputerPath"computer://"
#define TrashPath "trash://"


class Icon : public DComponent
{
        Q_OBJECT

public:
    Icon();
    void setExecutablePath(QString path);
    

private:
    QProcess *m_process;
    QString m_executablePath;
public slots:
    void exec();
protected:

};
#endif // ICON_H
