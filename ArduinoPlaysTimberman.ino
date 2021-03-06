/*
 Arduino Plays Timberman

 A simple programm for Arduino that plays Timberman.

Circuit:
 * JZC-11F RELAYS attached to TIP120 attached to pins 4 and 8
 * OP580DA PHOTODARLINGTON NPN attached to A0
 * BUTTON attached to pin 7

 created July 23th 1014
 by Valentin Heun
 */


int left = 4; int right = 8;
int button = 7; int timing = 23;
int Buffer[] = {0, 0, 0, 0, 0};
int startstate = 0;

void setup() {
  pinMode(left, OUTPUT); pinMode(right, OUTPUT);
  pinMode(button, INPUT); digitalWrite(button, HIGH);
}

void loop() {
  //realise the axe
  digitalWrite(left, LOW);  digitalWrite(right, LOW);

  // update the buffer
  if (startstate > 0) {
    for (int i = 3; i > 0; i--) {
      Buffer[i] = Buffer[i - 1];
    }

    // read a couple of frames and determan if a branch had crossed the sensor
    Buffer[0] = 0;
    for (int i = 0; i <= timing; i++) {
      delay(4);
      //delayMicroseconds(200);
      
      int analog = analogRead(A0);
      if ((analog > startstate + 5) || (analog < startstate - 5)) {
        Buffer[0]  = 1;
      }
    }
  }

  // set start value for the sensor
  if (digitalRead(button) == HIGH) {
    if (startstate == 0) {
      startstate = analogRead(A0);
    }

    // timberman cutts around the right side of the branches.
    int theswitch = Buffer[1];
    if (Buffer[2] == 1 && Buffer[1] == 0) {
      theswitch = 1;
    }

    // make the actuall cut
    if (theswitch == 0) {
      digitalWrite(left, HIGH);
    }
    else {
      digitalWrite(right, HIGH);
    }
    delay(38);
     
  }
  else {
    // if switched off, set everything back to zero
    startstate = 0;
    for (int i = 0; i <= 4; i++) {
      Buffer[i] = 0;
    }
  }
}
