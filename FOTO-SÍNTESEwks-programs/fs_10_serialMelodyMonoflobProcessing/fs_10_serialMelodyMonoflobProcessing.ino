/*
  monoflob 
  (vs. 20090621)
  
  started out as buttons to trigger things, ended up
  with a nice fade engine in the buttons due to presence
  this works really sweet connected to soundfile banks gains  
  loosely inspired from the great and simple monome
  
  andré sier 
  http://s373.net
 
 
 version to control arduino snd's
 */

import processing.opengl.*;
import processing.video.*;
import processing.serial.*;
import s373.flob.*;

/// vars
Capture video;
Serial port;
Flob flob; 
ArrayList blobs;
char incomingSerial = '0'; 
char notas[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'p'};  

/// video params
int tresh = 10;
int fade = 25;//120;
int om = 1;
int videores=128;
boolean drawimg=true;
String info="";
PFont font;
int videotex = 3;//0;
int colormode = flob.BLUE;
float fps = 60;

Monoflob mono;

void setup(){
  //bug 882 processing 1.0.1
  try { quicktime.QTSession.open(); } 
  catch (quicktime.QTException qte) { qte.printStackTrace(); }

  size(700,700,OPENGL);
  frameRate(fps);
  rectMode(CENTER);

  video = new Capture(this, videores, videores, (int)fps);  
  flob = new Flob(video, this); 

  flob.setTresh(tresh).setImage(videotex).setMirror(true,false);
  flob.setOm(1).setFade(fade).setMinNumPixels(20).setMaxNumPixels(1000);
  flob.setColorMode(colormode);

  font = createFont("monaco",9);
  textFont(font);

  mono = new Monoflob(7,7);
  //(20,20);//(10,10);//(3,3);//(5,4);
  
  
  // init serial
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

  
}



void draw(){

    // READ SERIAL  debug
  while(port.available()>0){
     incomingSerial = (char)port.read(); 
  }

  
  // process video  
  if(video.available()) {
    video.read();
    blobs = flob.calc(flob.binarize(video));    
  }

  if(drawimg)
    image(flob.getImage(), 0, 0, width, height);

  rectMode(CENTER);
  int numblobs = blobs.size();//flob.getNumBlobs();  
  for(int i = 0; i < numblobs; i++) {
    ABlob ab = (ABlob)flob.getABlob(i);     
    mono.touch(ab.cx,ab.cy, ab.dimx, ab.dimy);
    fill(0,0,255,100);
    rect(ab.cx,ab.cy,ab.dimx,ab.dimy);
    fill(0,255,0,200);
    rect(ab.cx,ab.cy, 5, 5);
    info = ""+ab.id+" "+ab.cx+" "+ab.cy;
    text(info,ab.cx,ab.cy+20);
  }

  mono.render();

  // stats
  fill(255,152,255);
  rectMode(CORNER);
  rect(5,5,flob.getPresencef()*width,10);
  String stats = ""+frameRate+"\nflob.numblobs: "+numblobs+"\nflob.thresh:" +tresh+
                 " <t/T>"+"\nflob.fade: "+fade+"   <f/F>"+"\nflob.om: "+flob.getOm()+
                 "\nflob.image: "+videotex+"\nflob.colormode: "+flob.getColorMode()+
                 "\nflob.presence:"+flob.getPresencef()+
                 "\nnota: "+mono.k +
                 "\nserial: "+incomingSerial
                 ;
  fill(0,255,0);
  text(stats,5,25);

}


void keyPressed(){
  if(key=='b')
    drawimg^=true;
  if (key=='S')
    video.settings();
  if (key=='s')
    saveFrame("monoflob-######.png");
  if (key=='i'){  
    videotex = (videotex+1)%4;
    flob.setImage(videotex);
  }
  if(key=='t'){
    tresh--;
    flob.setTresh(tresh);
  }
  if(key=='T'){
    tresh++;
    flob.setTresh(tresh);
  }   
  if(key=='f'){
    fade--;
    flob.setFade(fade);
  }
  if(key=='F'){
    fade++;
    flob.setFade(fade);
  }   
  if(key=='o'){
    om^=1;
    flob.setOm(om);
  }   
  if(key=='c'){
    colormode=(colormode+1)%5;
    flob.setColorMode(colormode);
  }   
 if(key==' ') //space clear flob.background
    flob.setBackground(video);
}



