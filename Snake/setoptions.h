#ifndef SETOPTIONS_H
#define SETOPTIONS_H

#include <QDialog>
#include <QHoverEvent>

namespace Ui {
class SetOptions;
}

class SetOptions : public QDialog
{
    Q_OBJECT

public:
    explicit SetOptions(QWidget *parent = nullptr);
    ~SetOptions();

    Ui::SetOptions* getUi(){
        return this->ui;
}
private slots:

    void LoadSettings();

    void SaveSettings();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::SetOptions *ui;
};

#endif // SETOPTIONS_H
