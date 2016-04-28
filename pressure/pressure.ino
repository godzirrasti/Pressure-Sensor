//Libraries
#include <SD.h>
#include <SPI.h>

//Define pin values.
#define redLedPin 2 //Red LED
#define greenLedPin 3 //Green LED
#define buzzerPin 4 //Buzzer
#define weightValue 100 //Adjusted so sensor does not read randomly
#define countTo 20 //Time count
int Senval=0; //Sensor Value
int Senpin=A0; //Sensor read pin
int i = 0; //Counter
int chipSelect = 10;
int pow_pin = 8;
String dataString = "";
File dataFile;

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
    pinMode(chipSelect, OUTPUT); //Chip select
    pinMode(pow_pin, OUTPUT);
    digitalWrite(pow_pin, HIGH);
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
    //String dataString = "";

    //Assign sensor readings to a variable
    Senval=analogRead(Senpin);

    //Open the file
    dataFile = SD.open("Datalog.txt", FILE_WRITE);
    int dataInt = (Senval);
    
    //Print if the file is available
    if (dataFile) {
      dataFile.println(dataInt);
      dataFile.close();
      Serial.println("File successfully written!");
    }
    else {
      Serial.println("Error opening file");
    }

    //Original print for testing
    Serial.println("R value:"); //Print resistance
    Serial.println(Senval);
    Serial.println("Time: "); //Print time value
    Serial.println(i);
    delay(200);
    i+=1; //Sets buzzer counter
    
    if (Senval >= weightValue && i <= countTo) //Adjust for weight reading
    {
      digitalWrite(greenLedPin, LOW); //Green LED
      digitalWrite(redLedPin, HIGH); //Red LED
      digitalWrite(buzzerPin, LOW); //Turns buzzer input to OFF
      //dataString += "Red LED set to ON, Sensor: " + dataInt;
    }
    else if (Senval >= weightValue && i >= countTo)
    {
      digitalWrite(buzzerPin, HIGH); //Sounds Buzzer after 2 hours
      digitalWrite(redLedPin, HIGH); //Red LED
      digitalWrite(greenLedPin, LOW); //Green LED
      //dataString += "Green LED set to ON, Sensor: " + dataInt;
    }
    else
    {
      digitalWrite(greenLedPin, HIGH); //Green LED
      digitalWrite(redLedPin, LOW); //Red LED
      digitalWrite(buzzerPin, LOW); //Turns buzzer input to OFF
      //dataString += "Green LED set to ON, Sensor: " + dataInt;
      i = 0; //Resets buzzer counter
    }
    
    
}
