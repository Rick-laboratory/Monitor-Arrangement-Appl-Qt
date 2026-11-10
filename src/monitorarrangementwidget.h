#pragma once

#include "monitorinfo.h"
#include <QVector>
#include <QWidget>

class QScreen;

class MonitorArrangementWidget final : public QWidget
{
  public:
    explicit MonitorArrangementWidget(QWidget *parent = nullptr);
    void visualizeMonitorArrangement();

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    void watchScreen(QScreen *screen);
    QVector<MonitorInfo> monitors_;
};
