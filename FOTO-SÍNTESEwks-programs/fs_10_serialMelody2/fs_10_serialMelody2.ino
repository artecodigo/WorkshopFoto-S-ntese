// adaptado do ex playMelody
// vamos ler serial, e converter comandos em char para notas a serem tocadas


int ledPin = 13;
int speakerOut = 9;               

byte notas[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'p'};  
int tones[] = {  1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 0};
int duracoes[] = {  20, 50, 70, 45, 100, 120, 220, 500, 1000};

int statePin = LOW;


byte nota = 'p'; // a nota actual
int duracao = 100; // a duracao actual
int toneIdx = 8;

void setup() {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);
}


void understand(){
    // triar o incoming serial
    if(Serial.available()>0){
       byte incoming = Serial.read();
       boolean found = false;
       for(int i=0; i<9; i++){
          if(incoming==notas[i]){
             nota = notas[i];
             toneIdx = i;
             found = true;
          }  
       }
       
       if(!found){
          int a = random(9);
          nota = notas[a];
          toneIdx = a; 
       }
       // a duraç~ao ´e sempre aleat´oria
       duracao = duracoes[random(9)];  
    } else { // se n~o houver Serial disponivel, silencio
      nota = 'p';
      duracao = duracoes[random(9)];  
      toneIdx = 8;
    }


}



boolean led = false;
void loop(){
   led = !led; //trocar o valor boolean de led de false a true e vice-versa
   digitalWrite(ledPin,led);

  // l^e serial coloca na var nota e dur os valores a tocar
  understand();

  //executar
  // 1º desligar o som == noTone()
  analogWrite(speakerOut, 0);     
  
  // 2º tocar o som seleccionado
  if(nota!='p'){    
      int currentmillis = millis();
      int maxmillis = currentmillis + duracao;
      
      while( currentmillis < maxmillis) {
          analogWrite(speakerOut,500); // 1/2 volume
          delayMicroseconds(tones[toneIdx]);
          analogWrite(speakerOut, 0);
          delayMicroseconds(tones[toneIdx]);
          
          currentmillis = millis();
      }
  }
    else { // tocar sil^encio   
 
      int currentmillis = millis();
      int maxmillis = currentmillis + duracao;

      while( currentmillis < maxmillis) {
           // make a pause of a certain size
          analogWrite(speakerOut, 0);
          delayMicroseconds(500);

          currentmillis = millis();
      }
        
    }
    
    
    // 3. debug
    Serial.println(duracao);
    Serial.print(" ");
    Serial.print(nota);
    

//    digitalWrite(ledPin, statePin);
//    for (count3 = 0; count3 <= (melody[count*2] - 48) * 30; count3++) {
//      for (count2=0;count2<8;count2++) {
//        if (names[count2] == melody[count*2 + 1]) {       
//          analogWrite(speakerOut,500);
//          delayMicroseconds(tones[count2]);
//          analogWrite(speakerOut, 0);
//          delayMicroseconds(tones[count2]);
//        } 
//        if (melody[count*2 + 1] == 'p') {
//          // make a pause of a certain size
//          analogWrite(speakerOut, 0);
//          delayMicroseconds(500);
//        }
//      }
//    }
  
}

