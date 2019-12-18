#include "Drop.h"

Drop::Drop(int base, int width, int col, int mtx_pins[8], int data_pin, int latch_pin, int clock_pin) {
  for(int i = 0; i < 8; i++){
    this->mtx_pins[i] = mtx_pins[i];	
  }
  this->base = base;
  this->width = width;
  this->col = col;
  this->data_pin = data_pin;
  this->latch_pin = latch_pin;
  this->clock_pin = clock_pin;
  this->next_drop = NULL;
}

Drop* const Drop::get_next_drop() {
  return this->next_drop;
}

void Drop::set_next_drop(Drop* drop) {
  this->next_drop = drop;
}

int Drop::update_drop(int lowest_row) {
  if (this->base < lowest_row) {
    return 0;
  }

  this->base--;

  return 1;
}

int Drop::get_col() {
  return this->col;
}

void Drop::draw_drop() {
  // Write to the column the drop is in
  for (int i = 0; i < 8; i++) {
    digitalWrite(mtx_pins[i], i == this->col ? LOW : HIGH);
  }

  // Write the row data
  int bits = 0;
  for (int i = 0; i < 8; i++) {
    if (this->base <= i && i <= this->base + this->width - 1) {
      bitWrite(bits, i, HIGH);
    }
  }

  // Push the data to the LED Matrix
  send_data(bits);
  delay(1);
  send_data(0x00);
}

void Drop::send_data(int data) {
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, LSBFIRST, data);
  digitalWrite(latch_pin, HIGH);
}
