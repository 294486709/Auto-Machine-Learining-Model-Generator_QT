#ifndef CREATE_MODE_H
#define CREATE_MODE_H
#include <string>
#include <QDialog>
#include <vector>


using std::vector;
using std::string;
typedef struct NN_Mission ms1;
struct NN_Mission{
    string Model_type;
    vector<int> neu;
    int Epoch_count;
    int Class_count;
    int Import_Mode;

};

bool IntorNot(QString target);
namespace Ui {
class Create_Mode;
}

class Create_Mode : public QDialog
{
    Q_OBJECT

public:

    explicit Create_Mode(QWidget *parent = nullptr);
    ~Create_Mode();


private slots:
    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

//    bool NN_expert_input_check();

//    bool CNN_expert_input_check();

//    bool CNN_EZ_input_check();

    bool NN_EZ_input_check();

    void on_Model_tpye_currentIndexChanged(int index);

    void on_pushButton_3_clicked();

    void change_tab();

    void on_Generation_Mode_currentIndexChanged(int index);

private:
    Ui::Create_Mode *ui;
};

#endif // CREATE_MODE_H
