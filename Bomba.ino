#define led_pin 10
#define buzzer_pin 6
#define activate_pin 3

float delayStart = 1.5; //secondi

float startDelay = 900;
int steps = 52;
bool even = false;
float lastFreq;

int minFreq = 1500;
int maxFreq = 2450;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}


float tick(int i) {
  even = !even;

  digitalWrite(led_pin, even ? HIGH : LOW);

  if (even){
    float freq = map(i, 0, steps, minFreq, maxFreq);
    Serial.println(i);
    tone(buzzer_pin, freq);
    return freq;
  } else {
    noTone(buzzer_pin);
    return lastFreq;
  }
}

void loop() {
  while(digitalRead(3)){ delay(10); }

  delay(delayStart * 1000);

  float delayTime = startDelay;
  int i = 0;
  do {
    lastFreq = tick(i);
    delay(delayTime);
    delayTime *= 0.98;
    i++;
  } while (abs(maxFreq - lastFreq) > 5);

  maxFreq = lastFreq;

  digitalWrite(led_pin, HIGH);
  tone(buzzer_pin, maxFreq);

  while(1){
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(led_pin, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(led_pin, HIGH);
    delay(100);
  }
}
