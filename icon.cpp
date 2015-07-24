#include "icon.h"

Icon::Icon()
{
    connect(this,SIGNAL(doubleClicked()),this,SLOT(exec()));
}

void Icon::setExecutablePath(QString path)
{
    m_executablePath = path;
}

void Icon::exec()
{
    if(!m_executablePath.isNull())
    {
        qDebug()<<"execute";
        m_process = new QProcess(this);
        m_process->start(m_executablePath);
        m_process->connect(m_process,SIGNAL(finished(int)),m_process,SLOT(deleteLater()));
    }
}
