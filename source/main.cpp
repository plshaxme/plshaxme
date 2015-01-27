#include "common.hpp"

int main(int argc, char **argv) {
	if(!platform_init()) {
		return 0;
	}

	while(platform_is_running()) {
		input_poll();
		if(input_is_pressed(BUTTON_START)) {
			break;
		}

		screen_begin_draw(TOP_SCREEN);
		screen_draw_string("Hello world!", (screen_get_width() - screen_get_str_width("Hello world!")) / 2, (screen_get_height() - screen_get_str_height("Hello world!")) / 2, 255, 255, 255);
		screen_end_draw();

		screen_swap_buffers();
	}

	platform_cleanup();
	return 0;
}
