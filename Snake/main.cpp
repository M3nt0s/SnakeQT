/**
\mainpage Temat projektu: Snake w QT

<h2><b>Politechnika Swietokrzyska</b></h2>

<h2><b>Wydzial Elektrotechniki, Automatyki i Informatyki </b></h2>

<h3>Kierunek: Informatyka</h3>

<b>Studia: Stacjonarne I stopnia</b>

<b>Grupa: 2ID15B</b>

<b>Tworzyli: Pawel Zacharz, Dominik Latas, Karol Mik</b>

//Menu główne w naszej grze Snake.
\image html glowna1.png
//Zrzut ekranu w trakcie rozgrywki. Rozgrywka polega na zbieraniu owoców, co dwa zjedzone owoce pojawiają sie kolejne, dodatkowe owoce, które mają
dodatkowe wlasciwosci skracanie węża, przyśpieszenie. Na kolejny poziom przechodzimy przez zebranie 5 owoców.
\image html glowna.png
// Na 4 i 8 poziomie pojawia sie boss, który strzela do nas pociskami(kule ognia). Walka z bossem wyglada tak, że po ugryzieniu go pojawia sie w nowym miejsca kontynuując strzelanie w kierunku węża.
\image html boss.png
*/

#include "mainwindow.h"
#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
