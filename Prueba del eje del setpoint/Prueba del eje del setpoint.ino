#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo 
// del estado de AD0. Si no se especifica, 0x68 estará implicito
MPU6050 sensor; 
int  gy;
long f_gy;
int  p_gy; 
int gy_o;
int gy_o;
int ay_o;
int gy_o;

void setup() {
  Serial.begin(9600);   //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor

  if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente");
   gy_o=sensor.getYGyroOffset();
   
  Serial.print(gy_o); Serial.print("\t");
  Serial.println("nnEnvie cualquier caracter para empezar la calibracionnn");  
  // Espera un caracter para empezar a calibrar
  while (true){if (Serial.available()) break;}  
  Serial.println("Calibrando, no mover IMU"); 
}
void loop() {
  filtros(); 

}
void filtros(){
   sensor.getRotation(&gx, &gy, &gz);
    f_gy = f_gy-(f_gy>>3)+gy;
    p_gy = f_gy>>3;
    if (counter==100){
        Serial.println(LINEALIZACION(p_gy));
         if (p_gy>0)
          gy_o--;
         else
          gy_o++;
         
         sensor.setYGyroOffset(gy_o);
         counter=0;
  }
  counter++;
  
} 

    
    
    
   