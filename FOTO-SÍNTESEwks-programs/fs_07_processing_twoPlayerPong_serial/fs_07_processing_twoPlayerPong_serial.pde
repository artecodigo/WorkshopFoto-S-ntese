

// Foto-si´ntese, Arduino + Processing Workshop, Andre Sier, 2013

import processing.serial.*;

Serial myPort;  // Create object from Serial class




//Two Player Pong
//Justin J. Pong, CP1, Mods 16/17
boolean gameover= false, right = false, left = false, d = false, a = false;
int topscore=0;
int bottomscore=0;
float changespeed=0;
Paddle bottom;
Ball pongball;
Paddle top;
void setup()
{
  frameRate(100);
  noStroke();
  pongball= new Ball();
  bottom=new Paddle();
  top=new Paddle();
  top.y=0;
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


void keyPressed()
{
  if (keyCode == LEFT)
  {
    left = true;
  }
  if (keyCode == RIGHT)
  {
    right = true;
  }
  if (key == 'a')
  {
    a=true;
  }
  if (key == 'd' )
  {
    d=true;
  }
}
void keyReleased()
{
  if (keyCode == LEFT)
  {
    left = false;
  }
  if (keyCode==RIGHT)
  {
    right = false;
  }
  if (key=='a')
  {
    a=false;
  }
  if (key=='d')
  {
    d=false;
  }
}




void draw()
{



// processar o serial protocol dos joysticks

 // se chegar algo via serial, processar a mensagem aqui
  while (myPort.available ()>0) {
    byte comando = (byte) myPort.read();
    
    // player 1
    if(comando == 'a'){
       a = false; 
    }
    else if(comando == 'A'){
       a = true; 
    }
    else if(comando == 'd'){
       d = false; 
    }
    else if(comando == 'D'){
       d = true; 
    }
    

    // player 2
    if(comando == 'j'){
       left = false; 
    }
    else if(comando == 'J'){
       left = true; 
    }
    else if(comando == 'l'){
       right = false; 
    }
    else if(comando == 'L'){
       right = true; 
    }



  }




  if (gameover==false)
  {
    background(0);
    bottom.show();
    top.show();
    if (left==true)
    {
      bottom.moveleft();
    }
    if (right==true)
    {
      bottom.moveright();
    }
    if (a==true)
    {
      top.moveleft();
    }
    if (d==true)
    {
      top.moveright();
    }
    pongball.move();
    pongball.bounce();
    pongball.show();
    if (pongball.y<-8)
    {
      gameover=true;
      bottomscore++;
    }
    if (pongball.y>508)
    {
      gameover=true;
      topscore++;
    }
  }
  else //gameover==true
  {
    background(0);
    fill(255, 0, 0);
    changespeed=0;
    textSize(18);
    text("Top Player's Score: "+topscore, 15, 290);
    text("Bottom Player's Score: "+bottomscore, 15, 330);
    textSize(36);
    text("Game over! Click to restart.", 15, 250);
    if (mousePressed==true)
    {
      pongball.x=int(random(200, 301));
      pongball.y=int(random(200, 301));
      int xdirection=int(random(2));
      int ydirection=int(random(2));
      if (xdirection==0)
      {
        pongball.right=true;
      }
      else //xidrection==1
      {
        pongball.right=false;
      }
      if (ydirection==0)
      {
        pongball.up=true;
      }
      else //ydirection==1
      {
        pongball.up=false;
      }
      gameover=false;
    }
  }
}
class Paddle
{
  int x, y;
  Paddle()
  {
    x=250;
    y=496;
  }
  void show()
  {
    fill(255, 0, 0);
    rect(x, y, 60, 4);
  }
  void moveleft()
  {
    if (x>=0)
    {
      x-=5;
    }
  }
  void moveright()
  {
    if (x<=440)
    {
      x+=5;
    }
  }
}
class Ball
{
  int x, y;
  boolean up, right;
  Ball()
  {
    x=16;
    y=484;
    up=true;
    right=true;
  }
  void move()
  {
    if (up==true)
    {
      y=int(y-2-changespeed/2);
    }
    else  //up==false
    {
      y=int(y+2+changespeed/2);
    }
    if (right==true)
    {
      x=int(x+1+changespeed);
    }
    else  //right==false
    {
      x=int(x-1-changespeed);
    }
  }
  void bounce()
  {
    if (get(int(x)-8, int(y))!=color(0))
    {
      right=true;
    }
    if (get(int(x)+8, int(y))!=color(0))
    {
      right=false;
    }
    if (get(int(x), int(y)-8)==color(255, 0, 0))
    {
      up=false;
    }
    if (get(int(x), int(y)+8)==color(255, 0, 0))
    {
      up=true;
      changespeed+=1.0/4;
    }
  }
  void show()
  {
    fill(247, 226, 47);
    ellipse(x, y, 16, 16);
  }
}

