/****************************************************************************/
//  Function:       Cpp file for AmperkaFet
//  Hardware:       IRLML0030, IRLML9301
//  Arduino IDE:    Arduino-1.8.5
//  Author:         Igor Dementiev
//  Date:           Jun 20,2018
//  Version:        v1.0.0
//  by www.amperka.ru
/****************************************************************************/

#include "AmperkaFET.h"

FET::FET(uint8_t pinCS, uint8_t qtyDevice) {
  _pinCS = pinCS;
  _qtyDevice = qtyDevice;
  _massValuePins = new uint8_t[_qtyDevice];
  _mask = 0;
}

FET::~FET() {
  if (_massValuePins != NULL) {
    delete[] _massValuePins;  
  }
}

void FET::begin() {
  SPI.begin();
  pinMode(_pinCS, OUTPUT);
  digitalWrite(ALL, ALL, LOW);
}


void FET::digitalWrite(uint8_t pin, bool val) {
  if (pin == ALL) {
    _mask = ALL;
  } else {
    _mask = 1 << pin;
  }
  if (val) {
      _massValuePins[0] |= _mask;
  } else {
      _massValuePins[0] &= ~_mask;
  }
  _sendData();
}

void FET::digitalWrite(uint8_t device, uint8_t pin, bool val) {
  if (pin == ALL) {
    _mask = ALL;
  } else {
    _mask = 1 << pin;
  }

  if (device == ALL) {
    for (uint8_t i = 0; i < _qtyDevice; i++) {
      if (val) {
        _massValuePins[i] |= _mask;
      } else {
        _massValuePins[i] &= ~_mask;
      }
    }
  } else {
    if (val) {
      _massValuePins[device] |= _mask;
    } else {
      _massValuePins[device] &= ~_mask;
    }
  }

  _sendData();
}

void FET::_sendData() {
  ::digitalWrite(_pinCS, LOW);
  for (int i = 0; i < _qtyDevice; i++) {
    SPI.transfer(_massValuePins[_qtyDevice - i - 1]);
  }
  ::digitalWrite(_pinCS, HIGH);
}
