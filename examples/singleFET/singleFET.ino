// библиотека для работы с модулями по интрефейсу SPI
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
  // включаем второй ключ на модуле
  mosfet.digitalWrite(2, HIGH);
  // ждём одну секунду
  delay(1000);
  // включаем пятый ключ на модуле
  mosfet.digitalWrite(5, HIGH);
  // ждём одну секунду
  delay(1000);
  // выключаем все ключи на модуле
  mosfet.digitalWrite(ALL, LOW);
  delay(1000);
}
