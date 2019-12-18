#include "Paddle.h"

Paddle::Paddle(int base_r, int base_c, int width, int height, int pin, int mtx_pins[8], int data_pin, int latch_pin, int clock_pin) {
  this->base_r = base_r;
  this->base_c = base_c;
  this->width  = width;
  this->height = height;
  this->pin = pin;
  this->health = 9;
  this->data_pin = data_pin;
  this->latch_pin = latch_pin;
  this->clock_pin = clock_pin;
  for(int i = 0; i < 8; i++){
    this->mtx_pins[i] = mtx_pins[i];	
  }
}

void Paddle::set_base_r(int row) {
  this->base_r = row;
}

int Paddle::get_base_r() {
  return this->base_r;
}

void Paddle::set_base_c(int col) {
  this->base_c = col;
}

int Paddle::get_base_c() {
  return this->base_c;
}

int Paddle::damage() {
  this->health -= 1;

  if (this->health < 1) {
    return 1;
  }

  return 0;
}

int Paddle::get_health() {
  return this->health;
}

int Paddle::get_width() {
  return this->width;
}

void Paddle::draw() {
  this->base_c = map(analogRead(this->pin), 0, 1023, 0, 9 - this->width);

  // Write to the columns the paddle is in
  for (int i = 0; i < 8; i++) {
    digitalWrite(mtx_pins[i], this->base_c <= i && i < this->base_c + this->width ? LOW : HIGH);
  }

  // Write the row data
  int bits = 0;
  for (int i = 0; i < 8; i++) {
    if (this->base_r <= i && i < this->base_r + this->height) {
      bitWrite(bits, i, HIGH);
    }
  }

  // Push the data to the LED Matrix
  send_data(bits);
  delay(1);
  send_data(0x00);
}

void Paddle::send_data(int data) {
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, LSBFIRST, data);
  digitalWrite(latch_pin, HIGH);
}
