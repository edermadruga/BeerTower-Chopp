#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dadosmesas.h"
#include <QPixmap>

#include <QDebug>
#include <QVector>
#include <numeric>
#include <algorithm>
#include <QFileDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QJsonDocument>
#include <QJsonObject>

#include <QThread>
#include <QMap>





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    DadosMesas mesas[10];
    int indice_mesa;
    int contador_historico=0;
    QSerialPort serial;

    int counter=0;








public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPic(int indice_mesa);

    void changeTemp(QString temp );

    void setPicState();

    void setChamada(QString feedback);



private slots:
    void on_button_mesa01_ocupar_clicked();

    void on_button_mesa01_desocupar_clicked();

    void on_comboBox_mesas_currentIndexChanged(const QString &arg1);

    void on_button_salvar_clicked();

    void dadosRecebidos();




    void on_btn_conectar_clicked();

    void on_btn_desconectar_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QString serial_aux = "";

    QString dados_serial = "";

    QString tipo_chamada="";
};

#endif // MAINWINDOW_H
