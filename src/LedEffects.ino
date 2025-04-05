// Статичная радуга
void staticRainbow() {
  for (int i = 0; i < LED_NUM; i++) {
    leds[i].setHue(i * 255 / LED_NUM);
  }
  FastLED.show();
}

// Подвижная радуга
void movingRainbow() {
  for (int i = 0; i < LED_NUM; i++) {
    leds[i].setHue(counter + i * 255 / LED_NUM);
  }
  counter++;
  FastLED.show();
}

// Рандомные цвета
void randomColors() {
  int led = random(0, LED_NUM);
  int hue = random(0, 255);
  leds[led].setHue(hue);
  FastLED.show();
}

// Мерцание
void flicker() {
  int bright = random(0, 255);
  int hue = random(0, 255);
  int d = random(0, bright);
  if (d < 10) {
    for (int i = 0; i < LED_NUM; i++) {
      leds[i] = CHSV(hue, 255, bright);
    }
    FastLED.show();
  }
}