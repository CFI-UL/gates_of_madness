#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

void setup(char *pin_number) {
	char buf[40] = {0};
	int export_fd = open("/sys/class/gpio/export", O_WRONLY);
	printf("export_fd: %d", export_fd);
	snprintf(buf, 40, "%s\n", pin_number);
	puts(buf);
	write(export_fd, pin_number, 3);

	snprintf(buf, 40, "/sys/class/gpio/gpio%s/direction", pin_number);
	int direction_fd = open(buf, O_WRONLY);
	write(direction_fd, "out\n", 4);
}

int main() {
	setup("19");

	write(1, "before loop\n", 12);

	int pin_fd = open("/sys/class/gpio/gpio19/value", O_WRONLY);

	for (int i = 0; ; i++) {
		// 2 ms
		write(pin_fd, "1\n", 2);
		usleep(2000);

		// 20ms
		write(pin_fd, "0\n", 2);
		usleep(18000);
	}

	write(1, "after loop\n", 11);
}
