#ifndef GLOBAL_ENUMS_H
#define GLOBAL_ENUMS_H

#include <QColor>

    enum Shapes { Triangle, Rectangle, Trapezium, Polygon, None }; //!< enum containing the types of shapes that can be drawn
    enum Colors { White, Black, Red, DarkRed, Green, DarkGreen, Blue, DarkBlue, Cyan, DarkCyan, Magenta, DarkMagenta, Yellow, DarkYellow, Gray, DarkGray, LightGray }; //!< enum containing the colors that can be used
    const int NUM_COLORS = 17;
    extern QColor colorMap [NUM_COLORS]; //!< map one of the inter color values to a QT colour constant

#endif // GLOBAL_ENUMS_H
