#include "layer_setting.h"
#include "ui_layer_setting.h"

Layer_Setting::Layer_Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Layer_Setting)
{
    ui->setupUi(this);
}

Layer_Setting::~Layer_Setting()
{
    delete ui;
}
