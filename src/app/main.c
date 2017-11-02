#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "../sensor/inc/process_sensor.h"
#include "../led_screen/inc/process_led_screen.h"

int main(void) {

	pid_t fpid_sensor;
	pid_t fpid_led_screen;

	fpid_sensor = fork();
	if (fpid_sensor < 0)
		printf("error in fork sensor!\n");
	else if (fpid_sensor == 0) {  //son

		process_sensor_loop();

		printf("sensor end\n");
		return EXIT_SUCCESS;
	}

	fpid_led_screen = fork();
	if (fpid_led_screen < 0)
		printf("error in fork led screen!\n");
	else if (fpid_led_screen == 0) {  //son

		process_led_screen_loop();

		printf("led screen end\n");
		return EXIT_SUCCESS;
	}

	waitpid(fpid_sensor, NULL, 0);
	waitpid(fpid_led_screen, NULL, 0);

	printf("end\n");
	return EXIT_SUCCESS;
}
