#include "Drops_list.h"

Drops_list::Drops_list(int mtx_pins[8], int data_pin, int latch_pin, int clock_pin) {
  for(int i = 0; i < 8; i++){
    this->mtx_pins[i] = mtx_pins[i];	
  }
  this->data_pin = data_pin;
  this->latch_pin = latch_pin;
  this->clock_pin = clock_pin;
  this->head = NULL;
}

void Drops_list::new_drop() {
  int width = random(1, 4);
  Drop* tmp = new Drop(7 - width + 1, width, random(0, 8), mtx_pins, data_pin, latch_pin, clock_pin);
  tmp->set_next_drop(this->head);
  this->head = tmp;
}

void Drops_list::draw_drops() {
  Drop* traverse = head;
  while (traverse != NULL) {
    traverse->draw_drop();
    traverse = traverse->get_next_drop();
  }
}

int Drops_list::update_drops(Paddle &paddle) {
  Drop* traverse = this->head;

  while (traverse != NULL) {
    if (!traverse->update_drop()) {
      if (paddle.get_base_c() <= traverse->get_col() && traverse->get_col() <= paddle.get_base_c() + paddle.get_width() - 1) {
        if (paddle.damage()) {
          return 1;
        }
      }
      Drop* tmp = traverse;
      traverse = traverse->get_next_drop();
      this->remove_drop(tmp);
    } else {
      traverse = traverse->get_next_drop();
    }
  }

  return 0;
}

void Drops_list::remove_drop(Drop* drop) {
  if (this->head == NULL || drop == NULL) {
    return;
  }

  if ((unsigned int)&*drop == (unsigned int)&*head) {
    head = drop->get_next_drop();
    delete drop;
    return;
  }

  Drop* current = this->head;
  Drop* previous = NULL;

  while (current != drop) {
    previous = current;
    current = current->get_next_drop();
  }

  if (previous != NULL) {
    previous->set_next_drop(current->get_next_drop());
    delete drop;
  }
}

void Drops_list::send_data(int data) {
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, LSBFIRST, data);
  digitalWrite(latch_pin, HIGH);
}
