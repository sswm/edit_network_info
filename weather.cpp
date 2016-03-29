#include "weather.h"
#include "ui_weather.h"

Weather::Weather(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Weather)
{
    ui->setupUi(this);
}

Weather::~Weather()
{
    delete ui;
}
