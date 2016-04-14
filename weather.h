#ifndef WEATHER_H
#define WEATHER_H

#include <QMainWindow>
#include <QTimer>
#include <QTimer>
#include <QDateTime>
#include <QLineEdit>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

#include "common.h"






namespace Ui {
class Weather;
}

class Weather : public QMainWindow
{
    Q_OBJECT
public:
    QTimer *showTimer;
    QLineEdit *lineEdit_Num[MAX_WEATHER_ID];
    QLineEdit *lineEdit_Country[MAX_WEATHER_ID];
    QLineEdit *lineEdit_City_English[MAX_WEATHER_ID];
    QLineEdit *lineEdit_City_Frechch[MAX_WEATHER_ID];
    QLineEdit *lineEdit_City_German[MAX_WEATHER_ID];
    QLineEdit *lineEdit_City_Italian[MAX_WEATHER_ID];
    QLineEdit *lineEdit_City_Spanish[MAX_WEATHER_ID];
    QLineEdit *lineEdit_Cid[MAX_WEATHER_ID];
    int now_weather_num;
public:
    explicit Weather(QWidget *parent = 0);
    ~Weather();
    void ReadFile(const char *path);
    void DealRadioInfo(int id, QString left_key, QString right_value);
    void RemoveBlank();
private slots:
    void on_pushButton_factory_clicked();

    void on_pushButton_read_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_clear_all_clicked();

    void on_pushButton_add_item_clicked();
    void ShowSystemTime(void);
    void Sort_A_Z(int star_pos, int end_pos);
    void on_pushButton_sort_city_clicked();

    void on_pushButton_sort_country_clicked();
    void Sort_Country_A_Z(void);

private:
    Ui::Weather *ui;
};

#endif // WEATHER_H
