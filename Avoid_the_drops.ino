#include "Drop.h"
#include "Paddle.h"
#include "Drops_list.h"

int const latch_pin = 9; // Pin connected to pin12 of 74HC595
int const clock_pin = 10; // Pin connected to pin11 of 74HC595
int const data_pin = 8; // Pin connected to pin14 of 74HC595
int const mtx_col_pins[] = {11, 12, 13, A1, A2, A3, A4, A5};
int const health_pins[] = {0, 1, 2, 3, 4, 5, 6, 7};
int const input_pin = A0;

void draw_health(unsigned int remaining);

// Globals
Drops_list drops(mtx_col_pins, data_pin, latch_pin, clock_pin);
Paddle paddle(0, 0, 2, 2, input_pin, mtx_col_pins, data_pin, latch_pin, clock_pin);
int timer;

void setup() {
  // set pins to output
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  
  for (int i = 0; i < 8; i++) {
    pinMode(mtx_col_pins[i], OUTPUT);
  }

  for (int i = 0; i < 9; i++) {
    pinMode(health_pins[i], OUTPUT);
  }
  
  timer = 60;
  
  randomSeed(analogRead(input_pin));

  // Create the drop objects
  drops.new_drop();
  drops.new_drop();
  drops.new_drop();

}

void loop() {
  for (int i = 0; i < timer; i++) {
    draw_health(paddle.get_health());
    drops.draw_drops();
    paddle.draw();
  }
  
  // If there is no health left stop the game
  // The arduino needs to be reset to fix this or replay the game
  if (drops.update_drops(paddle)) {
    while (1) {
      
    }
  }

  // Speed up the clock! The game needs to be hard
  if(random(0, 10) == 0){
    timer --;
  }

  // Spawn a new drop randomly
  if (random(0, 2) == 0) {
    drops.new_drop();
  }
}

void draw_health(unsigned int remaining) {
  for (int i = 1; i < 10; i++) {
    digitalWrite(health_pins[i - 1], i < remaining ? HIGH : LOW);
  }
}
