void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.write("Hello I'm ESP");
  delay(2000);  
}
