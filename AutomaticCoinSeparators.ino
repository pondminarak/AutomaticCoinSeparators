#define SENSOR_PIN_1 14 // กำหนด GPIO ที่เชื่อมต่อกับ sensor 1
#define SENSOR_PIN_2 27 // กำหนด GPIO ที่เชื่อมต่อกับ sensor 2
#define SENSOR_PIN_3 16 // กำหนด GPIO ที่เชื่อมต่อกับ sensor 3
#define SENSOR_PIN_4 17 // กำหนด GPIO ที่เชื่อมต่อกับ sensor 4

volatile int count1 = 0;  // ตัวแปรที่ใช้เก็บค่านับสำหรับ sensor 1
//volatile int count2 = 0;  // ตัวแปรที่ใช้เก็บค่านับสำหรับ sensor 2
volatile int count3 = 0;  // ตัวแปรที่ใช้เก็บค่านับสำหรับ sensor 3
volatile int count4 = 0;  // ตัวแปรที่ใช้เก็บค่านับสำหรับ sensor 4
volatile int CoinB1 = 0;
//volatile int CoinB2 = 0;
volatile int CoinB5 = 0;
volatile int CoinB10 = 0;  
volatile int totalCount = 0;

volatile bool coinDetected1 = false;  // ตัวแปรบอกสถานะว่ามีเหรียญถูกตรวจจับหรือไม่สำหรับ sensor 1
volatile bool coinDetected2 = false;  // ตัวแปรบอกสถานะว่ามีเหรียญถูกตรวจจับหรือไม่สำหรับ sensor 2
volatile bool coinDetected3 = false;  // ตัวแปรบอกสถานะว่ามีเหรียญถูกตรวจจับหรือไม่สำหรับ sensor 3
volatile bool coinDetected4 = false;  // ตัวแปรบอกสถานะว่ามีเหรียญถูกตรวจจับหรือไม่สำหรับ sensor 4

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN_1, INPUT);
  //pinMode(SENSOR_PIN_2, INPUT);
  pinMode(SENSOR_PIN_3, INPUT);
  pinMode(SENSOR_PIN_4, INPUT);

  // กำหนด callback function เมื่อมีการตรวจจับสัญญาณจาก sensor 1
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN_1), countPulse1, RISING);

  // กำหนด callback function เมื่อมีการตรวจจับสัญญาณจาก sensor 2
  //attachInterrupt(digitalPinToInterrupt(SENSOR_PIN_2), countPulse2, RISING);
  
  // กำหนด callback function เมื่อมีการตรวจจับสัญญาณจาก sensor 3
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN_3), countPulse3, RISING);

  // กำหนด callback function เมื่อมีการตรวจจับสัญญาณจาก sensor 4
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN_4), countPulse4, RISING);
}

void loop() {
  if (coinDetected1) {
    count1++;
    coinDetected1 = false;
  }

  if (coinDetected2) {
    count2++;
    coinDetected2 = false;
  }

  if (coinDetected3) {
    count3++;
    coinDetected3 = false;
  }

  if (coinDetected4) {
    count4++;
    coinDetected4 = false;
  }

  CoinB1 = count1;
  CoinB2 = count2 * 2;
  CoinB5 = count3 * 5;
  CoinB10 = count4 * 10;

  totalCount = CoinB1 + CoinB5 + CoinB10;

  // Check if totalCount is equal to or greater than 50
  if (totalCount >= 50) {
    // Reset all count variables to zero
    count1 = 0;
    count2 = 0;
    count3 = 0;
    count4 = 0;
    CoinB1 = 0;
    //CoinB2 = 0;
    CoinB5 = 0;
    CoinB10 = 0;
    totalCount = 0;
  }

  // Print results to Serial Monitor
  Serial.print("Count Coin 1: ");
  Serial.print(count1);
  Serial.print(" Coin Total = ");
  Serial.print(CoinB1);
  Serial.println(" Bath");

  //Serial.print("Count Coin 2: ");
  //Serial.print(count2);
  //Serial.print(" Coin Total = ");
  //Serial.print(CoinB2);
  //Serial.println(" Bath");

  Serial.print("Count Coin 5: ");
  Serial.print(count3);
  Serial.print(" Coin Total = ");
  Serial.print(CoinB5);
  Serial.println(" Bath");

  Serial.print("Count Coin 10: ");
  Serial.print(count4);
  Serial.print(" Coin Total = ");
  Serial.print(CoinB10);
  Serial.println(" Bath");

  Serial.print("Total = ");
  Serial.print(totalCount);
  Serial.println(" Bath");

  delay(1000);
}

void countPulse1() {
  coinDetected1 = true;
}

void countPulse2() {
  coinDetected2 = true;
}

void countPulse3() {
  coinDetected3 = true;
}

void countPulse4() {
  coinDetected4 = true;
}
