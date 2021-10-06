byte pin = 5,  pinB = 6, pinC = 9, pinD = 10;
void setup(){
  pinMode(pin, OUTPUT);   pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);   pinMode(pinD, OUTPUT);

}
void loop() {
    MoverMotores(-200); 
    delay(5000);
    MoverMotores(200);
    delay(5000);
}

void delante(int velocidad){
   analogWrite(9, velocidad); analogWrite(6,velocidad );
   analogWrite(10,0);    analogWrite(5,0); 
}
void atras(int velocidad){
  
   analogWrite(9, 0); analogWrite(6,0);
   analogWrite(10,velocidad);    analogWrite(5,velocidad); 
}

void MoverMotores(int velocidad){
   if(velocidad>0){
    delante(velocidad);
   }
  if(velocidad<0){
    atras(velocidad*-1); 
  }  
}
