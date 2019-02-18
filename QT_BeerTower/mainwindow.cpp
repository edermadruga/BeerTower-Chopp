#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&serial, SIGNAL(readyRead()),this,SLOT(dadosRecebidos()));


    for(auto& item : QSerialPortInfo::availablePorts()){
     ui->comboBox_portas->addItem(item.portName());
    }

    for(auto& item : QSerialPortInfo::standardBaudRates()){
     ui->comboBox_velocidade->addItem(QString::number(item) );
    }

    /*
    serial.setPortName("COM7");
    serial.setBaudRate(QSerialPort::Baud115200);

    if(serial.open(QIODevice::ReadWrite)){
       qDebug()<< "Conectado a COM7";
    }
    */

    indice_mesa=0;

    QPixmap MesaDisponivel ("C:/Users/Apolo/Downloads/083beer/083beer/chopp/mesa.png");
    ui->label_mesa01->setPixmap(MesaDisponivel.scaled(300,100,Qt::KeepAspectRatio));



}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_button_mesa01_ocupar_clicked()
{
    int indice_mesa = ui->comboBox_mesas->currentText().toInt();
    mesas[indice_mesa].setStatus(1);
    setPic(indice_mesa);

    setPicState();

    //QString aux = "MESA " + QString::number(indice_mesa);
    //serial.write(aux.toUtf8());


}

void MainWindow::on_button_mesa01_desocupar_clicked()
{
    changeTemp("0");
    int indice_mesa = ui->comboBox_mesas->currentText().toInt();
    mesas[indice_mesa].setStatus(0);
    setPic(indice_mesa);

    ui->tbl_historico->insertRow(contador_historico);
    ui->tbl_historico->setItem(contador_historico,0,new QTableWidgetItem("Mesa " + QString::number(indice_mesa)));
    ui->tbl_historico->setItem(contador_historico, 1, new QTableWidgetItem(QString::number(mesas[indice_mesa].getValorConta())));
    ui->tbl_historico->setItem(contador_historico, 2, new QTableWidgetItem(QString::number(contador_historico+1)));
    contador_historico++;


    ui->tbl_dados->setItem(indice_mesa,0, new QTableWidgetItem(QString::number(NULL)));
    ui->tbl_dados->setItem(indice_mesa, 1, new QTableWidgetItem(QString::number(NULL)));

    setPicState();

}

void MainWindow::setPic(int indice_mesa){

    if(mesas[indice_mesa].getStatus()==1){
        QPixmap MesaOcupada ("C:/Users/Apolo/Downloads/083beer/083beer/chopp/mesaocupada.png");
        ui->label_mesa01->setPixmap(MesaOcupada.scaled(300,100,Qt::KeepAspectRatio));

    }else if(mesas[indice_mesa].getStatus()==0){

        QPixmap MesaDisponivel ("C:/Users/Apolo/Downloads/083beer/083beer/chopp/mesa.png");
        ui->label_mesa01->setPixmap(MesaDisponivel.scaled(300,100,Qt::KeepAspectRatio));

    }
}

void MainWindow::on_comboBox_mesas_currentIndexChanged(const QString &arg1)
{
    indice_mesa = arg1.toInt();
    qDebug()<<arg1;
    setPic(indice_mesa);
    QString mesa = "[" + QString::number(indice_mesa) + "]";
    serial.write(mesa.toUtf8());
}

