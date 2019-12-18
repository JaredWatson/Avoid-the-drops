#ifndef DROP_H
#define DROP_H
#include <Arduino.h>

class Drop {
  public:
    Drop(int base, int width, int col, int mtx_pins[8], int data_pin, int latch_pin, int clock_pin);
    void draw_drop();
    int update_drop();
    int get_col();
    Drop* const get_next_drop();
    void set_next_drop(Drop* drop);
  private:
    int base;
    int width;
    int col;
    
    Drop* next_drop;
    
    int data_pin;
    int latch_pin;
    int clock_pin;
    int mtx_pins[8];
    void send_data(int data);
};

#endif
