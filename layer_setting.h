#ifndef LAYER_SETTING_H
#define LAYER_SETTING_H

#include <QDialog>

namespace Ui {
class Layer_Setting;
}

class Layer_Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Layer_Setting(QWidget *parent = nullptr);
    ~Layer_Setting();

private:
    Ui::Layer_Setting *ui;
};

#endif // LAYER_SETTING_H
