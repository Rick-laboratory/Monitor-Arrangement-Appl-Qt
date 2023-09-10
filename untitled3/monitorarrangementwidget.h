// monitorarrangementwidget.h
#ifndef MONITORARRANGEMENTWIDGET_H
#define MONITORARRANGEMENTWIDGET_H

#include <QWidget>
#include <QVector>
#include "monitorinfo.h" // Include the monitorinfo.h header
#include <windows.h>

class MonitorArrangementWidget : public QWidget
{
    Q_OBJECT

public:
    MonitorArrangementWidget(QWidget *parent = nullptr);

public slots:
    void visualizeMonitorArrangement();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<MonitorInfo> monitorInfoList; // Declare the monitorInfoList here
    static BOOL MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
};

#endif // MONITORARRANGEMENTWIDGET_H
