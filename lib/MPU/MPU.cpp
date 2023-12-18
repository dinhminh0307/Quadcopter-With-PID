#include "./MPU.h"
//Gyroscope sensor deviation
// float gyroXerror = 0.07;
// float gyroYerror = 0.03;
// float gyroZerror = 0.01;

// Create a sensor object
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;


float gyroX, gyroY, gyroZ;
float accX, accY, accZ;
float temperature;


// function definition
void initMPU(){
  
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void getGyroReadings(){
  mpu.getEvent(&a, &g, &temp);

  // float gyroX_temp = g.gyro.x;
  // if(abs(gyroX_temp) > gyroXerror)  {
  //   gyroX += gyroX_temp/50.00;
  //   Serial.println(gyroX);
  // }
  
  // float gyroY_temp = g.gyro.y;
  // if(abs(gyroY_temp) > gyroYerror) {
  //   gyroY += gyroY_temp/70.00;
  //   Serial.println(gyroY);
  // }

  // float gyroZ_temp = g.gyro.z;
  // if(abs(gyroZ_temp) > gyroZerror) {
  //   gyroZ += gyroZ_temp/90.00;
  //   Serial.println(gyroZ);
  // }

  // convert from radian to degree
  gyroDataSent.GyroX = g.gyro.x * RAD_2_DEG;
  gyroDataSent.GyroY = g.gyro.y * RAD_2_DEG;
  gyroDataSent.GyroZ = g.gyro.z * RAD_2_DEG;
}

void getAccReadings() {
  mpu.getEvent(&a, &g, &temp);
  // Get current acceleration values
  accX = a.acceleration.x;
  accY = a.acceleration.y;
  accZ = a.acceleration.z;
  
  Serial.print(accX);
  Serial.print(" ");
  Serial.print(accY);
  Serial.print(" ");
  Serial.print(accZ);
  Serial.print(" ");
}