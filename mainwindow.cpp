#include "mainwindow.h"
#include "connection.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Aplikacja");
    ui->male->setChecked(true);

    QStringList course;
    course.append("CPP");
    course.append("Java");
    course.append("Lua");
    course.append("Graphic Design");
    ui->course->addItems(course);
    createConnection();


}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string name;
std::string gender;
std::string email;
std::string phone;
std::string fv;
std::string course;

QStringList id_list;
QStringList name_list;
QStringList course_list;

void getData(){
   id_list.clear();
   name_list.clear();
   course_list.clear();
   QSqlQuery query;
   query.exec("SELECT id, name, course FROM users");
   while (query.next()) {
           int db_id = query.value(0).toInt();
           QString db_name = query.value(1).toString();
           QString db_course = query.value(2).toString();
           id_list << QString::number(db_id);
           name_list << db_name;
           course_list << db_course;
   }
}

void MainWindow::setDataModel(){
   getData();
   id_model = new QStringListModel(this);
   name_model = new QStringListModel(this);
   course_model = new QStringListModel(this);
   id_model->setStringList(id_list);
   name_model->setStringList(name_list);
   course_model->setStringList(course_list);

   ui->listid->setModel(id_model);
   ui->listnames->setModel(name_model);
   ui->listcourse->setModel(course_model);
}

void insertData(QString name, QString gender, QString email, QString phone, QString course, QString fv){
    QSqlQuery query;
    QString SQL = "insert into users (name,gender,email,phone,course,fv) values ("
            "'"+name+"', "
            "'"+gender+"', "
            "'"+email+"', "
            "'"+phone+"', "
            "'"+course+"', "
            "'"+fv+"')";
    std::cout << SQL.toStdString() << std::endl;
    std::cout <<query.exec(SQL) << std::endl;
}

void MainWindow::on_zapis_clicked(){

    if(ui->name->text() != "" && ui->email->text() != "" && ui->phone->text() != ""){
     name = ui->name->text();
     email = ui->email->text();
     phone = ui->phone->text();

     if(ui->male->isChecked()){
         gender = "mezczyzna";
      } else{
         gender = "kobieta";
     }
      course = ui->course->currentText();

      if(ui->fv->isChecked()){
          fv = "tak";
      } else{
          fv = "nie";
      }

      insertData(name, gender, email, phone, course, fv);
      setDataModel();

      ui->zapis->setText("Success!");
      ui->name->clear();
      ui->email->clear();
      ui->phone->clear();
      name = "";
      email = "";
      phone = "";
      ui->male->setChecked(true);
      ui->fv->setChecked(false);
      ui->course->setCurrentIndex(0);

    //   std::cout << name.toStdString() << " " << gender.toStdString() << " " << email.toStdString() << " " << phone.toStdString() << " " << course.toStdString() << " " << fv.toStdString() << std::endl;

    } else {
        ui->zapis->setText("Failed!");
    }
}

void deleteData(QString id){
    QSqlQuery query;
    query.exec("DELETE FROM users WHERE id = "+id);
}

void MainWindow::on_deletelist_clicked(){
    QString id = ui->query->text();
    deleteData(id);
    ui->query->clear();
    setDataModel();
}
