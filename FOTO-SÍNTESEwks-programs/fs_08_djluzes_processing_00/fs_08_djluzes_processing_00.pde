

import processing.serial.*;

Serial serie;
int led0 = 0;
int led1 = 0;
int led2 = 0;

void setup() {
  size(100,100);
  serie = new Serial(this, "nomedoard", 9600);
}

void draw(){
  
}

void keyPressed(){
 
  if(key=='1'){
     if(led0==0) led0 = 255;
     else led0 = 0; 
  }
  if(key=='2'){
     if(led1==0) led1 = 255;
     else led1 = 0; 
  }
  if(key=='3'){
     if(led2==0) led2 = 255;
     else led2 = 0; 
  }
   
   // protocolo de escrita
   serie.write(led0);
   serie.write(led1);
   serie.write(led2);
   serie.write(',');
  
}
