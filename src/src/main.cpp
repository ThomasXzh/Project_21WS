#include "systemc.h"
#include "TestBench.h"
#include <string>
#include"Bewaesserung_ohneregen.h"
#include"Bewaesserung_regen.h"
#include"Wassertank.h"
#include"Pflanzenschutzsystem.h"
#include"Duenung.h"
#include"Klimasteuerung.h"

int rest_wasser = 0;
int a = 0;
bool b = false;
int c = 0;
int d = 0;
int var2 = 0;
int var4 = 0;
int var5 = 0;
int regen_time = 0;
int regen_5time = 0;
bool regen_kontin = false;


int sc_main(int argc, char *argv[])
{
    // ------------------- In  Events -------------------
    
    //WETTER
    sc_signal<bool> regen;
    sc_signal<int> temperatur;
    sc_signal<TestBench::WetterTyp> wetter;

    //SALATFELD
    sc_fifo<bool> salatfeld_blattlaeuse(1);
    sc_fifo<bool> salatfeld_schnecken(1);

    //KÜRBISFELD
    sc_fifo<bool> kuerbisfeld_blattlaeuse(1);

    //WASSERTANK
    sc_fifo<int> wassertank_auffuellen(1);

    // ------------------- Out Events -------------------

    //SALATFELD
    sc_fifo<bool> salatfeld_bewaessern(1);
    sc_fifo<bool> salatfeld_duengen(1);
    sc_fifo<bool> salatfeld_pflanzenschutz(1);

    //KÜRBISFELD
    sc_fifo<bool> kuerbisfeld_bewaessern(1);
    sc_fifo<bool> kuerbisfeld_duengen(1);
    sc_fifo<bool> kuerbisfeld_pflanzenschutz(1);

    //GEWÄCHSHAUS
    sc_fifo<bool> gewaechshaus_bewaessern(1);
    sc_fifo<bool> gewaechshaus_duengen(1);
    sc_signal<int> gewaechshaus_heizung;
    sc_signal<int> gewaechshaus_lampe;

    //WASSERTANK
    sc_signal<bool> wassertank_warnlampe;
	
	// Connect testbench ports to channels:
	TestBench tb("TestBench", argv[1]);
	
    tb.regen(regen);
    tb.temperatur(temperatur);
    tb.wetter(wetter);

    tb.salatfeld_bewaessern(salatfeld_bewaessern);
    tb.salatfeld_duengen(salatfeld_duengen);
    tb.salatfeld_pflanzenschutz(salatfeld_pflanzenschutz);
    tb.salatfeld_blattlaeuse(salatfeld_blattlaeuse);
    tb.salatfeld_schnecken(salatfeld_schnecken);

    tb.kuerbisfeld_bewaessern(kuerbisfeld_bewaessern);
    tb.kuerbisfeld_duengen(kuerbisfeld_duengen);
    tb.kuerbisfeld_pflanzenschutz(kuerbisfeld_pflanzenschutz);
    tb.kuerbisfeld_blattlaeuse(kuerbisfeld_blattlaeuse);

    tb.gewaechshaus_bewaessern(gewaechshaus_bewaessern);
    tb.gewaechshaus_duengen(gewaechshaus_duengen);
    tb.gewaechshaus_heizung(gewaechshaus_heizung);
    tb.gewaechshaus_lampe(gewaechshaus_lampe);
    tb.wassertank_auffuellen(wassertank_auffuellen);
    tb.wassertank_warnlampe(wassertank_warnlampe);

    // TODO connect your module(s) to channels
    Wassertank wassertank("Wassertank");
    Bewaesserung_ohneregen bewaesserung_ohneregen("Bewaesserung_ohneregen");
    Bewaesserung_regen bewaesserung_regen("Bewaesserung_regen");
    Pflanzenschutzsystem pflanzenschutzsystem("Pflanzenschutzsystem");
    Gewaechshaus gewaechshaus("Gewaechshaus");
    Duenung duenung("Duenung");
    Klimasteuerung klimasteuerung("Klimasteuerung");

    //wassertank
    wassertank.regen_port(regen);
    wassertank.wassertank_auffuellen_port(wassertank_auffuellen);
    wassertank.wassertank_warnlampe_port(wassertank_warnlampe);

    //Bewaesserung_ohneregen
    bewaesserung_ohneregen.temperatur_port(temperatur);
    bewaesserung_ohneregen.regen_port(regen);
    bewaesserung_ohneregen.salatfeld_bewaessern_port(salatfeld_bewaessern);
    bewaesserung_ohneregen.kuerbisfeld_bewaessern_port(kuerbisfeld_bewaessern);
    bewaesserung_ohneregen.wassertank_warnlampe_port(wassertank_warnlampe);

    //Bewaesserung_regen
    bewaesserung_regen.regen_port(regen);
    bewaesserung_regen.kuerbisfeld_duengen_port(kuerbisfeld_duengen);



    //Pflanzenschutzsystem
    pflanzenschutzsystem.salatfeld_pflanzenschutz_port(salatfeld_pflanzenschutz);
    pflanzenschutzsystem.salatfeld_blattlaeuse_port(salatfeld_blattlaeuse);
    pflanzenschutzsystem.salatfeld_schnecken_port(salatfeld_schnecken);
    pflanzenschutzsystem.kuerbisfeld_blattlaeuse_port(kuerbisfeld_blattlaeuse);
    pflanzenschutzsystem.kuerbisfeld_pflanzenschutz_port(kuerbisfeld_pflanzenschutz);

    //Gewaechshaus
    gewaechshaus.gewaechshaus_bewaessern_port(gewaechshaus_bewaessern);
    gewaechshaus.gewaechshaus_duengen_port(gewaechshaus_duengen);
    gewaechshaus.salatfeld_duengen_port(salatfeld_duengen);
    gewaechshaus.wassertank_warnlampe_port(wassertank_warnlampe);

    //Duenung
    duenung.kuerbisfeld_duengen_port(kuerbisfeld_duengen);


    //Klimasteuerung
    klimasteuerung.regen_port(regen);
    klimasteuerung.gewaechshaus_heizung_port(gewaechshaus_heizung);
    klimasteuerung.gewaechshaus_lampe_port(gewaechshaus_lampe);
    klimasteuerung.wetter_port(wetter);
    klimasteuerung.temperatur_port(temperatur);




	// Run simulation:
    //NICHT ÄNDERN
	sc_start(3800, SC_SEC);
	return 0;
}