void MainWindow::on_button_salvar_clicked()
{


    if(mesas[indice_mesa].getStatus()==1){


        int quant_chop = ui->comboBox_pedidos->currentText().toInt();
        int n_chop = mesas[indice_mesa].getNumeroChoppServido();

        mesas[indice_mesa].setNumeroChoppServido(n_chop+quant_chop);
        mesas[indice_mesa].setValorConta(mesas[indice_mesa].getNumeroChoppServido()*49.90);
        qDebug()<<mesas[indice_mesa].getValorConta();

        ui->tbl_dados->setItem(indice_mesa,0, new QTableWidgetItem(QString::number(mesas[indice_mesa].getNumeroChoppServido())));
        ui->tbl_dados->setItem(indice_mesa, 1, new QTableWidgetItem(QString::number(mesas[indice_mesa].getValorConta())));

        QString novo_valor_conta = QString::number(mesas[indice_mesa].getValorConta());
        serial.write("{VALOR:" + novo_valor_conta.toUtf8() + "}");
        qDebug()<< novo_valor_conta;
}

}

void MainWindow::dadosRecebidos(){

    QString dados = serial.readAll();


    dados_serial = dados_serial + dados;

    if(dados_serial.startsWith("{") && dados_serial.endsWith("}")){
        qDebug()<<dados_serial;
        auto dados = QJsonDocument::fromJson(dados_serial.toUtf8()).object().toVariantMap();

        if(dados.contains("TEMPERATURA")){

         QString aux = dados["TEMPERATURA"].toString();
         changeTemp(aux);
         qDebug()<< aux;

        }

        if(dados.contains("CHAMADO")){

            QString aux_2 = dados["CHAMADO"].toString();
            tipo_chamada = "";
            setChamada(aux_2);

        }

        if(dados.contains("PAGAMENTO")){

            QString aux_2 = dados["PAGAMENTO"].toString();

            if(aux_2=="2"){
                tipo_chamada = " Finalizar conta: Dinheiro";
            }else if(aux_2=="3"){
                tipo_chamada = " Finalizar conta: Cartão";
            }
            setChamada("1");

        }

        dados_serial = "";

    }

    /*
    QString data = serial.readAll();


    dados_serial = dados_serial + data;

    qDebug()<<data;



    if(data.startsWith("{") && data.endsWith("}")){
    qDebug()<<dados_serial;
    auto dados = QJsonDocument::fromJson(dados_serial.toUtf8()).object().toVariantMap();

    if(dados.contains("TEMPERATURA")){

     QString aux = dados["TEMPERATURA"].toString();
     changeTemp(aux);
     qDebug()<<aux;

    }

   }
   */


}

void MainWindow::changeTemp(QString temp )
{
    if(mesas[indice_mesa].getStatus()==1){
    ui->tbl_dados->setItem(indice_mesa,2, new QTableWidgetItem(temp+"°C"));
    }
}

