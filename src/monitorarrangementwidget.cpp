#include "monitorarrangementwidget.h"
#include "monitorlayout.h"

#include <QGuiApplication>
#include <QPainter>
#include <QScreen>

MonitorArrangementWidget::MonitorArrangementWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(320, 200);
    for (auto *screen : QGuiApplication::screens())
        watchScreen(screen);
    connect(qGuiApp, &QGuiApplication::screenAdded, this, [this](QScreen *screen) {
        watchScreen(screen);
        visualizeMonitorArrangement();
    });
    connect(qGuiApp, &QGuiApplication::screenRemoved, this,
            [this](QScreen *) { visualizeMonitorArrangement(); });
    connect(qGuiApp, &QGuiApplication::primaryScreenChanged, this,
            [this](QScreen *) { visualizeMonitorArrangement(); });
    visualizeMonitorArrangement();
}

void MonitorArrangementWidget::watchScreen(QScreen *screen)
{
    connect(screen, &QScreen::geometryChanged, this,
            [this](const QRect &) { visualizeMonitorArrangement(); });
}

void MonitorArrangementWidget::visualizeMonitorArrangement()
{
    monitors_.clear();
    for (const auto *screen : QGuiApplication::screens())
        monitors_.append({screen->name(), screen->geometry(), screen == QGuiApplication::primaryScreen()});
    update();
}

void MonitorArrangementWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), QColor("#101827"));
    QVector<QRect> geometries;
    for (const auto &monitor : monitors_)
        geometries.append(monitor.geometry);
    const auto rectangles = fitMonitorRects(geometries, size());

    if (rectangles.isEmpty())
    {
        painter.setPen(QColor("#d9e2f1"));
        painter.drawText(rect(), Qt::AlignCenter, "No display geometry available");
        return;
    }
    for (int index = 0; index < rectangles.size(); ++index)
    {
        const auto &monitor = monitors_[index];
        const QRectF box = rectangles[index];
        painter.setPen(QPen(monitor.primary ? QColor("#67e8c5") : QColor("#7392b8"), 2));
        painter.setBrush(monitor.primary ? QColor("#174b4b") : QColor("#23354f"));
        painter.drawRoundedRect(box.adjusted(1, 1, -1, -1), 5, 5);
        painter.save();
        painter.setClipRect(box.adjusted(4, 4, -4, -4));
        painter.setPen(QColor("#f1f5f9"));
        const QString label = QString("Display %1%2\n%3\n%4 × %5\nOrigin: %6, %7")
                                  .arg(index + 1)
                                  .arg(monitor.primary ? " · primary" : "")
                                  .arg(monitor.name)
                                  .arg(monitor.geometry.width())
                                  .arg(monitor.geometry.height())
                                  .arg(monitor.geometry.x())
                                  .arg(monitor.geometry.y());
        painter.drawText(box.adjusted(8, 8, -8, -8), Qt::AlignCenter, label);
        painter.restore();
    }
}
