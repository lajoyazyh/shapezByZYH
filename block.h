#ifndef BLOCK_H
#define BLOCK_H

#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QDebug>  // 引入调试头文件

class Block {
public:
    Block(int x, int y, const QPixmap &blockPic = QPixmap(":/images/resource/images/block.png"))
        : x_(x), y_(y), blockPic_(blockPic) {
        if (blockPic_.isNull()) {
            qDebug() << "Block image failed to load:" << ":/images/resource/images/block.png";
        }
    }

    void draw(QPainter *painter) const {
        painter->drawPixmap(x_ * 50, y_ * 50, 50, 50, blockPic_);
    }

    int getX() const { return x_; }
    int getY() const { return y_; }

private:
    int x_;
    int y_;
    QPixmap blockPic_;
};

#endif // BLOCK_H
