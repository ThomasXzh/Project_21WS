//MotionSensor.h
#ifndef  _MOTIONSENSOR_H_
#define _MOTIONSENSOR_H_
#include "systemc.h"
#include "TestBench.h"
#include "stdio.h"

extern int State;
extern int on_state;
extern int ernte;
extern TestBench::Direction c;
extern bool d;

SC_MODULE(MotionSensor)
{
    //in
    sc_fifo_in<TestBench::Direction> direction_port;
    sc_in<bool> blocked_port;
    //out
    sc_out<bool> blink_left_port;
    sc_out<bool> blink_right_port;
    sc_out<bool> danger_lights_port;
    sc_event state;

    SC_CTOR(MotionSensor) {
        blink_left_port.initialize(false);
        blink_right_port.initialize(false);
        danger_lights_port.initialize(false);

        SC_THREAD(motion); 
        SC_THREAD(block);
        sensitive << blocked_port;
        SC_THREAD(statenow);
    }


    void motion() {
        while (true) {
            c = direction_port.read();
                if (c == TestBench::go_straight && ernte == 0 && on_state == 1) {
                    
                    State = 1;
                    state.notify();
                }
                else if (c == TestBench::turn_left && ernte == 0 && on_state == 1) {

                    
                    State = 2;
                    state.notify();
                }
                else if (c == TestBench::turn_right && ernte == 0 && on_state == 1) {
                    
                    State = 3;
                    state.notify();
                }

            }
            wait(SC_ZERO_TIME);
    }
    void block() {
        while (true) {
            wait();
            if (ernte == 0 && on_state == 1) {
                State = 4;
                state.notify();
            }
        }
    }

    void statenow() {
        while (true) {
            wait(state);
            if (State == 1) {
                blink_left_port.write(false);
                blink_right_port.write(false);
                danger_lights_port.write(false);
            }
            else if (State == 2) {
                blink_left_port.write(true);
                blink_right_port.write(false);
                danger_lights_port.write(false);
            }
            else if (State == 3) {
                blink_left_port.write(false);
                blink_right_port.write(true);
                danger_lights_port.write(false);
            }
            else if (State == 4) {
                blink_left_port.write(false);
                blink_right_port.write(false);
                danger_lights_port.write(true);
                State = 4;
            }
        }
        

    }
};
#endif
