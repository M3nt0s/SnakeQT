#ifndef BOARDS_H
#define BOARDS_H

#include <QDialog>
#include "game.h"
#include <QObject>

namespace Ui {
class boards;
}

class boards : public QDialog
{
    Q_OBJECT

public:
    explicit boards(QWidget *parent = nullptr);
    ~boards();

    Ui::boards* getUi(){
        return this->ui;
    }

private slots:

    void LoadSettings();

    void SaveSettings();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::boards *ui;
};

#endif // BOARDS_H
