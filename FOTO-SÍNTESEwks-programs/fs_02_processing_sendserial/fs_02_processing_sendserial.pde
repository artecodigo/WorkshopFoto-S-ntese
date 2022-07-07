
// Foto-si´ntese, Arduino + Processing Workshop, Andre Sier, 2013


// controlar a velocidade de piscar do led

import processing.serial.*;

Serial myPort;  // Create object from Serial class
int valor_a_enviar;        // Data a enviar da porta serie
int valor_do_rato;        // valor a enviar

void setup() 
{
  size(400, 200);
  
  // escrever as portas série disponiveis no computador
  println(Serial.list());
  
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  background(255);
  
  // calcular o valor do rato
  valor_do_rato = (int) map ( mouseX, 0, width, 0, 255);
  
  // se chegar algo via serial, processar a mensagem aqui
  while(myPort.available()>0){
    // chegam os códigos ascii serial em codigo numerico
    int ascii = myPort.read();
    char caractere = char(ascii);
    
     print(caractere); //escrever na consola do processing o q vem por serial 
  }
  
  
  if(mousePressed){
    // se o rato for pressionado, envia-lo
    
    valor_a_enviar = valor_do_rato;
    
    myPort.write(valor_a_enviar);
    
    fill(255,0,0); // cor vermelha
  } else {
    fill(0); // cor vermelha
  }
  
  rect( 20, 150, 50, 50);
  
  
  String info = "carrega no rato para enviar um byte para o arduino\n"+
 " valor enviado: " + valor_a_enviar+"\n"+
 " valor do rato: " + valor_do_rato + "\n"+
 " valor que chega ao arduino (ms): " + valor_do_rato*10 + "\n";
 

 
  fill(0);
  text(info, 10, 10);
  
  
}

boolean mouseOverRect() { // Test if mouse is over square
  return ((mouseX >= 50) && (mouseX <= 150) && (mouseY >= 50) && (mouseY <= 150));
}


/*
  // Wiring/Arduino code:
 // Read data from the serial and turn ON or OFF a light depending on the value
 
 char val; // Data received from the serial port
 int ledPin = 4; // Set the pin to digital I/O 4
 
 void setup() {
 pinMode(ledPin, OUTPUT); // Set pin as OUTPUT
 Serial.begin(9600); // Start serial communication at 9600 bps
 }
 
 void loop() {
 if (Serial.available()) { // If data is available to read,
 val = Serial.read(); // read it and store it in val
 }
 if (val == 'H') { // If H was received
 digitalWrite(ledPin, HIGH); // turn the LED on
 } else {
 digitalWrite(ledPin, LOW); // Otherwise turn it OFF
 }
 delay(100); // Wait 100 milliseconds for next reading
 }
 
 */
