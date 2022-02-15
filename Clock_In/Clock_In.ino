#define bit_0 9
#define bit_1 8
#define bit_2 7
#define bit_3 6
#define bit_4 5
#define bit_5 4
#define bit_6 3
#define bit_7 2
#define button 13

void setup() {
pinMode(bit_0, OUTPUT);
pinMode(bit_1, OUTPUT);
pinMode(bit_2, OUTPUT);
pinMode(bit_3, OUTPUT);
pinMode(bit_4, OUTPUT);
pinMode(bit_5, OUTPUT);
pinMode(bit_6, OUTPUT);
pinMode(bit_7, OUTPUT);
pinMode(button, INPUT);

Serial.begin(9600); // Start Serial Monitor
Serial.println("Loop Begin");
}

int eight_hour(){
  // Time starts at 0
  static int CLOCK = 0; 
  Serial.print("CLOCK: ");
  Serial.println(CLOCK);

  // Represent time in binary
  int next = CLOCK;
  if (bool(next / 128)){
    next -= 128;
    digitalWrite(bit_7, HIGH);
  } else { digitalWrite(bit_7, LOW);}
  if (bool(next / 64)){
    next -= 64;
    digitalWrite(bit_6, HIGH);
  } else { digitalWrite(bit_6, LOW);}
  if (bool(next / 32)){
    next -= 32;
    digitalWrite(bit_5, HIGH);
  } else { digitalWrite(bit_5, LOW);}
  if (bool(next / 16)){
    next -= 16;
    digitalWrite(bit_4, HIGH);
  } else { digitalWrite(bit_4, LOW);}
  if (bool(next / 8)){
    next -= 8;
    digitalWrite(bit_3, HIGH);
  } else { digitalWrite(bit_3, LOW);}
  if (bool(next / 4)){
    next -= 4;
    digitalWrite(bit_2, HIGH);
  } else { digitalWrite(bit_2, LOW);}
  if (bool(next / 2)){
    next -= 2;
    digitalWrite(bit_1, HIGH);
  } else { digitalWrite(bit_1, LOW);}
  if (bool(next / 1)){
    next -= 1;
    digitalWrite(bit_0, HIGH);
  } else { digitalWrite(bit_0, LOW);}

  // Clock increases every second due to main loop
  // Clock increases by one
  CLOCK += 1;

  // If clock reaches 4 hrs, return 0
  if (CLOCK == 240){ // 60mins x 4 hours
    Serial.println("4 Hour reached!");
    CLOCK = 0; // Resets for next loop
    return 0;
  } else{
    return 1;
  }
}


void turn_off(){ // Turns all LEDs off
  digitalWrite(bit_7, LOW);
  digitalWrite(bit_6, LOW);
  digitalWrite(bit_5, LOW);
  digitalWrite(bit_4, LOW);
  digitalWrite(bit_3, LOW);
  digitalWrite(bit_2, LOW);
  digitalWrite(bit_1, LOW);
  digitalWrite(bit_0, LOW);
}

void breaktime(int duration){
  // Turn all LEDs off
  turn_off(); 
  
  // Creating an alternating integer
  static int onoff = 0;

  for (int i = 0; i < duration; i++){ // 30 mins x 60 secs
    onoff = abs(onoff - 1);

    if (onoff == 1){
      digitalWrite(bit_7, HIGH); // can swap to alternate
    } else{
      digitalWrite(bit_7, LOW);
    }
    if (onoff == 1){
      digitalWrite(bit_6, HIGH);
    } else{
      digitalWrite(bit_6, LOW);
    }

    // Divide total 
    int six_interval = duration/6;
    int first = six_interval*1;
    int second = six_interval*2;
    int third = six_interval*3;
    int fourth = six_interval*4;
    int fifth = six_interval*5;
    int sixth = six_interval*6;
    if (i >= first){
      digitalWrite(bit_0, HIGH);
    }
    if (i >= second){
      digitalWrite(bit_1, HIGH);
    }
    if (i >= third){
      digitalWrite(bit_2, HIGH);
    }
    if (i >= fourth){
      digitalWrite(bit_3, HIGH);
    }
    if (i >= fifth){
      digitalWrite(bit_4, HIGH);
    }
    if (i >= sixth){
      digitalWrite(bit_5, HIGH);
    }

    // If button changed within the second, stops immediately
    for (int j = 0; j < 100; j++){ // every sec, check button
      if (button_check() == 0){
        break;
       }
      delay(10);
    } 
  }
  
}

