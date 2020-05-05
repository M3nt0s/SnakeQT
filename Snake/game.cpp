#include <QPainter>
#include <cstdlib>
#include <time.h>
#include <QTimer>
#include <QRect>
#include <QMessageBox>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMediaPlayer>
#include "game.h"
#include "boards.h"
#include "ui_boards.h"
#include "setoptions.h"
#include "ui_setoptions.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameover.h"
#include "ui_gameover.h"
#include <unistd.h>

using namespace std;


game::game(QDialog *parent)
        : QDialog(parent)
{
    resize(MARGIN*4+(AREA_COL+3)*SIZE,MARGIN*2+AREA_ROW*SIZE);
                 InitGame();
}

game::~game()
{

}
/**
Inicjalizacja calej gry
	
	Funkcja init_game odpowiada za inicjalizacje całej gry poprzez ustawienia początkowych prędkości, współrzędnych i wszystkich potrzebnych wielkości.
		
		
		
\image html init_game.png
*/
void game::InitGame()
{
   
    for(int j=4;j>=0;j--){
        snake.push_back(QPoint(j,0));
    }

    SetOptions *mute = new SetOptions();

    if(mute->getUi()->checkBox_4->isChecked()){
        music->setMuted(true);
    }

    playlist->addMedia(QUrl("qrc:/rec/sound/background.mp3"));
    music->setPlaylist(playlist);
    music->setVolume(20);
    music->play();


    foodPoint2.setX(50);
    foodPoint2.setY(50);

    GenerateFood();

    BossPoint1.setX(50);
    BossPoint1.setY(50);
    BossPoint2.setX(50);
    BossPoint2.setY(50);
    BossPoint3.setX(50);
    BossPoint3.setY(50);
    BossPoint4.setX(50);
    BossPoint4.setY(50);

    srand (static_cast<unsigned int>(time(nullptr)));

    dir=RIGHT;
    score = 0;
    level = 1;
    SPEED = 230;
    WEAPONSPEED = 200;
    bosshealth = 5;
    snakedie=5;
    weapon.push_back(QPoint(50, 50));
    isPause=false;
    gameTimer=new QTimer(this);
    gameTimer2=new QTimer(this);
    connect(gameTimer,SIGNAL(timeout()),this,SLOT(SnakeUpdate()));
    connect(gameTimer2,SIGNAL(timeout()),this,SLOT(WeaponUpdate()));
    gameTimer->start(SPEED);
    gameTimer2->start(WEAPONSPEED);
    delete mute;
}
/**
	Funkcja GenerateBarier odpowiedzialna jest za generowanie przeszkody dwuelementowej. Funkcja sprawdza czy wygenerowane współrzędne niekolidują z obecnym położeniem węża.
	
	
\image html generate_berier1.png

*/
void game::GenerateBarier()
{
    int x = rand()%AREA_COL/2;
    int y = rand()%AREA_ROW;
    int c = 1+rand()%2;
    if(x>4 && x<10 && y<13){
        BarierPoint.setX(x);
        BarierPoint.setY(y);
        if(c==1 && (y+1) <13 && (y-1)>0 && (x-1)>0 && (x+1)<10){
            BarierPoint0.setX(x+1);
            BarierPoint0.setY(y);
            BarierPoint1.setX(x-1);
            BarierPoint1.setY(y);
        }
        else if(c==2 && (y+1) <13 && (y-1)>0 && (x-1)>0 && (x+1)<10){
            BarierPoint0.setX(x);
            BarierPoint0.setY(y+1);
            BarierPoint1.setX(x+1);
            BarierPoint1.setY(y);
        }
        else{
            GenerateBarier();
        }
    }
    else{
        GenerateBarier();
    }


    if(snake.contains(BarierPoint) || snake.contains(BarierPoint0) || snake.contains(BarierPoint1)) {
        GenerateBarier();
    }

    if(((BossPoint1.x() == BarierPoint.x()) && (BossPoint1.y() == BarierPoint.y())) || ((BossPoint1.x() == BarierPoint0.x()) && (BossPoint1.y() == BarierPoint0.y()))
         || ((BossPoint1.x() == BarierPoint1.x()) && (BossPoint1.y() == BarierPoint1.y()))){
        GenerateBarier();
    }

    if(((BossPoint2.x() == BarierPoint.x()) && (BossPoint2.y() == BarierPoint.y())) || ((BossPoint2.x() == BarierPoint0.x()) && (BossPoint2.y() == BarierPoint0.y()))
             || ((BossPoint2.x() == BarierPoint1.x()) && (BossPoint2.y() == BarierPoint1.y()))){
        GenerateBarier();
    }

    if(((BossPoint3.x() == BarierPoint.x()) && (BossPoint3.y() == BarierPoint.y())) || ((BossPoint3.x() == BarierPoint0.x()) && (BossPoint3.y() == BarierPoint0.y()))
             || ((BossPoint3.x() == BarierPoint1.x()) && (BossPoint3.y() == BarierPoint1.y()))){
        GenerateBarier();
    }

    if(((BossPoint4.x() == BarierPoint.x()) && (BossPoint4.y() == BarierPoint.y())) || ((BossPoint4.x() == BarierPoint0.x()) && (BossPoint4.y() == BarierPoint0.y()))
             || ((BossPoint4.x() == BarierPoint1.x()) && (BossPoint4.y() == BarierPoint1.y()))){
        GenerateBarier();
    }
}
/**
	Funkcja GenerateBarier1 odpowiedzialna jest za generowanie bariery rozbudowanej Funkcja sprawdza czy wygenerowane współrzędne niekolidują z obecnym położeniem węża.
	
	
\image html generate_berier2.png

*/
void game::GenerateBarier1()
{
    int x = 10+ rand()%AREA_COL;
    int y = rand()%AREA_ROW;
    int c = 1+rand()%2;
    if(x>10 && x<20 && y<13){
        BarierPoint2.setX(x);
        BarierPoint2.setY(y);
        if(c==1 && (y+1) <13 && (y-1)>0 && (x-1)>10 && (x+1)<20){
            BarierPoint3.setX(x);
            BarierPoint3.setY(y-1);
            BarierPoint4.setX(x-1);
            BarierPoint4.setY(y);
            BarierPoint5.setX(x+1);
            BarierPoint5.setY(y);
        }
        else if(c==2 && (y+1) <13 && (y-1)>0 && (x-1)>10 && (x+1)<20){
            BarierPoint3.setX(x);
            BarierPoint3.setY(y-1);
            BarierPoint4.setX(x+1);
            BarierPoint4.setY(y);
            BarierPoint5.setX(x-1);
            BarierPoint5.setY(y-1);
        }
        else{
            GenerateBarier1();
        }
    }
    else{
        GenerateBarier1();
    }


    if(snake.contains(BarierPoint2) || snake.contains(BarierPoint3) || snake.contains(BarierPoint4) || snake.contains(BarierPoint5)) {
        GenerateBarier1();
    }


    if(((BossPoint1.x() == BarierPoint2.x()) && (BossPoint1.y() == BarierPoint2.y())) || ((BossPoint1.x() == BarierPoint3.x()) && (BossPoint1.y() == BarierPoint3.y()))
         || ((BossPoint1.x() == BarierPoint4.x()) && (BossPoint1.y() == BarierPoint4.y())) || ((BossPoint1.x() == BarierPoint5.x()) && (BossPoint1.y() == BarierPoint5.y()))){
        GenerateBarier1();
    }

    if(((BossPoint2.x() == BarierPoint2.x()) && (BossPoint2.y() == BarierPoint2.y())) || ((BossPoint2.x() == BarierPoint3.x()) && (BossPoint2.y() == BarierPoint3.y()))
         || ((BossPoint2.x() == BarierPoint4.x()) && (BossPoint2.y() == BarierPoint4.y())) || ((BossPoint2.x() == BarierPoint5.x()) && (BossPoint2.y() == BarierPoint5.y()))){
        GenerateBarier1();
    }

    if(((BossPoint3.x() == BarierPoint2.x()) && (BossPoint3.y() == BarierPoint2.y())) || ((BossPoint3.x() == BarierPoint3.x()) && (BossPoint3.y() == BarierPoint3.y()))
         || ((BossPoint3.x() == BarierPoint4.x()) && (BossPoint3.y() == BarierPoint4.y())) || ((BossPoint3.x() == BarierPoint5.x()) && (BossPoint3.y() == BarierPoint5.y()))){
        GenerateBarier1();
    }

    if(((BossPoint4.x() == BarierPoint2.x()) && (BossPoint4.y() == BarierPoint2.y())) || ((BossPoint4.x() == BarierPoint3.x()) && (BossPoint4.y() == BarierPoint3.y()))
         || ((BossPoint4.x() == BarierPoint4.x()) && (BossPoint4.y() == BarierPoint4.y())) || ((BossPoint4.x() == BarierPoint5.x()) && (BossPoint4.y() == BarierPoint5.y()))){
        GenerateBarier1();
    }


}
/**
	Funkcja GenerateFood odpowiedzialan jest na generowanie współrzędnych podstawowego owoca w grze. Sprawdza czy wygenerowane współrzędne niekolidują ze współrzędnymi bossa.
	
	
\image html generate_food.png

*/
void game::GenerateFood()
{
    foodPoint.setX(rand()%AREA_COL);
    foodPoint.setY(rand()%AREA_ROW);

    if(snake.contains(foodPoint)){
        GenerateFood();
    }

    if(((BossPoint1.x() == foodPoint.x()) && (BossPoint1.y() == foodPoint.y()))){
        GenerateFood();
    }
    if(((BossPoint2.x() == foodPoint.x()) && (BossPoint2.y() == foodPoint.y()))){
        GenerateFood();
    }
    if(((BossPoint3.x() == foodPoint.x()) && (BossPoint3.y() == foodPoint.y()))){
        GenerateFood();
    }
    if(((BossPoint4.x() == foodPoint.x()) && (BossPoint4.y() == foodPoint.y()))){
        GenerateFood();
    }

}
/**
	Funkcja która działa tylko kiedy w ustawieniach zaznaczony jest checkbox z dodatkowymi owocami i robi dokładnie to samo co funkcja Generate_food.
	
	
\image html generate_food2.png

*/
void game::GenerateFood2(){


    foodPoint2.setX(rand()%AREA_COL);
    foodPoint2.setY(rand()%AREA_ROW);

   if(foodPoint.x() == foodPoint2.x() && foodPoint.y() == foodPoint2.y()){
       GenerateFood2();
   }

   if(snake.contains(foodPoint2)){
        GenerateFood2();
    }

   if(((BossPoint1.x() == foodPoint2.x()) && (BossPoint1.y() == foodPoint2.y()))){
       GenerateFood2();
   }
   if(((BossPoint2.x() == foodPoint2.x()) && (BossPoint2.y() == foodPoint2.y()))){
       GenerateFood2();
   }
   if(((BossPoint3.x() == foodPoint2.x()) && (BossPoint3.y() == foodPoint2.y()))){
       GenerateFood2();
   }
   if(((BossPoint4.x() == foodPoint2.x()) && (BossPoint4.y() == foodPoint2.y()))){
       GenerateFood2();
    }
   Fruit();
}
/**
	Funkcja która określa jaki dodatkowy owoc ma sie pojawić.
	
	
\image html fruit.png

*/
void game::Fruit(){
    int s;
    s = rand()%2;
    if(s==0){
        random=0;
    }
    else if(s==1){
        random=1;
    }
}
/**
	Funkcja odpowiedzialna za ustawienie początkowych współrzędnych czy nie będą kolidować z przeszkodami, owocami i snakiem.
	
	
\image html generate_boss.png

*/
void game::GenerateBoss(){

    int x = rand()%AREA_COL;
    int y = rand()%AREA_ROW;
    QMediaPlayer *boss = new QMediaPlayer();
    SetOptions *ui3=new SetOptions();
    if(ui3->getUi()->checkBox_4->isChecked()){
        boss->setMuted(true);
    }
    boss->setMedia(QUrl("qrc:/rec/sound/boss_sound.mp3"));
    boss->play();

        if(x>0 && x<19 && y<13 && y>0){
            BossPoint1.setX(x);
            BossPoint1.setY(y);
            weapon.front().setX(x);
            weapon.front().setY(y);
            QMediaPlayer *fireball = new QMediaPlayer();
            fireball->setMedia(QUrl("qrc:/rec/sound/fireball.mp3"));
            if(ui3->getUi()->checkBox_4->isChecked()){
                fireball->setMuted(true);
            }
            fireball->play();
        }
        else{
            GenerateBoss();
        }

        if(x+1>0 && x+1<19 && y<13 && y>0){
            BossPoint2.setX(x+1);
            BossPoint2.setY(y);
        }
        else{
            GenerateBoss();
        }

        if(x>0 && x<19 && y-1<13 && y-1>0){
            BossPoint3.setX(x);
            BossPoint3.setY(y-1);
        }
        else{
            GenerateBoss();
        }

        if(x+1>0 && x+1<19 && y-1<13 && y-1>0){
            BossPoint4.setX(x+1);
            BossPoint4.setY(y-1);
        }
        else{
            GenerateBoss();
        }

    if(snake.contains(BossPoint1) || snake.contains(BossPoint2) || snake.contains(BossPoint3) || snake.contains(BossPoint4)) {
        GenerateBoss();
    }


    if(((BossPoint1.x() == foodPoint.x()) && (BossPoint1.y() == foodPoint.y())) || ((BossPoint1.x() == foodPoint2.x()) && (BossPoint1.y() == foodPoint2.y()))){
        GenerateBoss();
    }
    if(((BossPoint2.x() == foodPoint.x()) && (BossPoint2.y() == foodPoint.y())) || ((BossPoint2.x() == foodPoint2.x()) && (BossPoint2.y() == foodPoint2.y()))){
        GenerateBoss();
    }
    if(((BossPoint3.x() == foodPoint.x()) && (BossPoint3.y() == foodPoint.y())) || ((BossPoint3.x() == foodPoint2.x()) && (BossPoint3.y() == foodPoint2.y()))){
        GenerateBoss();
    }
    if(((BossPoint4.x() == foodPoint.x()) && (BossPoint4.y() == foodPoint.y())) || ((BossPoint4.x() == foodPoint2.x()) && (BossPoint4.y() == foodPoint2.y()))){
        GenerateBoss();
    }

    if(((BossPoint1.x() == BarierPoint.x()) && (BossPoint1.y() == BarierPoint.y())) || ((BossPoint1.x() == BarierPoint0.x()) && (BossPoint1.y() == BarierPoint0.y()))
             || ((BossPoint1.x() == BarierPoint1.x()) && (BossPoint1.y() == BarierPoint1.y()))
             || ((BossPoint1.x() == BarierPoint2.x()) && (BossPoint1.y() == BarierPoint2.y()))  || ((BossPoint1.x() == BarierPoint3.x()) && (BossPoint1.y() == BarierPoint3.y()))
             || ((BossPoint1.x() == BarierPoint4.x()) && (BossPoint1.y() == BarierPoint4.y()))  || ((BossPoint1.x() == BarierPoint5.x()) && (BossPoint1.y() == BarierPoint5.y()))){
        GenerateBoss();
    }

    if(((BossPoint2.x() == BarierPoint.x()) && (BossPoint2.y() == BarierPoint.y())) || ((BossPoint2.x() == BarierPoint0.x()) && (BossPoint2.y() == BarierPoint0.y()))
             || ((BossPoint2.x() == BarierPoint1.x()) && (BossPoint2.y() == BarierPoint1.y()))
             || ((BossPoint2.x() == BarierPoint2.x()) && (BossPoint2.y() == BarierPoint2.y()))  || ((BossPoint2.x() == BarierPoint3.x()) && (BossPoint2.y() == BarierPoint3.y()))
             || ((BossPoint2.x() == BarierPoint4.x()) && (BossPoint2.y() == BarierPoint4.y()))  || ((BossPoint2.x() == BarierPoint5.x()) && (BossPoint2.y() == BarierPoint5.y()))){
        GenerateBoss();
    }

    if(((BossPoint3.x() == BarierPoint.x()) && (BossPoint3.y() == BarierPoint.y())) || ((BossPoint3.x() == BarierPoint0.x()) && (BossPoint3.y() == BarierPoint0.y()))
             || ((BossPoint3.x() == BarierPoint1.x()) && (BossPoint3.y() == BarierPoint1.y()))
             || ((BossPoint3.x() == BarierPoint2.x()) && (BossPoint3.y() == BarierPoint2.y()))  || ((BossPoint3.x() == BarierPoint3.x()) && (BossPoint3.y() == BarierPoint3.y()))
             || ((BossPoint3.x() == BarierPoint4.x()) && (BossPoint3.y() == BarierPoint4.y()))  || ((BossPoint3.x() == BarierPoint5.x()) && (BossPoint3.y() == BarierPoint5.y()))){
        GenerateBoss();
    }

    if(((BossPoint4.x() == BarierPoint.x()) && (BossPoint4.y() == BarierPoint.y())) || ((BossPoint4.x() == BarierPoint0.x()) && (BossPoint4.y() == BarierPoint0.y()))
             || ((BossPoint4.x() == BarierPoint1.x()) && (BossPoint4.y() == BarierPoint1.y()))
             || ((BossPoint4.x() == BarierPoint2.x()) && (BossPoint4.y() == BarierPoint2.y()))  || ((BossPoint4.x() == BarierPoint3.x()) && (BossPoint4.y() == BarierPoint3.y()))
             || ((BossPoint4.x() == BarierPoint4.x()) && (BossPoint4.y() == BarierPoint4.y()))  || ((BossPoint4.x() == BarierPoint5.x()) && (BossPoint4.y() == BarierPoint5.y()))){
        GenerateBoss();
    }

    if(snake.front().y()>weapon.front().y()){
        weaponstatus = 1;
    }

    if(snake.front().y()<weapon.front().y()){
        weaponstatus = 2;
    }

    if(snake.front().x()<weapon.front().x()){
        weaponstatus = 3;
    }

    if(snake.front().x()>weapon.front().x()){
        weaponstatus = 4;
    }

    if(snake.front().x()==weapon.front().x()){
        weaponstatus = 2;
    }

    if(snake.front().y()==weapon.front().y()){
        weaponstatus = 1;
    }
    delete ui3;
}
/**
	Funkcja paintEvent odpowiedzialna za rysowanie tego co widzimy na ekranie rozgrywki. Implementowane są textury owoców, bossa, pocisku bossa, węża, barier i kolor wybranego tła w ustawieniach. 
	
	
\image html paint_event.png

*/
void game::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.setFont(QFont("Arial",14));
    painter.drawLine(0*SIZE,0*SIZE,0*SIZE,13*SIZE);
    painter.drawLine(20*SIZE,0*SIZE,20*SIZE,13*SIZE);
    painter.drawLine(0*SIZE,13*SIZE,20*SIZE,13*SIZE);
    boards* ui2 = new boards();

    //Wybór tła

    if(ui2->getUi()->radioButton->isChecked()){
        painter.drawImage(QRect(MARGIN,MARGIN,AREA_COL*SIZE,AREA_ROW*SIZE), QImage(":/rec/img/board1.jpg"));
    }
    else if(ui2->getUi()->radioButton_2->isChecked()){
        painter.drawImage(QRect(MARGIN,MARGIN,AREA_COL*SIZE,AREA_ROW*SIZE), QImage(":/rec/img/board2.jpg"));
   }
    else if(ui2->getUi()->radioButton_3->isChecked()){
        painter.drawImage(QRect(MARGIN,MARGIN,AREA_COL*SIZE,AREA_ROW*SIZE), QImage(":/rec/img/board3.jpg"));
   }
    else if(ui2->getUi()->radioButton_4->isChecked()){
        painter.drawImage(QRect(MARGIN,MARGIN,AREA_COL*SIZE,AREA_ROW*SIZE), QImage(":/rec/img/board4.jpg"));
    }
    else if(ui2->getUi()->radioButton_5->isChecked()){
       painter.drawImage(QRect(MARGIN,MARGIN,AREA_COL*SIZE,AREA_ROW*SIZE), QImage(":/rec/img/board5.jpg"));
   }

    SetOptions *ui4 = new SetOptions();


    //Rysowanie bossa

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawImage(QRect(MARGIN+BossPoint1.x()*SIZE,MARGIN+BossPoint1.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/boss4.png"));
    painter.drawImage(QRect(MARGIN+BossPoint2.x()*SIZE,MARGIN+BossPoint2.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/boss3.png"));
    painter.drawImage(QRect(MARGIN+BossPoint3.x()*SIZE,MARGIN+BossPoint3.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/boss1.png"));
    painter.drawImage(QRect(MARGIN+BossPoint4.x()*SIZE,MARGIN+BossPoint4.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/boss2.png"));

    //painter.drawRect(MARGIN+BossPoint1.x()*SIZE,MARGIN+BossPoint1.y()*SIZE,SIZE,SIZE);
   // painter.drawRect(MARGIN+BossPoint2.x()*SIZE,MARGIN+BossPoint2.y()*SIZE,SIZE,SIZE);
   // painter.drawRect(MARGIN+BossPoint3.x()*SIZE,MARGIN+BossPoint3.y()*SIZE,SIZE,SIZE);
   // painter.drawRect(MARGIN+BossPoint4.x()*SIZE,MARGIN+BossPoint4.y()*SIZE,SIZE,SIZE);


    //Rysowanie przeszkod
    if(ui4->getUi()->checkBox->isChecked())
  {

      if(level==1){
      }

      else if(level == 2){


        painter.drawImage(QRect(MARGIN+BarierPoint.x()*SIZE,MARGIN+BarierPoint.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
        painter.drawImage(QRect(MARGIN+BarierPoint0.x()*SIZE,MARGIN+BarierPoint0.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));

        if(((snake.front().x() == BarierPoint.x()) && (snake.front().y() == BarierPoint.y())) || ((snake.front().x() == BarierPoint0.x()) && (snake.front().y() == BarierPoint0.y()))){
            GameOver();
        }

    }
    else if(level==3 || level == 4){

          painter.drawImage(QRect(MARGIN+BarierPoint.x()*SIZE,MARGIN+BarierPoint.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint0.x()*SIZE,MARGIN+BarierPoint0.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint1.x()*SIZE,MARGIN+BarierPoint1.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));

        if(((snake.front().x() == BarierPoint.x()) && (snake.front().y() == BarierPoint.y())) || ((snake.front().x() == BarierPoint0.x()) && (snake.front().y() == BarierPoint0.y())) || ((snake.front().x() == BarierPoint1.x()) && (snake.front().y() == BarierPoint1.y()))){
            GameOver();
        }
    }
    else if(level==5 || level == 6){

          painter.drawImage(QRect(MARGIN+BarierPoint.x()*SIZE,MARGIN+BarierPoint.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint0.x()*SIZE,MARGIN+BarierPoint0.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint1.x()*SIZE,MARGIN+BarierPoint1.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));

          painter.drawImage(QRect(MARGIN+BarierPoint2.x()*SIZE,MARGIN+BarierPoint2.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint3.x()*SIZE,MARGIN+BarierPoint3.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint4.x()*SIZE,MARGIN+BarierPoint4.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));



        if(((snake.front().x() == BarierPoint.x()) && (snake.front().y() == BarierPoint.y())) || ((snake.front().x() == BarierPoint0.x()) && (snake.front().y() == BarierPoint0.y())) || ((snake.front().x() == BarierPoint1.x()) && (snake.front().y() == BarierPoint1.y())) || ((snake.front().x() == BarierPoint2.x()) && (snake.front().y() == BarierPoint2.y())) || ((snake.front().x() == BarierPoint3.x()) && (snake.front().y() == BarierPoint3.y())) || ((snake.front().x() == BarierPoint4.x()) && (snake.front().y() == BarierPoint4.y()))){
            GameOver();
        }
    }
    else if(level==7 || level== 8){

          painter.drawImage(QRect(MARGIN+BarierPoint.x()*SIZE,MARGIN+BarierPoint.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint0.x()*SIZE,MARGIN+BarierPoint0.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint1.x()*SIZE,MARGIN+BarierPoint1.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));

          painter.drawImage(QRect(MARGIN+BarierPoint2.x()*SIZE,MARGIN+BarierPoint2.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint3.x()*SIZE,MARGIN+BarierPoint3.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint4.x()*SIZE,MARGIN+BarierPoint4.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint5.x()*SIZE,MARGIN+BarierPoint5.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));


        if(((snake.front().x() == BarierPoint.x()) && (snake.front().y() == BarierPoint.y())) || ((snake.front().x() == BarierPoint0.x()) && (snake.front().y() == BarierPoint0.y())) || ((snake.front().x() == BarierPoint1.x()) && (snake.front().y() == BarierPoint1.y())) || ((snake.front().x() == BarierPoint2.x()) && (snake.front().y() == BarierPoint2.y())) || ((snake.front().x() == BarierPoint3.x()) && (snake.front().y() == BarierPoint3.y())) || ((snake.front().x() == BarierPoint4.x()) && (snake.front().y() == BarierPoint4.y())) || ((snake.front().x() == BarierPoint5.x()) && (snake.front().y() == BarierPoint5.y()))){
            GameOver();
        }
    }

    else{

          painter.drawImage(QRect(MARGIN+BarierPoint.x()*SIZE,MARGIN+BarierPoint.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint0.x()*SIZE,MARGIN+BarierPoint0.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint1.x()*SIZE,MARGIN+BarierPoint1.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));

          painter.drawImage(QRect(MARGIN+BarierPoint2.x()*SIZE,MARGIN+BarierPoint2.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint3.x()*SIZE,MARGIN+BarierPoint3.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint4.x()*SIZE,MARGIN+BarierPoint4.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));
          painter.drawImage(QRect(MARGIN+BarierPoint5.x()*SIZE,MARGIN+BarierPoint5.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/brick.png"));


          if(((snake.front().x() == BarierPoint.x()) && (snake.front().y() == BarierPoint.y())) || ((snake.front().x() == BarierPoint0.x()) && (snake.front().y() == BarierPoint0.y())) || ((snake.front().x() == BarierPoint1.x()) && (snake.front().y() == BarierPoint1.y())) || ((snake.front().x() == BarierPoint2.x()) && (snake.front().y() == BarierPoint2.y())) || ((snake.front().x() == BarierPoint3.x()) && (snake.front().y() == BarierPoint3.y())) || ((snake.front().x() == BarierPoint4.x()) && (snake.front().y() == BarierPoint4.y())) || ((snake.front().x() == BarierPoint5.x()) && (snake.front().y() == BarierPoint5.y()))){
              GameOver();
          }
    }
}

    //Rysowanie strzału bossa
    for(int i=0; i<weapon.size(); i++){
        painter.drawImage(QRect(MARGIN+weapon.front().x()*SIZE,MARGIN+weapon.front().y()*SIZE-2,SIZE,SIZE+5), QImage(":/rec/img/fireball.png"));
    }

    //Rysowanie głowy węża.
    for(int j=0;j<snake.size();j++){
         if(snake[j].x()<20){
             if(dir==RIGHT){
                 painter.drawImage(QRect(MARGIN+snake.front().x()*SIZE,MARGIN+snake.front().y()*SIZE-2,SIZE,SIZE+5), QImage(":/rec/img/headRight.png"));
             }
             else if(dir==DOWN){
                 painter.drawImage(QRect(MARGIN+snake.front().x()*SIZE-2,MARGIN+snake.front().y()*SIZE,SIZE+5,SIZE), QImage(":/rec/img/headDown.png"));
             }
             else if(dir==UP){
                 painter.drawImage(QRect(MARGIN+snake.front().x()*SIZE-2,MARGIN+snake.front().y()*SIZE,SIZE+5,SIZE), QImage(":/rec/img/headUp.png"));
             }
             else if(dir==LEFT){
                 painter.drawImage(QRect(MARGIN+snake.front().x()*SIZE,MARGIN+snake.front().y()*SIZE-2,SIZE,SIZE+5), QImage(":/rec/img/headLeft.png"));
             }
         }
   }


    QPen pen(QColor(79,127,108), 5);
    painter.setPen(pen);
    painter.setBrush(QColor(99,160,135));

    //Rysowanie węża

    for(int i=1;i<snake.size();i++){
        if(snake[i].x()<20){
            painter.drawRect(MARGIN+snake[i].x()*SIZE,MARGIN+snake[i].y()*SIZE,SIZE,SIZE);
        }
    }


    if((foodPoint.x() == BarierPoint.x() && foodPoint.y() == BarierPoint.y()) || ((foodPoint.x() == BarierPoint0.x()) && (foodPoint.y() == BarierPoint0.y()))
        || ((foodPoint.x() == BarierPoint1.x()) && (foodPoint.y() == BarierPoint1.y())) || ((foodPoint.x() == BarierPoint2.x()) && (foodPoint.y() == BarierPoint2.y()))
        || ((foodPoint.x() == BarierPoint3.x()) && (foodPoint.y() == BarierPoint3.y())) || ((foodPoint.x() == BarierPoint4.x()) && (foodPoint.y() == BarierPoint4.y()))
        || ((foodPoint.x() == BarierPoint5.x()) && (foodPoint.y() == BarierPoint5.y()))){
        GenerateFood();
    }
    else{
        painter.drawImage(QRect(MARGIN+foodPoint.x()*SIZE,MARGIN+foodPoint.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/food.png"));
    }



    SetOptions *ui3 = new SetOptions();

    if(ui3->getUi()->checkBox_3->isChecked()){

        if((foodPoint2.x() == BarierPoint.x() && foodPoint2.y() == BarierPoint.y()) || ((foodPoint2.x() == BarierPoint0.x()) && (foodPoint2.y() == BarierPoint0.y()))
                || ((foodPoint2.x() == BarierPoint1.x()) && (foodPoint2.y() == BarierPoint1.y())) || ((foodPoint2.x() == BarierPoint2.x()) && (foodPoint2.y() == BarierPoint2.y()))
                || ((foodPoint2.x() == BarierPoint3.x()) && (foodPoint2.y() == BarierPoint3.y())) || ((foodPoint2.x() == BarierPoint4.x()) && (foodPoint2.y() == BarierPoint4.y()))
                || ((foodPoint2.x() == BarierPoint5.x()) && (foodPoint2.y() == BarierPoint5.y()))){
                if(score>1){
                    GenerateFood2();
                }
            }

                 else{
                    if(score%3==0 && score>1){
                        if(random==0){
                           painter.drawImage(QRect(MARGIN+foodPoint2.x()*SIZE,MARGIN+foodPoint2.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/fruit2.png"));
                        }
                        if(random==1){
                          painter.drawImage(QRect(MARGIN+foodPoint2.x()*SIZE,MARGIN+foodPoint2.y()*SIZE,SIZE,SIZE), QImage(":/rec/img/fruit3.png"));
                        }
                    }
                 }
    }

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",14));
    painter.drawText(MARGIN*2+AREA_COL*SIZE,MARGIN+1*SIZE,"Level: "+QString::number(level));
    painter.drawText(MARGIN*3+AREA_COL*SIZE,MARGIN+2*SIZE,"Score: "+QString::number(score));
    painter.drawText(MARGIN*4+AREA_COL*SIZE,MARGIN+3*SIZE,"Speed: "+QString::number(SPEED));
    if(BossPoint1.x() > 0 && BossPoint1.x() <20){
        painter.drawText(MARGIN*5+AREA_COL*SIZE,MARGIN+4*SIZE,"BossHealth: "+QString::number(bosshealth));
        painter.drawText(MARGIN*6+AREA_COL*SIZE,MARGIN+5*SIZE,"Health: "+QString::number(snakedie-1));
    }
    delete ui2;
    delete ui3;
    delete ui4;
}
/**
  W funkcji keyPressEvent jest całe nasze sterowanie w grze. Strzałki poruszanie sie wężem, klawisz P pauza gry, ESC powrót do menu glownego. Zaimplementowane również dźwięki poruszania sie węża.

  \image html keypress.png
  
*/
void game::keyPressEvent(QKeyEvent *event)
{

    QMediaPlayer *gora = new QMediaPlayer();
    QMediaPlayer *dol = new QMediaPlayer();
    QMediaPlayer *lewo = new QMediaPlayer();
    QMediaPlayer *prawo = new QMediaPlayer();

    gora->setMedia(QUrl("qrc:/rec/sound/up.mp3"));
    dol->setMedia(QUrl("qrc:/rec/sound/down.mp3"));
    lewo->setMedia(QUrl("qrc:/rec/sound/left.mp3"));
    prawo->setMedia(QUrl("qrc:/rec/sound/right.mp3"));

    SetOptions *mute = new SetOptions();

    if(mute->getUi()->checkBox_4->isChecked()){
        gora->setMuted(true);
        dol->setMuted(true);
        lewo->setMuted(true);
        prawo->setMuted(true);
    }

    switch(event->key())
    {
    case Qt::Key_Up:
        gora->play();
            dir=UP;
        break;
    case Qt::Key_Down:
        dol->play();
            dir=DOWN;
        break;
    case Qt::Key_Left:
        lewo->play();
            dir=LEFT;
        break;
    case Qt::Key_Right:
        prawo->play();
            dir=RIGHT;
        break;
    case Qt::Key_P:
        PauseResumeGame();
        break;
    case Qt::Key_Escape:
        music->setMuted(true);
        gameTimer->stop();
        game::close();
        MainWindow *mainwidow = new MainWindow();
        mainwidow->show();
    }
    delete mute;
}
/**
	Funkcja odpowiada za sprawdzenie czy przegralismy gre. Jeśli tak to zwaraca true, jeśli nie to false.
	
	\image html is_game_over.png
*/
bool game::IsGameOver(){

    int x=snake.front().x();
    int y=snake.front().y();

    if(x<0||x>AREA_COL-1||y<0||y>AREA_ROW-1)
        return true;
    for(int i=3;i<snake.size();i++)
        if(snake[i]==snake.front())
            return true;
    return false;
}
/**
	Funkcja odpowiedzialna za poruszanie sie pocisku, który wystrzeliwuje boss. Działa na bazie listy.
	
	\image html weapon_update.png
 
*/
void game::WeaponUpdate(){


    if(level>3){

        QMediaPlayer *fireball = new QMediaPlayer();
        SetOptions *ui3 = new SetOptions();
        fireball->setMedia(QUrl("qrc:/rec/sound/fireball.mp3"));
        if(ui3->getUi()->checkBox_4->isChecked()){
            fireball->setMuted(true);
        }
        if(bosshealth==0){
            fireball->setMuted(true);
        }
        if(weapon.front().x()>19){
            weapon.front().setX(BossPoint1.x());
            weapon.front().setY(BossPoint1.y());
            weaponstatus = 1+rand()%4;
                fireball->play();
        }

        else if(weapon.front().x()<0){
            weapon.front().setX(BossPoint1.x());
            weapon.front().setY(BossPoint1.y());
            weaponstatus = 1+rand()%4;
                fireball->play();
        }

        else if(weapon.front().y()>13){
            weapon.front().setX(BossPoint1.x());
            weapon.front().setY(BossPoint1.y());
            weaponstatus = 1+rand()%4;
                fireball->play();
        }

        else if(weapon.front().y()<0){
            weapon.front().setX(BossPoint1.x());
            weapon.front().setY(BossPoint1.y());
            weaponstatus = 1+rand()%4;
                fireball->play();
        }


        //up
        if(weaponstatus==1){
        weapon.push_front(QPoint(weapon.front().x(), weapon.front().y()+1));
        }
        //down
        else if(weaponstatus==2){
        weapon.push_front(QPoint(weapon.front().x(), weapon.front().y()-1));
        }
        //left
        else if(weaponstatus==3){
        weapon.push_front(QPoint(weapon.front().x()-1, weapon.front().y()));
        }
        //right
        else if(weaponstatus==4){
        weapon.push_front(QPoint(weapon.front().x()+1, weapon.front().y()));
        }


        if((weapon.front().x() == snake.front().x()) && (weapon.front().y() == snake.front().y())){
            GameOver();
        }

        for(int i = 0; i<snake.length();i++){
               if(weapon.front().x() == snake[i].x() && weapon.front().y() == snake[i].y()){

                   QMediaPlayer *explosion = new QMediaPlayer;
                   if(ui3->getUi()->checkBox_4->isChecked()){
                       explosion->setMuted(true);
                   }
                   explosion->setMedia(QUrl("qrc:/rec/sound/explosion.mp3"));
                   explosion->play();
                   snakedie--;
                   weapon.front().setX(BossPoint1.x());
                   weapon.front().setY(BossPoint1.y());
                }

        }

        if(snakedie<2){
            GameOver();
        }
     delete ui3;
    }

}
/**
	Funkcja SnakeUpdate odpowiedzialna jest za poruszanie się wężem. Całość działa na bazie listy.
	Obsługa kolizji węża z bossem oraz z owocami. Opisane też jest co ma sie wykonac po każdej kolizji węża z bosem. 
	
\image html snake_update.png
*/
void game::SnakeUpdate(){


         SetOptions *ui3 = new SetOptions();

         if(ui3->getUi()->checkBox_2->isChecked()==false){

            switch(dir)
            {
            case UP:
                snake.push_front(QPoint(snake.front().x(),snake.front().y()-1));
                break;
            case DOWN:
                snake.push_front(QPoint(snake.front().x(),snake.front().y()+1));
                break;
            case LEFT:
                snake.push_front(QPoint(snake.front().x()-1,snake.front().y()));
                break;
            case RIGHT:
                snake.push_front(QPoint(snake.front().x()+1,snake.front().y()));
                break;
            }
         }

         else
         {
            switch(dir)
            {
                case UP:
                    snake.push_front(QPoint(snake.front().x(),snake.front().y()-1));
                    if(snake.front().y() < 0){
                        snake.front().setY(12);
                    }
                    break;
                case DOWN:
                    snake.push_front(QPoint(snake.front().x(),snake.front().y()+1));
                    if(snake.front().y() > 12 ){
                        snake.front().setY(0);
                    }
                    break;
                case LEFT:
                    snake.push_front(QPoint(snake.front().x()-1,snake.front().y()));
                    if(snake.front().x() < 0 ){
                        snake.front().setX(19);
                    }
                    break;
                case RIGHT:
                    snake.push_front(QPoint(snake.front().x()+1,snake.front().y()));
                    if(snake.front().x() > 19 ){
                        snake.front().setX(0);
                    }
                    break;
                }

         }


    if(((snake.front().x()) == (foodPoint.x()) && ((snake.front().y()) == (foodPoint.y()))) || (((snake.front().x()) == (foodPoint2.x())) && ((snake.front().y()) == (foodPoint2.y())))){



        QMediaPlayer *eat = new QMediaPlayer();

        if(ui3->getUi()->checkBox_4->isChecked()){
            eat->setMuted(true);
        }

        eat->setMedia(QUrl("qrc:/rec/sound/eat.mp3"));
        eat->play();
        score+=1;


        if(snake.front().x() == foodPoint.x() && snake.front().y() == foodPoint.y()){
            GenerateFood();
        }

        if(snake.front().x() == foodPoint2.x() && snake.front().y() == foodPoint2.y()){
             if(random==1 && snake.size()>5){
                 snake.pop_back();
                 snake.pop_back();
                 snake.pop_back();
                 snake.pop_back();
                 snake.pop_back();
             }
             else if(random == 0 && SPEED>50){
                 SPEED-=5;
             }
             foodPoint2.setX(50);
             foodPoint2.setY(50);
         }

        if(score%3==0 && score>1){
            GenerateFood2();
            Fruit();
        }
        if (level>8 && bosshealth ==0){
        gameTimer2->stop();
        }

        if(!(score%3==0)){
            foodPoint2.setX(50);
            foodPoint2.setY(50);
        }

        if(score%5 == 0 && score != 0 && SPEED>30){
            level+=1;
            if(level==2){
                GenerateBarier();
            }
            if(level==4){
                GenerateBoss();
            }
            if(level==5){
                GenerateBarier1();
            }
            if(level==8){
                GenerateBoss();
                snakedie=7;
                bosshealth=8;
                WEAPONSPEED = 150;
            }
            SPEED -=5;
            gameTimer->start(SPEED);
        }
    }
    else{
        snake.pop_back();
    }


    if(((snake.front().x()) == (BossPoint1.x()) && ((snake.front().y()) == (BossPoint1.y()))) || (((snake.front().x()) == (BossPoint2.x())) && ((snake.front().y()) == (BossPoint2.y())))
      || (((snake.front().x()) == (BossPoint3.x())) && ((snake.front().y()) == (BossPoint3.y()))) || (((snake.front().x()) == (BossPoint4.x())) && ((snake.front().y()) == (BossPoint4.y())))){

        QMediaPlayer *boss = new QMediaPlayer();

        if(ui3->getUi()->checkBox_4->isChecked()){
            boss->setMuted(true);
        }
        boss->setMedia(QUrl("qrc:/rec/sound/boss_sound.mp3"));
        boss->play();


        GenerateBoss();
        bosshealth-=1;

        if(bosshealth <1){
            weapon.front().setX(500);
            weapon.front().setY(500);
            BossPoint1.setX(500);
            BossPoint1.setY(500);
            BossPoint2.setX(500);
            BossPoint2.setY(500);
            BossPoint3.setX(500);
            BossPoint3.setY(500);
            BossPoint4.setX(500);
            BossPoint4.setY(500);
        }
        if(bosshealth==0){

        }
    }


    if(IsGameOver()){
        GameOver();
    }
    update();
    delete ui3;


}
/**
	 Funkcja GameOver wywołuje okno przegrania gry, zatrzymuje timery. 
	 \image html game_over.png
*/
void game::GameOver()
{
    QMediaPlayer *crash = new QMediaPlayer();
    SetOptions *mute = new SetOptions();
    if(mute->getUi()->checkBox_4->isChecked()){
        crash->setMuted(true);
    }

    crash->setMedia(QUrl("qrc:/rec/sound/crash.mp3"));
    crash->play();
    gameTimer->stop();
    gameTimer2->stop();
    music->setMuted(true);
    gameover *ui5 = new gameover();
    ui5->getUi()->label_2->setNum(score);
    ui5->exec();
    game::close();
    delete mute;
    delete crash;
}
/**
	 Funkcja odpowiedzialna za pauzowanie gry.
	 \image html pause.png
*/
void game::PauseResumeGame()
{
    if(!isPause)
    {
        isPause=!isPause;
        gameTimer->stop();
        gameTimer2->stop();
        music->pause();
    }
    else
    {
        isPause=!isPause;
        gameTimer->start(SPEED);
        gameTimer2->start(WEAPONSPEED);
        music->play();
    }
}


