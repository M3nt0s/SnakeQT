#include "boards.h"
#include "ui_boards.h"
#include "game.h"
#include "setoptions.h"
#include "ui_setoptions.h"
#include <QSettings>
#include <QMediaPlayer>

boards::boards(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::boards)
{
    ui->setupUi(this);
    LoadSettings();
}

boards::~boards()
{
    delete ui;
}

/** 
Funkcja odczytujaca ktora plansza1, 2, itd zostala wybrana w opcjach.

	*Ta funkcja odczytuje stan checkboxów z pliku systemowego z wykorzystaniem biblioteki QSettings.
\image html loadsettings.png
*/

void boards::LoadSettings()
{
    QSettings setting("Snake","Plansze");
    setting.beginGroup("Opcje");
    ui->radioButton->setChecked(setting.value("plansza1",false).toBool());
    ui->radioButton_2->setChecked(setting.value("plansza2",false).toBool());
    ui->radioButton_3->setChecked(setting.value("plansza3",false).toBool());
    ui->radioButton_4->setChecked(setting.value("plansza4",false).toBool());
    ui->radioButton_5->setChecked(setting.value("plansza5",false).toBool());
    setting.endGroup();
}

/**
Zapis ustawien w wyborze planszy
		*Ta funkcja sprawdza stan checkboxów i zapisuje ich stan do pliku systemowego z uzyciem biblioteki QSettings.
\image html savesettings.png
*/
void boards::SaveSettings()
{
    QSettings setting("Snake","Plansze");
    setting.beginGroup("Opcje");
    setting.setValue("plansza1", ui->radioButton->isChecked());
    setting.setValue("plansza2", ui->radioButton_2->isChecked());
    setting.setValue("plansza3", ui->radioButton_3->isChecked());
    setting.setValue("plansza4", ui->radioButton_4->isChecked());
    setting.setValue("plansza5", ui->radioButton_5->isChecked());
    setting.endGroup();
}


/**
Zamykanie okna zmiany tła bez zatwierdzana zmian

\image html closesettings.png
*/
void boards::on_pushButton_2_clicked()
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
/**
Zamykanie okna zmiany tła z zatwierdzeniem zmian

\image html closesettingssave.png
*/
void boards::on_pushButton_clicked()
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
