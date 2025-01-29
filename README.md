# Arduino Morse Trainer - Arduino ile Morse Kod Verici ve Çözücü

Bu proje, Arduino tabanlı bir Morse kodu verici ve çözücüdür. 4x20 LCD ekran, iki buton, bir potansiyometre, bir buzzer ve bir LED içerir.

## Özellikler

✔️ Gerçek zamanlı Morse kodu girişi ve çözümü\
✔️ Ayarlanabilir hız (WPM)\
✔️ Kullanıcı dostu 4x20 LCD ekran arayüzü\
✔️ Sesli ve görsel geri bildirim (Buzzer & LED)\
✔️ 3D yazıcı ile basılabilir özel tasarım kutu\
✔️ Dört farklı ekran ve bağlantı opsiyonu

## Donanım Bağlantıları

### **LCD Bağlantısı (Paralel - I2C Olmadan)**

- VSS → GND
- VDD → 5V
- VO → Orta parlaklık için GND (veya potansiyometre)
- RS → D7
- RW → GND
- EN → D8
- D4 → D9
- D5 → D10
- D6 → D11
- D7 → D12
- A+ (arka ışık) → 5V (220Ω direnç üzerinden)
- K (arka ışık) → GND

### **LCD I2C Bağlantısı**

- GND → GND
- VCC → 5V
- SDA → A4
- SCL → A5

### **Diğer Bağlantılar**

- **Potansiyometre:**
  - Orta bacak → A0
  - Yan bacaklar → 5V ve GND
- **LED:** D13
- **Buzzer:** D2
- **Mors Buton:** D3
- **Ekran temizleme Butonu:** D4

## Kod Versiyonları

Bu proje için dört farklı kod versiyonu bulunmaktadır:

1. **2x16 LCD, I2C olmadan**
2. **2x16 LCD, I2C ile**
3. **4x20 LCD, I2C olmadan**
4. **4x20 LCD, I2C ile**

## **Kurulum ve Kullanım**

1. Arduino'ya uygun kod versiyonunu yükleyin.
2. Potansiyometre ile hızınızı belirleyin.
3. Buton ile Morse kodu gönderin, ekranı takip edin.
4. Ekranı temizlemek için ikinci butonu kullanın.

## **Bağlantı Şeması**

Fritzing ile hazırlanmış bağlantı şemasını aşağıda görebilirsiniz:

