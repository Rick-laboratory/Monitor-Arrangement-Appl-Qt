#pragma once

#include <QRectF>
#include <QSizeF>
#include <QVector>
#include <algorithm>
#include <cmath>

// One shared translation and scale preserve relative origins, including negative coordinates.
inline QVector<QRectF> fitMonitorRects(const QVector<QRect> &screens, QSizeF viewport, qreal padding = 24.0)
{
    if (screens.isEmpty() || !std::isfinite(padding) || padding < 0 || !std::isfinite(viewport.width()) ||
        !std::isfinite(viewport.height()) || viewport.width() <= 2 * padding ||
        viewport.height() <= 2 * padding)
        return {};

    QRectF bounds;
    for (const auto &screen : screens)
    {
        if (screen.width() <= 0 || screen.height() <= 0)
            return {};
        bounds = bounds.united(QRectF(screen));
    }
    const qreal scale = std::min((viewport.width() - 2 * padding) / bounds.width(),
                                 (viewport.height() - 2 * padding) / bounds.height());
    const QPointF offset((viewport.width() - bounds.width() * scale) / 2,
                         (viewport.height() - bounds.height() * scale) / 2);
    QVector<QRectF> result;
    result.reserve(screens.size());
    for (const auto &screen : screens)
        result.append(QRectF(offset + (QPointF(screen.topLeft()) - bounds.topLeft()) * scale,
                             QSizeF(screen.size()) * scale));
    return result;
}
