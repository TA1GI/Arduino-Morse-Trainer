#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Ayarları (I2C Adresi: 0x27, Boyut: 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Sabitler
const int tonePin = 2;
const int ledPin = 13;
const int buttonPin = 3;
const int resetButtonPin = 4;
const int potPin = A0;
const int debounceDelay = 30;

// Morse Kod Süreleri (Başlangıç)
int dotLength = 240;
int dashLength, dotSpace, letterSpace, wordSpace;

// Durum Değişkenleri
bool newLetter = false;
bool newWord = false;
bool letterFound = false;
int t1, t2, onTime, gap;
String dashSeq = "";
String decodedText = "";

// Harf ve Rakam Tablosu
const char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

const char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....",
  "-....", "--...", "---..", "----."
};

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);

  lcd.init();           // LCD'yi başlat
  lcd.backlight();      // Arka ışığı aç
  lcd.setCursor(0, 0);
  lcd.print("TA1GI MORS: ");

  Serial.begin(9600);
  updateTimings(); // Başlangıç sürelerini hesapla
}

void loop() {
  int potValue = analogRead(potPin);
  updateSpeed(potValue); // Potansiyometreye göre hız ayarı

  // Sıfırlama Butonu
  if (digitalRead(resetButtonPin) == LOW) {
    delay(debounceDelay);
    if (digitalRead(resetButtonPin) == LOW) {
      decodedText = "";
      dashSeq = "";
      updateLCD();
      while (digitalRead(resetButtonPin) == LOW); // Buton bırakılana kadar bekle
    }
  }

  if (digitalRead(buttonPin) == LOW) { // Buton basılı
    newLetter = true;
    newWord = true;
    t1 = millis();
    digitalWrite(ledPin, HIGH);
    tone(tonePin, 1000);

    while (digitalRead(buttonPin) == LOW) {
      delay(debounceDelay);
    }

    digitalWrite(ledPin, LOW);
    noTone(tonePin);

    t2 = millis();
    onTime = t2 - t1;

    // Nokta veya Çizgi Belirleme
    if (onTime <= dotLength * 1.5) {
      dashSeq += ".";
    } else {
      dashSeq += "-";
    }

    updateLCD(); // LCD güncelle
  }

  gap = millis() - t2;
  if (newLetter && gap >= letterSpace) {
    char decodedChar = decodeMorse(dashSeq);
    if (decodedChar != '\0') {
      decodedText += decodedChar;
    } else {
      decodedText += "?"; // Geçersiz kod
    }

    dashSeq = "";
    newLetter = false;
    updateLCD();
  }

  if (newWord && gap >= wordSpace) {
    decodedText += " "; // Kelime boşluğu
    newWord = false;
    updateLCD();
  }

  // Uzun metinlerde kaydırma
  if (decodedText.length() > 16) {
    decodedText = decodedText.substring(1);
    updateLCD();
  }
}

void updateSpeed(int potValue) {
  dotLength = map(potValue, 0, 1023, 50, 500);
  updateTimings();
  lcd.setCursor(10, 0);
  lcd.print(map(dotLength, 50, 500, 24, 2)); // Hızı WPM olarak yazdır
  lcd.print(" WPM ");
}

void updateTimings() {
  dotSpace = dotLength;
  dashLength = dotLength * 3;
  letterSpace = dotLength * 3;
  wordSpace = dotLength * 7;
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kod: ");
  lcd.print(dashSeq);
  lcd.setCursor(0, 1);
  lcd.print(decodedText);
}

char decodeMorse(String code) {
  for (int i = 0; i < 26; i++) {
    if (code == letters[i]) {
      return (char)(i + 'A');
    }
  }

  for (int i = 0; i < 10; i++) {
    if (code == numbers[i]) {
      return (char)(i + '0');
    }
  }

  return '\0'; // Geçersiz kod
}
