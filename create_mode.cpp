#include "create_mode.h"
#include "ui_create_mode.h"
#include "mainwindow.h"
#include "ctype.h"
#include <string>
#include <vector>
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <fstream>

void pure_NN_generate(NN_Mission NNM);


using std::ofstream;
using std::vector;
using std::string;
QStringList GFiles = {};

Create_Mode::Create_Mode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_Mode)
{
    ui->setupUi(this);
    change_tab();
    combobox3_check();
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
    MainWindow *MW = new MainWindow();
    MW->show();
    this->close();



}
void Create_Mode::combobox3_check() {
    int arg1 = ui->checkBox->checkState();
    if (arg1 == 2){
        ui->label_6->setEnabled(false);
        ui->CLASS_COUNT->setEnabled(false);
        ui->label_29->setEnabled(false);
        ui->CLASS_COUNT_5->setEnabled(false);
        ui->label_17->setEnabled(false);
        ui->File_Name_2->setEnabled(false);
    }
    else {
        ui->label_6->setEnabled(true);
        ui->CLASS_COUNT->setEnabled(true);
        ui->label_29->setEnabled(true);
        ui->CLASS_COUNT_5->setEnabled(true);
        ui->label_17->setEnabled(true);
        ui->File_Name_2->setEnabled(true);
    }
}

void Create_Mode::on_checkBox_stateChanged(int arg1)
{
    combobox3_check();
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
        if (GFiles.size()<2 and ui->comboBox_3->currentIndex()!=0 ) {
            QMessageBox::warning(this, tr("Input Error"),tr("Import File Error!"));
            return false;
        }
        return true;
    }

}


void Create_Mode::on_pushButton_clicked()
{   if (ui->NUM_LAYER->text().size() == 0) {ui->NUM_LAYER->setText(ui->NUM_LAYER->placeholderText());}
    if (ui->NUM_NEU->text().size() == 0) {ui->NUM_NEU->setText(ui->NUM_NEU->placeholderText());}
    if (ui->CLASS_COUNT->text().size() == 0) {ui->CLASS_COUNT->setText(ui->CLASS_COUNT->placeholderText());}
    if (ui->CLASS_COUNT_2->text().size() == 0) {ui->CLASS_COUNT_2->setText(ui->CLASS_COUNT_2->placeholderText());}
    if (ui->File_Name->text().size() == 0) {ui->File_Name->setText(ui->File_Name->placeholderText());}
    if (ui->CLASS_COUNT_5->text().size() == 0) {ui->CLASS_COUNT_5->setText(ui->CLASS_COUNT_5->placeholderText());}
    if (ui->File_Name_2->text().size() == 0) {ui->File_Name_2->setText(ui->File_Name_2->placeholderText());}
    //if (ui->->text().size() == 0) {ui->NUM_LAYER->setText(ui->NUM_LAYER->placeholderText());}
    if (NN_EZ_input_check()) {
        int Num_layer = ui->NUM_LAYER->text().toInt();
        int batch_size = 100;
        int Num_neu = ui->NUM_NEU->text().toInt();
        int Num_epoch = ui->CLASS_COUNT_2->text().toInt();
        int Num_class = ui->CLASS_COUNT->text().toInt();
        int Import_Mode = ui->comboBox_3->currentIndex();
        int Sample_size = ui->CLASS_COUNT_5->text().toInt();
        string File_Name = ui->File_Name->text().toStdString();
        string activation = "nn.relu";
        string Read_File_Name = ui->File_Name_2->text().toStdString();
        bool auto_dataset = ui->checkBox->checkState();
        vector<string> load_files = {};
        vector<string> act = {};
        vector<int> ners = {};
        NN_Mission EZ_NN_MISSION;
        EZ_NN_MISSION.Model_type = "NN_EZ";
        EZ_NN_MISSION.Optimizer = "Adam";
        EZ_NN_MISSION.Learning_rate = 0.001;
        EZ_NN_MISSION.Epoch_count = Num_epoch;
        EZ_NN_MISSION.Class_count = Num_class;
        EZ_NN_MISSION.Import_Mode = Import_Mode;
        EZ_NN_MISSION.Auto_Dataset = auto_dataset;
        EZ_NN_MISSION.Sample_Size = Sample_size;
        EZ_NN_MISSION.File_name = File_Name;

        EZ_NN_MISSION.Batch_size = batch_size;
        EZ_NN_MISSION.Dataset_File_Name = Read_File_Name;
        if (Import_Mode != 0) {
            for (int i=0;i<GFiles.size();i++) {
                load_files.push_back(GFiles[i].toStdString());
            }
        }
        for (int i=0;i<Num_layer;i++) {
            ners.push_back(Num_neu);
            act.push_back(activation);
        }
        EZ_NN_MISSION.Neu = ners;
        EZ_NN_MISSION.Actvision = act;
        ofstream NN_EZ_JOB;
        NN_EZ_JOB.open("NN_EZ_JOB.txt");
        NN_EZ_JOB << "Model Type:" << EZ_NN_MISSION.Model_type <<"\n";
        NN_EZ_JOB << "Optimizer:" << EZ_NN_MISSION.Optimizer << "\n";
        NN_EZ_JOB << "Learning Rate:" << EZ_NN_MISSION.Learning_rate << "\n";
        NN_EZ_JOB << "Class Count:" << EZ_NN_MISSION.Class_count << "\n";
        NN_EZ_JOB << "Epoch Count:" << EZ_NN_MISSION.Epoch_count << "\n";
        NN_EZ_JOB << "Import Mode:" << EZ_NN_MISSION.Import_Mode << "\n";
        NN_EZ_JOB << "Auto Dataset:" << EZ_NN_MISSION.Auto_Dataset << "\n";
        NN_EZ_JOB << "Sample Size:" << EZ_NN_MISSION.Sample_Size << "\n";
        NN_EZ_JOB << "File Name:" << EZ_NN_MISSION.File_name << "\n";
        NN_EZ_JOB << "Read Script:" << EZ_NN_MISSION.Dataset_File_Name<<"\n";
        NN_EZ_JOB << "Batch Size:" << EZ_NN_MISSION.Batch_size;
        NN_EZ_JOB << "Import Files:";
        for (int i=0;i<load_files.size();i++) {
            NN_EZ_JOB << load_files[i] << "   ";
        }
        NN_EZ_JOB << "\n";
        NN_EZ_JOB << "Neural Network Detail:";
        for (int i=0;i<ners.size();i++) {
            NN_EZ_JOB << ners[i] << "   ";
        }
        NN_EZ_JOB << "\n";
        NN_EZ_JOB << "Activation Function:";
        for (int i=0;i<act.size();i++) {
            NN_EZ_JOB << act[i] << "   ";
        }
        NN_EZ_JOB.close();
        pure_NN_generate(EZ_NN_MISSION);

    }


}

