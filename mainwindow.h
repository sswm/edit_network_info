#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QScrollArea>

#define FILE_PATH   "url_play_list.txt"
#define FACTORY_FILE_PATH   "factory.txt"


#define MAX_RADIO_ID        1024




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QTimer  *showTimer;
    QLineEdit *lineEdit_Num[MAX_RADIO_ID];
    QLineEdit *lineEdit_Country[MAX_RADIO_ID];
    QLineEdit *lineEdit_Style[MAX_RADIO_ID];
    QLineEdit *lineEdit_Name[MAX_RADIO_ID];
    QLineEdit *lineEdit_Url[MAX_RADIO_ID];

    int now_radio_num;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ReadFile(const char *path);
    void SaveFile(const char *path);
    void DealRadioInfo(int id, QString left_key, QString right_value);
private slots:
    void on_pushButton_factory_clicked();

    void on_pushButton_read_clicked();

    void on_pushButton_save_clicked();
    void ShowSystemTime(void);

    void on_pushButton_clear_clicked();

    void on_pushButton_add_item_clicked();

    void on_pushButton_clear_all_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