void MainWindow::setPicState()
{
    QPixmap ocupado ("C:/Users/Apolo/Documents/083beer/chopp/ocupado.png");
    QPixmap livre ("C:/Users/Apolo/Documents/083beer/chopp/livre.png");

    if(indice_mesa==0){

        if(mesas[indice_mesa].getStatus()==1){
            ui->label_0->setPixmap(ocupado.scaled(71,81,Qt::KeepAspectRatio));
        }else if(mesas[indice_mesa].getStatus()==0){
            ui->label_0->setPixmap(livre.scaled(71,81,Qt::KeepAspectRatio));
        }

    }

    else if(indice_mesa==1){

        if(mesas[indice_mesa].getStatus()==1){
            ui->label_1->setPixmap(ocupado.scaled(71,81,Qt::KeepAspectRatio));
        }else if(mesas[indice_mesa].getStatus()==0){
            ui->label_1->setPixmap(livre.scaled(71,81,Qt::KeepAspectRatio));
        }

    }

    else if(indice_mesa==2){

        if(mesas[indice_mesa].getStatus()==1){
            ui->label_2->setPixmap(ocupado.scaled(71,81,Qt::KeepAspectRatio));
        }else if(mesas[indice_mesa].getStatus()==0){
            ui->label_2->setPixmap(livre.scaled(71,81,Qt::KeepAspectRatio));
        }

    }

    else if(indice_mesa==3){

        if(mesas[indice_mesa].getStatus()==1){
            ui->label_3->setPixmap(ocupado.scaled(71,81,Qt::KeepAspectRatio));
        }else if(mesas[indice_mesa].getStatus()==0){
            ui->label_3->setPixmap(livre.scaled(71,81,Qt::KeepAspectRatio));
        }

    }

    else if(indice_mesa==4){

        if(mesas[indice_mesa].getStatus()==1){
            ui->label_4->setPixmap(ocupado.scaled(71,81,Qt::KeepAspectRatio));
        }else if(mesas[indice_mesa].getStatus()==0){
            ui->label_4->setPixmap(livre.scaled(71,81,Qt::KeepAspectRatio));
        }

    }

    else if(indice_mesa==5){

        if(mesas[indice_mesa].getStatus()==1){
            ui->label_5->setPixmap(ocupado.scaled(71,81,Qt::KeepAspectRatio));
        }else if(mesas[indice_mesa].getStatus()==0){
            ui->label_5->setPixmap(livre.scaled(71,81,Qt::KeepAspectRatio));
        }

    }

    else if(indice_mesa==6){

        if(mesas[indice_mesa].getStatus()==1){
            ui->label_6->setPixmap(ocupado.scaled(71,81,Qt::KeepAspectRatio));
        }else if(mesas[indice_mesa].getStatus()==0){
            ui->label_6->setPixmap(livre.scaled(71,81,Qt::KeepAspectRatio));
        }

    }

    else if(indice_mesa==7){

        if(mesas[indice_mesa].getStatus()==1){
            ui->label_7->setPixmap(ocupado.scaled(71,81,Qt::KeepAspectRatio));
        }else if(mesas[indice_mesa].getStatus()==0){
            ui->label_7->setPixmap(livre.scaled(71,81,Qt::KeepAspectRatio));
        }

    }

    else if(indice_mesa==8){

        if(mesas[indice_mesa].getStatus()==1){
            ui->label_8->setPixmap(ocupado.scaled(71,81,Qt::KeepAspectRatio));
        }else if(mesas[indice_mesa].getStatus()==0){
            ui->label_8->setPixmap(livre.scaled(71,81,Qt::KeepAspectRatio));
        }

    }

    else if(indice_mesa==9){

        if(mesas[indice_mesa].getStatus()==1){
            ui->label_9->setPixmap(ocupado.scaled(71,81,Qt::KeepAspectRatio));
        }else if(mesas[indice_mesa].getStatus()==0){
            ui->label_9->setPixmap(livre.scaled(71,81,Qt::KeepAspectRatio));
        }

    }
}

void MainWindow::setChamada(QString feedback)
{
    qDebug()<< feedback;

    if(mesas[indice_mesa].getStatus()==1){
    if(feedback=="1"){
         ui->tbl_chamadas->removeRow(0);
         ui->tbl_chamadas->insertRow(0);
         ui->tbl_chamadas->setItem(0,0, new QTableWidgetItem("MESA " + QString::number(indice_mesa)+tipo_chamada));

     }else if(feedback=="0"){
         ui->tbl_chamadas->removeRow(0);

    }

    }

}

void MainWindow::on_btn_conectar_clicked()
{
     serial.setPortName(ui->comboBox_portas->currentText());
     serial.setBaudRate(ui->comboBox_velocidade->currentText().toInt());
     if(serial.open(QIODevice::ReadWrite)){
     ui->lbl_status->setText("Status: Conectado");
     qDebug()<<"Conectado a " + ui->comboBox_portas->currentText();

     serial.write("{VALOR:0}");

     }

}

void MainWindow::on_btn_desconectar_clicked()
{
    serial.close();
     ui->lbl_status->setText("Status: Desconectado");
}

void MainWindow::on_pushButton_clicked()
{

    int linha = ui->tbl_chamadas->currentRow();
    QString aux  = "{ok}";

    if(linha!=-1){
        ui->tbl_chamadas->removeRow(linha);
        serial.write(aux.toUtf8());
    }

}
