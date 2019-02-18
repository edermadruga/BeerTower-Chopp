
  #include <ESP8266HTTPClient.h>
  #include <ESP8266WiFi.h>
  const char* SSID = "JSNFNDB";
  const char* PASS = "t06iohph";
  HTTPClient http;
  const String LOCATION = "http://beertowerchopp.herokuapp.com/";
  const String UPLOAD = "upload";
  const String DOWNLOAD = "download";

  const String TEMPERATURA = "\"TEMPERATURA\":";
  const String CHAMADO = "\"CHAMADO\":";
  const String VALOR = "\"VALOR\":";

  #include <DallasTemperature.h>
  #include <OneWire.h>
  #define ONE_WIRE_BUS 5                          //D1 pin of nodemcu
  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature sensors(&oneWire);

  int sensor_de_nivel = 16;

  int btn_1 = 4;
  int btn_2 = 13;
  int led_1 = 14;
 
  String atendimento;
  String my_json;

  #include <Servo.h>
  Servo servo1; // Cria um Objeto servo chamado Servo1

   String valor_cliente = "";

  void setup() {

    servo1.attach(15);

  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led_1, OUTPUT);
  pinMode(btn_1, INPUT);
  pinMode(btn_2, INPUT);
  pinMode(sensor_de_nivel, INPUT);

  WiFi.begin(SSID, PASS); //WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println(" Aguardando conexão");
 }
 
 sensors.begin();
 servo1.write(0); 
 
}

void loop() {

     my_json = downloadWEB();
      if(my_json!="1"){
        Serial.print(my_json);
        if(my_json.indexOf("\"CHAMADO\": 1")!=-1){
        digitalWrite(led_1, HIGH);
        }else if(my_json.indexOf("\"CHAMADO\": 0")!=-1){
        digitalWrite(led_1, LOW);
        }
              
     }else{
   
     if(Serial.available() > 0){
      String linha = Serial.readStringUntil('\n');
    if(linha.startsWith("{") && linha.endsWith("}")){
      
          if(linha.indexOf("ok")!=-1){                  
            for(int i=0; i<5; i++){
              digitalWrite(led_1, HIGH);
              delay(500);
              digitalWrite(led_1, LOW);
              delay(500);
            }
          }
          
          if(linha.indexOf("VALOR:")!=-1){
            valor_cliente = ""; 
              //valor_cliente = valor_cliente +"1"; 
              for(int i=7; i<linha.length() - 1; i++){
              valor_cliente = valor_cliente + linha[i];
              }       
          }  
        }
      }

  //verifica o sensor de nível para fazer um chamado
  if(digitalRead(sensor_de_nivel) == HIGH){   
  digitalWrite(led_1, HIGH);
  Serial.print(JSON_CHAMADO());
  delay(1000);
  
  }else if(digitalRead(btn_1)==HIGH){   // botão para chamado
        digitalWrite(led_1, HIGH);
        Serial.print(JSON_CHAMADO());     
   }else{
    
  uploadTEMPERATURA();
  delay(50);
  uploadVALOR();
  delay(50);
  
  }

//servomotor
 if(digitalRead(btn_2)==LOW){   //servo motor
      servo1.write(90); // Comando para angulo específico
   }else if(digitalRead(btn_2)==HIGH){   //servo motor
        // Comando que muda a posição do servo de 180 para 0°
       servo1.write(0); // Comando para angulo específico   
   }
     }
}

 void uploadTEMPERATURA(){
  http.begin(LOCATION+UPLOAD);
  http.addHeader("Content-Type", "application/json");
  http.POST(JSON_TEMP());
  Serial.print(JSON_TEMP());
  http.end();
 }

 void uploadCHAMADO(){
  http.begin(LOCATION+UPLOAD);
  http.addHeader("Content-Type", "application/json");
  http.POST(JSON_CHAMADO());
  Serial.print(JSON_CHAMADO());
  http.end();
 }
 
 String JSON_TEMP(){
  sensors.requestTemperatures();                 
  float temp = sensors.getTempCByIndex(0);
  return "{" +
  TEMPERATURA + String(temp) +
  "}";
 }

 String JSON_CHAMADO(){
  return "{" +
  CHAMADO + "1" +
  "}";
 }

 void uploadVALOR(){
  http.begin(LOCATION+UPLOAD);
  http.addHeader("Content-Type", "application/json");
  http.POST(JSON_VALOR());
  http.end();
 }

 String JSON_VALOR(){
  return "{" +
  VALOR + valor_cliente +
  "}";
 }

 String downloadWEB(){
 http.begin(LOCATION+DOWNLOAD);
 http.GET();
 String payload = http.getString();
 http.end();
 return payload;
}

 
