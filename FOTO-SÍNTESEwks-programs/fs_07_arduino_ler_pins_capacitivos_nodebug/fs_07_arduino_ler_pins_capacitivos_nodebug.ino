

// Foto-si´ntese, Arduino + Processing Workshop, Andre Sier, 2013


// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//  how much capacitance is on the pin

int botaoThresh = 5;
boolean debugSerial = false;//true;


// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//  how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher
#include "pins_arduino.h" // Arduino pre-1.0 needs this
uint8_t readCapacitivePin(int pinToMeasure) {
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.
  uint8_t cycles = 17;
       if (*pin & bitmask) { cycles =  0;}
  else if (*pin & bitmask) { cycles =  1;}
  else if (*pin & bitmask) { cycles =  2;}
  else if (*pin & bitmask) { cycles =  3;}
  else if (*pin & bitmask) { cycles =  4;}
  else if (*pin & bitmask) { cycles =  5;}
  else if (*pin & bitmask) { cycles =  6;}
  else if (*pin & bitmask) { cycles =  7;}
  else if (*pin & bitmask) { cycles =  8;}
  else if (*pin & bitmask) { cycles =  9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}









// classe de cada botao

class BotaoJoystick{
public:
  int pin;
  boolean on;
  boolean changed;
  char comandoOn, comandoOff;

  void setup(int p, char con, char coff){
    pin = p;
    comandoOn = con;
    comandoOff = coff;
    on = false; 
    changed = false;
  }

  void set(boolean o){
    if(o!=on){
      on = o;
      changed = true; 
    }
  }

  void loop(){

    int buttonval = readCapacitivePin(pin);
    if(buttonval>=botaoThresh){
      set(true); 
    } 
    else {
      set(false); 
    }

    if(debugSerial){
       Serial.print("botao pin valor estado: "); 
       Serial.print(pin); 
       Serial.print("  "); 
       Serial.print(buttonval); 
       Serial.print("  "); 
       Serial.print(on); 
       Serial.println();
    }


    if(changed){
      changed = false;

      if(on){
        Serial.write(comandoOn); 
      } 
      else {
        Serial.write(comandoOff); 

      }

    }
  }

};




/// os botoes dos players sao os nossos objectos

BotaoJoystick ALeft, ARight, BLeft, BRight;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // configurar os botoes e os comandos serial q enviam  
  ALeft.setup(7, 'A', 'a');
  ARight.setup(8, 'D', 'd');
  BLeft.setup(9, 'J', 'j');
  BRight.setup(10, 'L', 'l');
  
  digitalWrite(13,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly: 

  ALeft.loop();
  ARight.loop();
  BLeft.loop();
  BRight.loop();

  delay(40); // 25fps
}



