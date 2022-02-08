#ifndef  _BEWAESSERUNG_OHNEREGEN_H_
#define  _BEWAESSERUNG_OHNEREGEN_H_
#include "systemc.h"
#include "stdio.h"

extern rest_wasser;
extern b;
extern c;
extern d;



SC_MODULE(Bewaesserung_ohneregen) {
	sc_in<int> temperatur_port;
	sc_in<bool> regen_port;
	sc_fifo_out<bool> salatfeld_bewaessern_port;
	sc_fifo_out<bool> kuerbisfeld_bewaessern_port;
	sc_out<bool> wassertank_warnlampe_port;

	//sc_event event1;
	//sc_event event2;


	SC_CTOR(Bewaesserung_ohneregen) {
		salatfeld_bewaessern_port.initialize(false);
		kuerbisfeld_bewaessern_port.initialize(false);
		wassertank_warnlampe_port.initialize(false);

		/*SC_THREAD(Temperatur_anderung);

		SC_THREAD(Trigger);
		sensitive << event2;*/

		SC_THREAD(kuerbisfeld_bewaess_wu30);
		//sensitive << event1;

		SC_THREAD(kuerbisfeld_bewaess_ub30);
		//sensitive << event1;

		SC_THREAD(wasser_check);

		SC_THREAD(salatfeld_bewaess);
	}

	/*void Temperatur_anderung() {
		while (true) {
			c = d;
		    d = temperatur_port.read();
			if (c == d) {
				b = false;
			}
			else {
				b = true;
			}
		}
		
	}

	void Trigger() {
		while (b) {
			wait()
				event1.notify();
		}

	}*/


	void kuerbisfeld_bewaess_wu30() {
		while (regen_port.read() == false) {
			//wait();
			while (temperatur_port.read() <= 30) {
				wait(480, SC_SEC);
				kuerbisfeld_bewaessern_port.write(true);
				//event2.notify();
				rest_wasser -= 1000;
				if(temperatur_port.read() <= 30)

			}

		}
	}

	void kuerbisfeld_bewaess_ub30() {
		while (regen_port.read() == false) 
		{
			//wait();
			while (temperatur_port.read() > 30) {
				wait(360, SC_SEC);
				kuerbisfeld_bewaessern_port.write(true);
				//event2.notify();
				rest_wasser -= 1000;

			}

		}
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

	void salatfeld_bewaess() {
		while (regen_port.read() == false) {
			wait(600, SE_SEC);
			salatfeld_bewaessern_port.write(true);
			rest_wasser -= 1000;

		}
	}

}   
