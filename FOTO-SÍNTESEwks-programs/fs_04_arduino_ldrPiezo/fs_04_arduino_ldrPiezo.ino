
// Foto-si´ntese, Arduino + Processing Workshop, Andre Sier, 2013


// variaveis a usar no programa

int led_status_pin = 13;

int ldr_pin = A0;
int ldr_val = 0;

int ldr_min = 70; // valor minimo capturado pelo ldr
int ldr_max = 250; // valor maximo capturado pelo ldr


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
  ldr_val = byte(analogRead(ldr_pin));// converter 0-1023 -> 0-255

  // escrever o valor na porta serie
  Serial.write(ldr_val); // escrever como byte
//  Serial.println(ldr_val); // escrever o valor + newline
  
 

  // som
  int hz = map(ldr_val, ldr_min, ldr_max, 100, 5022);
  tone(speaker_pin, hz,30);

  delay(30); // espera 30 ms
  noTone(speaker_pin);

}


