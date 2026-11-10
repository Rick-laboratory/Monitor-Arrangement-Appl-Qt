#include "monitorlayout.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

void require(bool condition, const char *message)
{
    if (!condition)
        throw std::runtime_error(message);
}
bool near(qreal a, qreal b)
{
    return std::abs(a - b) < 0.000001;
}

int main()
{
    try
    {
        const QVector<QRect> screens{{-1920, 0, 1920, 1080}, {0, 0, 1920, 1080}, {0, -1200, 1600, 1200}};
        const auto fitted = fitMonitorRects(screens, {900, 600});
        require(fitted.size() == 3, "screen count");
        require(near(fitted[0].right(), fitted[1].left()), "horizontal adjacency");
        require(near(fitted[2].bottom(), fitted[1].top()), "vertical adjacency");
        const qreal scale = fitted[0].width() / 1920;
        require(near(fitted[2].height() / 1200, scale), "shared aspect ratio");
        for (const auto &box : fitted)
            require(box.left() >= 24 && box.top() >= 24 && box.right() <= 876.000001 &&
                        box.bottom() <= 576.000001,
                    "viewport bounds");

        const auto one = fitMonitorRects({QRect(500, 700, 100, 200)}, {400, 400}, 0);
        require(one.size() == 1 && near(one[0].left(), 100) && near(one[0].top(), 0),
                "nonzero origin centered");
        require(fitMonitorRects({}, {400, 400}).isEmpty(), "empty input");
        require(fitMonitorRects({QRect(0, 0, 0, 100)}, {400, 400}).isEmpty(), "invalid screen");
        require(fitMonitorRects(screens, {20, 20}).isEmpty(), "small viewport");
        require(fitMonitorRects(screens, {400, 400}, -1).isEmpty(), "negative padding");
        std::cout << "Monitor geometry checks passed\n";
        return 0;
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
