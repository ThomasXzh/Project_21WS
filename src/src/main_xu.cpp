#include "systemc.h"
#include "Panel.h"
#include "Tank.h"
#include "TestBench.h"
#include "AppleSensor.h"
#include "MotionSensor.h"
#include <string>

int State = 0;
int AppleAmount = 0;
int rest_fuel = 0;
int on_state = 0;
int ernte = 0;
int a = 0;
bool b = 0;
TestBench::Direction c;
bool d = 0;
int har_now = 0;
bool h = 0;
bool o = 0;
bool of = 0;
bool fueloff = 0;

int sc_main(int argc, char *argv[])
{
   

	// Channel definitions:
    
    //Panel
    sc_fifo<bool> btn_start(1);
    sc_fifo<bool> btn_stop(1);
    sc_signal<bool> tank_on;
    sc_signal<bool>fuel_off;
    //Apple_Sensor
	sc_signal<TestBench::AppleHeight> apple_sensed;
    sc_fifo<bool> apple_harvested(1);
    sc_signal<bool> apple_off;

    //Direction_Sensor
	sc_fifo<TestBench::Direction> direction(1);
    sc_signal<bool> blocked;

    //Tank
    sc_fifo<int> add_fuel(1);

    //Lights
    sc_signal<bool> on;
    sc_signal<bool> blink_left;
    sc_signal<bool> blink_right;
    sc_signal<bool> danger_lights;  
    sc_signal<bool> done;
    sc_signal<bool> vacuum_active;
    sc_signal<bool> low_fuel;
	


	// Connect testbench ports to channels:
	TestBench tb("TestBench", argv[1]);
    tb.btn_start(btn_start);
    tb.btn_stop(btn_stop);
    tb.apple_sensed(apple_sensed);
    tb.apple_harvested(apple_harvested);
    tb.direction(direction);
    tb.blocked(blocked);
    tb.add_fuel(add_fuel);
    tb.on(on);
    tb.blink_left(blink_left);
    tb.blink_right(blink_right);
    tb.danger_lights(danger_lights);
    tb.done(done);
    tb.vacuum_active(vacuum_active);
    tb.low_fuel(low_fuel);


	 /*TODO connect your module(s) to channels*/
    AppleSensor applesensor("AppleSensor");
    MotionSensor motionsensor("MotionSensor");
    Panel panel("Panel");
    Tank tank("Tank");

    //AppleSenPort:
    applesensor.apple_sensed_port(apple_sensed);
    applesensor.apple_harvested_port(apple_harvested);
    applesensor.done_port(done);
    applesensor.vacuum_active_port(vacuum_active);
    applesensor.apple_off_port(apple_off);
    //MotionSenPort:
    motionsensor.direction_port(direction);
    motionsensor.blocked_port(blocked);
    motionsensor.blink_left_port(blink_left);
    motionsensor.blink_right_port(blink_right);
    motionsensor.danger_lights_port(danger_lights);
    //PanelPort:
    panel.btn_start_port(btn_start);
    panel.btn_stop_port(btn_stop);
    panel.on_port(on);
    panel.tank_on_port(tank_on);
    panel.fuel_off_port(fuel_off);
    panel.apple_off_port(apple_off);
    //TankPort:
    tank.add_fuel_port(add_fuel);
    tank.low_fuel_port(low_fuel);
    tank.tank_on_port(tank_on);
    tank.fuel_off_port(fuel_off);



	// Run simulation:
	sc_start(13000, SC_SEC); //nicht verändern
	return 0;
}
