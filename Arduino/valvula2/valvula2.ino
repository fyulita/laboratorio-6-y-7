#include <MHZ19.h> ;

void setup()
{    Serial.begin(115200);
     Serial.println(F("Starting..."));

//     Serial1.begin(9600);
}

MHZ19_RESULT response = mhz.retrieveData(); //ACA TIRA ERROR.

if (response == MHZ19_RESULT_OK)
{   Serial.print(F("CO2: "));
    Serial.println(mhz.getCO2());
    Serial.print(F("Temperature: "));
}
else
{   Serial.print(F("Error, code: "));
    Serial.println(response);
}
