
// Foto-si´ntese, Arduino + Processing Workshop, Andre Sier, 2013


// visualizar o LDR

import processing.serial.*;

Serial myPort;  // Create object from Serial class
int valor_do_ldr;        // valor cru do LDR

float valor_do_ldr_suave; // valor filtrado do LDR

// variáveis para os gráficos
float linhax=0, linhay=25, linhavelx=5, linhavely=25;

void setup() 
{
  size(1024, 720);
  // escrever as portas série disponiveis no computador
  println(Serial.list());

  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.

  String portName = "/dev/ttyUSB0";////Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  
  background(255); // limpar o background na setup
}



void draw() {

//  background(255); // não desenhar o background


  // se chegar algo via serial, processar a mensagem aqui
  while (myPort.available ()>0) {
    // chegam os códigos ascii serial em codigo numerico
    // os valores do LDR ocupam 1byte(0-255)
    valor_do_ldr = myPort.read();
    println(valor_do_ldr);
  }

  
  // calcular o valor suave do ldr
  // o_valor = (valordestino - o_valor) * percentagemfiltro;
  valor_do_ldr_suave += ( valor_do_ldr - valor_do_ldr_suave ) * 0.12;

  // avançar a linha
  linhax += linhavelx;
  if(linhax>=width){
     linhax = 0;
     linhay += linhavely;
     if(linhay >= (height - linhavely) ){
        linhay = linhavely; 
     }
  }

  // desenhar uma linha desde a posição anterior à nova posição
  stroke(0, 100); // cor preta, alpha 100/255
  
  // cor dependente do valor do ldr, alpha 100/255
  fill ( valor_do_ldr_suave, 100);
  
  float diametro = valor_do_ldr_suave * 0.55;
  
  ellipse ( linhax, linhay, diametro, diametro);
  

}