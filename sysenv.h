#ifndef SYSENV_H
#define SYSENV_H

#include <QString>

class SysEnv
{
public:
    SysEnv();

    void loadEnv();

    static QString homePath;
};

#endif // SYSENV_H
