# BeerTower-Chopp


#### Este projeto foi desenvolvido por APOLO DE LIMA (20181610009), EDER MADRUGA COELHO (20181610028), EVERTON JÚNIOR DA SILVA ARRUDA (20181610044) e IVIS FERREIRA DE BRITO (20181610013) na disciplina de Técnicas de Programação (2018.2) tendo como base as aulas ministradas pelo professor PATRIC LACOUTH.

![](figuras/chopeira.png)

# Introdução

Este protótipo é um primeiro fruto de um projeto de um sistema de dosagem automática a ser implementado em torres de Chopp, onde o usuário através de um push button pode dosar uma quantidade exata do Chopp em seu copo. Além dessa função básica, será implementado outras funções como a informação do nível mínimo da chopeira, bem como a solicitação da substituição da mesma por parte do usuário. Para tanto utilizaremos como controlador o ESP8266, push button, LED's, sensor de temperatura DS18B20 e uma válvula de controle de elaboração própria, contendo um servomotor acoplado a uma válvula manual através de um suporte.

O estabelicimento terá acesso aos clientes através de uma aplicação em QT em comunicação serial com o NODE MCU 8266. Já o cliente por sua vez, terá acesso a temperatura do Chopp, bem como a solicitação do garçom junto a mesa e o andamento desta solicitação, A forma de pagamento e o valor gasto através de uma página WEB que poderá ser acessada com qualquer dispositivo móvel com acesso a internet através de um QR Code.

![](figuras/1.png)

É possível visualizar uma tela de estatísticas onde teremos um resumo que informa ao usuário a quantidade total de itens do estoque, bem como a menor quantidade e também a maior. Na figura abaixo, é possível ver esta tela.

![](figuras/2.PNG)

A utilização do formulário é bastante intuitiva. Observe na figura abaixo os diversos itens do formulário e a ação de sua interação com o usuário.

![](figuras/2N.PNG)

![](figuras/4.PNG)

## Menu Arquivo

Neste Menu podemos acessar as opções de Salvar ou Carregar uma lista de Itens. O formato do arquivo será .txt.

## Tela Inserir
