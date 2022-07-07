// protocolo led1 led2 led3 , ( 4 bytes )
// 3 luzes
int vals[4] = { 0,0,0,0};
int head = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // vel comunicacao serial
  // portas dos leds, com resistencias
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(40); // 25 fps
  // parsing da mensagem serial
  while (Serial.available() > 0){
    int incoming = Serial.read(); 
    vals[head] = incoming;
    head++;
    if(head > 3) {
      head = 0;
    }

    //Serial.println(incoming);
    // so aqui a mensagem correcta
    if( vals[3] == 44 ) {
      doLeds( vals[0], vals[1], vals[2] );
      head=0; // reset da cebeça de escrita
      vals[3]=0; // assegurar que está pronto p nova msg
      //Serial.println("DOLEDS");
    }
   
  }
}

void doLeds( int v0, int v1, int v2 ) {
  analogWrite( 3, v0);
  analogWrite( 5, v1);
  analogWrite( 6, v2);
}



