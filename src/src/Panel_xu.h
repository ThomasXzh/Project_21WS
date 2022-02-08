//panel.h
#ifndef  _PANEL_H_
#define _PANEL_H_
#include "systemc.h"
#include "stdio.h"
#include "TestBench.h"
#include "AppleSensor.h"
#include "Tank.h"

extern int on_state;
extern int AppleAmount;
extern int rest_fuel;
extern bool b;
extern bool o;
extern bool of;
extern bool fueloff;

SC_MODULE(Panel)
{
    //PanelPort:
    //in
    sc_fifo_in<bool> btn_start_port;
    sc_fifo_in<bool> btn_stop_port;
    sc_in<bool> fuel_off_port;
    sc_in<bool> apple_off_port;
    //out
    sc_out<bool> on_port;
    sc_out<bool> tank_on_port;

    sc_event on_event;
    sc_event off_event;

    SC_CTOR(Panel) {
        on_port.initialize(false);
        SC_THREAD(panel_on);
        SC_THREAD(panel_off);
        SC_THREAD(caozuo);
        sensitive << on_event << off_event;
        SC_THREAD(panel_fuel_off);
        sensitive << fuel_off_port;
        SC_THREAD(panel_apple_off);
        sensitive << apple_off_port;
    }


    void panel_on() {
        while (true) {
            o = btn_start_port.read();
            if (o == true && rest_fuel > 50) {
                on_state = 1;  
                on_event.notify();
            }
            if (btn_stop_port.read() || rest_fuel < 10 || AppleAmount > 100) {
                on_state = 0;
                off_event.notify();
            }
            wait(SC_ZERO_TIME);
        }
    }
    
    void panel_off() {
        while (true) {
            of = btn_start_port.read();
            if (of == true) {
                on_state = 0;
                off_event.notify();
            }
        }
        
    }
    
    void panel_fuel_off() {
        while (true) {
            wait();
            fueloff = fuel_off_port.read();
            if (fueloff == true) {
                on_state = 0;
                off_event.notify();
            }
        }

    }

    void panel_apple_off() {
        while (true) {
            wait();
            if (apple_off_port.read() == true) {
                on_state = 0;
                off_event.notify();
            }
        }

    }

    void caozuo() {
        while (true) {
            wait();
            if (on_state == 1) {
                on_port.write(true);
                tank_on_port.write(true);
            }
            else if (on_state == 0) {
                on_port.write(false);
                tank_on_port.write(false);
            }
        }
    }
    
};
#endif