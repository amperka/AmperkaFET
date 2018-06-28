// библиотека для работы с модулями по интерфейсу SPI
#include <SPI.h>
// библиотека для работы со сборкой силовых ключей
#include <AmperkaFET.h>
// пин выбора устройства на шине SPI
#define PIN_CS  8

// создаём объект mosfet для работы со сборкой силовых ключей
// передаём номер пина выбора устройства на шине SPI
FET mosfet(PIN_CS);

void setup() {
  // начало работы с силовыми ключами
  mosfet.begin();
}

void loop() {
  for(int i = 0; i < 8; i++ ) {
    // включаем по очереди каждый ключ на модуле
    mosfet.digitalWrite(i, HIGH);
    // ждём пол секунды
    delay(500);
  }
  // выключаем все ключи на модуле
  mosfet.digitalWrite(ALL, LOW);
  delay(500);
}
