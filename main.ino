class Sound {
public:
  int pin;
  Sound() {
    this->pin = 0;
  }
  Sound(int pin) {
    this->pin = pin;
  }  
  void activate(void) {
    digitalWrite(this->pin,LOW);    
  }
  void deactivate(void) {
    digitalWrite(this->pin,HIGH);    
  }
  void init() {
    digitalWrite (this->pin, HIGH);
    pinMode(this->pin, OUTPUT);
  }
};

class Led {
public:
  int pin;
  int red;
  int green;
  int blue;

  Led() {
    this->pin=0;
    this->red = 0;
    this->green = 0;
    this->blue = 0;
  }
  Led(int pin) {
    this->pin=pin;
    this->red = 0;
    this->green = 0;
    this->blue = 0;
  }
  void setColor(int red, int green, int blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;  
  }
  void activate(void) {
    digitalWrite(this->pin,LOW);
  }
  void deactivate(void) {
    digitalWrite(this->pin,HIGH);
  }

  void init() {
    this->deactivate();
    pinMode(this->pin, OUTPUT);
  }
};

class Staff {
public:
  Staff() {
    this->sound = Sound(this->SOUND_PIN);
    this->leds[0] = Led(A0);
    this->leds[1] = Led(A1);
    this->leds[2] = Led(A2);
    this->leds[3] = Led(A3);
    this->leds[4] = Led(A4);
    this->leds[5] = Led(A5);
  }
  
  void setColor(int red, int green, int blue) {
    analogWrite(this->RED_PIN, red);
    analogWrite(this->GREEN_PIN, green);
    analogWrite(this->BLUE_PIN, blue);
  }

  void init() {
    pinMode(this->BUTTON_PIN, INPUT);
    pinMode(this->RED_PIN, OUTPUT);
    pinMode(this->GREEN_PIN, OUTPUT);
    pinMode(this->BLUE_PIN, OUTPUT);
    pinMode(13, OUTPUT);
    for(int i =0; i < 6; i++) {
      leds[i].init();
    }
    sound.init();
  }

  void update() {
    while(true) {
      if(digitalRead(this->BUTTON_PIN)) {
        digitalWrite(13, HIGH);
        
        this->run();
        digitalWrite(13, LOW);    
      } else {

        digitalWrite(13, LOW);
      }
      delay(1);
    }
  }

  void run() {
    sound.activate();
    this->illuminate(5000);
    sound.deactivate();
  }

  void illuminate(int duration) {
    long deadline = millis() + duration;
    int incr = 255 / 7;
    while(millis() < deadline) {
      for(int shift=1; shift < 6; shift++) {
        for(int i=0; i < 6; i++) {
          int red = incr + (incr * ((i + shift) % 7));
          this->setColor(red, 0, 0);
          this->leds[i].activate();
          delay(50);
          this->leds[i].deactivate();
        }
      }
      delay(1);
    }
    for(int i=0; i < 6; i++) {
      leds[i].deactivate();
    }
  }
private:
  const int RED_PIN=5;
  const int GREEN_PIN = 3;
  const int BLUE_PIN = 6;
  const int BUTTON_PIN = 12;
  const int SOUND_PIN = 8;
  Sound sound = Sound();
  Led leds[6];
};

Staff staff = Staff();
void setup() {
  staff.init();
}
void loop() {
  staff.update();
}
