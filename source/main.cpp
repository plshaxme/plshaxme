#include <citrus/core.hpp>
#include <citrus/gpu.hpp>
#include <citrus/gput.hpp>
#include <citrus/hid.hpp>

#include <sstream>

int main(int argc, char **argv) {
    if(!ctr::init()) {
        return 0;
    }

    const std::string message = "Hello world!";

    ctr::gpu::setViewport(ctr::gpu::SCREEN_TOP, 0, 0, TOP_WIDTH, TOP_HEIGHT);
    ctr::gput::setOrtho(0, ctr::gpu::getViewportWidth(), 0, ctr::gpu::getViewportHeight(), -1, 1);
    ctr::gpu::setClearColor(0xFF, 0xFF, 0xFF, 0xFF);
    while(ctr::running()) {
        ctr::hid::poll();
        if(ctr::launcher() && ctr::hid::pressed(ctr::hid::BUTTON_START)) {
            break;
        }

        ctr::gpu::clear();
        ctr::gput::drawString(message, (ctr::gpu::getViewportWidth() - ctr::gput::getStringWidth(message, 16)) / 2, (ctr::gpu::getViewportHeight() - ctr::gput::getStringHeight(message, 16)) / 2, 16, 16, 0, 0, 0);
        ctr::gpu::flushCommands();
        ctr::gpu::flushBuffer();
        ctr::gpu::swapBuffers(true);
    }

    ctr::exit();
    return 0;
}
