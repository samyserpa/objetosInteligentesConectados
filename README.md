# Objetos Inteligentes Conectados

## [Video Projeto](https://youtu.be/nSacb9xlhKQ)

# Introdução
Um projeto inspirado em fornecer melhor assistência de iluminação para plantas de interiores que não tem muito acesso ao sol, junto à medição de temperatura e umidade do ambiente. Tem a finalidade de ligar e desligar a luz por meio do aplicativo, assim como ver as informações de temperatura e umidade no mesmo, dando mais praticidade para o cultivo das plantas.

## Funcionamento
O protótipo consiste em um dispositivo ESP32, um protoboard, um atuador led, e um sensor como mostrado na figura 3 (LOCATELLI, 2022), o aplicativo controla as saídas do ESP32 e recebe leituras do sensor do ESP32 usando o protocolo de comunicação MQTT, podendo alterar seu estado para ligado ou desligado. A aplicação publica mensagens (“ l ” ou “ d ”) no tópico esp32/output . O ESP32 está inscrito nesse tópico. Assim, ele recebe a mensagem com “l” ou “d” para ligar ou desligar o LED. O ESP32 publica a temperatura no tópico esp32/tempe e a umidade no tópico esp32/umid . O aplicativo está inscrito nesses tópicos. Assim, ele recebe leituras de temperatura e umidade que podem ser exibidas em um gráfico.
Foi utilizado 4 resistores de 1k conectado ao DHT22 e 1 resistor na led (Figura 4). Os aplicativos foram configurados (Figura 6 e 7) para receber as leituras enviadas do ESP32 pelo Host MQTT.

## Hardware
ESP32 escolhido pela praticidade de ter o wi-fi imbutido além do custo benefício. DHT22 sensor para a leitura de temperatura e umidade. Protoboard, jumpers da preferência de cada um, utilizei 2 macho x macho e 7 macho x fêmea. Um led e 5 resistores, 4 para o DHT22 e 1 para o led.

## Módulo de comunicação
O MQTTBox e MQTT Dahs(Figura 6 e 8) é leve e seu funcionamento se baseia na troca de informações entre Subscriber(Subscrito) e Publisher(Publicador), sendo que o mensageiro responsável por encaminhar e receber os dados é chamado de broker, podendo esse ser hospedado na nuvem ou local.   O sensor de temperatura atua como Publisher e publica o dado medido no tópico “tempe”, esse dado é transmitido ao Broker que encaminha para todos os clientes que estão subscritos nesse mesmo tópico “tempe”, no caso, o Computador e o Celular.
