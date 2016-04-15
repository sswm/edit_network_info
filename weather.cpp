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
        lineEdit_City_English[i] = NULL;
        lineEdit_City_Frechch[i] = NULL;
        lineEdit_City_German[i] = NULL;
        lineEdit_City_Italian[i] = NULL;
        lineEdit_City_Spanish[i] = NULL;
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
        if (lineEdit_City_English[id] == NULL) {
            lineEdit_City_English[id] = new QLineEdit(ui->centralwidget);
            lineEdit_City_English[id]->setGeometry(ENG_START_X, STYLE_START_Y + id * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City_English[id]->setText(right_value);
        lineEdit_City_English[id]->show();
    } else if (left_key.toLower().compare(W_CITY_STR_FRENCH) == 0) {
        if (lineEdit_City_Frechch[id] == NULL) {
            lineEdit_City_Frechch[id] = new QLineEdit(ui->centralwidget);
            lineEdit_City_Frechch[id]->setGeometry(FRE_START_X, STYLE_START_Y + id * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City_Frechch[id]->setText(right_value);
        lineEdit_City_Frechch[id]->show();
    } else if (left_key.toLower().compare(W_CITY_STR_GERMAN) == 0) {
        if (lineEdit_City_German[id] == NULL) {
            lineEdit_City_German[id] = new QLineEdit(ui->centralwidget);
            lineEdit_City_German[id]->setGeometry(GER_START_X, STYLE_START_Y + id * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City_German[id]->setText(right_value);
        lineEdit_City_German[id]->show();
    } else if (left_key.toLower().compare(W_CITY_STR_ITALIAN) == 0) {
        if (lineEdit_City_Italian[id] == NULL) {
            lineEdit_City_Italian[id] = new QLineEdit(ui->centralwidget);
            lineEdit_City_Italian[id]->setGeometry(ITA_START_X, STYLE_START_Y + id * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City_Italian[id]->setText(right_value);
        lineEdit_City_Italian[id]->show();
    } else if (left_key.toLower().compare(W_CITY_STR_SPANISH) == 0) {
        if (lineEdit_City_Spanish[id] == NULL) {
            lineEdit_City_Spanish[id] = new QLineEdit(ui->centralwidget);
            lineEdit_City_Spanish[id]->setGeometry(SPA_START_X, STYLE_START_Y + id * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City_Spanish[id]->setText(right_value);
        lineEdit_City_Spanish[id]->show();
    } if (left_key.toLower().compare(W_CITY_CID) == 0) {
        if (lineEdit_Cid[id] == NULL) {
            lineEdit_Cid[id] = new QLineEdit(ui->centralwidget);
            lineEdit_Cid[id]->setGeometry(ID_START_X, ID_START_Y + id * INTERVAL_H, STYLE_W, FONT_HEIGHT);
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
        if (sys_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&sys_file);
            stream.setCodec("UTF-8");
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
                    //qDebug() << "id~~" << weather_id << "~" <<left_key <<"~~~"<< right_value;
                    if (left_key.compare(W_COUNTRY_STR) == 0) {
                        weather_id++;
                        int central_width;
                        int central_height;
                        central_width = this->width();
                        central_height = this->height();
                        //qDebug() << "width:" << central_width;
                        //qDebug() << "height:" << central_height;
                        if ((NUM_START_Y + weather_id * INTERVAL_H) > (central_height - INTERVAL_H)) {
                            central_height = NUM_START_Y + weather_id * INTERVAL_H + 50;
                            //radio->setGeometry(0, 0, 1050, 2200);
                            this->resize(QSize(central_width, central_height));
                            //ui->centralwidget->setGeometry(0, 0, central_width, central_height);

                            //tabwidget->resize(central_width,central_height);
                            //int wi = NUM_START_Y + weather_id * INTERVAL_H;
                            //qDebug() << "weather resize here~~" << central_height << "--now:" << wi;
                            //ui->centralwidget->resize(central_width,central_height);
                            //QScrollArea *scrollArea_t = new QScrollArea;
                            //scrollArea_t->setWidget(radio);
                            //tabwidget->show();

                        } else {
                            central_height = NUM_START_Y + weather_id * INTERVAL_H + 50;
                            this->resize(QSize(central_width, central_height));
                            //qDebug() << "weather here~~~~~~~~~";
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
        if (lineEdit_City_English[i] != NULL) {
            lineEdit_City_English[i]->hide();
            lineEdit_City_English[i]->setText("");
        }
        if (lineEdit_City_Frechch[i] != NULL) {
            lineEdit_City_Frechch[i]->hide();
            lineEdit_City_Frechch[i]->setText("");
        }
        if (lineEdit_City_German[i] != NULL) {
            lineEdit_City_German[i]->hide();
            lineEdit_City_German[i]->setText("");
        }
        if (lineEdit_City_Italian[i] != NULL) {
            lineEdit_City_Italian[i]->hide();
            lineEdit_City_Italian[i]->setText("");
        }
        if (lineEdit_City_Spanish[i] != NULL) {
            lineEdit_City_Spanish[i]->hide();
            lineEdit_City_Spanish[i]->setText("");
        }
        if (lineEdit_Cid[i] != NULL) {
            lineEdit_Cid[i]->hide();
            lineEdit_Cid[i]->setText("");
        }
    }
    //Sort_Country_A_Z();
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
        if (lineEdit_City_English[i] != NULL) {
            lineEdit_City_English[i]->setText("");
        }
        if (lineEdit_City_Frechch[i] != NULL) {
            lineEdit_City_Frechch[i]->setText("");
        }
        if (lineEdit_City_German[i] != NULL) {
            lineEdit_City_German[i]->setText("");
        }
        if (lineEdit_City_Italian[i] != NULL) {
            lineEdit_City_Italian[i]->setText("");
        }
        if (lineEdit_City_Spanish[i] != NULL) {
            lineEdit_City_Spanish[i]->setText("");
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

        if (lineEdit_City_English[i] == NULL) {
            lineEdit_City_English[i] = new QLineEdit(ui->centralwidget);
            lineEdit_City_English[i]->setGeometry(ENG_START_X, STYLE_START_Y + i * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City_English[i]->setText("");
        lineEdit_City_English[i]->show();

        if (lineEdit_City_Frechch[i] == NULL) {
            lineEdit_City_Frechch[i] = new QLineEdit(ui->centralwidget);
            lineEdit_City_Frechch[i]->setGeometry(FRE_START_X, STYLE_START_Y + i * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City_Frechch[i]->setText("");
        lineEdit_City_Frechch[i]->show();

        if (lineEdit_City_German[i] == NULL) {
            lineEdit_City_German[i] = new QLineEdit(ui->centralwidget);
            lineEdit_City_German[i]->setGeometry(GER_START_X, STYLE_START_Y + i * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City_German[i]->setText("");
        lineEdit_City_German[i]->show();

        if (lineEdit_City_Italian[i] == NULL) {
            lineEdit_City_Italian[i] = new QLineEdit(ui->centralwidget);
            lineEdit_City_Italian[i]->setGeometry(ITA_START_X, STYLE_START_Y + i * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City_Italian[i]->setText("");
        lineEdit_City_Italian[i]->show();

        if (lineEdit_City_Spanish[i] == NULL) {
            lineEdit_City_Spanish[i] = new QLineEdit(ui->centralwidget);
            lineEdit_City_Spanish[i]->setGeometry(SPA_START_X, STYLE_START_Y + i * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_City_Spanish[i]->setText("");
        lineEdit_City_Spanish[i]->show();

        if (lineEdit_Cid[i] == NULL) {
            lineEdit_Cid[i] = new QLineEdit(ui->centralwidget);
            lineEdit_Cid[i]->setGeometry(ID_START_X, ID_START_Y + i * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_Cid[i]->setText("");
        lineEdit_Cid[i]->show();


    }
    char buf[256];
    sprintf(buf, "add %d items here!", COMMON_ADD_SIZE);
    ui->textEdit_info->append(QString(buf));
}

/*
sort area for start_pos to end_pos
for example [1,8]
[9,20]
*/
void Weather::Sort_A_Z(int star_pos, int end_pos)
{
    int i,j;
    //qDebug() << now_weather_num;
    //ui->textEdit_info->append("sort city form a to z");


    for (i = 0; i < end_pos - star_pos; i++) {
        for (j = star_pos; j < end_pos - i; j++) {
            QString p;
            QString q;

            p = lineEdit_City_English[j]->text();
            q = lineEdit_City_English[j+1]->text();
//            if (p.compare("") == 0) {
//                qDebug() << "no city and not sort city";
//                break;
//            }
            if (QString::compare(p, q, Qt::CaseInsensitive) > 0) {
                QString tmp;
                tmp = lineEdit_City_English[j]->text();
                lineEdit_City_English[j]->setText(lineEdit_City_English[j+1]->text());
                lineEdit_City_English[j + 1]->setText(tmp);


                tmp = lineEdit_City_Frechch[j]->text();
                lineEdit_City_Frechch[j]->setText(lineEdit_City_Frechch[j+1]->text());
                lineEdit_City_Frechch[j + 1]->setText(tmp);

                tmp = lineEdit_City_German[j]->text();
                lineEdit_City_German[j]->setText(lineEdit_City_German[j+1]->text());
                lineEdit_City_German[j + 1]->setText(tmp);

                tmp = lineEdit_City_Italian[j]->text();
                lineEdit_City_Italian[j]->setText(lineEdit_City_Italian[j+1]->text());
                lineEdit_City_Italian[j + 1]->setText(tmp);

                tmp = lineEdit_City_Spanish[j]->text();
                lineEdit_City_Spanish[j]->setText(lineEdit_City_Spanish[j+1]->text());
                lineEdit_City_Spanish[j + 1]->setText(tmp);


                tmp = lineEdit_Cid[j]->text();
                lineEdit_Cid[j]->setText(lineEdit_Cid[j+1]->text());
                lineEdit_Cid[j + 1]->setText(tmp);


            }



        }

    }

}

void Weather::on_pushButton_sort_city_clicked()
{
    ui->textEdit_info->append("sort city form a to z");

    int start_pos = 1;
    int end_pos = 1;
    int i = 0;

    Sort_Country_A_Z();

    QString first_tmp = lineEdit_Country[1]->text().trimmed().toLower();

    if (first_tmp.compare("") == 0) {
        qDebug() << "no country data here!!!";
        ui->textEdit_info->append("no country data here!!!");
        return;
    }

    start_pos = 1;
    for (i = 2; i <= now_weather_num; i++) {
        QString second_tmp = lineEdit_Country[i]->text().trimmed().toLower();
        if (QString::compare(first_tmp, second_tmp, Qt::CaseInsensitive) != 0) {
            end_pos = i - 1;
            qDebug() << "start:" << QString::number(start_pos) << "end:" << QString::number(end_pos);
            Sort_A_Z(start_pos, end_pos);
            first_tmp = second_tmp;
            start_pos = i;
        }
    }
    end_pos = i - 1;
    qDebug() << "start:" << QString::number(start_pos) << "end:" << QString::number(end_pos);
    Sort_A_Z(start_pos, end_pos);
}


void Weather::Sort_Country_A_Z(void)
{
    int i,j;
    RemoveBlank();
    for (i = 0; i < now_weather_num - 1; i++) {
        for (j = 1; j < now_weather_num - i; j++) {
            QString p;
            QString q;

            p = lineEdit_Country[j]->text();
            q = lineEdit_Country[j+1]->text();
            //qDebug() << p << q;
            if (p.compare("") == 0 || q.compare("") == 0) {
                qDebug() << "no country and not sort country";
                break;
            }
            if (QString::compare(p, q, Qt::CaseInsensitive) > 0) {
                QString tmp;

                tmp = lineEdit_Country[j]->text();
                lineEdit_Country[j]->setText(lineEdit_Country[j+1]->text());
                lineEdit_Country[j + 1]->setText(tmp);

                tmp = lineEdit_City_English[j]->text();
                lineEdit_City_English[j]->setText(lineEdit_City_English[j+1]->text());
                lineEdit_City_English[j + 1]->setText(tmp);


                tmp = lineEdit_City_Frechch[j]->text();
                lineEdit_City_Frechch[j]->setText(lineEdit_City_Frechch[j+1]->text());
                lineEdit_City_Frechch[j + 1]->setText(tmp);

                tmp = lineEdit_City_German[j]->text();
                lineEdit_City_German[j]->setText(lineEdit_City_German[j+1]->text());
                lineEdit_City_German[j + 1]->setText(tmp);

                tmp = lineEdit_City_Italian[j]->text();
                lineEdit_City_Italian[j]->setText(lineEdit_City_Italian[j+1]->text());
                lineEdit_City_Italian[j + 1]->setText(tmp);

                tmp = lineEdit_City_Spanish[j]->text();
                lineEdit_City_Spanish[j]->setText(lineEdit_City_Spanish[j+1]->text());
                lineEdit_City_Spanish[j + 1]->setText(tmp);


                tmp = lineEdit_Cid[j]->text();
                lineEdit_Cid[j]->setText(lineEdit_Cid[j+1]->text());
                lineEdit_Cid[j + 1]->setText(tmp);


            }



        }

    }

}

void Weather::RemoveBlank()
{
    int i,j;

    for (i = 0; i < now_weather_num - 1; i++) {
        for (j = 1; j < now_weather_num - i; j++) {
            QString p;
            QString q;

            p = lineEdit_Country[j]->text();
            q = lineEdit_Country[j+1]->text();
            //qDebug() << p << q;
            if (p.compare("") != 0) {
                //qDebug() << "break here";
                continue;
            }
            if (QString::compare(p, q, Qt::CaseInsensitive) < 0) {
                QString tmp;

                tmp = lineEdit_Country[j]->text();
                lineEdit_Country[j]->setText(lineEdit_Country[j+1]->text());
                lineEdit_Country[j + 1]->setText(tmp);

                tmp = lineEdit_City_English[j]->text();
                lineEdit_City_English[j]->setText(lineEdit_City_English[j+1]->text());
                lineEdit_City_English[j + 1]->setText(tmp);


                tmp = lineEdit_City_Frechch[j]->text();
                lineEdit_City_Frechch[j]->setText(lineEdit_City_Frechch[j+1]->text());
                lineEdit_City_Frechch[j + 1]->setText(tmp);

                tmp = lineEdit_City_German[j]->text();
                lineEdit_City_German[j]->setText(lineEdit_City_German[j+1]->text());
                lineEdit_City_German[j + 1]->setText(tmp);

                tmp = lineEdit_City_Italian[j]->text();
                lineEdit_City_Italian[j]->setText(lineEdit_City_Italian[j+1]->text());
                lineEdit_City_Italian[j + 1]->setText(tmp);

                tmp = lineEdit_City_Spanish[j]->text();
                lineEdit_City_Spanish[j]->setText(lineEdit_City_Spanish[j+1]->text());
                lineEdit_City_Spanish[j + 1]->setText(tmp);


                tmp = lineEdit_Cid[j]->text();
                lineEdit_Cid[j]->setText(lineEdit_Cid[j+1]->text());
                lineEdit_Cid[j + 1]->setText(tmp);


            }



        }

    }

}

void Weather::on_pushButton_sort_country_clicked()
{
    ui->textEdit_info->append("sort country form a to z");

    Sort_Country_A_Z();
}
