#ifndef PADDLE_H
#define PADDLE_H
#include <Arduino.h>

class Paddle {
  public:
    Paddle(int base_r, int base_c, int width, int height, int pin, int mtx_pins[8], int data_pin, int latch_pin, int clock_pin);
    
    void set_base_r(int row);
    int get_base_r();

    void set_base_c(int col);
    int get_base_c();

    int damage();
    int get_health();
    int get_width();
    void draw();
  private:
    int base_r;
    int base_c;
    int width;
    int height;
    
    int health;

    int pin;

    int data_pin;
    int latch_pin;
    int clock_pin;
    int mtx_pins[8];

    void send_data(int data);
};

#endif
