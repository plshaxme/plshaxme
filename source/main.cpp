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

		screen_begin_draw_info();
		screen_draw_string("Hello world!", 0, 0, 255, 255, 255);
		screen_end_draw();

		screen_swap_buffers();
	}

	platform_cleanup();
	return 0;
}
