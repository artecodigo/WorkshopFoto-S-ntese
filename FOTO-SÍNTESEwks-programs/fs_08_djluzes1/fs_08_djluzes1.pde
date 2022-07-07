

import processing.serial.*;

Serial serie;
int led0 = 0;
int led1 = 0;
int led2 = 0;

void setup() {
  size(100,100);
  serie = new Serial(this, "/dev/ttyUSB1", 9600);
  frameRate(10);
}

void draw(){
 
    float angulo = frameCount * 0.25;
  
   led0 = (int) map( sin(frameCount*0.07), -1,1, 0, 100);
   led1 = (int) map( sin(frameCount*0.25), -1,1, 0, 100);
   led2 = (int) map( sin(frameCount*0.505), -1,1, 0, 100);
  
  // protocolo de escrita
   serie.write(led0);
   serie.write(led1);
   serie.write(led2);
   serie.write(',');
 
  
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
