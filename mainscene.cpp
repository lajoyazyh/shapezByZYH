#include "mainscene.h"
#include "ui_mainscene.h"
#include "gamescene.h"
#include <QMediaPlayer>
#include <QTimer>
#include <QPushButton>
#include <QMediaPlayer>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
    , gameMap(12, 20)  // 假设默认地图大小为 12x20
{
    ui->setupUi(this);
    setFixedSize(1000, 800);
    gamescene_ = new gamescene;

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.8);  //调节音频音量
    player->setSource(QUrl("qrc:/music/resource/music/background_music_june.mp3"));
    player->play();
    player->setLoops(999);
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::on_pushButton_clicked()
{
    QTimer::singleShot(300,this,[=](){
        this->hide();
        gamescene_->show();
    });
}


void MainScene::on_pushButton_2_clicked()
{
    loadGameProgress();
}

void MainScene::loadGameProgress() {
    QString filePath = QFileDialog::getOpenFileName(this, "加载存档", "", "存档文件 (*.dat)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "加载失败", "未选择任何存档文件。");
        return;
    }

    // 调用 GameScene 的加载函数
    gamescene_->loadGameProgress(filePath);

    // 切换到游戏场景
    gamescene_->show();
    this->hide();
}
