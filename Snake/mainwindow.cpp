#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setoptions.h"
#include "ui_setoptions.h"
#include "game.h"
#include "boards.h"
#include <QDialog>
#include <QPushButton>
#include <QMediaPlayer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

game::game(const game&) : QDialog(){};

/**
	Przycisk, który startuje gre.
	
	\image html pushbaton.png
*/
void MainWindow::on_pushButton_clicked()
{
    QMediaPlayer *pick = new QMediaPlayer();
    SetOptions *mute = new SetOptions();

    if(mute->getUi()->checkBox_4->isChecked()){
        pick->setMuted(true);
    }
    pick->setMedia(QUrl("qrc:/rec/sound/pick.mp3"));
    pick->play();

    hide();
    game *g = new game();
    g->setModal(true);
    g->exec();
}
/**
	Przycisk, który wyświetla opcje w grze.
	
	\image html puszbaton2.png
	\image html opcje.png
*/
void MainWindow::on_pushButton_2_clicked()
{

    QMediaPlayer *pick = new QMediaPlayer();
    SetOptions *mute = new SetOptions();

    if(mute->getUi()->checkBox_4->isChecked()){
        pick->setMuted(true);
    }
    pick->setMedia(QUrl("qrc:/rec/sound/pick.mp3"));    
    pick->play();


    SetOptions setoptions;
    setoptions.setModal(true);
    setoptions.exec();
}

/**
	Przycisk, który wyświetla plansze do wyboru
	
	\image html puszbaton4.png
	\image html plansze.png
*/
void MainWindow::on_pushButton_4_clicked()
{
    QMediaPlayer *pick = new QMediaPlayer();
    SetOptions *mute = new SetOptions();

    if(mute->getUi()->checkBox_4->isChecked()){
        pick->setMuted(true);
    }
    pick->setMedia(QUrl("qrc:/rec/sound/pick.mp3"));
    pick->play();

    boards board;
    board.setModal(true);
    board.exec();
}
/**
	Przycisk, który zamyka gre.
	
	\image html puszbaton3.png
	
*/
void MainWindow::on_pushButton_3_clicked()
{
    QMediaPlayer *pick = new QMediaPlayer();
    SetOptions *mute = new SetOptions();

    if(mute->getUi()->checkBox_4->isChecked()){
        pick->setMuted(true);
    }
    pick->setMedia(QUrl("qrc:/rec/sound/pick.mp3"));
    pick->play();
}

