
#include <BluetoothSerial.h>

BluetoothSerial bt;

#define trig 19
#define echo 2

#define enA 25   //left
#define in1 26
#define in2 27
#define enB 13   //right
#define in3 14
#define in4 32



char cmd = 'S';
unsigned long duration;
unsigned long distance;
int safeDistance = 15; 
bool isForward = 0;

unsigned long lastSensorRead = 0;
const unsigned long sensorInterval = 60; // ms

bool obstacleBlocking = false;

void setup()
{
    Serial.begin(115200); 
    bt.begin("car");

    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    digitalWrite(trig, LOW);

    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    pinMode(buzzer, OUTPUT);
    digitalWrite(buzzer, LOW); 

    stop();
}

void loop()
{
    
    if (bt.available())
    {
        cmd = bt.read();
        switch (cmd)
        {
            case 'F':
                if (obstacleBlocking) stop();
                else moveforward();
                break;
            case 'B': moveBack(); break;
            case 'L': moveLeft(); break;
            case 'R': moveRight(); break;
            default: stop(); break;
        }
    }

    
    if (millis() - lastSensorRead >= sensorInterval)
    {
        lastSensorRead = millis();
        readDistance();
        updateSafety();
    }

 
    buzzertone(obstacleBlocking);
}

// ---------------- Ultrasonic ----------------
void readDistance()
{
   
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH, 30000);

    if (duration == 0)
    {
        distance = 999;
    }
    else
    {
        distance = duration * 0.0343 / 2; // cm
    }

}

void updateSafety()
{
    bool close = (distance > 0 && distance <= safeDistance);
    obstacleBlocking = close;

    if (obstacleBlocking && cmd == 'F')
    {
        stop();
        cmd = 'S';
    }
}


unsigned long delayTime = 0;
bool isSoundOn = 0;
void buzzertone(bool state)
{
    if (state)
    {
        if (millis() - delayTime >= 250)
        { 
            isSoundOn = !isSoundOn;
            digitalWrite(buzzer, isSoundOn ? HIGH : LOW); 
            delayTime = millis();
        }
    }
    else
    {
        digitalWrite(buzzer, LOW);
        isSoundOn = 0;
    }
}


void stop()
{
    isForward = 0;
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    digitalWrite(in1, LOW); digitalWrite(in2, LOW);
    digitalWrite(in3, LOW); digitalWrite(in4, LOW);
}

void moveforward()
{
    isForward = 1;
    analogWrite(enA, 125);
    analogWrite(enB, 125);
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void moveBack()
{
    isForward = 0;
    analogWrite(enA, 125);
    analogWrite(enB, 125);
    digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
}

void moveRight()
{
    analogWrite(enA, 125);
    analogWrite(enB, 50);
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void moveLeft()
{
    analogWrite(enA, 50);
    analogWrite(enB, 125);
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}
