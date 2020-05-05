#include "gameover.h"
#include "ui_gameover.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"


gameover::gameover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
}


gameover::~gameover()
{
    delete ui;
}


/**
	Guzik który po wklinięciu otwiera menu główne.
	
	\image html pusz2batongameover.png

*/

void gameover::on_pushButton_clicked()
{
    hide();
    MainWindow *mainwidow = new MainWindow();
    mainwidow->show();

}

/**
	Guzik który po wklinięciu zamykana jest gra.
	
	\image html puszbatongameover.png

*/
void gameover::on_pushButton_2_clicked()
{
    exit(0);
}

