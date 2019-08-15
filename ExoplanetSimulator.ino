/*
 ----------          --------------
|                   |
|                   |
|                   |
|                   |
 ---------- XOPLANET ------------- IMULATOR
|                                 |
|                                 | 
|                                 |
|                                 |
 -----------         -------------
 Created by Sammarth Kumar and Vikas Sharma

 This program was created to look at the readings of light coming from a star and check if an exoplanet is revolving aound it. If so, the dips in the brightness would be periodic, and that 
 is checked by this program.

 
*/
//global variables declared here:
//to avoid first few results
int loopCount = 0;
//to determine the outcome of our test for periodicity
int res = 5;
//to calculate the average of the three periods whose data has been taken
float avg = 0;
//to record time stamps
float time1 = 0;
//first time stamp value storage
float p1 = 0;
//second value time stamp storage
float p2 = 0;
//third value time stamp storage
float p3 = 0;
//pin for green LED
int green = 13;
//pin for red LED
int red = 8;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //setup red LED
  pinMode(red, OUTPUT);
  //setup green LED
  pinMode(green, OUTPUT);
  Serial.print("Initializing command sequence...");
  digitalWrite(green, HIGH);
  delay(500);
  digitalWrite(green,LOW);
  digitalWrite(red, HIGH);
  delay(500);
  digitalWrite(red,LOW);
  Serial.println("Ready to go...");
  delay(500);
  //variable to store value of light sensed
  int svi = 0;
  //defining a temporary variable
  int x = 1;
  //while loop to repeat function
  while (x < 11) {
  //to keep adding values read
    svi = svi + analogRead(A0);
  //time delay of 100 milliseconds
    delay(100);
  //increasing value of x by 1 each time
    x++;
  }
//calculating average flux
  avg = (svi) / 10;
//printing the average flux value
  Serial.println("The normalized flux is: ");
  Serial.println(avg);
}
// the loop routine runs over and over again forever:
void loop() {
  //increasing value of loopCount by 1
  loopCount++;
  //defining a temporary variable to sense the brightness
  float sensorValue = analogRead(A0);
  delay(10);        // delay in between reads for stability
  //if loop to cancel out first 3 readings which are uneccesary
  if (loopCount < 4) {
    return; //if the loop runs for 3 times the program will not note down its values
  }
  //if statement to check whether the value detected is less than the normalized flux
  if (sensorValue < avg) {
  //if statement to check if variable time1 is 0
    if (time1 == 0) {
  //taking in the time since the program started
      time1 = millis();
  //else statement in case there is a value of time1
    } else {
  //creating temporary variable to store another timestamp
      float time2 = millis();
  //if statement to check whether the difference between timestamps is sufficient
      if ((time2 - time1) > 1000) {
  //defining temporary variable p to store period detected
        float p = time2 - time1;
  //printing detected period
        Serial.println(p);
  //replacing value of time1 with time2 so that new values can be added
        time1 = time2;
  //if statement to check if p1 has a stored value or not
        if (p1 == 0) {
  //assigning value of p to p1
          p1 = p;
  //checking if p2 has a stored value
        } else if (p2 == 0) {
  //assigning value of new time period to p2
          p2 = p;
  //checking if p3 has a stored value
        } else if (p3 == 0) {
  //assigning value of new time period to p3
          p3 = p;
  //in case values are already present, we shift values up
        } else {
  //assigning value of p2 to p1
          p1 = p2;
  //assigning value of p3 to p2
          p2 = p3;
  //assigning value of new period to p3
          p3 = p;
  //after each run of the loop, values will be bumped up
        }
  //checking if p1,p2,p3 have values
        if (p1 > 0 && p2 > 0 && p3 > 0) {
          Serial.println("printing periods detected: ");
          Serial.println("First period is: ");
          Serial.println(p1);
          Serial.println("Second period is:");
          Serial.println(p2);
          Serial.println("The third period is:");
          Serial.println(p3);
          Serial.println("__________________________");
           //average of the three periods
          float av = (p1 + p2 + p3) / 3;
          //deviation of time gap between p(x) and p(y) from average
          float check = ((p3 - p2) / av) * 100;
          float check2 = ((p2 - p1) / av) * 100;
          float check3 = ((p3 - p1) / av) * 100;
          //if all three values are deviated less than 5%:
          if (check < 5 && check2 < 5 && check3 < 5) {
          //variable res is assigned the value of 0
            res = 0;
          //if one or more values has larger deviation:
          } else {
          //variable res is assigned the value of 1
            res = 1;
          }
          //if value of res is 0:
          if (res == 0) {
            //turn on green LED
            digitalWrite(green, HIGH);
            //turn off red LED
            digitalWrite(red, LOW);
            Serial.println("Exoplanet is orbiting periodically...");
          //if value of res is 1
          } else if (res == 1) {
            Serial.println("No exoplanet detected...");
          //turn on red LED
            digitalWrite(red, HIGH);
          //turn off green LED
            digitalWrite(green, LOW);
          }
        }
      }
    }
  }
}
