const int switchPin = 2;
const int ledStripLightPin = 10;
const int motionSensorPin = 9;

int switchState = 0;
int ledStripState = LOW;
int lightSensorValue;
int motionState = LOW;
int i;

unsigned long lastMovementTime;

const unsigned long maxInterval = (5 * 60 * 1000UL);//5min in millis
const int minLightLevel = 460;//adjust this in the kitchen for accurate light level

void setup()
{
  pinMode(ledStripLightPin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(motionSensorPin, INPUT);
//  Serial.begin(9600);
}

void loop()
{
  updateMotionStateValue();
  updateLightSensorValue();
  
//  debug();

  dealWithAnyMotion();
  dealWithNoMotion();  
  
  dealWithButtonIfPressed();

  delay(100);
}

void dealWithButtonIfPressed()
{
  switchState = digitalRead(switchPin);
  if (switchState == HIGH)
  {
    Serial.println("Button Pressed");
    if (ledStripState == HIGH)
    {
      turnOffLights();
      delay(300);
    }
    else
    {
      turnOnLights();
      delay(300);
    }
  }
}

void dealWithNoMotion()
{
  if (motionState == LOW)
  {
    if (ledStripState == HIGH)
    {
      unsigned long now = millis();
      if ((now - lastMovementTime) > maxInterval)
      {
        turnOffLights();
      } 
    } 
  } 
}

void dealWithAnyMotion()
{
  if (motionState == HIGH)
  {
    if (ledStripState == HIGH)
    {
      resetTimer(); 
    }
    else
    {
      if (lightSensorValue < minLightLevel)
      {
        turnOnLights();
      }
    }
  }  
}

void turnOnLights()
{
  ledStripState = HIGH;
  for (i = 0; i <= 255; i++)
  {
    analogWrite(ledStripLightPin, i);
    delay(15);
  } 
//  digitalWrite(ledStripLightPin, ledStripState);
  resetTimer();
}

void turnOffLights()
{
  ledStripState = LOW;
  for (i = 255; i >= 0; i--)
  {
    analogWrite(ledStripLightPin, i);
    delay(15); 
  } 
//  digitalWrite(ledStripLightPin, ledStripState);
}

void resetTimer()
{
  lastMovementTime = millis(); 
}

void updateMotionStateValue()
{
  motionState = digitalRead(motionSensorPin);
}

void updateLightSensorValue()
{
  lightSensorValue = analogRead(A0);
}

void debug()
{
  Serial.print("Motion state: ");
  Serial.print(motionState);
  Serial.print(" Light Sensor Value: ");
  Serial.print(lightSensorValue);
  Serial.print(" Led light state ");
  Serial.println(ledStripState); 
}