void pure_NN_generate(NN_Mission NNM) {
    ofstream FILE_OUT;
    FILE_OUT.open(NNM.File_name);
    string importfile = NNM.Dataset_File_Name;
    importfile.pop_back();
    importfile.pop_back();
    importfile.pop_back();
    string TAB = "    ";
    FILE_OUT << "# Copyright Yixue Zhang jedzhang@bu.edu\n";
    FILE_OUT << "import tensorflow as tf\n";
    if (NNM.Import_Mode != 0) {FILE_OUT << "from "<<importfile << "import data_set_generation\n";}
    FILE_OUT << "from tqdm import tqdm\n";
    FILE_OUT << "from random import shuffle\n";
    FILE_OUT << "NUM_Class = " << NNM.Class_count<<'\n';
    for (int i=0;i<NNM.Neu.size();i++) {
        FILE_OUT << "NUM_Layer_"<<i<<" = "<<NNM.Neu[i]<<"\n";
    }
    FILE_OUT << "NUM_SAMPLE_SIZE = " << NNM.Sample_Size<<"\n";
    FILE_OUT << "BATCH_SIZE = " << NNM.Batch_size<<"\n";
    FILE_OUT << "NUM_EPOCH = " << NNM.Epoch_count<<"\n";
    FILE_OUT << "\n";
    FILE_OUT << "\n";
    FILE_OUT << "x = tf.placeholder('float', [None, NUM_SAMPLE_SIZE])\n";
    FILE_OUT << "y = tf.placeholder('float', [None, NUM_Class])\n";
    FILE_OUT << "\n";
    FILE_OUT << "\n";
    FILE_OUT << "def nn_model(data):\n";
    FILE_OUT << TAB << "Layer_0 = {'weights':tf.Variable(tf.random_normal([NUM_SAMPLE_SIZE, NUM_Layer_0])),'biases':tf.Variable(tf.random_normal([NUM_Layer_0]))}\n";
    for (int i=1;i<NNM.Neu.size()-1;i++) {
        FILE_OUT << TAB << "Layer_"<<i<<" = {'weights':tf.Variable(tf.random_normal([NUM_Layer_" << i-1  <<", NUM_Layer_"<< i << "])),'biases':tf.Variable(tf.random_normal([NUM_Layer_"<< i <<"]))}\n";
    }
    FILE_OUT << TAB << "Layer_"<<NNM.Neu.size()-1<<" = {'weights':tf.Variable(tf.random_normal([NUM_Layer_" << NNM.Neu.size()-2  <<", NUM_Layer_"<< NNM.Neu.size()-1 << "])),'biases':tf.Variable(tf.random_normal([NUM_Layer_"<< NNM.Neu.size()-1  <<"]))}\n";
    FILE_OUT << TAB << "Out_put = {'weights':tf.Variable(tf.random_normal([NUM_Layer_"<< NNM.Neu.size()-1<<", NUM_Class])),'biases':tf.Variable(tf.random_normal([NUM_Class]))}\n";
    FILE_OUT << "\n";
    FILE_OUT << TAB << "l0 = tf.add(tf.matmul(data, Layer_0['weights']), Layer_0['biases'])\n";
    FILE_OUT << TAB << "l0 = tf." << NNM.Actvision[0] <<"(l0)\n";
    FILE_OUT << "\n";
    for (int i=1;i<NNM.Neu.size()-1;i++) {
        FILE_OUT << TAB << "l" << i << " = tf.add(tf.matmul(l"<<i-1<<", Layer_"<<i<<"['weights']), Layer_"<<i<<"['biases'])\n";
        FILE_OUT << TAB << "l" << i << " = tf." << NNM.Actvision[i] << "(l"<<i<<")\n";
        FILE_OUT << "\n";
    }
    FILE_OUT << TAB << "l" << NNM.Neu.size()-1 << " = tf.add(tf.matmul(l"<< NNM.Neu.size()-2<<", Layer_"<<NNM.Neu.size()-1<<"['weights']), Layer_"<<NNM.Neu.size()-1<<"['biases'])\n";
    FILE_OUT << TAB << "l" << NNM.Neu.size()-1 << " = tf." <<NNM.Actvision[NNM.Neu.size() - 1] << "(l"<<NNM.Neu.size() - 1<<")\n";
    FILE_OUT << TAB << "lout = tf.add(tf.matmul(l" << NNM.Neu.size()-1 <<", Out_put['weights']),Out_put['biases'])\n";
    FILE_OUT << TAB << "\n";
    FILE_OUT << TAB << "return lout\n";
    FILE_OUT << "\n";
    FILE_OUT << "\n";
    FILE_OUT << "def shuffle_batch(xtrain, ytrain):\n";
    FILE_OUT << TAB << "com = list(zip(xtrain, ytrain))\n";
    FILE_OUT << TAB << "shuffle(com)";
    FILE_OUT << TAB << "xtrain[:], ytrain[:] = zip(*com)\n";
    FILE_OUT << TAB << "return xtrain, ytrain\n";
    FILE_OUT << "\n";
    FILE_OUT << "\n";
    FILE_OUT << "def next_batch(idx, xtrain, ytrain):\n";
    FILE_OUT << TAB << "resx = xtrain[idx*BATCH_SIZE:(idx+1)*BATCH_SIZE]\n";
    FILE_OUT << TAB << "resy = ytrain[idx*BATCH_SIZE:(idx+1)*BATCH_SIZE]\n";
    FILE_OUT << TAB << "return resx, resy\n";
    FILE_OUT << "\n";
    FILE_OUT << "\n";

    FILE_OUT.close();

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

void Create_Mode::on_find_file_clicked()
{
    QStringList Files = QFileDialog::getOpenFileNames(
                this,
                tr("Select File"),
                QDir::currentPath(),
                "All Files *.*"
                );
    QString num_files = QString::number(Files.size());
    ui->CLASS_COUNT->setEnabled(true);
    ui->CLASS_COUNT->setText(QString(num_files));
    ui->CLASS_COUNT->setPlaceholderText(QString(num_files));
    ui->CLASS_COUNT->setEnabled(false);
    GFiles = Files;
}
void Create_Mode::combobox3_change() {



}


void Create_Mode::on_comboBox_3_currentIndexChanged(int index)
{

}

void Create_Mode::on_comboBox_3_activated(int index)
{

}
