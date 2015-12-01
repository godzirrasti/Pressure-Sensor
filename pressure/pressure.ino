#define redLedPin 11 //Red LED
#define greenLedPin 12 //Green LED
#define buzzerPin 13 //Buzzer
#define weightValue 100 //Adjusted so sensor does not read randomly
#define countTo 20 //Time count
int Senval=0; //Sensor Value
int Senpin=A0; //Sensor read pin
int i = 0; //Counter


//Yellow wire is +5v, Red wire is read pin A0, Black wire is ground
//Led lights have the same ground. Label led and buzzer wire

void setup()
{
    Serial.begin(9600);
    pinMode(redLedPin, OUTPUT); //Red Led
    pinMode(greenLedPin, OUTPUT); //Green Led
    pinMode(buzzerPin, OUTPUT); //Buzzer
    
    /*Used for datalogging
    Serial.print("Initializing SD card...");
    // make sure that the default chip select pin is set to
    // output, even if you don't use it:
    pinMode(10, OUTPUT);
    // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;*/
   //Serial.println("card initialized.");
    
}

void loop()
{
    // make a string for assembling the data to log:
    String dataString = "";

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
      dataString += "Red LED set to ON, Sensor: " + Senval;
    }
    else if (Senval >= weightValue && i >= countTo)
    {
      digitalWrite(buzzerPin, HIGH); //Sounds Buzzer after 2 hours
      digitalWrite(redLedPin, HIGH); //Red LED
      digitalWrite(greenLedPin, LOW); //Green LED
      dataString += "Green LED set to ON, Sensor: " + Senval;
    }
    else
    {
      digitalWrite(greenLedPin, HIGH); //Green LED
      digitalWrite(redLedPin, LOW); //Red LED
      digitalWrite(buzzerPin, LOW); //Turns buzzer input to OFF
      dataString += "Green LED set to ON, Sensor: " + Senval;
      i = 0; //Resets buzzer counter
    }
    
    
}
