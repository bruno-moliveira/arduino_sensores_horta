#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

//IMPORTAR BIBLIOTECA
#include "DHT.h"

//MYSQL
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

IPAddress server_addr(54,207,123,154);  // IP of the MySQL *server* here
char user[] = "admin";              // MySQL user login username
char password[] = "12345678";        // MySQL user login password

// Sample query
char query[] = "select * from arduino.sensores s;";

WiFiClient client;
MySQL_Connection conn((Client *)&client);

//DEFINIÇÃO DE PINAGEM
#define DHTPIN A1 //PINO DHT11
#define DHTTYPE DHT11 //DHT 11
#define pinoRele 7  //PINO QUE ATIVA O RELE
const int pinoSolo = A0; //PINO UTILIZADO PELO SENSOR DE UMIDADE DO SOLO
DHT dht(DHTPIN, DHTTYPE);
int ValAnalogIn; //INTRODUZ O VALOR ANALÓGICO AO CÓDIGO

void setup(){

    Serial.begin(115200); //INICIALIZA A SERIAL
    dht.begin(); //INICIALIZA O DHT11
    while (!Serial);

    Serial.println("Conectando...");
    
    if (conn.connect(server_addr, 3306, user, password)) {
      delay(1000);
    }
    else
      Serial.println("Connection failed.");

    
    pinMode(pinoRele, OUTPUT); //SAIDA DE DADOS
    Serial.println("Ligando sensores..."); //IMPRIME O TEXTO NO MONITOR SERIAL
    delay(3000); //INTERVALO DE 3 SEGUNDOS
    

}

void loop(){  

    //s = UMIDADE DO SOLO | sMin = UMIDADE MINIMA DO SOLO | u = UMIDADE DO AR | t = TEMPERATURA 
    float u = dht.readHumidity(); //COLETA DOS DADOS DE UMIDADE DO AR
    float t = dht.readTemperature(); //COLETA DOS DADOS DE TEMPERATURA
    ValAnalogIn = analogRead(pinoSolo); //RELACIONA O VALOR ANALÓGICO COM O RECEBIDO DO SENSOR
    int s = map(ValAnalogIn, 1023, 0, 0, 100); //RELACIONA O VALOR ANALÓGICO À PORCENTAGEM 
    int sMin = 45; //UMIDADE MINIMA DO SOLO
    
    
    Serial.print("|Umidade do solo: "+String(s)+"%|Umidade do ar: "+String(u)+"%|Temperatura: "+String(t)+"ºC|"); //IMPRIME O TEXTO NO MONITOR SERIAL

    //CONDIÇÕES PARA ATIVAR A BOMBA DE AGUA
    if (s <= sMin && s <= sMin*0.50) { //SE A PORCENTAGEM FOR MENOR OU IGUAL E MENOR QUE A METADE DO IDEAL
        Serial.println("Irrigando a planta|"); //IMPRIME A FRASE NO MONITOR SERIAL
        digitalWrite(pinoRele, LOW); //DESATIVA O PINO E ATIVA O RELE
        delay(6000); //INTERVALO DE 6 SEGUNDOS
    } else if (s <= sMin) {
        Serial.println("Irrigando a planta|"); //IMPRIME A FRASE NO MONITOR SERIAL
        digitalWrite(pinoRele, LOW); //DESATIVA O PINO E ATIVA O RELE
        delay(3000); //INTERVALO DE 3 SEGUNDOS
    } else { //SE NAO
            Serial.println("Planta Irrigada|"); //IMPRIME A FRASE NO MONITOR SERIAL
            digitalWrite(pinoRele, HIGH);  //ATIVA O PINO E DESARMA O RELE
    }

    digitalWrite(pinoRele, HIGH); //ATIVA O PINO E DESARMA O RELE

  

    delay(1000);  //INTERVALO DE 60 SEGUNDOS
}
