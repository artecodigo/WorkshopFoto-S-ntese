
// Foto-si´ntese, Arduino + Processing Workshop, Andre Sier, 2013


// variaveis a usar no programa

int led_status_pin = 13;

// Use of the tone() function will interfere with PWM output on pins 3 and 11 (on boards other than the Mega).
int led_control_pin = 5;
int led_control_val = 0; //valor analogico a enviar para o led
int led_max_val = 50; //valor maximo de brilho 0-255

int ldr_pin = A0;
int ldr_val = 0;

int ldr_min = 80; // valor minimo capturado pelo ldr
int ldr_max = 200; // valor maximo capturado pelo ldr


int speaker_pin = 4;
/*
 0- ler o valor do ldr
 1- usar o valor do ldr para controlar a luz do led
 */


// funcao setup
void setup() {
  // put your setup code here, to run once:

  //pinMode(13, OUTPUT);
  pinMode(led_status_pin, OUTPUT); // o pin do led e output
  pinMode(led_control_pin, OUTPUT); // o pin do led e output
  pinMode(speaker_pin, OUTPUT); // o pin do speaker e output

  Serial.begin(9600); // iniciar a comunicaçao serial 

}

// funcao loop
boolean ledblink = false;
void loop() {
  // put your main code here, to run repeatedly: 

  ledblink = !ledblink;
  digitalWrite(led_status_pin, ledblink ? HIGH : LOW);

  // ler o valor do ldr
  ldr_val = analogRead(ldr_pin);

  // escrever o valor na porta serie
//  Serial.print(ldr_val);
  Serial.println(ldr_val); // escrever o valor + newline
  
  

//  led_control_val = ldr_val;
  led_control_val = map(ldr_val, ldr_min, ldr_max, 0, led_max_val);

  if(true){
    led_control_val = constrain(led_control_val,0,led_max_val);    
  }


  analogWrite(led_control_pin, led_control_val);


  // som
  int hz = map(ldr_val, ldr_min, ldr_max, 100, 1022);
  tone(speaker_pin, hz,30);

  delay(30); // espera 30 ms
  noTone(speaker_pin);

}


