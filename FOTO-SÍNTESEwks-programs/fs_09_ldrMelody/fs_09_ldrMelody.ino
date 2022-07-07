#define ldrMin 0
#define ldrMax 200

class ldrMelody {

public:

  int speakerPin, ldrPin;
  int val,valMin,valMax, ldrVal, dur;
  

  ldrMelody (int sp, int lp) {
    speakerPin = sp;
    ldrPin = lp;
    reset();     
  } 


  void reset(){
    valMin = random(1,100);
    valMax = random(100,2000);
    val = random(valMin,valMax);
    dur = random(20,100);
  }

  void play(){

      ldrVal = analogRead(ldrPin);
      val = map(ldrVal,ldrMin, ldrMax, valMin, valMax );
//      val = constrain(val, valMin, valMax);
    
      tone(speakerPin, val);
      delay(dur);
      noTone(speakerPin);
      
  }


};





/// criamos dois objectos do tipo ldrMelody, definidos acima
ldrMelody ldrmel1(4,0); //speaker pin, ldr pin
ldrMelody ldrmel2(5,1);
/// l´ogica para reset
int frameCount = 0;
int maxFrames = 200;


void reset(){
  frameCount = 0;
  maxFrames = random(500); 
  ldrmel1.reset();
  ldrmel2.reset();
}


void setup(){
  Serial.begin(9600);
  reset();
}


boolean led = false;
void loop(){
  led = !led; //trocar o valor boolean de led de false a true e vice-versa
  digitalWrite(13,led);

  frameCount++;
  if(frameCount>maxFrames||random(1000)<5){
    reset();
  }

  Serial.print(frameCount);
  Serial.print(" ");
  Serial.print(ldrmel1.val);
  Serial.print(" ");
  Serial.print(ldrmel2.val);
  Serial.print(" ");
  Serial.print(ldrmel1.ldrVal);
  Serial.print(" ");
  Serial.print(ldrmel2.ldrVal);  
  Serial.println();

  ldrmel1.play();
  ldrmel2.play();
}


