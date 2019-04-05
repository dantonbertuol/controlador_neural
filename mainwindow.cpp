#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qserialportinfo.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->plotLayout()->insertRow(0);
    ui->widget->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widget, "Gráfico", QFont("sans", 12, QFont::Bold)));
    ui->widget->xAxis->setRange(0, 200);
    ui->widget->yAxis->setRange(-1, 1);
    ui->checkBoxRunning->setDisabled(true);

    serial.setPortName("COM11");
    serial.setBaudRate(serial.Baud115200);
    serial.setDataBits(serial.Data8);
    serial.setParity(serial.NoParity);
    serial.setFlowControl(serial.NoFlowControl);

    if(!serial.open(QIODevice::ReadWrite)){
        qDebug("Erro ao abrir Porta serial");
        return;
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    ui->widget->graph(0)->data().clear();
    ui->widget->graph(1)->data().clear();
    xAxis.clear();
    yAxis.clear();
    x2Axis.clear();
    y2Axis.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readSerial(){

    recvBytes.append(serial.readAll());

    if (recvBytes.size() >= 11) {

        int p = StringSearch("$A:");

        if (p >= 0) {

            char checksum = 0;
            for (int i = p; i < p + 10; i++) {
                checksum ^= recvBytes.at(i);
            }

            if (checksum == recvBytes.at(p + 10)) {

                unsigned char bytesValues[6];
                signed short raw_x,raw_y,raw_z;
                signed long totalVector;

                bytesValues[0] = recvBytes.at(p + 3);
                bytesValues[1] = recvBytes.at(p + 4);
                bytesValues[2] = recvBytes.at(p + 5);
                bytesValues[3] = recvBytes.at(p + 6);
                bytesValues[4] = recvBytes.at(p + 7);
                bytesValues[5] = recvBytes.at(p + 8);

                raw_x = ((bytesValues[0] << 8) | (bytesValues[1]));
                raw_y = ((bytesValues[2] << 8) | (bytesValues[3]));
                raw_z = ((bytesValues[4] << 8) | (bytesValues[5]));

                totalVector = sqrt((raw_x*raw_x)+(raw_y*raw_y)+(raw_z*raw_z));

                //57.296 = 1 / (3.142 / 180) The asin function is in radians
                pitch = asin((float)raw_y/totalVector)* 57.296;       //Calculate the pitch angle
                roll = asin((float)raw_x/totalVector)* -57.296;       //Calculate the roll angle

                x = (raw_x * 2.0/32768.0);
                y = (raw_y * 2.0/32768.0);
                z = (raw_z * 2.0/32768.0);

                //qDebug("X: %2.2f Y: %2.2f Z: %2.2f     p:%d",x,y,z,p);
                qDebug("Pitch: %f  |  Roll: %f",pitch,roll);

                ui->dialSetPoint->setValue(pitch);

                static long counter = 0;
                contAux2++;
                atualizaGrafico(0,0,contAux2,(pitch/100));
                if(contAux2==190){
                    xAxis.clear();
                    x2Axis.clear();
                    yAxis.clear();
                    y2Axis.clear();
                    ui->widget->graph(0)->data().clear();
                    ui->widget->graph(1)->data().clear();
                    ui->widget->replot();
                    contAux2=0;
                }



                // Propagação dos padrões de entrada pela camada C1.
                n = 0;
                for (j = 0; j < c1; j++)
                {
                    soma = 0;
                    for (i = 0; i < cx; i++)
                    {
                        soma += w1[n] * (pitch/100);
                        //soma += w1[n] * ui->doubleSpinBoxSetPoint->value();
                        n += 1;
                    }

                    entrada_camada1[j] = soma;
                    saida_camada1[j] = funcao_ativacao(entrada_camada1[j],funcao,1.0);
                }

                // Propagação dos padrões de entrada pela camada C2.
                n = 0;

                for (j = 0; j < c2; j++)
                {
                    soma = 0;
                    for (i = 0; i < c1; i++)
                    {
                        soma += w2[n] * saida_camada1[i];
                        n += 1;
                    }

                    entrada_camada2[j] = soma;
                    saida_camada2[j] = funcao_ativacao(entrada_camada2[j],funcao,1.0);
                }

                ativaNeuronio(entrada_camada1,entrada_camada2,saida_camada2);

                float result = 0.0;

                result += (0.015*saida_camada2[0]);
                result += (0.012*saida_camada2[1]);
                result -= (0.012*saida_camada2[3]);
                result -= (0.015*saida_camada2[4]);

                qDebug("Saída: %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f ",
                       saida_camada2[0],
                        saida_camada2[1],
                        saida_camada2[2],
                        saida_camada2[3],
                        saida_camada2[4],
                        result
                        );

                ui->doubleSpinBoxSetPoint->setValue(
                            ui->doubleSpinBoxSetPoint->value() + result
                            );

            }

            recvBytes.clear();
        }
    }

}

void MainWindow::on_dialSetPoint_valueChanged(int value)
{

}

void MainWindow::on_doubleSpinBoxSetPoint_valueChanged(double arg1)
{
    QByteArray pack;
    pack.clear();
    pack.append("$P:");
    pack.append((char)0);
    pack.append((char)77-arg1*100);
    pack.append('*');

    char checksum = 0;
    for(int i = 0; i < pack.size(); i++){
        checksum ^= pack.at(i);
    }

    pack.append(checksum);
    serial.write(pack);

}

void MainWindow::on_pushButton_clicked()
{
    /* initialize random seed: */
    srand (time(NULL));
    yAxis.clear();
    xAxis.clear();
    ui->widget->graph(0)->data().clear();
    ui->widget->plotLayout()->removeAt(0);
    ui->widget->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widget, "Gráfico de Treinamento", QFont("sans", 12, QFont::Bold)));

    ui->widget->replot();

    ui->checkBoxRunning->setEnabled(true);

    // Inicialização de variáveis.
    numero_de_padroes = 21;          // Número de padrões a treinar na rede neural.
    funcao = 0;                     // Função Logística(0).
    taxa_aprendizado = 0.001;         // Taxa de Aprendizado.
    ERRO = 0.01;                 // Erro mínimo aceitável da rede (se aplicável).
    MOMENTUM = 0.7;                 // Termo de MOMENTUM.
    epocas = 8000;                 // Número máximo de épocas de treinamento.
    rnd = 0;                        // Variável auxiliar para a randomização dos pesos.
    soma = 0;                       // Variável auxiliar para a soma das sinapses.
    erro_medio_quadratico = 0;      // Variável auxiliar do Erro médio quadrático.
    erro_quadratico = 0;            // Variável auxiliar do erro quadrático.
    fim = 0;                        // Variável de controle do final do treinamento.
    contador = 0;                   // Variável de controle do número de épocas.

    // Zera o vetor de pesos da camada de entrada da rede e da camada 1.
    for (j = 0; j < (cx * c1); j++)
    {
        w1[j] = 0.0;
    }

    // Zera o vetor de pesos da camada 1 e da camada 2.
    for (j = 0; j < (c1 * c2); j++)
    {
        w2[j] = 0.0;
    }

    // Zera os vetores envolvidos aos neurônios da camada 1.
    for (j = 0; j < c1; j++)
    {
        entrada_camada1[j] = 0.0;
        saida_camada1[j] = 0.0;
        erro_camada1[j] = 0.0;
    }

    // Zera os vetores envolvidos aos neurônios da camada 2.
    for (j = 0; j < c2; j++)
    {
        entrada_camada2[j] = 0.0;
        saida_camada2[j] = 0.0;
        erro_camada2[j] = 0.0;
    }

    // Randomização dos pesos para a camada 1.
    for (j = 0; j < (cx*c1); j++)
    {
        w1[j] = (float)(rand() % 100) / 1000;
    }

    // Randomização dos pesos para a camada 2.
    for (j = 0; j < (c1*c2); j++)
    {
        w2[j] = (float)(rand() % 100) / 1000;
    }

    do{
        contador++;

        // Propaga os k padrões pela rede.
        for (k = 0; k < numero_de_padroes; k++)
        {
            // Propagação dos padrões de entrada pela camada C1.
            n = 0;
            for (j = 0; j < c1; j++)
            {
                soma = 0;
                for (i = 0; i < cx; i++)
                {
                    soma += w1[n] * p[k][i];
                    n += 1;
                }
                entrada_camada1[j] = soma;
                saida_camada1[j] = funcao_ativacao(entrada_camada1[j],funcao,1.0);
            }

            // Propagação dos padrões de entrada pela camada C2.
            n = 0;
            for (j = 0; j < c2; j++)
            {
                soma = 0;
                for (i = 0; i < c1; i++)
                {
                    soma += w2[n] * saida_camada1[i];
                    n += 1;
                }
                entrada_camada2[j] = soma;
                saida_camada2[j] = funcao_ativacao(entrada_camada2[j],funcao,1.0);
            }

            //-----------------------------------------------------------------------------
            //                      Cálculo do Erro Médio Quadrático
            //-----------------------------------------------------------------------------

            // Calculo do Erro Quadratico.
            erro_quadratico = 0;
            for(j = 0; j < c2; j++)
            {
                erro_quadratico += pow((d[k][j] - saida_camada2[j]),2);
            }

            // Calculo do Erro Medio Quadrático (Critério de Parada).
            erro_medio_quadratico += (0.5 * erro_quadratico);

            //-----------------------------------------------------------------------------
            //                          Retropropagação do Erro
            //-----------------------------------------------------------------------------

            // Calculo do erro para camada 2.
            for (i = 0; i < c2; i++)
            {
                erro_camada2[i] = (d[k][i] - saida_camada2[i]) * derivada(entrada_camada2[i],funcao,1.0);
            }

            // Atualizacao dos pesos para camada 2.
            for (i = 0; i < c1; i++)
            {
                n = 0;
                for (j = 0; j < c2; j++)
                {
                    dw2[n + i] = taxa_aprendizado * saida_camada1[i] * erro_camada2[j] + (MOMENTUM * dw2[n + i]);
                    w2[n + i] = w2[n + i] + dw2[n + i];
                    n += c1;
                }
            }

            // Calculo do erro para camada 1.
            for (i = 0; i < c1; i++)
            {
                n = 0;
                soma = 0;
                for (j = 0; j < c2; j++)
                {
                    soma += (erro_camada2[j] * w2[n + i]);
                    n += c1;
                }
                erro_camada1[i] = soma * derivada(entrada_camada1[i],funcao,1.0);
            }

            // Atualizacao dos pesos para camada 1.
            for (i = 0; i < cx; i++)
            {
                n = 0;
                for (j = 0; j < c1; j++)
                {
                    dw1[n + i] = taxa_aprendizado * p[k][i] * erro_camada1[j] + (MOMENTUM * dw1[n + i]);
                    w1[n + i] = w1[n + i] + dw1[n + i];
                    n += cx;
                }
            }
        }

        // Cálculo do erro médio quadrático da época de treinamento.
        erro_medio_quadratico = (1.0 / numero_de_padroes) * erro_medio_quadratico;

        QCoreApplication::processEvents();
        qDebug("Epoca: %d  Erro: %f ", (int) contador, erro_medio_quadratico);
        xAxis << (double) contador;
        yAxis << (double) erro_medio_quadratico;

        contAux++;

        if(contAux==50){
            atualizaGraficoRede((double) contador, (double) erro_medio_quadratico);
            contAux=0;
        }

    }
    while(!fim && (contador != epocas));
}

