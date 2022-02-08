#ifndef  _PFLANZENSCHUTZSYSTEM_H_
#define _PFLANZENSCHUTZSYSTEM_H_
#include "systemc.h"
#include "stdio.h"



SC_MODULE(Pflanzenschutzsystem) {

    sc_fifo_in<bool> salatfeld_blattlaeuse_port;
    sc_fifo_in<bool> salatfeld_schnecken_port;
    sc_fifo_in<bool> kuerbisfeld_blattlaeuse_port;
    sc_fifo_out<bool> salatfeld_pflanzenschutz_port;
    sc_fifo_out<bool> kuerbisfeld_pflanzenschutz_port;


    SC_CTOR(Pflanzenschutzsystem) {
        
        salatfeld_pflanzenschutz_port.initialize(false);
        kuerbisfeld_pflanzenschutz_port.initialize(false);
        SC_THREAD(salatfeld_blattlaeuse_schutz);
        SC_THREAD(salatfeld_schnecken_schutz);
        SC_THREAD(kuerbisfeld_blattlaeuse_schutz);
        
    }

    void kuerbisfeld_blattlaeuse_schutz() {
        while (true) {
            while (kuerbisfeld_blattlaeuse_port.read() == true) {
                kuerbisfeld_pflanzenschutz_port.write(true);
            }
        }
    }

    void salatfeld_blattlaeuse_schutz() {
        while (true) {
            while (salatfeld_blattlaeuse_port.read() == true) {
                salatfeld_pflanzenschutz_port.write(true);
            }
        }
    }

    void salatfeld_schnecken_schutz() {
        while (salatfeld_schnecken_port.read() == true) {
            salatfeld_pflanzenschutz_port.write(true);
            wait(20, SE_SEC);
            salatfeld_pflanzenschutz_port.write(true);
        }
    }
}