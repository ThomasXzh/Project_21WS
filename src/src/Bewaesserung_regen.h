#ifndef  _BEWAESSERUNG_REGEN_H_
#define  _BEWAESSERUNG_REGEN_H_
#include "systemc.h"
#include "stdio.h"

extern regen_5time;
extern regen_kontin;
extern regen_time

SC_MODULE(Bewaesserung_regen) {
	sc_in<bool> regen_port;
	sc_out<bool> kuerbisfeld_duengen_port;

	SC_CTOR(Bewaesserung_regen) {
		kuerbisfeld_duengen_port.initialize(false);
		SC_THREAD(regen);
		SC_THREAD(regen_time);
	}

	void regen_600() {
		while (regen_port.read() == true) {
			wait(600, SE_SEC);
			kuerbisfeld_duengen_port.write(true);
			while (true) {
				wait(300, SE_SEC);
				kuerbisfeld_duengen_port.write(true);
				regen_5time += 1;
				regen_kontin = true;
			}

        }
	}

	void regen_time() {
		while (regen_port.read() == true) {
			wait(1, SE_SEC);
			regen_time += 1;
        }
	}
}
