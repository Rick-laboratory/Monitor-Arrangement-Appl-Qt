#pragma once

#include <QRect>
#include <QString>

struct MonitorInfo
{
    QString name;
    QRect geometry;
    bool primary = false;
};
