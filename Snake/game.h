#ifndef GAME_H
#define GAME_H

#include "boards.h"
#include "ui_boards.h"
#include <QWidget>
#include <QDialog>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>


namespace Ui {
class game;
}


const int SIZE=40;
const int MARGIN=1;
const int AREA_ROW=13;
const int AREA_COL=20;


enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};



class game : public QDialog
{
    Q_OBJECT

public:
    game(QDialog *parent = nullptr);
    ~game();

    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    game(const game&);

public:
    void Fruit();
    void InitGame();
    void PauseResumeGame();
    void GameOver();
    void GenerateFood();
    void GenerateFood2();
    bool IsGameOver();
    void GenerateBarier();
    void GenerateBarier1();
    void GenerateBoss();




private slots:
    void SnakeUpdate();
    void WeaponUpdate();

private:

	///Zmienna typu QTimer, która odpowiada za prędkośc poruszania się węża.
    QTimer *gameTimer;
	///Zmienna typu QTimer, która odpowiada za prędkośc poruszania się pocisku bossa.
    QTimer *gameTimer2;
	///Zmienna typu bool, która odpowiada za to czy gra jest zapauzowana.
    bool isPause;
	


    QMediaPlayer *music = new QMediaPlayer();
    QMediaPlaylist *playlist = new QMediaPlaylist();

	///Zmienna typu QPoint odpowiada za współrzędne owoców.
    QPoint foodPoint;
	///Zmienna typu QPoint odpowiada za współrzędne owoców dodatkowych.
    QPoint foodPoint2;
	///Zmienne typu QPoint odpowiedzialne za współrzędne barier.
    QPoint BarierPoint;
	QPoint BarierPoint0;
    QPoint BarierPoint1;
    QPoint BarierPoint2;
    QPoint BarierPoint3;
    QPoint BarierPoint4;
    QPoint BarierPoint5;
	///Zmienne typu QPoint odpowiedzialne za współrzędne bosa.
    QPoint BossPoint1;
    QPoint BossPoint2;
    QPoint BossPoint3;
    QPoint BossPoint4;
	///Lista na której opiera się działanie węża.
    QList<QPoint> snake;
	///Lista na której opiera się poruszanie pocisku.
    QList<QPoint> weapon;
	///Kierunek w którym patrzy wąż, jest zmieniany przez klawisze strzałek.
    Direction dir;
	/// Zmienna odpowiedzialna za punkty w grze
    int score;
	//Zmienna która odpowiada za to czy wąż został uderzony prosto w głowę. Jeśli został uderzony przyjmuje wartość zero i gra kończy się.
    int snakedie;
	/// Zmienna odpowiedzialna za level rozgrywki.
    int level;
/// Zmienna określająca prędkość początkowa węża.
    int SPEED;
	/// Zmienna określająca prędkość początkową pocisku bossa.
    int WEAPONSPEED;
	/// Zmienna przechowująca informację w którą strone wystrzeliwany jest pocisk bosa.
    int weaponstatus;
	///Zmienna która przechowuje wynik w zależności od którego rysuje się ananas lub winogron..
    int random;
	///Zmienna która przechowuje ilość życia bossa.
    int bosshealth;
	
    Ui::game *ui;
};

#endif // GAME_H
