#ifndef  _WASSERTANK_H_
#define _WASSERTANK_H_
#include "systemc.h"
#include "stdio.h"

extern rest_wasser;
extern a;

SC_MODULE(Wassertank)
{
	sc_in<bool> regen_port;
	sc_fifo_in<int> wassertank_auffuellen_port;
	sc_out<bool> wassertank_warnlampe_port;


	SC_CTOR(Wassertank)
	{
		wassertank_warnlampe_port.initialize(false);
		SC_THREAD(wasser_check);
		SC_THREAD(wasser_vermeidung);
		SC_THREAD(wasser_manuell);
		SC_THREAD(wasser_regen);
		sensitive << regen;
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

	void wasser_vermeidung()
	{
		while (true)
		{
			if (rest_wasser < 0) {
				rest_wasser = 0;
			}
			else if(rest_wasser >5000){
				rest_wasser = 5000;
			}
		}
	}

	void wasser_regen()
	{
		while (true)
		{
			wait();
			wait(95, SC_SEC);
			rest_wasser += 100;
		}
	}

	void wasser_manuell()
	{
		while (true)
		{
			a = wassertank_auffuellen_port.read();
			rest_wasser += a;
		}
	}
}  
#endif