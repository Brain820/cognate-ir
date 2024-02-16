
#include <IRremote.h>

int RECV_PIN = PA8;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long myTime;
/*
 *  0 - A
 *  F82C959B - B
 *  25AE7EE0 - C
 *  49B0F625 - D
 * DBC8CB72 - E
 */

/*
006321927366321927361236334117
00632192736632192736
632192736006321927361236334117
006321927360123633411706321927360
6321927360000-6075977106321927360
000012363341176321927366321927360
006321927366321927361236334117
06321927360006321927366321927360
-60759771000006321927366321927360



*/

unsigned int data = 0;
int count = 0;
unsigned int buff[8];
char temp[50];
char run[350];

void setup()
{
  Serial1.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  memset(run, 0, sizeof(run));
}

void loop()
{

  if (irrecv.decode(&results))
  {
    myTime = millis();
    data = results.value;
    buff[count] = data;
    count++;
    irrecv.resume();
  }

  if (millis() - myTime > 100)
  {

    if (count != 0)
    {
      for (int i = 0; i <= count; i++)
      {
        sprintf(temp, "%d", buff[i]);
        strcat(run, temp);
      }

      // Serial.println(run);

      if (strcmp(run, "006321927366321927360") == 0)
        Serial.println("$2");
      else if (strcmp(run, "00632192736632192736")  == 0)
        Serial.println("$3");
      else if (strcmp(run, "632192736006321927360")  == 0)
        Serial.println("$4");
      else if (strcmp(run, "006321927360123633411706321927360")  == 0)
        Serial.println("$5");

      else if (strcmp(run, "6321927360000-6075977106321927360")  == 0)
        Serial.println("$10");
      else if (strcmp(run, "000012363341176321927366321927360")  == 0)
        Serial.println("$11");
      else if (strcmp(run, "006321927366321927361236334117")  == 0)
        Serial.println("$12");

      else if (strcmp(run, "06321927360006321927366321927360")  == 0)
        Serial.println("$13");
      else if (strcmp(run, "-60759771000006321927366321927360")  == 0)
        Serial.println("$14");
    }

    count = 0;
    memset(run, 0, sizeof(run));
  }
}
