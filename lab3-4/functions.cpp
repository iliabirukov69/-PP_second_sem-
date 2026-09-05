#include "functions.h"
#include "ui_cub.h"
#include <iostream>
#include <exception>
#include <cmath>

Cub::Cub(QWidget *parent, float side_cub)
    : QMainWindow(parent)
    , ui(new Ui::Cub)
{
    ui->setupUi(this);
}

bool Cub::is_side_cub_valid_(float side_cub) {
    return side_cub >= 0.001f;
}

void Cub::calculate_S_cub() {
    S_cub_ = side_cub_ * side_cub_ * 6.0f;
}

void Cub::calculate_V_cub() {
    V_cub_ = side_cub_ * side_cub_ * side_cub_;
}

void Cub::calculate_diag_cub() {
    diag_cub_ = std::sqrt(3.0f) * side_cub_;
}

Cub::~Cub()
{
    delete ui;
}

void Cub::on_Edit_side_cub_textChanged(const QString &arg1)
{
}

void Cub::Clear(){
    ui->side_out->clear();
    ui->Area_out->clear();
    ui->Volume_out->clear();
    ui->diag_out->clear();
    side_cub_ = 0.0f;
    S_cub_ = 0.0f;
    V_cub_ = 0.0f;
    diag_cub_ = 0.0f;
}

void Cub::on_input_side_clicked()
{
    Clear();
    q_side = ui->Edit_side_cub->text();
    float side_cub = q_side.toFloat();
    if (!is_side_cub_valid_(side_cub)) {
        ui->side_out->append("Вы ввели сторону неправильно");
    }
    else{
        side_cub_ = side_cub;
        ui->side_out->append(q_side);
    }
}

void Cub::on_Area_calculate_clicked()
{
    ui->Area_out->clear();
    if (!is_side_cub_valid_(side_cub_)) {
        ui->Area_out->append("Вы не ввели сторону куба");
    }
    else{
        calculate_S_cub();
        q_Area = QString::number(S_cub_);
        ui->Area_out->append(q_Area);
    }
}

void Cub::on_Volume_calculate_clicked()
{
    ui->Volume_out->clear();
    if (!is_side_cub_valid_(side_cub_)) {
        ui->Volume_out->append("Вы не ввели сторону куба");
    }
    else{
        calculate_V_cub();
        q_Volume = QString::number(V_cub_, 'f', 4);
        ui->Volume_out->append(q_Volume);
    }
}

void Cub::on_diag_calculate_clicked()
{
    ui->diag_out->clear();
    if (!is_side_cub_valid_(side_cub_)) {
        ui->diag_out->append("Вы не ввели сторону куба");
    }
    else{
        calculate_diag_cub();
        q_diag = QString::number(diag_cub_);
        ui->diag_out->append(q_diag);
    }
}
