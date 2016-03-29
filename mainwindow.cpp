#include "mainwindow.h"
#include "ui_mainwindow.h"


#define     COUNTRY_STR         "country"
#define     FILE_STYLE_STR      "file_style"
#define     PROG_INDEX_STR      "prog_index"
#define     PROG_NAME_STR       "prog_name"
#define     MEDIA_TYPE_STR      "media_type"
#define     URL_STR                 "url"

#define     VERTICAL_SIZE       5
#define     FONT_HEIGHT         21
#define     INTERVAL_H          (FONT_HEIGHT + VERTICAL_SIZE)


#define     NUM_START_X         10
#define     COUNTRY_START_X     110
#define     STYLE_START_X       220
#define     NAME_START_X        340
#define     URL_START_X         540

#define     NUM_START_Y         99
#define     COUNTRY_START_Y     99
#define     STYLE_START_Y       99
#define     NAME_START_Y        99
#define     URL_START_Y         99

#define     NUM_W               41
#define     COUNTRY_W           81
#define     STYLE_W             101
#define     NAME_W              181
#define     URL_W               411



extern QTabWidget *tabwidget;
extern MainWindow *radio;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showTimer = new QTimer();
    connect(showTimer, SIGNAL(timeout()), this, SLOT(ShowSystemTime()));
    showTimer->setInterval(1000);
    showTimer->start();

    ui->lineEdit_Num1->hide();
    ui->lineEdit_Country1->hide();
    ui->lineEdit_Name1->hide();
    ui->lineEdit_Style1->hide();
    ui->lineEdit_Url1->hide();

    int i;
    for (i = 0; i < MAX_RADIO_ID; i++) {
        lineEdit_Num[i] = NULL;
        lineEdit_Country[i] = NULL;
        lineEdit_Style[i] = NULL;
        lineEdit_Name[i] = NULL;
        lineEdit_Url[i] = NULL;
    }
    now_radio_num = 0;
    ReadFile(FILE_PATH);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::DealRadioInfo(int id, QString left_key, QString right_value)
{
    if (id > MAX_RADIO_ID) {
        qDebug() << "more than " << MAX_RADIO_ID << "items";
        return;

    }
    if (lineEdit_Num[id] == NULL) {
        lineEdit_Num[id] = new QLineEdit(ui->centralwidget);
        lineEdit_Num[id]->setGeometry(NUM_START_X, NUM_START_Y + id * INTERVAL_H, NUM_W, FONT_HEIGHT);
    }

    lineEdit_Num[id]->setText(QString::number(id));
    lineEdit_Num[id]->show();

    if (left_key.toLower().compare(COUNTRY_STR) == 0) {
        if (lineEdit_Country[id] == NULL) {
            lineEdit_Country[id] = new QLineEdit(ui->centralwidget);
            lineEdit_Country[id]->setGeometry(COUNTRY_START_X, COUNTRY_START_Y + id * INTERVAL_H, COUNTRY_W, FONT_HEIGHT);
        }
        lineEdit_Country[id]->setText(right_value);
        lineEdit_Country[id]->show();
    } else if (left_key.toLower().compare(FILE_STYLE_STR) == 0) {
        if (lineEdit_Style[id] == NULL) {
            lineEdit_Style[id] = new QLineEdit(ui->centralwidget);
            lineEdit_Style[id]->setGeometry(STYLE_START_X, STYLE_START_Y + id * INTERVAL_H, STYLE_W, FONT_HEIGHT);
        }
        lineEdit_Style[id]->setText(right_value);
        lineEdit_Style[id]->show();
    } if (left_key.toLower().compare(PROG_INDEX_STR) == 0) {
        return;
    } if (left_key.toLower().compare(PROG_NAME_STR) == 0) {
        if (lineEdit_Name[id] == NULL) {
            lineEdit_Name[id] = new QLineEdit(ui->centralwidget);
            lineEdit_Name[id]->setGeometry(NAME_START_X, NAME_START_Y + id * INTERVAL_H, NAME_W, FONT_HEIGHT);
        }
        lineEdit_Name[id]->setText(right_value);
        lineEdit_Name[id]->show();
    } if (left_key.toLower().compare(MEDIA_TYPE_STR) == 0) {
        return;
    } if (left_key.toLower().compare(URL_STR) == 0) {
        if (lineEdit_Url[id] == NULL) {
            lineEdit_Url[id] = new QLineEdit(ui->centralwidget);
            lineEdit_Url[id]->setGeometry(URL_START_X, URL_START_Y + id * INTERVAL_H, URL_W, FONT_HEIGHT);
        }
        lineEdit_Url[id]->setText(right_value);
        lineEdit_Url[id]->show();
    }

}
void MainWindow::ReadFile(const char *path)
{

    QFile sys_file(path);
    QString line;
    char buf[256];
    int start_pos;
    char *tmp_p;
    QString left_key;
    QString right_value;
    int radio_id = 0;



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
                    qDebug() << "id~~" << radio_id << "~" <<left_key <<"~~~"<< right_value;
                    if (left_key.compare(COUNTRY_STR) == 0) {
                        radio_id++;
                        int central_width;
                        int central_height;
                        central_width = this->width();
                        central_height = this->height();
                        qDebug() << "width:" << central_width;
                        qDebug() << "height:" << central_height;
                        if ((NUM_START_Y + radio_id * INTERVAL_H) > (central_height - INTERVAL_H)) {
                            central_height = NUM_START_Y + radio_id * INTERVAL_H + 50;
                            //radio->setGeometry(0, 0, 1050, 2200);
                            this->resize(QSize(central_width, central_height));
                            //ui->centralwidget->setGeometry(0, 0, central_width, central_height);

                            //tabwidget->resize(central_width,central_height);
                            int wi = NUM_START_Y + radio_id * INTERVAL_H;
                            qDebug() << "resize here~~" << central_height << "--now:" << wi;
                            //ui->centralwidget->resize(central_width,central_height);
                            //QScrollArea *scrollArea_t = new QScrollArea;
                            //scrollArea_t->setWidget(radio);
                            //tabwidget->show();

                        } else {
                            central_height = NUM_START_Y + radio_id * INTERVAL_H + 50;
                            this->resize(QSize(central_width, central_height));
                            qDebug() << "here~~~~~~~~~";
                        }
                    }
                    if (radio_id > 0) {
                        DealRadioInfo(radio_id, left_key, right_value);
                        now_radio_num = radio_id;
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
    radio_id++;
    for (i = radio_id; i < MAX_RADIO_ID; i++) {
        if (lineEdit_Num[i] != NULL) {
            lineEdit_Num[i]->hide();
        }
        if (lineEdit_Country[i] != NULL) {
            lineEdit_Country[i]->hide();
        }
        if (lineEdit_Style[i] != NULL) {
            lineEdit_Style[i]->hide();
        }
        if (lineEdit_Name[i] != NULL) {
            lineEdit_Name[i]->hide();
        }
        if (lineEdit_Url[i] != NULL) {
            lineEdit_Url[i]->hide();
        }
    }
}

void MainWindow::SaveFile(const char *path)
{
    QFile sys_file(path);
    QString line;

    if (sys_file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&sys_file);
        stream << "good";
    } else {
        QMessageBox::information(this,"tips","can not create url_play_list.txt");
    }
    sys_file.close();
    //QMessageBox::information(this,"tips","save url_play_list.txt ok!");
    char buf[256];
    sprintf(buf, "Save %s ok!", path);
    //ui->textEdit_info->setText(QString(buf));
    ui->textEdit_info->append(QString(buf));
}
void MainWindow::ShowSystemTime(void)
{

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间

    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    ui->label_time->setText(str);//在标签上显示时间

}










