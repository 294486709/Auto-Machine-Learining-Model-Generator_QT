#include "create_mode.h"
#include "ui_create_mode.h"
#include "mainwindow.h"
#include "ctype.h"
#include <string>
#include <vector>
#include <QMessageBox>





using std::vector;
using std::string;


Create_Mode::Create_Mode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_Mode)
{
    ui->setupUi(this);
    change_tab();
}

Create_Mode::~Create_Mode()
{
    delete ui;
}

void Create_Mode::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "EZ Mode"){
        ///show ez box
    }
    else {
        ///show normal box
    }
}

void Create_Mode::on_pushButton_2_clicked()
{
//    MainWindow *MW = new MainWindow();
//    MW->show();
//    this->close();
    ui->Tabls->removeTab(1);


}

void Create_Mode::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == 1){
        //not show
    }
    else {
        //show
    }
}

bool IntorNot(QString target)
{
    int count = 0;
    for (int i=0;i<target.size();i++) {
        if (target[i].isDigit()){
            count ++;
        }
        else if (target[i] == ".") {
            return false;
        }
        else {
            return false;
        }
    }
    if (count == target.size()) {
        return true;
    }
    else {
        return false;
    }
}

bool Create_Mode::NN_EZ_input_check(){
    auto Class_count = ui->CLASS_COUNT->text();
    auto Epoch_count = ui->CLASS_COUNT_2->text();
    auto Num_layer =  ui->NUM_LAYER->text();
    auto Num_neu = ui->NUM_NEU->text();
    bool input_check = true;
    string input_error = "";
    if (!IntorNot(Class_count)) {
        input_error += "Input Error in: Class Count!\n";
        input_check = false;
    }
    if (!IntorNot(Epoch_count)) {
        input_error += "Input Error in: Epoch Count!\n";
        input_check = false;
    }
    if (!IntorNot(Num_layer)) {
        input_error += "Input Error in: Number of Layers!\n";
        input_check = false;
    }
    if (!IntorNot(Num_neu)) {
        input_error += "Input Error in: Number of Neuron in each Layer!";
        input_check = false;
    }
    auto chr = input_error.c_str();
    if (!input_check) {
        QMessageBox::warning(this, tr("Input Error"),tr(chr));
        return false;
    }

    else {
        return true;
    }

}


void Create_Mode::on_pushButton_clicked()
{
    auto Model_type = ui->Model_tpye->currentIndex();
    auto Gen_Mode = ui->Generation_Mode->currentIndex();
    int case_control;
    if (Model_type == 0) {
        if (Gen_Mode == 0) {
            case_control = 0; // NN and expert
        }
        else {
            case_control = 1; // NN and EZ
        }
    }
    else {
        if (Gen_Mode == 0) {
            case_control = 2; // CNN and expert
        }
        else {
            case_control = 3; // CNN and EZ
        }
    }
    switch(case_control) {
        case 0:  //NN and expert
            break;
        case 1: //NN and EZ
            if (!NN_EZ_input_check()) {
                break;
            }
            else {
                //GO ON
            }
        case 2: // CNN and expert
            break;
        case 3: // CNN and EZ
            break;
    }


}

void Create_Mode::on_Model_tpye_currentIndexChanged(int index)
{
    change_tab();
}

void Create_Mode::change_tab() {
    auto Model_type = ui->Model_tpye->currentIndex();
    auto Gen_Mode = ui->Generation_Mode->currentIndex();
    if (Model_type == 0) {
        if (Gen_Mode == 0) { // NN and Expert
            ui->NN_EXP->setEnabled(true);
            ui->NN_EZ->setEnabled(false);
            ui->CNN_EXP->setEnabled(false);
            ui->CNN_EZ->setEnabled(false);
        }
        else { // NN and EZ
            ui->NN_EXP->setEnabled(false);
            ui->NN_EZ->setEnabled(true);
            ui->CNN_EXP->setEnabled(false);
            ui->CNN_EZ->setEnabled(false);
        }
    }
    else {
        if (Gen_Mode == 0) { // CNN and expert
            ui->NN_EXP->setEnabled(false);
            ui->NN_EZ->setEnabled(false);
            ui->CNN_EXP->setEnabled(true);
            ui->CNN_EZ->setEnabled(false);
        }
        else {// CNN and EZ
            ui->NN_EXP->setEnabled(false);
            ui->NN_EZ->setEnabled(false);
            ui->CNN_EXP->setEnabled(false);
            ui->CNN_EZ->setEnabled(true);
        }
    }
}


void Create_Mode::on_Generation_Mode_currentIndexChanged(int index)
{
    change_tab();
}
