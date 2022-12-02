#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
#include "DHT.h"

#define SERVO 3 // Exemplo de porta 
#define DHTPIN A1 // exemplo de porta (Pode ser digital ou analogica)
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

Servo s; // Variável Servo
int pos=0; // Posição Servo
int angulo = 0;
int x=0;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 125); 
EthernetServer server(8888);  

void setup()
{
    Ethernet.begin(mac, ip);  
    server.begin();    
    s.attach(SERVO);
    Serial.begin(9600);
    s.write(0); // Inicia motor posição zero
    Serial.begin(9600);
    Serial.println("DHT11 test!");
    dht.begin();  
}

void loop()
{
    EthernetClient client = server.available();  
    String req_str = "";
    int h = dht.readHumidity();
    int t = dht.readTemperature();
    if (client) {  
        boolean currentLineIsBlank = true;
        while (client.connected()) { 
            if (client.available()) {  
                char c = client.read(); 
                req_str += c;
                 if (c == '\n' && currentLineIsBlank && req_str.startsWith("G#")) {
                    client.println("GTMS05#");
                  break;
                }
                if (c == '\n' && currentLineIsBlank && req_str.startsWith("L0001#")) {
                  if (isnan(t) || isnan(h)) 
                  {
                    client.println("Nao foi possivel ler o sensor!");
                  } 
                  else
                  {
                    client.println("Umidade: " + (String)h + "P Temperatura: " + (String)t + "C (CODIGO: T"+(String)t+"CM"+(String)h+"P# )");
                  }
                  break;
                }
                if (c == '\n' && currentLineIsBlank && req_str.startsWith("L0002#")) {
                  int cont = 0;
                  while (cont != 2) {
                    if (isnan(t) || isnan(h)) 
                    {
                      client.println("Nao foi possivel ler o sensor!");
                    } 
                    else
                    {
                      client.println("Umidade: " + (String)h + "P Temperatura: " + (String)t + "C (CODIGO: T"+(String)t+"CM"+(String)h+"P# )");
                    }
                    cont++;
                    delay(1000);
                  }
                  break;
                }
                if (c == '\n' && currentLineIsBlank && req_str.startsWith("L0003#")) {
                  int cont = 0;
                  while (cont != 2) {
                    if (isnan(t) || isnan(h)) 
                    {
                      client.println("Nao foi possivel ler o sensor!");
                    } 
                    else
                    {
                      client.println("Umidade: " + (String)h + "P Temperatura: " + (String)t + "C (CODIGO: T"+(String)t+"CM"+(String)h+"P# )");
                    }
                    cont++;
                    delay(1000);
                  }
                  break;
                }
                if (c == '\n' && currentLineIsBlank && req_str.startsWith("L0004#")) {
                  int cont = 0;
                  while (cont != 2) {
                    if (isnan(t) || isnan(h)) 
                    {
                      client.println("Nao foi possivel ler o sensor!");
                    } 
                    else
                    {
                      client.println("Umidade: " + (String)h + "P Temperatura: " + (String)t + "C (CODIGO: T"+(String)t+"CM"+(String)h+"P# )");
                    }
                    cont++;
                    delay(1000);
                  }
                  break;
                }
                if (c == '\n' && currentLineIsBlank && req_str.startsWith("A0001#")) {
                  client.println("ABRINDO VALVULA");
                  pos=180;
                  s.write(pos); // Comando para angulo específico
                  break;
                } 
                if (c == '\n' && currentLineIsBlank && req_str.startsWith("A1001#")) {
                  client.println("FECHANDO VALVULA");
                  pos=0;
                  s.write(pos); // Comando para angulo específico
                  break;
                }
                if (c == '\n' && currentLineIsBlank && req_str.startsWith("L1001#")) {
                  if (pos == 180) 
                  {
                    client.println("A VALVULA ESTA ABERTA (CODIGO: S"+(String)pos+"W#)");
                  }
                  else
                  {
                    client.println("A VALVULA ESTA FECHADA (CODIGO: S"+(String)pos+"W#)");
                  }
                  break;
                } 
                if (c == '\n' && currentLineIsBlank && req_str.startsWith("L1002#")) {
                  int cont = 0;
                  while (cont != 4) {
                    if (pos == 180) 
                    {
                      client.println("A VALVULA ESTA ABERTA (CODIGO: S"+(String)pos+"W#)");
                    }
                    else
                    {
                      client.println("A VALVULA ESTA FECHADA (CODIGO: S"+(String)pos+"W#)");
                    }
                    cont++;
                    delay(1000);
                  }
                  break;
                } 
                if (c == '\n' && currentLineIsBlank && req_str.startsWith("L1003#")) {
                  int cont = 0;
                  while (cont != 4) {
                    if (pos == 180) 
                    {
                      client.println("A VALVULA ESTA ABERTA (CODIGO: S"+(String)pos+"W#)");
                    }
                    else
                    {
                      client.println("A VALVULA ESTA FECHADA (CODIGO: S"+(String)pos+"W#)");
                    }
                    cont++;
                    delay(1000);
                  }
                  break;
                } 
                if (c == '\n' && currentLineIsBlank && req_str.startsWith("L1004#")) {
                  int cont = 0;
                  while (cont != 4) {
                    if (pos == 180) 
                    {
                      client.println("A VALVULA ESTA ABERTA (CODIGO: S"+(String)pos+"W#)");
                    }
                    else
                    {
                      client.println("A VALVULA ESTA FECHADA (CODIGO: S"+(String)pos+"W#)");
                    }
                    cont++;
                    delay(1000);
                  }
                  break;
                } 
                if (c == '\n' && currentLineIsBlank && req_str.startsWith("EXIT#")) {
                  client.println("DESCONECTADO!");
                  client.stop();
                  break;
                }  
    
                if (c == '\n' && currentLineIsBlank) {
                    client.println("escreveu errado fih, escreve dnv!");
                    break;
                }
                if (c == '\n') {
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    currentLineIsBlank = false;
                }
            } 
        } 
        delay(1);      
        client.stop(); 
    } 
}
