int Senval=0;
int Senpin=A0;
int i = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(10, OUTPUT); //Red Led
    pinMode(11, OUTPUT); //Green Led
    pinMode(12, OUTPUT); //Buzzer
}

void loop()
{

    Senval=analogRead(Senpin);
    Serial.println(Senval); //Print resistance
    Serial.println(i);
    delay(200);
    i+=1; //Sets buzzer counter
    
    if (Senval >= 50 && i <= 20) //Adjust for weight reading
    {
      digitalWrite(11, LOW); //Green LED
      digitalWrite(10, HIGH); //Red LED
      digitalWrite(12, LOW); //Turns buzzer input to OFF
    }
    else if (Senval >= 50 && i >= 20)
    {
      digitalWrite(12, HIGH); //Sounds Buzzer after 2 hours
      digitalWrite(10, HIGH); //Red LED
    }
    else
    {
      digitalWrite(11, HIGH); //Green LED
      digitalWrite(10, LOW); //Red LED
      digitalWrite(12, LOW); //Turns buzzer input to OFF
      i = 0; //Resets buzzer counter
    }
}
