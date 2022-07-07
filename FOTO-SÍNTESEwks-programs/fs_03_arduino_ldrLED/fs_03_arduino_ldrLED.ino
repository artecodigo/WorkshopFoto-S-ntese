
// Foto-si´ntese, Arduino + Processing Workshop, Andre Sier, 2013


/*

	LDR voltage divider connection


	+5v--LDR--T---resist(+-10k)---ground
			      |
            |analog-read

*/




// variaveis a usar no programa

int led_status_pin = 13;

int led_control_pin = 5;
int led_control_val = 0; //valor analogico a enviar para o led
int led_max_val = 250; //valor maximo de brilho 0-255

int ldr_pin = A0;
int ldr_val = 0;

int ldr_min = 70; // valor minimo capturado pelo ldr
int ldr_max = 250; // valor maximo capturado pelo ldr

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

  Serial.begin(9600); // iniciar a comunicaçao serial
digitalWrite(13,HIGH);
}

// funcao loop
void loop() {
  // put your main code here, to run repeatedly:

  // ler o valor do ldr convertido para byte 0-255
  ldr_val = byte(analogRead(ldr_pin));

  // escrever o valor na porta serie
 // Serial.write(ldr_val); // escrever como byte
  Serial.println(ldr_val); // escrever o valor + newline


//  led_control_val = ldr_val;
  led_control_val = map(ldr_val, ldr_min, ldr_max, 0, led_max_val);

  if(true){
    led_control_val = constrain(led_control_val,0,led_max_val);    
  }


  analogWrite(led_control_pin, led_control_val);

  delay(30); // espera 30 ms


}
