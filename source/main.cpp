#include <ctrcommon/input.hpp>
#include <ctrcommon/gpu.hpp>
#include <ctrcommon/platform.hpp>

int main(int argc, char **argv) {
    if(!platformInit()) {
        return 0;
    }

    const std::string message = "Hello world!";

    gpuClearColor(0xFF, 0xFF, 0xFF, 0xFF);
    while(platformIsRunning()) {
        inputPoll();
        if(inputIsPressed(BUTTON_START) && platformIsNinjhax()) {
            break;
        }

        gpuClear();
        gputDrawString(message, (gpuGetViewportWidth() - gputGetStringWidth(message, 2)) / 2, (gpuGetViewportHeight() - gputGetStringHeight(message, 2)) / 2, 2, 0, 0, 0);
        gpuFlush();
        gpuFlushBuffer();
        gpuSwapBuffers(true);
    }

    platformCleanup();
    return 0;
}
