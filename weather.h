#ifndef WEATHER_H
#define WEATHER_H

#include <QMainWindow>

namespace Ui {
class Weather;
}

class Weather : public QMainWindow
{
    Q_OBJECT

public:
    explicit Weather(QWidget *parent = 0);
    ~Weather();

private:
    Ui::Weather *ui;
};

#endif // WEATHER_H
