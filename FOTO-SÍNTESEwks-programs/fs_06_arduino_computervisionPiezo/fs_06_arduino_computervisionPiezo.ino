
// Foto-si´ntese, Arduino + Processing Workshop, Andre Sier, 2013


// variaveis a usar no programa

int led_status_pin = 13;

int speaker_pin = 4;

int tempo_som = 0;

int frequencia = 440;

// funcao setup
void setup() {
  // put your setup code here, to run once:

  //pinMode(13, OUTPUT);
  pinMode(led_status_pin, OUTPUT); // o pin do led e output
  pinMode(speaker_pin, OUTPUT); // o pin do speaker e output

  Serial.begin(9600); // iniciar a comunicaçao serial 

}

// funcao loop
boolean ledblink = false;
void loop() {
  // put your main code here, to run repeatedly: 

  ledblink = !ledblink;
  digitalWrite(led_status_pin, ledblink ? HIGH : LOW);



  while(Serial.available()>0){
   
      // o protocolo envia sempre primeiro a frequencia e logo depois o num frames ligado

      // a frequencia de 0-255 e convertida aqui
      frequencia = Serial.read() * 10;
      
      tempo_som = Serial.read(); // tempo de som em frames de 30ms
    
      Serial.println(frequencia);
      Serial.println(tempo_som);
  }


  if( tempo_som-- <= 0 ){
   
       tempo_som = 0; 
       
       noTone(speaker_pin);
    
  } else {
   
       tone(speaker_pin,  frequencia);
    
  }


  delay(30); // espera 30 ms

}


