#ifndef  _KLIMASTEUERUNG_H_
#define _KLIMASTEUERUNG_H_
#include "systemc.h"
#include "stdio.h"


SC_MODULE(Klimasteuerung) {
	sc_in<bool> regen_port;
	sc_in<int> temperatur_port;
	sc_in<TestBench::WetterTyp> wetter_port;
	sc_out<int> gewaechshaus_heizung_port;
	sc_out<int> gewaechshaus_lampe_port;

	SC_CTOR(Klimasteuerung) {
		gewaechshaus_heizung_port.initialize(1);
		gewaechshaus_lampe_port.initialize(0);

		SC_THREAD(Heizung_uw30);
		SC_THREAD(Heizung_ue30);
		SC_THREAD(Lampe_nomal);
		SC_THREAD(Lampe_mix);


	}

	void Heizung_uw30{
		while (temperatur_port.read() <= 30) {
			if (wetter_port.read() == 0) {
				gewaechshaus_heizung_port.write(1);
			}
			else if (wetter_port.read() == 1) {
				gewaechshaus_heizung_port.write(2);
			}
			else if (wetter_port.read() == 2) {
				gewaechshaus_heizung_port.write(3);
			}
			else if (regen_port.read() == true) {
				gewaechshaus_heizung_port.write(3);
			}
			else if (wetter_port.read() == 3) {
				gewaechshaus_heizung_port.write(4);
			}
		
		}
	}

	void Heizung_ue30 {
	    while (temperatur_port.read() > 30) {
			if (wetter_port.read() == 0) {
				gewaechshaus_heizung_port.write(0);
			}
			else if (wetter_port.read() == 1) {
				gewaechshaus_heizung_port.write(0);
			}
			else if (wetter_port.read() == 2) {
				gewaechshaus_heizung_port.write(1);
			}
			else if (regen_port.read() == true) {
				gewaechshaus_heizung_port.write(1);
			}
			else if (wetter_port.read() == 3) {
				gewaechshaus_heizung_port.write(2);
			}
        }

	}

	void Lampe_nomal {
		while (true) {
			if (wetter_port.read() == 0) {
				gewaechshaus_lampe_port.write(0);
			}
			else if (wetter_port.read() == 1) {
				gewaechshaus_lampe_port.write(0);
			}
			else if (wetter_port.read() == 2) {
				gewaechshaus_lampe_port.write(2);
			}
			else if (wetter_port.read() == 3) {
				gewaechshaus_lampe_port.write(3);
			}

		}
	}

	void Lampe_mix {
		while (wetter_port.read() == 0 || wetter_port.read() == 1) {
			if (regen_port.read() == true) {
				gewaechshaus_lampe_port.write(1);
			}	
        }

	    while (wetter_port.read() == 2 || wetter_port.read() == 3) {
			if (regen_port.read() == true) {
				gewaechshaus_lampe_port.write(3);
			}
		}

	}
}