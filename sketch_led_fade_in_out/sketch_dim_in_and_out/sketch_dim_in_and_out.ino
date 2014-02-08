const int LED = 9;
const int BUTTON = 6;
int val = 0;
int oldVal = 0;
int state = 0;
int brightness = 128;
int increase = 0;
unsigned long startTime = 0;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop()
{
  val = digitalRead(BUTTON);
  
  if (val == HIGH && oldVal == LOW) //button pressed
  {
    state = 1;// - state;
    increase == 1;
    startTime = millis();
    delay(30);
  } 
  else if (val == LOW && oldVal == HIGH)
  {
    increase == 1;
    startTime = millis();
    delay(30);    
  }
  
  if (val == HIGH && oldVal == HIGH) //if the button is being pressed
  {
    if (state == 1 && (millis() - startTime) > 500) //if we've held down the button more than 500ms
    {
       if (increase == 1)
       {      
         brightness++;
       }
       else
       {
         brightness--;
       }
       
       delay(10);
       
       if (brightness > 254)
       {
         increase = 0;
//         brightness = 0; 
       }
       else if (brightness < 1)
       {
         increase = 1; 
       }
    }
  }
  
//  for (int i=0;i < 255; i++)
//  {
//    analogWrite(LED, i);
//    delay(10);
//  } 
//  
//  for (int i = 255; i > 0; i--)
//  {
//    analogWrite(LED, i);
//    delay(10); 
//  } 

  oldVal = val;
  
  if (state == 1)
  {
    analogWrite(LED, brightness);
  }
  else
  {
    analogWrite(LED, 0);
  }
}
