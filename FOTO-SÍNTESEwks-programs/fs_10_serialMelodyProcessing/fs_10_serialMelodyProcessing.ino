// send serial to control melody
// AS, 2011

import processing.serial.*;
Serial port;

PFont font;

char k='p', prevK='p';

void setup() {
  size(256, 150);

  println("Available serial ports:");
  println(Serial.list());
  
    // Uses the first port in this list (number 0).  Change this to
  // select the port corresponding to your Arduino board.  The last
  // parameter (e.g. 9600) is the speed of the communication.  It
  // has to correspond to the value passed to Serial.begin() in your
  // Arduino sketch.
  port = new Serial(this, Serial.list()[0], 9600);  

  // If you know the name of the port used by the Arduino board, you
  // can specify it directly like this.
  //port = new Serial(this, "COM1", 9600);
  font = createFont("",52);
  textFont(font,52);
}


char incomingSerial = '0'; 

void draw(){
 
  // READ SERIAL  debug
  while(port.available()>0){
     incomingSerial = (char)port.read(); 
  }
  
  
  // SEND COMMANDS from keys  
  
   boolean send = false;

   if(keyPressed){   
      k = (char) key; 
   } else { //keyReleased
      k = 'p';     
   }   

      if(prevK!=k){
         send=true;
         prevK = k; 
         println(k);    
      }
      
   if(send){
      port.write(k); 
      println("sent: "+k);    
   }
   
   // graphix
   background(255);
   fill(0);
   textFont(font, 52);
   text(k+"     "+incomingSerial, width/5, height/2);
   textFont(font, 14);
   text("notas[] 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'p' ", 2, height/1.2);
  
}