int button_check(){
  static int count = 0;
  if (digitalRead(button) == LOW){
    if (count == 0){
      count = 1; // 1 means the counting is ON
      turn_off();
      delay(300);
    }
    else {
      count = 0; // 0 means the counting is OFF
      turn_off();
      delay(300);
      }
  }
  return count;
}

int finish_flash(){
  // Pattern 1
  for (int i=0; i<2; i++){
    digitalWrite(bit_7, HIGH);
    digitalWrite(bit_6, HIGH);
    digitalWrite(bit_5, HIGH);
    digitalWrite(bit_4, HIGH);
    digitalWrite(bit_3, LOW);
    digitalWrite(bit_2, LOW);
    digitalWrite(bit_1, LOW);
    digitalWrite(bit_0, LOW);
    delay(500);
    digitalWrite(bit_7, LOW);
    digitalWrite(bit_6, LOW);
    digitalWrite(bit_5, LOW);
    digitalWrite(bit_4, LOW);
    digitalWrite(bit_3, HIGH);
    digitalWrite(bit_2, HIGH);
    digitalWrite(bit_1, HIGH);
    digitalWrite(bit_0, HIGH);
    delay(500);
  }
  // Pattern 2
  for (int i=0; i<2; i++){
    digitalWrite(bit_7, HIGH);
    digitalWrite(bit_6, HIGH);
    digitalWrite(bit_5, LOW);
    digitalWrite(bit_4, LOW);
    digitalWrite(bit_3, HIGH);
    digitalWrite(bit_2, HIGH);
    digitalWrite(bit_1, LOW);
    digitalWrite(bit_0, LOW);
    delay(500);
    digitalWrite(bit_7, LOW);
    digitalWrite(bit_6, LOW);
    digitalWrite(bit_5, HIGH);
    digitalWrite(bit_4, HIGH);
    digitalWrite(bit_3, LOW);
    digitalWrite(bit_2, LOW);
    digitalWrite(bit_1, HIGH);
    digitalWrite(bit_0, HIGH);
    delay(500);
  }
  // Pattern 3
  for (int i=0; i<2; i++){
    digitalWrite(bit_7, HIGH);
    digitalWrite(bit_6, LOW);
    digitalWrite(bit_5, HIGH);
    digitalWrite(bit_4, LOW);
    digitalWrite(bit_3, HIGH);
    digitalWrite(bit_2, LOW);
    digitalWrite(bit_1, HIGH);
    digitalWrite(bit_0, LOW);
    delay(500);
    digitalWrite(bit_7, LOW);
    digitalWrite(bit_6, HIGH);
    digitalWrite(bit_5, LOW);
    digitalWrite(bit_4, HIGH);
    digitalWrite(bit_3, LOW);
    digitalWrite(bit_2, HIGH);
    digitalWrite(bit_1, LOW);
    digitalWrite(bit_0, HIGH);
    delay(500);
  }
  return 0;
}


void loop() {
  // pass is the count of loops
  int pass = 0;

  // Timer ON
  while (button_check() == 1){
    
    if (eight_hour() == 0){
      pass += 1;
      if (pass == 2){
        break;
      }
      breaktime(1800);
      Serial.println("pass: ");
      Serial.println(pass);
    }

    // Checks every 10ms if button check
    // Total time run is 60 sec
    for (int i = 0; i != 6000; i++){
      if (pass == 2){
        break;
      }
      delay(10); 
      if (button_check() == 0){
        break;
      }
    }
  }  

  // Timer OFF
  while (button_check() == 0){
    // Bit 7 and 6 alternate
    digitalWrite(bit_7, HIGH);
    digitalWrite(bit_6, LOW);
    // Waits 500ms with button check every 10ms
    for (int i = 0; i != 50; i++){
      delay (10);
      if (button_check() == 1){
        break;
      }
    }
    digitalWrite(bit_7, LOW);
    digitalWrite(bit_6, HIGH);
    // Waits 500ms with button check every 10ms
    for (int i = 0; i != 50; i++){
      delay (10);
      if (button_check() == 1){
        break;
      }
    }    
  }

  // If it loops 2 times, the finish sequence loops forever
  while (pass == 2){ // Finish sequence
      Serial.println("FINISH SEQUENCE");
      finish_flash(); 
      }
}
