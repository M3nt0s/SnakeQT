#include "setoptions.h"
#include "ui_setoptions.h"
#include <QSettings>
#include <QCheckBox>
#include <QMediaPlayer>
#include <QtCore>
#include <QDebug>
#include <game.h>

SetOptions::SetOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetOptions)
{
    ui->setupUi(this);
    LoadSettings();
}

SetOptions::~SetOptions()
{
    delete ui;
}



/**
	Ta funkcja odczytuje stan checkboxów z pliku systemowego z wykorzystaniem biblioteki QSettings.
	
	\image html loadsettings_setopt.png

*/
void SetOptions::LoadSettings()
{
    QSettings setting("Snake","Tryby");
    setting.beginGroup("Opcje");
    ui->checkBox->setChecked(setting.value("przeszkody",false).toBool());
    ui->checkBox_2->setChecked(setting.value("przechodzenie",false).toBool());
    ui->checkBox_3->setChecked(setting.value("owoce",false).toBool());
    ui->checkBox_4->setChecked(setting.value("sound",false).toBool());
    setting.endGroup();
}


/**
	Ta funkcja zapisuje wybrane opcje do pliku systemowego z użyciem biblioteki QSettings.
	
	\image html savesetting_setopt.png

*/
void SetOptions::SaveSettings()
{
    QSettings setting("Snake","Tryby");
    setting.beginGroup("Opcje");
    setting.setValue("przeszkody", ui->checkBox->isChecked());
    setting.setValue("przechodzenie", ui->checkBox_2->isChecked());
    setting.setValue("owoce", ui->checkBox_3->isChecked());
    setting.setValue("sound", ui->checkBox_4->isChecked());
    setting.endGroup();
}
/**
	Guzik zamykający okno opcji zatwierdzając zmiany.
	
	\image html pushbaton_setopt.png

*/
void SetOptions::on_pushButton_clicked()
{
    QMediaPlayer *pick = new QMediaPlayer();
    SetOptions *mute = new SetOptions();

    if(mute->getUi()->checkBox_4->isChecked()){
        pick->setMuted(true);
    }
    pick->setMedia(QUrl("qrc:/rec/sound/pick.mp3"));
    pick->play();

    SaveSettings();
    hide();
}
/**
	Guzik zamykający okno opcji bez zatwierdzania zmian.
	
	\image html pushbaton2_setopt.png

*/
void SetOptions::on_pushButton_2_clicked()
{
    QMediaPlayer *back = new QMediaPlayer();
    SetOptions *mute = new SetOptions();

    if(mute->getUi()->checkBox_4->isChecked()){
        back->setMuted(true);
    }
    back->setMedia(QUrl("qrc:/rec/sound/back.mp3"));
    back->play();
    hide();
}


