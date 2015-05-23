#include <citrus/core.hpp>
#include <citrus/gpu.hpp>
#include <citrus/gput.hpp>
#include <citrus/hid.hpp>

#include <sstream>

using namespace ctr;

int main(int argc, char **argv) {
    if(!core::init()) {
        return 0;
    }

    const std::string message = "Hello world!";
    float messageX = (TOP_WIDTH - gput::getStringWidth(message, 16)) / 2;
    float messageY = (TOP_HEIGHT - gput::getStringHeight(message, 16)) / 2;

    gpu::setClearColor(0xFF, 0xFF, 0xFF, 0xFF);
    gpu::setViewport(gpu::SCREEN_TOP, 0, 0, TOP_WIDTH, TOP_HEIGHT);
    gput::setOrtho(0, TOP_WIDTH, 0, TOP_HEIGHT, -1, 1);

    while(core::running()) {
        hid::poll();
        if(core::launcher() && hid::pressed(hid::BUTTON_START)) {
            break;
        }

        gpu::clear();
        gput::drawString(message, messageX, messageY, 16, 16, 0, 0, 0);
        gpu::flushCommands();
        gpu::flushBuffer();
        gpu::swapBuffers(true);
    }

    core::exit();
    return 0;
}
