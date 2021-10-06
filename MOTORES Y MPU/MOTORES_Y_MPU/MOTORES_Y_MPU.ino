// GIROSCOPIO
#include "Wire.h" // This library allows you to communicate with I2C devices.
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
//%6d es para el tabulador
  return tmp_str;
}
//MOTORES 
byte pin = 5,  pinB = 6, pinC = 9, pinD = 10;

//CONTROLADOR 
int16_t error; 
int16_t setpoint= 300;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(pin, OUTPUT);   pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);   pinMode(pinD, OUTPUT);
}
void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  
  // print out data
  //Serial.print(convert_int16_to_str(accelerometer_x));Serial.print(","); 
  //Serial.print(convert_int16_to_str(accelerometer_y));Serial.print(","); 
  //Serial.print(convert_int16_to_str(accelerometer_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  //Serial.print(temperature/340.00+36.53);
//  Serial.print("Z");Serial.print(convert_int16_to_str(gyro_z));Serial.print(","); 
  Serial.print("Y");Serial.print(convert_int16_to_str(gyro_y)); Serial.print(","); 
//  Serial.print("X");Serial.print(convert_int16_to_str(gyro_x));
//  Serial.println();
//  
  error=gyro_y-setpoint;  Serial.print(error); Serial.print("\t");
  int Respuesta= error * 0.1; Serial.println(Respuesta);
  MoverMotores(Respuesta);
  delay(20);
}

//FUNCIONES DE MOTORES
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
