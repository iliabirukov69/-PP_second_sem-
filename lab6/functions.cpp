#include "functions.h"
#include "./ui_mainwindow.h"
#include <QTextEdit>
#include <QListWidget>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    for (Shape* sh : shapes) {
        delete sh;
    }
}

void MainWindow::on_choice_figure_textActivated(const QString &arg1)
{
    if (arg1 == "Треугольник"){
        shape_bool = 2;
        ui->textEdit->clear();
        ui->textEdit_2->clear();
        ui->textEdit_3->clear();
        ui->textEdit->append("Введите первую сторону");
        ui->textEdit_2->append("Введите вторую сторону");
        ui->textEdit_3->append("Введите третью сторону");
    }
    else if (arg1 == "Окружность"){
        shape_bool = 3;
        ui->textEdit->clear();
        ui->textEdit_2->clear();
        ui->textEdit_3->clear();
        ui->textEdit->append("Введите радиус");
        ui->textEdit_2->append("---");
        ui->textEdit_3->append("---");
    }
    else {
        shape_bool = 1;
        ui->textEdit->clear();
        ui->textEdit_2->clear();
        ui->textEdit_3->clear();
        ui->textEdit->append("Введите длину");
        ui->textEdit_2->append("Введите ширину");
        ui->textEdit_3->append("---");
    }
}

void MainWindow::error(){
    if (er == 1){
        delete ui->listWidget->takeItem(ui->listWidget->count()-1);
        er = 0;
    }
}

bool MainWindow::error_par(QString s){
    bool ok;
    float t = s.toFloat(&ok);
    if (ok){
        if (t <= 0) {
            return 0;
        }
        return 1;
    }
    return 0;
}

bool MainWindow::error_triangle(){
    if (error_par(ui->par_1->text()) &&
        error_par(ui->par_2->text()) &&
        error_par(ui->par_3->text())){
        float side_1 =  ui->par_1->text().toFloat();
        float side_2 =  ui->par_2->text().toFloat();
        float side_3 =  ui->par_3->text().toFloat();
        if ((side_1+side_2 > side_3) && (side_1+side_3 > side_2) && (side_2+side_3 > side_1)){
            return 1;
        }
        return 0;
    }
    return 0;
}

void MainWindow::on_par_1_textChanged(const QString &arg1) {}
void MainWindow::on_par_2_textChanged(const QString &arg1) {}
void MainWindow::on_par_3_textChanged(const QString &arg1) {}
void MainWindow::on_num_textChanged(const QString &arg1) {}

void MainWindow::on_input_clicked()
{
    error();
    if (shape_bool == 0){
        ui->listWidget->addItem("Выберите тип фигуры");
        er = 1;
    }
    else if (shape_bool == 1) {
        if (ui->par_3->text()!=""){
            ui->listWidget->addItem("Не нужно вводить в третье окно");
            er = 1;
        }
        else if (!error_par(ui->par_1->text()) || !error_par(ui->par_2->text())){
            ui->listWidget->addItem("Неверно введены параметры");
            er = 1;
        }
        else {
            float l = ui->par_1->text().toFloat();
            float w = ui->par_2->text().toFloat();
            Shape* rectangle = new Rectangle(l, w);
            rectangle->area();
            rectangle->perimeter();
            shapes.push_back(rectangle);
            ui->listWidget->addItem(QString::number(ui->listWidget->count()) + " Прямоугольник с длиной " +
                                    QString::number(l) + " и шириной " +
                                    QString::number(w) + ", площадь и периметр: " +
                                    QString::number(rectangle->get_area()) + " " + QString::number(rectangle->get_perimeter()));
        }
    }
    else if (shape_bool == 2) {
        if (!error_triangle()) {
            ui->listWidget->addItem("Неверно введены параметры");
            er = 1;
        }
        else {
            float side_1 = ui->par_1->text().toFloat();
            float side_2 = ui->par_2->text().toFloat();
            float side_3 = ui->par_3->text().toFloat();
            Shape* triangle = new Triangle(side_1, side_2, side_3);
            triangle->area();
            triangle->perimeter();
            shapes.push_back(triangle);
            ui->listWidget->addItem(QString::number(ui->listWidget->count()) +
                                    " Треугольник со сторонами " + QString::number(side_1) +
                                    " " + QString::number(side_2) +
                                    " " + QString::number(side_3) + ", площадь и периметр: " +
                                    QString::number(triangle->get_area()) + " " + QString::number(triangle->get_perimeter()));
        }
    }
    else {
        if (ui->par_3->text()!="" || ui->par_2->text()!=""){
            ui->listWidget->addItem("Не нужно вводить в третье и второе окно");
            er = 1;
        }
        else if (!(error_par(ui->par_1->text()))){
            ui->listWidget->addItem("Неверно введены параметры");
            er = 1;
        }
        else {
            float radius = ui->par_1->text().toFloat();
            Shape* circle = new Circle(radius);
            circle->area();
            circle->perimeter();
            shapes.push_back(circle);
            ui->listWidget->addItem(QString::number(ui->listWidget->count()) +
                                    " Окружность с радиусом " + QString::number(radius)  + ", площадь и периметр: " +
                                    QString::number(circle->get_area()) + " " + QString::number(circle->get_perimeter()));
        }
    }
}

void MainWindow::on_clear_clicked()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->listWidget->clear();
    ui->par_1->clear();
    ui->par_2->clear();
    ui->par_3->clear();
    ui->num->clear();
    for (Shape* sh : shapes) {
        delete sh;
    }
    shapes.clear();
}

