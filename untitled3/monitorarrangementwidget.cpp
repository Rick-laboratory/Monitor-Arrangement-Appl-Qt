#include "monitorarrangementwidget.h"
#include <QPainter>
#include <Windows.h>
#include "monitorinfo.h" // Include the monitorinfo.h header

MonitorArrangementWidget::MonitorArrangementWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Monitor Arrangement Visualization");
}

void MonitorArrangementWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Define a scaling factor for the visualization (e.g., 10%)
    const qreal scalingFactor = 0.1;

    // Iterate through the monitorInfoList and draw scaled rectangles for each monitor
    for (int i = 0; i < monitorInfoList.size(); ++i) {
        const MonitorInfo& monitor = monitorInfoList.at(i);

        // Calculate the scaled dimensions
        int scaledWidth = static_cast<int>(monitor.width * scalingFactor);
        int scaledHeight = static_cast<int>(monitor.height * scalingFactor);

        // Calculate the scaled position (centered)
        int scaledX = (width() - scaledWidth) / 2;
        int scaledY = (height() - scaledHeight) / 2;

        // Clear the background
        painter.fillRect(scaledX, scaledY, scaledWidth, scaledHeight, Qt::white);

        // Draw the scaled rectangle
        painter.drawRect(scaledX, scaledY, scaledWidth, scaledHeight);


        // Create a text string with monitor number, resolution,
        QString text = QString("Monitor %1\nResolution: %2 x%3\n")
                           .arg(i + 1) // Monitor number (1-based index)
                           .arg(monitor.width)
                           .arg(monitor.height);

        // Set the text color to black for contrast with the background
        painter.setPen(Qt::black);

        // Draw the text within the rectangle
        painter.drawText(scaledX, scaledY, scaledWidth, scaledHeight, Qt::AlignCenter, text);
    }
}




void MonitorArrangementWidget::visualizeMonitorArrangement()
{
    // Clear existing monitor information
    monitorInfoList.clear();

    // Enumerate monitors and store their information
    EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, reinterpret_cast<LPARAM>(this));

    // Redraw the widget
    update();
}

BOOL CALLBACK MonitorArrangementWidget::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
    MonitorArrangementWidget* widget = reinterpret_cast<MonitorArrangementWidget*>(dwData);
    MONITORINFOEX monitorInfo = { {sizeof(MONITORINFOEX)} };

    if (GetMonitorInfo(hMonitor, &monitorInfo)) {
        MonitorInfo info;
        info.left = monitorInfo.rcMonitor.left;
        info.top = monitorInfo.rcMonitor.top;
        info.width = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
        info.height = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;
        widget->monitorInfoList.append(info);
    }

    return TRUE;
}
