#ifndef SOURCE_H
#define SOURCE_H

#include <QPoint>
#include <QPixmap>
#include <QPainter>

class Source {
public:
    enum Type {
        SQUARE_ORE,
        CIRCLE_ORE
    };

    Source(int x, int y, const QPixmap &sourcePic, Type type)
        : x_(x), y_(y), sourcePic_(sourcePic), type_(type) {}

    void draw(QPainter *painter) const {
        painter->drawPixmap(x_ * 50, y_ * 50, 50, 50, sourcePic_);
    }

    int getX() const { return x_; }
    int getY() const { return y_; }
    Type getType() const { return type_; }

private:
    int x_;
    int y_;
    QPixmap sourcePic_;
    Type type_;
};

#endif // SOURCE_H
