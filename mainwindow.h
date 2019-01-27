#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_zapis_clicked();
    void setDataModel();

    void on_deletelist_clicked();

private:
    Ui::MainWindow *ui;
    QString name;
    QString gender;
    QString email;
    QString phone;
    QString fv;
    QString course;

    QStringListModel *id_model;
    QStringListModel *name_model;
    QStringListModel *course_model;
};

#endif // MAINWINDOW_H
