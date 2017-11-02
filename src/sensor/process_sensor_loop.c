/*
 * process_sensor_loop.c
 *
 *  Created on: Nov 2, 2017
 *      Author: root
 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "inc/process_sensor.h"
#include "../libmodbus/modbus.h"

void process_sensor_loop(void) {

	modbus_t *mb;
	uint16_t tab_reg[32] = { 0 };
	mb = modbus_new_rtu("/dev/ttyUSB0", 115200, 'N', 8, 1); //open port
	if (mb == NULL) {
		printf("mb is NULL\n");
		return;
	}

	modbus_set_slave(mb, 1); //set slave address

	modbus_connect(mb);

	struct timeval t;
	t.tv_sec = 0;
	t.tv_usec = 1000000; //set modbus time 1000ms
	modbus_set_response_timeout(mb, &t);

	int regs = modbus_read_registers(mb, 0, 20, tab_reg);

	printf("%d %d %d %d %d\n", regs, tab_reg[0], tab_reg[1], tab_reg[2],
			tab_reg[3]);
	modbus_close(mb);
	modbus_free(mb);

}
