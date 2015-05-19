#include <ctrcommon/input.hpp>
#include <ctrcommon/gpu.hpp>
#include <ctrcommon/platform.hpp>

int main(int argc, char **argv) {
    if(!platformInit()) {
        return 0;
    }

    const std::string message = "Hello world!";

    gpuViewport(TOP_SCREEN, 0, 0, TOP_WIDTH, TOP_HEIGHT);
    gputOrtho(0, TOP_WIDTH, 0, TOP_HEIGHT, -1, 1);
    gpuClearColor(0xFF, 0xFF, 0xFF, 0xFF);
    while(platformIsRunning()) {
        inputPoll();
        if(inputIsPressed(BUTTON_START) && platformIsNinjhax()) {
            break;
        }

        gpuClear();
        gputDrawString(message, (gpuGetViewportWidth() - gputGetStringWidth(message, 16)) / 2, (gpuGetViewportHeight() - gputGetStringHeight(message, 16)) / 2, 16, 16, 0, 0, 0);
        gpuFlush();
        gpuFlushBuffer();
        gpuSwapBuffers(true);
    }

    platformCleanup();
    return 0;
}
