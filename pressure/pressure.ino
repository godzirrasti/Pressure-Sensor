int Senval=0;

int Senpin=A0;

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
    delay(200);
    
    if (Senval >= 50) //Adjust for weight reading
    {
    digitalWrite(11, LOW); //Green Led
    digitalWrite(10, HIGH); //Red Led
    }
    else
    {
    digitalWrite(11, HIGH); //Green Led
    digitalWrite(10, LOW); //Red Led
    }    
}
