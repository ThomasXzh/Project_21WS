//AppleSensor.h
#ifndef  _APPLESENSOR_H_
#define _APPLESENSOR_H_
#include "systemc.h"
#include "TestBench.h"
#include "stdio.h"

extern int on_state;
extern int AppleAmount;
extern int State;
extern int ernte;
extern int har_now;
extern bool h;

SC_MODULE(AppleSensor)
{
    //AppleSenPort:
    //in
    sc_in<TestBench::AppleHeight> apple_sensed_port;
    sc_fifo_in<bool> apple_harvested_port;
    //out
    sc_out<bool>done_port;
    sc_out<bool>vacuum_active_port;
    sc_out<bool>apple_off_port;

    sc_event Har_now;
    sc_event check;

    SC_CTOR(AppleSensor) {
        SC_THREAD(apple);
        sensitive << apple_sensed_port;
        SC_THREAD(har);
        /*SC_THREAD(checkamount);
        sensitive << check;*/
    }

    void har() {
        while (true) {
            h = apple_harvested_port.read();
            if (h == true) {
                har_now = 1;
                Har_now.notify();
            }
            else {
                har_now = 0;
            }
        }
    }

    void checkamount() {
        while (true) {
            wait();
            if (AppleAmount >= 100) {
                apple_off_port.write(true);
                done_port.write(true);
            }
        }
    }
    void apple() {
        while (true) {
                wait();
                if (apple_sensed_port.read() == TestBench::apple_low && State == 1 && on_state == 1) {
                    ernte = 1;
                    wait(1000, SC_MS);
                    vacuum_active_port.write(true);
                    wait(6000, SC_MS, Har_now);
                    if (har_now == 1) {
                        AppleAmount++;
                        if (AppleAmount == 100) {
                            apple_off_port.write(true);
                            done_port.write(true);
                        }
                        wait(1000, SC_MS);
                        vacuum_active_port.write(false);
                                    
                        
                        check.notify();
                        ernte = 0;
                    }
                    else {
                        wait(1000, SC_MS);
                        vacuum_active_port.write(false);
                        ernte = 0;
                    }
                }
                else if (apple_sensed_port.read() == TestBench::apple_high && State == 1 && on_state == 1) {
                    ernte = 1;
                    wait(5000, SC_MS);
                    vacuum_active_port.write(true);
                    wait(6000, SC_MS, Har_now);
                    if (har_now == 1) {
                        AppleAmount++;
                        if (AppleAmount == 100) {
                            apple_off_port.write(true);
                            done_port.write(true);
                        }
                        wait(5000, SC_MS);
                        vacuum_active_port.write(false);
                        
                        
                        check.notify();
                        ernte = 0;
                    }
                    else {
                        wait(5000, SC_MS);
                        vacuum_active_port.write(false);
                        ernte = 0;
                    }
                }
                else if (apple_sensed_port.read() == TestBench::apple_very_high && State == 1 && on_state == 1) {
                    ernte = 1;
                    wait(8000, SC_MS);
                    vacuum_active_port.write(true);
                    wait(6000, SC_MS, Har_now);
                    if (har_now == 1) {
                        AppleAmount++;
                        if (AppleAmount == 100) {
                            apple_off_port.write(true);
                            done_port.write(true);
                        }
                        wait(8000, SC_MS);
                        vacuum_active_port.write(false);
                        
                        
                        check.notify();
                        ernte = 0;
                    }
                    else {
                        wait(8000, SC_MS);
                        vacuum_active_port.write(false);
                        ernte = 0;
                    }
                }
                
            
            
        }
    }
};
#endif
