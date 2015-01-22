#include "common.h"

int main(int argc, char **argv) {
	if(!platform_init()) {
		return 0;
	}

	while(platform_is_running()) {
		input_poll();
		if(input_is_pressed(BUTTON_START)) {
			break;
		}

		// Do stuff!

		screen_swap_buffers();
	}

	platform_cleanup();
	return 0;
}
