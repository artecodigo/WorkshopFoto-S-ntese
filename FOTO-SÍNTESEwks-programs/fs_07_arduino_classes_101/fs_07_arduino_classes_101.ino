/// arduino classes 101
// andre´ sier, 2010


/// definir o nome de uma classe
// esta class gera rui´do castanho
class myClass {
  /// todas as vari´veis e m´todos s~o p´blicas 
  /// para lhes acedermos e modificarmos os valores
public:  
  int myval; // apenas guardamos 1 valor int dentro desta classe

  // o construtor da classe recebe um valor que copia para myval
  myClass(int v){
    myval = v;
  }

  // a funç~o update avança e constrange o ru´do castanho
  void update(){
    myval += random(-2,3);
    if(myval<0)
      myval =0;
    if(myval>255)
      myval =255;

  }

};


/// se quiseremos derivar classes filhas da classe pai
/// fazemos assim
class myChild : 
public myClass {

};



/// criamos dois objectos do tipo myClass, definidos acima
/// estes s~o os nossos objectos principais
myClass obj1(100);
myClass obj2(50);




void setup(){
  Serial.begin(9600);
}


void loop(){
  obj1.update();
  obj2.update();
  Serial.print(obj1.myval);
  Serial.print(" ");
  Serial.println(obj2.myval);
  delay(25);
}