void MainWindow::on_checkBoxRunning_stateChanged(int arg1)
{
    yAxis.clear();
    xAxis.clear();
    ui->widget->graph(0)->data().clear();
    ui->widget->plotLayout()->removeAt(0);
    ui->widget->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widget, "Gráfico de Execução", QFont("sans", 12, QFont::Bold)));
    ui->widget->replot();
    if(arg1){
        timer->start(50);
        return;
    }
    timer->stop();
}

void MainWindow::update()
{
    QCoreApplication::processEvents();
    readSerial();
}

int MainWindow::StringSearch(const char *value) {

    int ptr_buffer = 0, ptr_value = 0;

    // Busca até encontrar o fim, do literal ou do buffer.
    while ((value[ptr_value] != '\0')&&(ptr_buffer < recvBytes.size())) {

        if (recvBytes.at(ptr_buffer++) == value[ptr_value]) {
            ptr_value++;
            continue;
        }
        ptr_value = 0;
    }

    return (ptr_value == 0) ? (-1) : (ptr_buffer - ptr_value);
}

void MainWindow::atualizaGrafico(double x, double y, double x2, double y2){
    xAxis << x;
    yAxis << y;
    x2Axis << x2;
    y2Axis << y2;
    ui->widget->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->widget->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->widget->graph(0)->setData(xAxis, yAxis);
    ui->widget->graph(1)->setData(x2Axis, y2Axis);
    ui->widget->xAxis->setRange(0, 200);
    ui->widget->yAxis->setRange(-2, 2);
    ui->widget->xAxis->setLabel("Ciclo");
    ui->widget->yAxis->setLabel("Erro");
    ui->widget->replot();
}

