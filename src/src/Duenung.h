#ifndef  _DUENUNG_H_
#define _DUENUNG_H_
#include "systemc.h"
#include "stdio.h"

extern regen_time;
extern regen_5time;
extern regen_kontin;

SC_MODULE(Duenung) {
	sc_fifo_out<bool> kuerbisfeld_duengen_port;

	SC_CTOR(Duenung) {
		kuerbisfeld_duengen_port.initialize(false);
		SC_THREAD(duengen);
		SC_THREAD(stark_duengen);
	}

	void duengen() {
		while (regen_kontin == false){
			wait(1380 - regen_time + 300 * (regen_5time - 1), SE_SEC);
			kuerbisfeld_duengen_port.write(true);
			while (true) {
				wait(780, SE_SEC);
				kuerbisfeld_duengen_port.write(true);
			}
		}
	}

	void stark_duengen() {
		while (regen_kontin == true) {
			while (true) {
				wait(300, SE_SEC);
				kuerbisfeld_duengen_port.write(true);
			}
        }
	}









}