void MainWindow::on_pushButton_factory_clicked()
{
    ReadFile(FACTORY_FILE_PATH);
}

void MainWindow::on_pushButton_read_clicked()
{
    ReadFile(FILE_PATH);
}

void MainWindow::on_pushButton_save_clicked()
{
    SaveFile("save_url.txt");
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->textEdit_info->setText("");
}

void MainWindow::on_pushButton_add_item_clicked()
{
    int i;
    int cur_num;
    cur_num = now_radio_num;
    int central_width;
    int central_height;

    for (i = cur_num; i < cur_num + 5; i++) {


    }
    now_radio_num += 5;

    central_width = this->width();
    central_height = this->height();
    qDebug() << "width:" << central_width;
    qDebug() << "height:" << central_height;
    if ((NUM_START_Y + now_radio_num * INTERVAL_H) > (central_height - INTERVAL_H)) {
        central_height = NUM_START_Y + now_radio_num * INTERVAL_H + 50;
        //radio->setGeometry(0, 0, 1050, 2200);
        this->resize(QSize(central_width, central_height));
        //ui->centralwidget->setGeometry(0, 0, central_width, central_height)
    }

    for (i = cur_num + 1; i < cur_num + 6; i++) {
        if (lineEdit_Num[i] != NULL) {
            lineEdit_Num[i]->setText(QString::number(i));
        } else {
            lineEdit_Num[i] = new QLineEdit(ui->centralwidget);
        }
        lineEdit_Num[i]->show();

        if (lineEdit_Country[i] != NULL) {
            lineEdit_Country[i]->setText("");
        } else {
            lineEdit_Country[i] = new QLineEdit(ui->centralwidget);
        }
        lineEdit_Country[i]->show();

        if (lineEdit_Style[i] != NULL) {
            lineEdit_Style[i]->setText("");
        } else {
            lineEdit_Style[i] = new QLineEdit(ui->centralwidget);
        }
        lineEdit_Style[i]->show();

        if (lineEdit_Name[i] != NULL) {
            lineEdit_Name[i]->setText("");
        } else {
            lineEdit_Name[i] = new QLineEdit(ui->centralwidget);
        }
        lineEdit_Name[i]->show();

        if (lineEdit_Url[i] != NULL) {
            lineEdit_Url[i]->setText("");
        } else {
            lineEdit_Url[i] = new QLineEdit(ui->centralwidget);
        }
        lineEdit_Url[i]->show();
    }
    ui->textEdit_info->append("add 5 items here!");
}

void MainWindow::on_pushButton_clear_all_clicked()
{
    int i;
    for (i = 0; i < MAX_RADIO_ID; i++) {
        if (lineEdit_Country[i] != NULL) {
            lineEdit_Country[i]->setText("");
        }
        if (lineEdit_Style[i] != NULL) {
            lineEdit_Style[i]->setText("");
        }
        if (lineEdit_Name[i] != NULL) {
            lineEdit_Name[i]->setText("");
        }
        if (lineEdit_Url[i] != NULL) {
            lineEdit_Url[i]->setText("");
        }
    }
    ui->textEdit_info->append("clear all items here!");
}
