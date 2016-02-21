
uint8_t b0,b1 = 0;    // how bright the LED is
uint8_t d2 = HIGH;
uint8_t counter = 0;

// the setup routine runs once when you press reset:
void setup()  { 
  // declare pins to be an outputs:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
} 
 
// the loop routine runs over and over again forever:
void loop()  {
  
  if (counter % 30 == 0) {
    b0 = ~b0;
    analogWrite(0, b0);
  }

  if (counter % 50 == 0) {
    b1 = ~b1;
    analogWrite(1, b1);
  }
  
  
  if (counter % 70 == 0) {
    d2 = (d2==HIGH) ? LOW : HIGH;
    digitalWrite(2, d2);
  }

  delay(10); 
 
  counter++;
}
  
