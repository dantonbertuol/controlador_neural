#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_dialSetPoint_valueChanged(int value);

    void on_doubleSpinBoxSetPoint_valueChanged(double arg1);

    void on_pushButton_clicked();

    void on_checkBoxRunning_stateChanged(int arg1);

    void update();

    void readSerial();

    void atualizaGrafico(double, double, double, double);

    void ativaNeuronio(float*, float*, float*);

    void atualizaGraficoRede(double, double);

private:
    Ui::MainWindow *ui;

    QSerialPort serial;
    QTimer *timer;

    QByteArray recvBytes;

    float x,y,z, pitch, roll;

    // Declaração de Variáveis.
    unsigned long contador = 0;
    unsigned long epocas = 0;

    QVector <double> xAxis;
    QVector <double> yAxis;
    QVector <double> x2Axis;
    QVector <double> y2Axis;

    int a = 0;
    int b = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int n = 0;
    int contAux=0;
    int contAux2=0;
    int numero_de_padroes = 0;
    int fim = 0;
    int funcao = 0;

    float rnd = 0;
    float soma = 0;
    float taxa_aprendizado = 0;
    float MOMENTUM = 0;
    float ERRO = 0;
    float erro_medio_quadratico = 0;
    float erro_quadratico = 0;
    float threshold = 0;

    // Declaração do Número de Neurônios nas Camadas.
    static const int cx = 1;
    static const int c1 = 10;
    static const int c2 = 5;

    // Declaração do Vetor de Pesos entre Camadas.
    float w1[cx*c1] = {0};  // camada de entrada x camada1
    float w2[c1*c2] = {0};  // camada1 x camada2
    float dw1[cx*c1] = {0}; //cx*c1
    float dw2[c1*c2] = {0}; //c1*c2

    // Delcaração dos Vetores das Camadas de Neurônios.
    float entrada_camada1[c1] = {0};
    float saida_camada1[c1] = {0};
    float erro_camada1[c1] = {0};

    float entrada_camada2[c2] = {0};
    float saida_camada2[c2] = {0};
    float erro_camada2[c2] = {0};

    float saidas[c2] = {0};

    float p[21][1] =
    {
        {-1.0},
        {-0.9},
        {-0.8},
        {-0.7},
        {-0.6},
        {-0.5},
        {-0.4},
        {-0.3},
        {-0.2},
        {-0.1},

        {0.0},
        {0.1},
        {0.2},
        {0.3},
        {0.4},
        {0.5},
        {0.6},
        {0.7},
        {0.8},
        {0.9},
        {1.0}
    };

    float d[21][5] =
    {
        {1.0, 1.0, 0.0, 0.0, 0.0},    // -1.0
        {1.0, 1.0, 0.0, 0.0, 0.0},    // -0.9
        {1.0, 1.0, 0.0, 0.0, 0.0},    // -0.8
        {1.0, 1.0, 0.0, 0.0, 0.0},    // -0.7
        {1.0, 1.0, 0.0, 0.0, 0.0},    // -0.6
        {1.0, 1.0, 0.0, 0.0, 0.0},    // -0.5
        {0.0, 1.0, 0.0, 0.0, 0.0},    // -0.4
        {0.0, 1.0, 0.0, 0.0, 0.0},    // -0.3
        {0.0, 1.0, 0.0, 0.0, 0.0},    // -0.2
        {0.0, 1.0, 0.0, 0.0, 0.0},    // -0.1
        {0.0, 0.0, 1.0, 0.0, 0.0},    //  0.0
        {0.0, 0.0, 0.0, 1.0, 0.0},    //  0.1
        {0.0, 0.0, 0.0, 1.0, 0.0},    //  0.2
        {0.0, 0.0, 0.0, 1.0, 0.0},    //  0.3
        {0.0, 0.0, 0.0, 1.0, 0.0},    //  0.4
        {0.0, 0.0, 0.0, 1.0, 1.0},    //  0.5
        {0.0, 0.0, 0.0, 1.0, 1.0},    //  0.6
        {0.0, 0.0, 0.0, 1.0, 1.0},    //  0.7
        {0.0, 0.0, 0.0, 1.0, 1.0},    //  O.8
        {0.0, 0.0, 0.0, 1.0, 1.0},    //  0.9
        {0.0, 0.0, 0.0, 1.0, 1.0}     //  1.0
    };

    //---------------------------------------------------------------------------
    float funcao_ativacao(float net, int funcao, float a)
    {
        if (funcao)
        {
            return( (exp(a * net) - exp(-a * net)) / (exp(a * net) + exp(-a * net)) );
        }
        return( 1.0 / (1.0 + exp(-a * net)) );
    }

    //---------------------------------------------------------------------------
    float derivada(float net, int funcao, float a)
    {
        if (funcao){
            return( 1.0 - pow((exp(a * net) - exp(-a * net)) / (exp(a * net) + exp(-a * net)),2) );
        }
        return( (1.0 / (1.0 + exp(-a * net))) * (1.0 - (1.0 / (1.0 + exp(-a * net)))) );
    }

    int StringSearch(const char *value);

};

#endif // MAINWINDOW_H
