
// Foto-si´ntese, Arduino + Processing Workshop, Andre Sier, 2013


// visualizar o LDR

import processing.serial.*;

Serial myPort;  // Create object from Serial class
int valor_do_ldr;        // valor cru do LDR
float valor_do_ldr_suave; // valor filtrado do LDR

void setup() 
{
  size(500, 500);
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


  // se chegar algo via serial, processar a mensagem aqui
  while (myPort.available ()>0) {
    // chegam os códigos ascii serial em codigo numerico
    // os valores do LDR ocupam 1byte(0-255)
    valor_do_ldr = myPort.read();
    println(valor_do_ldr);
  }

  // calcular o valor suave do ldr
  // o_valor = (valordestino - o_valor) * percentagemfiltro;
  valor_do_ldr_suave += ( valor_do_ldr - valor_do_ldr_suave ) * 0.05;


  fill(255, 0, 0); //vermelho cru
  // circulo centrado no primeiro quarto do ecran, com raio máximo de 1/2 width
  float raiocru = map(valor_do_ldr, 0, 255, 10, width/2);
  ellipse( width/4, height/2, raiocru, raiocru);


  fill(0, 255, 0); //verde suave
  // circulo centrado no primeiro quarto do ecran, com raio máximo de 1/4 width
  float raiosuave = map(valor_do_ldr_suave, 0, 255, 10, width/2);
  ellipse( width - width/4, height/2, raiosuave, raiosuave);
  
  String info = "LDR cru: "+valor_do_ldr+"\n"+"LDR smo: "+valor_do_ldr_suave;
  fill(0);
  text(info, 5, 15);
}

