int val; 


int encoder1Pins[3] = {
  2,3,4}; // channelA, channelB, direction pins
int encoder1Data[5] = {
  0, LOW, 0, 0, 0};           // 0 = encoder position, 1 = encoderChannelALast, 2 = prevTime,  3 = encoderSpeed

int encoder2Pins[3] = {
  5,6,7}; // channelA, channelB, direction pins
int encoder2Data[5] = {
  0, LOW, 0, 0, 0}; 

//labels for encoder*pins array
int channelA = 0;
int channelB = 1;
int directionPin = 2;

//labels for encoderData array elements
int position = 0;       //first element
int channelALast = 1;   //second element
int prevTime = 2;       //third element
int theSpeed = 3;          //4th element
int theDirection = 4;


//variables for calculating speed
int encoderSpeed = 0;
int sampleTime = 20;
int lastSampleTime = 0;
int currentTime = 0;

int n = LOW;

void setup() {

  //set pin state for both encoders
  for(int i = 0; i < 3; i++) {
    pinMode (encoder1Pins[i],INPUT);
    pinMode (encoder2Pins[i],INPUT);
  } 
  Serial.begin (57600);
} 

void loop() { 
  if (millis()-lastSampleTime > sampleTime) {

    readEncoder1(encoder1Pins, 'L', 1);
    readEncoder2(encoder2Pins, 'R', -1);

    if ( (encoder1Data[theSpeed] != 0) || (encoder2Data[theSpeed] != 0) ) {

      Serial.print('L');
      Serial.print(" ");
      Serial.print(encoder1Data[theSpeed]);
      Serial.print(" ");
      Serial.print(encoder1Data[theDirection]);
      Serial.print(" ");
      Serial.print("R");
      Serial.print(" ");
      Serial.print(encoder2Data[theSpeed]);
      Serial.print(" ");
      Serial.print(encoder2Data[theDirection]);    
      Serial.print(10,BYTE);


    }

    lastSampleTime = millis();
  }
}

void readEncoder1(int pins[], char wheel, int encoderDirCorrection) {

  n = digitalRead(pins[channelA]);
  if ((encoder1Data[channelALast] == LOW) && (n == HIGH)) {
    if (digitalRead(pins[channelB]) == LOW) {
      encoder1Data[position]--;
    } 
    else {
      encoder1Data[position]++; 
    }

    if (digitalRead(pins[directionPin])) {
      encoder1Data[theDirection] = 1 * encoderDirCorrection; 
    } 
    else {
      encoder1Data[theDirection] = -1 * encoderDirCorrection; 
    }



    // get time
    currentTime = millis();
    encoder1Data[theSpeed] = currentTime - encoder1Data[prevTime];


  } 
  else {
    encoder1Data[theSpeed] = 0;
    encoder1Data[theDirection] = 0; 

  }



  encoder1Data[channelALast] = n;
  encoder1Data[prevTime] = currentTime;

} 

void readEncoder2(int pins[], char wheel, int encoderDirCorrection) {

  n = digitalRead(pins[channelA]);
  if ((encoder2Data[channelALast] == LOW) && (n == HIGH)) {
    if (digitalRead(pins[channelB]) == LOW) {
      encoder2Data[position]--;
    } 
    else {
      encoder2Data[position]++; 
    }

    if (digitalRead(pins[directionPin])) {
      encoder2Data[theDirection] = 1 * encoderDirCorrection; 
    } 
    else {
      encoder2Data[theDirection] = -1 * encoderDirCorrection; 
    }



    // get time
    currentTime = millis();
    encoder2Data[theSpeed] = currentTime - encoder2Data[prevTime];


  } 
  else {
    encoder2Data[theSpeed] = 0;
    encoder2Data[theDirection] = 0; 

  }



  encoder2Data[channelALast] = n;
  encoder2Data[prevTime] = currentTime;

} 


