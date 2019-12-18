#ifndef DROPS_LIST_H
#define DROPS_LIST_H
#include "Drop.h"
#include "Paddle.h"
#include <Arduino.h>

class Drops_list {
  public:
    Drops_list(int mtx_pins[8], int data_pin, int latch_pin, int clock_pin);
    void new_drop();
    void draw_drops();
    int update_drops(Paddle &paddle);
    void remove_drop(Drop* drop);
  private:
    Drop* head;

    int data_pin;
    int latch_pin;
    int clock_pin;
    int mtx_pins[8];

    void send_data(int data);
};

#endif
