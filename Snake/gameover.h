#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include "game.h"

namespace Ui {
class gameover;
}

class gameover : public QDialog
{
    Q_OBJECT

public:
    explicit gameover(QWidget *parent = nullptr);
    ~gameover();

    Ui::gameover* getUi(){
        return this->ui;
    }


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::gameover *ui;
};

#endif // GAMEOVER_H
