#ifndef  _GEWAECHSHAUS_H_
#define _GEWAECHSHAUS_H_
#include "systemc.h"
#include "stdio.h"

extern rest_wasser;

SC_MODULE() {
	sc_fifo_out<bool> gewaechshaus_bewaessern_port;
	sc_fifo_out<bool> gewaechshaus_duengen_port;
	sc_fifo_out<bool> salatfeld_duengen_port;
	sc_signal_out<bool> wassertank_warnlampe_port;


	SC_CTOR(Gewaechshaus) {

		gewaechshaus_bewaessern_port.initialize(false);
		gewaechshaus_duengen_port.initialize(false);
		salatfeld_duengen_port.initialize(false);
		wassertank_warnlampe_port.initialize(false);

		SC_THREAD(wasser_check);
		SC_THREAD(gewaechshaus_bewaesse);
		SC_THREAD(gewaechshaus_duengen);
		SC_THREAD(salat_duengen);
		
	}

	void wasser_check()
	{
		while (true)
		{
			if (rest_wasser < 1000) {
				wassertank_warnlampe_port.write(true);
			}
			else {
				wassertank_warnlampe_port.write(false);
			}


		}
	}

	void gewaechshaus_bewaesse() {
		while (true) {
			wait(95, SC_SEC);
			gewaechshaus_bewaessern_port.write(true);
			rest_wasser -= 1000;
		}
	}

	void gewaechshaus_duengen() {
		while (true) {
			wait(1020, SE_SEC);
		    gewaechshaus_duengen_port.write(true);

		}
	}

	void salat_duengen() {
		while (true) {
			wait(1500, SE_SEC);
			salatfeld_duengen_port.write(true);
		}
	}
}