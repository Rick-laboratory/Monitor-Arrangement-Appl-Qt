#include "mainwindow.h"

#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QStringList>
#include <cstdio>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Monitor Arrangement");
    const auto args = app.arguments();
    if (args.size() > 2 || (args.size() == 2 && args[1] != "--check" && args[1] != "--help"))
        return 2;
    if (args.contains("--help"))
    {
        std::puts(
            "monitor-arrangement [--check]\nVisualize connected screens; no display settings are changed.");
        return 0;
    }

    MainWindow window;
    if (args.contains("--check"))
    {
        window.ensurePolished();
        QImage image(window.size(), QImage::Format_ARGB32_Premultiplied);
        if (image.isNull())
            return 1;
        image.fill(Qt::transparent);
        QPainter painter(&image);
        window.render(&painter);
        return painter.end() ? 0 : 1;
    }
    window.show();
    return app.exec();
}
