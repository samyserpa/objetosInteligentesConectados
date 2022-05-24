#include <WiFi.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
#include <DHT.h>
#define DHTPIN 33
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);                                                                              
const char* ssid = "SEU SSID";                                                          
const char* password = "SUA SENHA";                                                              
const char* mqtt_server = "broker.mqtt-dashboard.com";                                            
WiFiClient espClient;                                                                             
PubSubClient client(espClient);                                                                   
unsigned long lastMsg = 0;                                                                               

char Led;                                                                                  

void setup() {                                                                                    

  Serial.begin(9600);
  dht.begin();                                                                                    
  
  Led = 27;                                                                                 

  pinMode(Led, OUTPUT);                                                                             
  0
  setup_wifi();                                                                                   
  client.setServer(mqtt_server, 1883);                                                            
  client.setCallback(callback);                                                                  
}

void setup_wifi() {                                                                               

  delay(10);                                                                                      
  Serial.println("");                                                                             
  Serial.print("Conectando com ");                                                                
  Serial.println(ssid);                                                                           

  WiFi.begin(ssid, password);                                                                     

  while (WiFi.status() != WL_CONNECTED) {                                                         
    delay(500);                                                                                   
    Serial.print(".");                                    
  }                  

  Serial.println("");                                                                             
  Serial.println("WiFi conectado");                                                               
  Serial.println("IP: ");                                                                         
  Serial.println(WiFi.localIP());                                                                 
}

void callback(char* topic, byte* payload, unsigned int length) {                                  
  Serial.print("Mensagem recebida [");                                                            
  Serial.print(topic);                                                                            
  Serial.print("] ");                                                                             
  for (int i = 0; i < length; i++) {                                                              
    Serial.print((char)payload[i]);                                                               
  }
  Serial.println("");                                                                             
  if ((char)payload[0] == 'l') {                                                                  
    digitalWrite(Led, HIGH);                                                                     
    snprintf (msg, MSG_BUFFER_SIZE, "A led está ligada");                                 
    Serial.print("Publica mensagem: ");                                                           
    Serial.println(msg);                                                                          
    client.publish("led", msg);                                                             
  }
  Serial.println("");                                                                             
  if ((char)payload[0] == 'd') {                                                                  
    digitalWrite(Led, LOW);                                                                      
    snprintf (msg, MSG_BUFFER_SIZE, "A led está desligada");                              
    Serial.print("Publica mensagem: ");                                                           
    Serial.println(msg);                                                                          
    client.publish("led", msg);                                                             
  }
}

void reconnect() {                                                                                
  while (!client.connected()) {                                                                   
    Serial.print("Aguardando conexão MQTT...");                                                   
    String clientId = "ESP32Client";                                       
    clientId += String(random(0xffff), HEX);                                                      
    if (client.connect(clientId.c_str())) {                                                       
      Serial.println("conectado");                                                                
      client.subscribe("publisher");                                                         
    } else {                                                                                      
      Serial.print("falhou, rc=");                                                                
      Serial.print(client.state());                                                               
      Serial.println("tente novamente em 5s");                                                    
      delay(5000);                                                                                
    }
  }
}

void loop() {                                                                                     
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();  
  float f = dht.readTemperature(true);
  float tempf = dht.computeHeatIndex(f, h);
  float tempc = dht.computeHeatIndex(t, h, false);
  
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }   
  sprintf(msg,"%f",tempc);                                                          
  client.publish("tempe", msg); 
  sprintf(msg,"%f",h);                                                    
  client.publish("umid", msg);
  if (!client.connected()) {                                                                      
    reconnect();                                                                                  
  }  
  client.loop();                                                                                                                                           
}
