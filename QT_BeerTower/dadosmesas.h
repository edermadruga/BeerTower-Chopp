#ifndef DADOSMESAS_H
#define DADOSMESAS_H


class DadosMesas
{

private:
    double valor_chopp = 48.90;
    float valor_da_conta_mesa = 0;
    int quantidade_chopp_mesa = 0;
    int status = 0;
public:

    DadosMesas();


    void setNumeroChoppServido(int valor);
    int getNumeroChoppServido();
    void setValorConta(float valor);
    float getValorConta();
    void setStatus(int index);
    int getStatus();

};

#endif // DADOSMESAS_H
