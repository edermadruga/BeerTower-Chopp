#include "dadosmesas.h"

DadosMesas::DadosMesas()
{

}

int DadosMesas::getNumeroChoppServido(){

    return quantidade_chopp_mesa;
}
void DadosMesas::setNumeroChoppServido(int valor){

    quantidade_chopp_mesa = valor;
}

float DadosMesas::getValorConta(){

    return valor_da_conta_mesa;
}
void DadosMesas::setValorConta(float valor){

    valor_da_conta_mesa = valor;
}

int DadosMesas::getStatus(){

    return status;

}
void DadosMesas::setStatus(int index){

    status = index;
}
