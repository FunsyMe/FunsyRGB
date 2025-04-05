/* 
  FunsyRGB -  умный
  контроллер для
  адресных светодиодных
  лент на чипе WS2812
  на ESP32S3, by Fusny,
  2025
*/

#define LED_NUM 50  // Количество светодиодов на ленте
#define LED_PIN 6   // Пин ленты

#include <FastLED.h>  // Подключаем ленту
#include <WiFi.h>     // Подключаем Wi-Fi
#include <SettingsGyver.h> // Подключаем настройки 

CRGB leds[LED_NUM]; // Класс сыетодиодов
SettingsGyver sett("FunsyRGB"); // Класс настроек

uint8_t curMode = 0;  // Текущий режим

uint8_t counter;  // Вспомогательная переменная для эффектов
uint32_t ledTmr;  // Таймер дял эффектов
uint8_t bright = 50; // Ярокость ленты
uint8_t effectSpeed = 190; // Скорость эффектов

void build(sets::Builder& b) {
  b.Slider("Яркость", 0, 255, 1, "", &bright);
  b.Slider("Скорость Режима", 0, 255, 1, "", &effectSpeed);
  b.Select("Режим", "Static Rainbow;Moving Rainbow;Random Colors;Flicker;", &curMode);
}

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1800);
  FastLED.setBrightness(bright);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("FunsyRGB");

  sett.begin();
  sett.onBuild(build);
}

void loop() {
  sett.tick();

  if (millis() - ledTmr >= 255 - effectSpeed) {
    ledTmr = millis();

    switch (curMode) {
      case 0: staticRainbow(); break;
      case 1: movingRainbow(); break;
      case 2: randomColors(); break;
      case 3: flicker(); break;
    }

  }

  FastLED.setBrightness(bright);
  
}
