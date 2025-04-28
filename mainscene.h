#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "gamescene.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QIODevice>
#include "map.h"
#include "gamescene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainScene;
}
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    QMediaPlayer *player = nullptr;
    QAudioOutput *audioOutput = nullptr;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainScene *ui;
    gamescene *gamescene_;
    Map gameMap;  // 修改变量名

    int task1Count = 0;  // 任务1：交付20个物品1
    int task2Count = 0;  // 任务2：交付30个物品2
    int task3Count = 0;  // 任务3：交付50个切割后的物品1

    void loadGameProgress();
};
#endif // MAINSCENE_H
