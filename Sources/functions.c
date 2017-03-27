#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "red.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "MCUC1.h"
#include "green.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "blue.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "delay.h"
#include "main_header.h"

int count_poll;

void blink_blue(void){

	if (flag_500ms==1){
					   blue_Neg();
					  }
}

void poll_modbus(void){

	extern int flag_poll;
	extern unsigned int polling;

	if (flag_1ms==1){
		count_poll++;}

	if (count_poll>=polling){
		flag_poll = 1;
		green_Neg();
		count_poll = 0;
	}
	else{
		flag_poll = 0;
	}

}

void time_stamp(){

	extern int count_1ms;
	extern int count_10ms;
	extern int count_100ms;
	extern int count_200ms;
	extern int count_500ms;
	extern int count_1s;

	extern int flag_1ms;
	extern int flag_10ms;
	extern int flag_100ms;
	extern int flag_200ms;
	extern int flag_500ms;
	extern int flag_1s;

	if (count_1ms >= 1) {flag_1ms = 1; count_1ms = 0;}
	else {flag_1ms = 0;}

	if (count_10ms >= 10) {flag_10ms = 1; count_10ms = 0;}
	else {flag_10ms = 0;}

	if (count_100ms >= 100) {flag_100ms = 1; count_100ms = 0;}
	else {flag_100ms = 0;}

	if (count_200ms >= 200) {flag_200ms = 1; count_200ms = 0;}
	else {flag_200ms = 0;}

	if (count_500ms >= 500) {flag_500ms = 1; count_500ms = 0;}
	else {flag_500ms = 0;}

	if (count_1s >= 1000) {flag_1s = 1; count_1s = 0;}
	else {flag_1s = 0;}

}
