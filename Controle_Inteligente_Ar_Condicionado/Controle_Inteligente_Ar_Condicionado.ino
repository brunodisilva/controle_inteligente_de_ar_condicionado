////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                        //
//    Programa: Controle Inteligente de Ar Condicionado com DHT11                                         //
//    Empresa: ABL Tecnologia                                                                             //
//    Autor: Eduardo Aquino                                                                               //
//    Versão: 1.0                                                                                         //
//    Data: 2014/02/07                                                                                    //
//                                                                                                        //  
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Abaixo incluimos a biblioteca DHT11.
#include <dht.h>
//Pino DATA do Sensor ligado na porta Analogica A0.
#define dht_dpin A0
//Instanciamos a variável referente ao controle do rele da turbina, e especificamos o Pino Digital 2.
int rotacaoTurbina = 2;
//Inicializamod o Sensor DHT11.
dht DHT;

void setup(){
  //Configurações básicas da Porta Serial.
  Serial.begin(9600);
  //Aguarda 1 seg antes de acessar as informações do Sensor DHT11.
  delay(1000);
  //Especificamos que o Pino Digital 2 que foi setado para uso com o rele, será saída.
  pinMode(rotacaoTurbina, OUTPUT);
}

void loop(){
  //Lemos as informações do sensor DHT11
  DHT.read11(dht_dpin);

  //Imprimimos na Serial a palavra Humidade. 
  Serial.print("Humidade: ");
  //Logo a fente da palavra Humidade, imprimimos o valor lido pelo Sensor em Porcentagem.
  Serial.print(DHT.humidity,0);
  //Imprime o simbolo % após o valor lido pelo Sensor DHT11.
  Serial.print("% - ");
  //Imprimimos na Serial a palavra Temperatura.
  Serial.print("Temperatura: ");
  //Logo a fente da palavra Temperatura, imprimimos o valor lido pelo Sensor em Graus Célsius.
  Serial.print(DHT.temperature,0);
  //Imprimimos na Serial a letra C para indicar que a leitura é em Graus Célsius.
  Serial.println("C");
  //Tempo de intervalo de cada leitura. Não diminuir muito este valor. O ideal é a leitura a cada 2 segundos
  delay(3000);  
  
  /////////////////////////////////////////////////////////////////////////ROTINAS REFERENTE AO CONTROLE DA TEMPERATURA/////////////////////////////////////////////////////////////////////////
  
  //Se a temperatura for maior ou igual a 30 Graus Célsius, verifica o estado da Porta Digital 2, referente a rotação da turbina, se for maior ou igual a 30, se sim, então.  
  if(DHT.temperature >= 30){ 
    //Verifica se o estado da Porta Digital 2 referente a rotação da turbina for igual a LOW, ou seja em Estado Lógico Baixo, se sim, então   
    if(digitalRead(rotacaoTurbina) == LOW){
      //Colocamos a Porta Digital 2 referente a rotação da turbina em HIGH, ou seja em Estado Lógico Alto.      
      digitalWrite(rotacaoTurbina, HIGH);         
    }     
  }
  
  //Se a temperatura for menor ou igual a 26 Graus Célsius, verifica o estado da Porta Digital 2, referente a rotação da turbina, se for menor ou igual a 26, então.  
  if(DHT.temperature <= 27){
    //Verifica se o estado da Porta Digital 2 referente a rotação da turbina for igual a HIGH, ou seja em Estado Lógico Alto, se sim, então    
    if(digitalRead(rotacaoTurbina) == HIGH){
      //Colocamos a Porta Digital 2 referente a rotação da turbina em LOW, ou seja em Estado Lógico Alto      
      digitalWrite(rotacaoTurbina, LOW);         
    }     
  }
  
  /////////////////////////////////////////////////////////////////////////ROTINAS REFERENTE AO CONTROLE DA TEMPERATURA/////////////////////////////////////////////////////////////////////////
}
