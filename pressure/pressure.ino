//Libraries
#include <SPI.h>
#include <SD.h>

//Define pin values.
#define redLedPin 11 //Red LED
#define greenLedPin 12 //Green LED
#define buzzerPin 13 //Buzzer
#define weightValue 100 //Adjusted so sensor does not read randomly
#define countTo 20 //Time count
int Senval=0; //Sensor Value
int Senpin=A0; //Sensor read pin
int i = 0; //Counter
const int chipSelect = 4;


//Yellow wire is +5v, Red wire is read pin A0, Black wire is ground
//Led lights use the same ground. 
//Need to label led and buzzer wire


//Datalogging pins
//13 SPI clock
//12 MISO 
//11 MOSI

void setup()
{
    Serial.begin(9600);
    pinMode(redLedPin, OUTPUT); //Red Led
    pinMode(greenLedPin, OUTPUT); //Green Led
    pinMode(buzzerPin, OUTPUT); //Buzzer

    while (!Serial) {
      ; //Wait for serial port.
    }

    Serial.print("Initializing SD card..");
    if (!SD.begin(chipSelect)){
      Serial.println("SD card not present or failed to load");
      return;
    }

    Serial.println("SD card initialized");
}

void loop()
{
    //Start string for data log
    String dataString = "";

    //Assign sensor readings to a variable
    Senval=analogRead(Senpin);

    //Read variable and write to string
    //Only one pin will be read, change middle value for more pins.
    for (int analogPin = 0; analogPin < 1; analogPin++) {
      int sensor = analogRead(analogPin);
      dataString += String(sensor);
    }

    //Open the file
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    
    //Print if the file is available
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      Serial.println(dataString);
    }

    //Original print for testing
    //Serial.println(Senval); //Print resistance
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