void MainWindow::atualizaGraficoRede(double x, double y){
    xAxis << x;
    yAxis << y;
    ui->widget->graph(0)->setData(xAxis, yAxis);
    ui->widget->xAxis->setLabel("Época");
    ui->widget->yAxis->setLabel("Erro Médio");
    ui->widget->yAxis->setRange(0, 1);
    ui->widget->xAxis->setRange(0, x);
    ui->widget->replot();
}

void MainWindow::ativaNeuronio(float* entrada, float* intermediaria, float* saida){
    const float thresh = 0.3;
    if(entrada[0]>thresh){
        ui->btnEntrada->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnEntrada->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(intermediaria[0]>thresh){
        ui->btnMid01->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnMid01->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(intermediaria[1]>thresh){
        ui->btnMid02->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnMid02->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(intermediaria[2]>thresh){
        ui->btnMid03->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnMid03->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(intermediaria[3]>thresh){
        ui->btnMid04->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnMid04->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(intermediaria[4]>thresh){
        ui->btnMid05->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnMid05->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(intermediaria[5]>thresh){
        ui->btnMid06->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnMid06->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(intermediaria[6]>thresh){
        ui->btnMid07->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnMid07->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(intermediaria[7]>thresh){
        ui->btnMid08->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnMid08->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(intermediaria[8]>thresh){
        ui->btnMid09->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnMid09->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(intermediaria[9]>thresh){
        ui->btnMid10->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnMid10->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(saida[0]>thresh){
        ui->btnSaida01->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnSaida01->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(saida[1]>thresh){
        ui->btnSaida02->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnSaida02->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(saida[2]>thresh){
        ui->btnSaida03->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnSaida03->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(saida[3]>thresh){
        ui->btnSaida04->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnSaida04->setStyleSheet("background-color: rgb(255, 0, 0);");
    }

    if(saida[4]>thresh){
        ui->btnSaida05->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else{
        ui->btnSaida05->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
}
