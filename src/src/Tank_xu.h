//tank.h
#ifndef  _TANK_H_
#define _TANK_H_
#include "systemc.h"
#include "stdio.h"

extern int rest_fuel;
extern int State;
extern int on_state;
extern int a;

SC_MODULE(Tank)
{   
    sc_in<bool> tank_on_port;
    sc_fifo_in<int> add_fuel_port;

    sc_out<bool> low_fuel_port;
    sc_out<bool> fuel_off_port;

    sc_event tankon;
    sc_event check;

    SC_CTOR(Tank) {
        low_fuel_port.initialize(true);
        SC_THREAD(fuel);
        SC_THREAD(on);
        sensitive << tank_on_port;
        SC_THREAD(fuel_cost);
        sensitive << tankon;
        SC_THREAD(check_fuel);
        sensitive << tankon << check;
    }



    void fuel() {
        while (true) {
            a = add_fuel_port.read();
            if (rest_fuel + a <= 500) {
                rest_fuel += a; 
            }
            else if (rest_fuel + a >= 500) {
                rest_fuel = 500;
                cout << rest_fuel;
                /*printf( "The Tank is full");*/
            }
      
        }
        
    }

    void fuel_cost() {
        while (true) {
            wait();
            while (rest_fuel > 0 && on_state == 1) {
                wait(3000, SC_MS);
                if (State == 0 || State == 4) {
                    rest_fuel -= 1;
                }
                else {
                    rest_fuel -= 2;
                }
                check.notify();
            }
        }
    }

    void on() {
        while (true) {
            wait();
            if (tank_on_port.read() == true) {
                tankon.notify();
            }
        }
    }

    void check_fuel() {
        while (true) {
            wait();
                if (rest_fuel < 50 && on_state == 1) {
                    low_fuel_port.write(true);
                    if (rest_fuel < 10) {
                        fuel_off_port.write(true);
                    }
                }
                else {
                    low_fuel_port.write(false);
                }
        }
    }
};

#endif