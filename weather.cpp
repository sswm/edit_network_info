#include "weather.h"
#include "ui_weather.h"
#include "mainwindow.h"
extern MainWindow *radio;


Weather::Weather(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Weather)
{
    ui->setupUi(this);

    showTimer = new QTimer();
    connect(showTimer, SIGNAL(timeout()), this, SLOT(ShowSystemTime()));
    showTimer->setInterval(1000);
    showTimer->start();

    int i;
    for (i = 0; i < MAX_WEATHER_ID; i++) {
        lineEdit_Num[i] = NULL;
        lineEdit_Country[i] = NULL;
        lineEdit_City[i] = NULL;
        lineEdit_Cid[i] = NULL;
    }
    now_weather_num = 0;
    ReadFile(FILE_PATH);
}

Weather::~Weather()
{
    delete ui;
}

void Weather::DealRadioInfo(int id, QString left_key, QString right_value)
{
    if (id > MAX_WEATHER_ID) {
        qDebug() << "more than " << MAX_WEATHER_ID << "items";
        return;

    }
    if (lineEdit_Num[id] == NULL) {
        lineEdit_Num[id] = new QLineEdit(ui->centralwidget);
        lineEdit_Num[id]->setEnabled(false);
        lineEdit_Num[id]->setGeometry(NUM_START_X, NUM_START_Y + id * INTERVAL_H, NUM_W, FONT_HEIGHT);
    }

    lineEdit_Num[id]->setText(QString::number(id));
    lineEdit_Num[id]->show();

    if (left_key.toLower().compare(W_COUNTRY_STR) == 0) {
        if (lineEdit_Country[id] == NULL) {
            lineEdit_Country[id] = new QLineEdit(ui->centralwidget);
            lineEdit_Country[id]->setGeometry(COUNTRY_START_X, COUNTRY_START_Y + id * INTERVAL_H, COUNTRY_W, FONT_HEIGHT);
        }
        lineEdit_Country[id]->setText(right_value);
        lineEdit_Country[id]->show();
    } else if (left_key.toLower().compare(W_CITY_STR) == 0) {
        if (lineEdit_City[id] == NULL) {
            lineEdit_City[id] = new QLineEdit(ui->centralwidget);
            lineEdit_City[id]->setGeometry(STYLE_START_X, STYLE_START_Y + id * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City[id]->setText(right_value);
        lineEdit_City[id]->show();
    } if (left_key.toLower().compare(W_CITY_CID) == 0) {
        if (lineEdit_Cid[id] == NULL) {
            lineEdit_Cid[id] = new QLineEdit(ui->centralwidget);
            lineEdit_Cid[id]->setGeometry(NAME_START_X, NAME_START_Y + id * INTERVAL_H, NAME_W, FONT_HEIGHT);
        }
        lineEdit_Cid[id]->setText(right_value);
        lineEdit_Cid[id]->show();
    }

}

void Weather::ReadFile(const char *path)
{

    QFile sys_file(path);
    QString line;
    char buf[256];
    int start_pos;
    char *tmp_p;
    QString left_key;
    QString right_value;
    int weather_id = 0;



    if (sys_file.exists()) {
        if (sys_file.open(QIODevice::ReadOnly)) {
            QTextStream stream(&sys_file);
            do {
                line = stream.readLine().trimmed();
                //qDebug() << line;
                tmp_p = line.toLatin1().data();
                if (tmp_p[0] == '#') {
                    qDebug() << "Comment here!";
                    continue;
                }
                start_pos = line.indexOf("=");
                if (start_pos > 0) {
                    left_key = line.left(start_pos);
                    right_value = line.right(line.length() - start_pos - 1);
                    qDebug() << "id~~" << weather_id << "~" <<left_key <<"~~~"<< right_value;
                    if (left_key.compare(W_COUNTRY_STR) == 0) {
                        weather_id++;
                        int central_width;
                        int central_height;
                        central_width = this->width();
                        central_height = this->height();
                        qDebug() << "width:" << central_width;
                        qDebug() << "height:" << central_height;
                        if ((NUM_START_Y + weather_id * INTERVAL_H) > (central_height - INTERVAL_H)) {
                            central_height = NUM_START_Y + weather_id * INTERVAL_H + 50;
                            //radio->setGeometry(0, 0, 1050, 2200);
                            this->resize(QSize(central_width, central_height));
                            //ui->centralwidget->setGeometry(0, 0, central_width, central_height);

                            //tabwidget->resize(central_width,central_height);
                            int wi = NUM_START_Y + weather_id * INTERVAL_H;
                            qDebug() << "weather resize here~~" << central_height << "--now:" << wi;
                            //ui->centralwidget->resize(central_width,central_height);
                            //QScrollArea *scrollArea_t = new QScrollArea;
                            //scrollArea_t->setWidget(radio);
                            //tabwidget->show();

                        } else {
                            central_height = NUM_START_Y + weather_id * INTERVAL_H + 50;
                            this->resize(QSize(central_width, central_height));
                            qDebug() << "weather here~~~~~~~~~";
                        }
                    }
                    if (weather_id > 0) {
                        DealRadioInfo(weather_id, left_key, right_value);
                        now_weather_num = weather_id;
                    }
                }
            }while(!line.isNull());

            sys_file.close();


            sprintf(buf, "Read %s ok!", path);
            ui->textEdit_info->append(QString(buf));
        } else {
            sprintf(buf, "Open %s fail!", path);
            ui->textEdit_info->append(QString(buf));
            QMessageBox::information(this,"tips",QString(buf));
        }
    } else {
        qDebug() << "no " << QString(path);
        QMessageBox::information(this,"tips","There is no url_play_list.txt");
    }

    int i;
    weather_id++;
    for (i = weather_id; i < MAX_WEATHER_ID; i++) {
        if (lineEdit_Num[i] != NULL) {
            lineEdit_Num[i]->hide();
            lineEdit_Num[i]->setText("");
        }
        if (lineEdit_Country[i] != NULL) {
            lineEdit_Country[i]->hide();
            lineEdit_Country[i]->setText("");
        }
        if (lineEdit_City[i] != NULL) {
            lineEdit_City[i]->hide();
            lineEdit_City[i]->setText("");
        }
        if (lineEdit_Cid[i] != NULL) {
            lineEdit_Cid[i]->hide();
            lineEdit_Cid[i]->setText("");
        }
    }
}


void Weather::ShowSystemTime(void)
{

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间

    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    ui->label_time->setText(str);//在标签上显示时间

}

void Weather::on_pushButton_factory_clicked()
{
    ReadFile(FACTORY_FILE_PATH);
}

void Weather::on_pushButton_read_clicked()
{
    ReadFile(FILE_PATH);
}

void Weather::on_pushButton_save_clicked()
{
    char buf[256];
    radio->on_pushButton_save_clicked();
    sprintf(buf, "Save %s ok!", SAVE_PATH);
    //ui->textEdit_info->setText(QString(buf));
    ui->textEdit_info->append(QString(buf));
}

void Weather::on_pushButton_clear_clicked()
{
    ui->textEdit_info->setText("");
}

void Weather::on_pushButton_clear_all_clicked()
{
    int i;
    for (i = 0; i < MAX_RADIO_ID; i++) {
        if (lineEdit_Country[i] != NULL) {
            lineEdit_Country[i]->setText("");
        }
        if (lineEdit_City[i] != NULL) {
            lineEdit_City[i]->setText("");
        }
        if (lineEdit_Cid[i] != NULL) {
            lineEdit_Cid[i]->setText("");
        }
    }
    ui->textEdit_info->append("clear all items here!");
}

void Weather::on_pushButton_add_item_clicked()
{
    int i;
    int cur_num;
    cur_num = now_weather_num;
    int central_width;
    int central_height;


    now_weather_num += COMMON_ADD_SIZE;

    central_width = this->width();
    central_height = this->height();
    qDebug() << "width:" << central_width;
    qDebug() << "height:" << central_height;
    if ((NUM_START_Y + now_weather_num * INTERVAL_H) > (central_height - INTERVAL_H)) {
        central_height = NUM_START_Y + now_weather_num * INTERVAL_H + 50;
        //radio->setGeometry(0, 0, 1050, 2200);
        this->resize(QSize(central_width, central_height));
        //ui->centralwidget->setGeometry(0, 0, central_width, central_height)
    }

    for (i = cur_num + 1; i < cur_num + 1 + COMMON_ADD_SIZE; i++) {
        if (lineEdit_Num[i] == NULL) {
            lineEdit_Num[i] = new QLineEdit(ui->centralwidget);
            lineEdit_Num[i]->setEnabled(false);
            lineEdit_Num[i]->setGeometry(NUM_START_X, NUM_START_Y + i * INTERVAL_H, NUM_W, FONT_HEIGHT);
        }
        lineEdit_Num[i]->setText(QString::number(i));
        lineEdit_Num[i]->show();

        if (lineEdit_Country[i] == NULL) {
            lineEdit_Country[i] = new QLineEdit(ui->centralwidget);
            lineEdit_Country[i]->setGeometry(COUNTRY_START_X, COUNTRY_START_Y + i * INTERVAL_H, COUNTRY_W, FONT_HEIGHT);
        }
        lineEdit_Country[i]->setText("");
        lineEdit_Country[i]->show();

        if (lineEdit_City[i] == NULL) {
            lineEdit_City[i] = new QLineEdit(ui->centralwidget);
            lineEdit_City[i]->setGeometry(STYLE_START_X, STYLE_START_Y + i * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City[i]->setText("");
        lineEdit_City[i]->show();

        if (lineEdit_Cid[i] == NULL) {
            lineEdit_Cid[i] = new QLineEdit(ui->centralwidget);
            lineEdit_Cid[i]->setGeometry(NAME_START_X, NAME_START_Y + i * INTERVAL_H, NAME_W, FONT_HEIGHT);
        }
        lineEdit_Cid[i]->setText("");
        lineEdit_Cid[i]->show();


    }
    char buf[256];
    sprintf(buf, "add %d items here!", COMMON_ADD_SIZE);
    ui->textEdit_info->append(QString(buf));
}
