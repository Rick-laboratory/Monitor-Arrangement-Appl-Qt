#include "mainwindow.h"
#include "monitorarrangementwidget.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Monitor Arrangement");
    resize(850, 520);
    setMinimumSize(420, 300);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);
    auto *caption = new QLabel("Connected screens · primary display highlighted\n"
                               "Positions and sizes use Qt logical desktop coordinates.",
                               central);
    auto *monitors = new MonitorArrangementWidget(central);
    auto *refresh = new QPushButton("Refresh displays", central);
    connect(refresh, &QPushButton::clicked, monitors, &MonitorArrangementWidget::visualizeMonitorArrangement);
    layout->addWidget(caption);
    layout->addWidget(monitors, 1);
    layout->addWidget(refresh, 0, Qt::AlignRight);
    setCentralWidget(central);
}