void MainWindow::on_inf_clicked()
{
    error();
    if(!error_par(ui->num->text()) || ui->listWidget->count()<ui->num->text().toInt()){
        ui->listWidget->addItem("Неверно введён номер");
        er = 1;
    }
    else {
        Shape* fig = shapes[(ui->num->text().toInt())-1];
        fig->area();
        fig->perimeter();
        QString nam = QString::fromStdString(fig->name());
        ui->listWidget->clear();
        ui->listWidget->addItem("Название фигуры: " + nam);
        ui->listWidget->addItem("Площадь: " + QString::number(fig->get_area()));
        ui->listWidget->addItem("Периметр: " + QString::number(fig->get_perimeter()));
    }
}

void MainWindow::on_back_clicked()
{
    ui->listWidget->clear();
    QString nam;
    for (size_t i = 0; i < shapes.size(); i++) {
        nam = QString::fromStdString(shapes[i]->name());
        if (nam == "Окружность") {
            ui->listWidget->addItem(QString::number(ui->listWidget->count()+1) +
                                    " Окружность с радиусом " + QString::number(shapes[i]->get_par()[0]) + ", площадь и периметр: " +
                                    QString::number(shapes[i]->get_area()) + " " + QString::number(shapes[i]->get_perimeter()));
        }
        else if (nam == "Треугольник"){
            ui->listWidget->addItem(QString::number(ui->listWidget->count()+1) +
                                    " Треугольник со сторонами " + QString::number(shapes[i]->get_par()[0]) +
                                    " " + QString::number(shapes[i]->get_par()[1]) +
                                    " " + QString::number(shapes[i]->get_par()[2])  + ", площадь и периметр: " +
                                    QString::number(shapes[i]->get_area()) + " " + QString::number(shapes[i]->get_perimeter()));
        }
        else {
            ui->listWidget->addItem(QString::number(ui->listWidget->count()+1) + " Прямоугольник с длиной " +
                                    QString::number(shapes[i]->get_par()[0]) + " и шириной " +
                                    QString::number(shapes[i]->get_par()[1])  + ", площадь и периметр: " +
                                    QString::number(shapes[i]->get_area()) + " " + QString::number(shapes[i]->get_perimeter()));
        }
    }
}
void MainWindow::on_sort_area_clicked()
{
    for (size_t i = 0; i < shapes.size() - 1; i++) {
        for (size_t j = 0; j < shapes.size() - i - 1; j++){
            shapes[j]->area();
            shapes[j+1]->area();
            if (shapes[j]->get_area() < shapes[j+1]->get_area()){
                std::swap(shapes[j], shapes[j+1]);
            }
        }
    }
    ui->listWidget->clear();
    for (size_t i = 0; i < shapes.size(); i++) {
        QString nam = QString::fromStdString(shapes[i]->name());
        if (nam == "Окружность") {
            ui->listWidget->addItem(QString::number(ui->listWidget->count()+1) +
                                    " Окружность с радиусом " + QString::number(shapes[i]->get_par()[0])  + ", площадь и периметр: " +
                                    QString::number(shapes[i]->get_area()) + " " + QString::number(shapes[i]->get_perimeter()));
        }
        else if (nam == "Треугольник"){
            ui->listWidget->addItem(QString::number(ui->listWidget->count()+1) +
                                    " Треугольник со сторонами " + QString::number(shapes[i]->get_par()[0]) +
                                    " " + QString::number(shapes[i]->get_par()[1]) +
                                    " " + QString::number(shapes[i]->get_par()[2])  + ", площадь и периметр: " +
                                    QString::number(shapes[i]->get_area()) + " " + QString::number(shapes[i]->get_perimeter()));
        }
        else {
            ui->listWidget->addItem(QString::number(ui->listWidget->count()+1) + " Прямоугольник с длиной " +
                                    QString::number(shapes[i]->get_par()[0]) + " и шириной " +
                                    QString::number(shapes[i]->get_par()[1])  + ", площадь и периметр: " +
                                    QString::number(shapes[i]->get_area()) + " " + QString::number(shapes[i]->get_perimeter()));
        }
    }
}

void MainWindow::on_sort_perimeter_clicked()
{
    for (size_t i = 0; i < shapes.size() - 1; i++) {
        for (size_t j = 0; j < shapes.size() - i - 1; j++){
            shapes[j]->perimeter();
            shapes[j+1]->perimeter();
            if (shapes[j]->get_perimeter() < shapes[j+1]->get_perimeter()){
                std::swap(shapes[j], shapes[j+1]);
            }
        }
    }
    ui->listWidget->clear();
    for (size_t i = 0; i < shapes.size(); i++) {
        QString nam = QString::fromStdString(shapes[i]->name());
        if (nam == "Окружность") {
            ui->listWidget->addItem(QString::number(ui->listWidget->count()+1) +
                                    " Окружность с радиусом " + QString::number(shapes[i]->get_par()[0])  + ", площадь и периметр: " +
                                    QString::number(shapes[i]->get_area()) + " " + QString::number(shapes[i]->get_perimeter()));
        }
        else if (nam == "Треугольник"){
            ui->listWidget->addItem(QString::number(ui->listWidget->count()+1) +
                                    " Треугольник со сторонами " + QString::number(shapes[i]->get_par()[0]) +
                                    " " + QString::number(shapes[i]->get_par()[1]) +
                                    " " + QString::number(shapes[i]->get_par()[2])  + ", площадь и периметр: " +
                                    QString::number(shapes[i]->get_area()) + " " + QString::number(shapes[i]->get_perimeter()));
        }
        else {
            ui->listWidget->addItem(QString::number(ui->listWidget->count()+1) + " Прямоугольник с длиной " +
                                    QString::number(shapes[i]->get_par()[0]) + " и шириной " +
                                    QString::number(shapes[i]->get_par()[1])  + ", площадь и периметр: " +
                                    QString::number(shapes[i]->get_area()) + " " + QString::number(shapes[i]->get_perimeter()));
        }
    }
}

