#include <ctrcommon/input.hpp>
#include <ctrcommon/platform.hpp>
#include <ctrcommon/screen.hpp>

int main(int argc, char **argv) {
    if(!platformInit()) {
        return 0;
    }

    while(platformIsRunning()) {
        inputPoll();
        if(inputIsPressed(BUTTON_START)) {
            break;
        }

        screenBeginDraw(TOP_SCREEN);
        screenDrawString("Hello world!", (screenGetWidth() - screenGetStrWidth("Hello world!")) / 2, (screenGetHeight() - screenGetStrHeight("Hello world!")) / 2, 255, 255, 255);
        screenEndDraw();

        screenSwapBuffers();
    }

    platformCleanup();
    return 0;
}
