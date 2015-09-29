#include <citrus/core.hpp>
#include <citrus/gpu.hpp>
#include <citrus/gput.hpp>
#include <citrus/hid.hpp>

using namespace ctr;

int main(int argc, char **argv) {
    if(!ctr::core::init(argc)) {
        return 0;
    }

    gpu::setViewport(gpu::SCREEN_TOP, 0, 0, TOP_WIDTH, TOP_HEIGHT);
    gput::setOrtho(0, TOP_WIDTH, 0, TOP_HEIGHT, -1, 1);

    const std::string message = "Hello world!";
    while(ctr::core::running()) {
        hid::poll();
        if(core::launcher() && hid::pressed(hid::BUTTON_START)) {
            break;
        }

        gpu::clear();
        gput::drawString(message, (TOP_WIDTH - gput::getStringWidth(message, 16)) / 2, (TOP_HEIGHT - gput::getStringHeight(message, 16)) / 2, 16, 16);
        gpu::flushCommands();
        gpu::flushBuffer();
        gpu::swapBuffers(true);
    }

    ctr::core::exit();
    return 0;
}
