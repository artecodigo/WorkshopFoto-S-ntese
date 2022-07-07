
// Foto-si´ntese, Arduino + Processing Workshop, Andre Sier, 2013

/*
 0-ve se ha alguma mensagem nova
 1-liga o led
 2-espera
 3-desliga o led
 4-espera
 
 repete
 */




// variaveis a usar no programa

int onde_esta_o_led = 13;

int tempo_de_delay = 1000;



// funcao setup
void setup() {
  // put your setup code here, to run once:

  //pinMode(13, OUTPUT);
  pinMode(onde_esta_o_led, OUTPUT); // o pin do led e output

  Serial.begin(9600); // iniciar a comunicaçao serial 

}

// funcao loop
void loop() {
  // put your main code here, to run repeatedly: 

  // ve se ha alguma mensagem nova
  while (Serial.available()>0){

    int val = Serial.read();
    
    Serial.print("recebi o valor: "); // receber 1 byte (0-255)
    Serial.print(val);
    
    val = val * 10; // multiplicar por 10 (0-2550)
    
    tempo_de_delay = val; // ligar o valor ao tempo de delay

  }

  digitalWrite( onde_esta_o_led, HIGH); // ligar o led

  delay(tempo_de_delay);

  digitalWrite( onde_esta_o_led, LOW); // desligar o led


  delay(tempo_de_delay);


}


