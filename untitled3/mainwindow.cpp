#include "mainwindow.h"
#include "monitorarrangementwidget.h"
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Monitor Arrangement Application");

    // Create a central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create the custom widget for monitor arrangement
    MonitorArrangementWidget *monitorWidget = new MonitorArrangementWidget(this);

    // Create a button to trigger monitor visualization
    QPushButton *visualizeButton = new QPushButton("Visualize Monitors", this);
    connect(visualizeButton, &QPushButton::clicked, monitorWidget, &MonitorArrangementWidget::visualizeMonitorArrangement);

    // Layout setup
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(visualizeButton);
    layout->addWidget(monitorWidget);
}
MainWindow::~MainWindow()
{
    // Destructor implementation
    // Include any necessary cleanup or resource release code here
}
