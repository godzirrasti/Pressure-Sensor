#define redLedPin 10
#define greenLedPin 11
#define buzzerPin 12
#define weightValue 50
#define countTo 20
int Senval=0;
int Senpin=A0;
int i = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(redLedPin, OUTPUT); //Red Led
    pinMode(greenLedPin, OUTPUT); //Green Led
    pinMode(buzzerPin, OUTPUT); //Buzzer
}

void loop()
{

    Senval=analogRead(Senpin);
    Serial.println(Senval); //Print resistance
    Serial.println(i); //Print time value
    delay(200);
    i+=1; //Sets buzzer counter
    
    if (Senval >= weightValue && i <= countTo) //Adjust for weight reading
    {
      digitalWrite(greenLedPin, LOW); //Green LED
      digitalWrite(redLedPin, HIGH); //Red LED
      digitalWrite(buzzerPin, LOW); //Turns buzzer input to OFF
    }
    else if (Senval >= weightValue && i >= countTo)
    {
      digitalWrite(buzzerPin, HIGH); //Sounds Buzzer after 2 hours
      digitalWrite(redLedPin, HIGH); //Red LED
      digitalWrite(greenLedPin, LOW); //Green LED
    }
    else
    {
      digitalWrite(greenLedPin, HIGH); //Green LED
      digitalWrite(redLedPin, LOW); //Red LED
      digitalWrite(buzzerPin, LOW); //Turns buzzer input to OFF
      i = 0; //Resets buzzer counter
    }
}
