#include <citrus/core.hpp>
#include <citrus/gpu.hpp>
#include <citrus/hid.hpp>
#include <citrus/ui.hpp>

#include <sstream>
#include <math.h>

using namespace ctr;

ui::Application* app = NULL;

class TopScreen : public ui::Component {
public:
    void added() {
        u32 width = 128;
        u32 height = 128;
        u32* pixels = (u32*) gpu::galloc(width * height * 4);
        for(u32 x = 0; x < width; x++) {
            for(u32 y = 0; y < height; y++) {
                u8 r = (u8) (sin(0.2f * (x + y)) * 128 + 127);
                u8 g = (u8) (cos(0.2f * (x + y)) * 128 + 127);
                u8 b = (u8) (tan(0.2f * (x + y)) * 128 + 127);
                pixels[(height - y - 1) * width + x] = (u32) ((r << 24) | (g << 16) | (b << 8) | 0xFF);
            }
        }

        gpu::createTexture(&this->texture);
        gpu::setTextureData(this->texture, pixels, width, height, gpu::PIXEL_RGBA8, gpu::FILTER_LINEAR);
        gpu::gfree(pixels);

        ui::Image* image = new ui::Image();
        image->setDimensions((this->getWidth() - width) / 2, (this->getHeight() - height) / 2, width, height);
        image->setTexture(this->texture);
        this->addChild("img", image);
    }

    void removed() {
        delete this->removeChild("img");

        if(this->texture != 0) {
            gpu::freeTexture(this->texture);
            this->texture = 0;
        }
    }

    void update() {
        if(ctr::core::launcher() && ctr::hid::pressed(ctr::hid::BUTTON_START)) {
            app->setTopScreen(NULL);
            app->setBottomScreen(NULL);
            return;
        }

        ui::Component* component = this->getChild("img");
        if(hid::held(hid::BUTTON_LEFT)) {
            component->setX(component->getX() - 1);
        }

        if(hid::held(hid::BUTTON_RIGHT)) {
            component->setX(component->getX() + 1);
        }

        if(hid::held(hid::BUTTON_UP)) {
            component->setY(component->getY() + 1);
        }

        if(hid::held(hid::BUTTON_DOWN)) {
            component->setY(component->getY() - 1);
        }
    }
private:
    u32 texture = 0;
};

class BottomScreen : public ui::Component {
public:
    void added() {
        const std::string message = "Hello world!";
        u32 width = ui::getDefaultFont()->getStringWidth(message) * 2;
        u32 height = ui::getDefaultFont()->getStringHeight(message) * 2;

        ui::Text* text = new ui::Text();
        text->setDimensions((this->getWidth() - width) / 2, (this->getHeight() - height) / 2, width, height);
        text->setFont(ui::getDefaultFont());
        text->setText(message);
        this->addChild("text", text);
    }

    void removed() {
        delete this->removeChild("text");
    }

    void update() {
        ui::Component* component = this->getChild("text");
        if(hid::held(hid::BUTTON_LEFT)) {
            component->setX(component->getX() - 1);
        }

        if(hid::held(hid::BUTTON_RIGHT)) {
            component->setX(component->getX() + 1);
        }

        if(hid::held(hid::BUTTON_UP)) {
            component->setY(component->getY() + 1);
        }

        if(hid::held(hid::BUTTON_DOWN)) {
            component->setY(component->getY() - 1);
        }
    }
};

int main(int argc, char **argv) {
    if(!ctr::core::init(argc)) {
        return 0;
    }

    TopScreen topScreen;
    topScreen.setDimensions(0, 0, TOP_WIDTH, TOP_HEIGHT);

    BottomScreen bottomScreen;
    bottomScreen.setDimensions(0, 0, BOTTOM_WIDTH, BOTTOM_HEIGHT);

    app = new ui::Application();
    app->setTopScreen(&topScreen);
    app->setBottomScreen(&bottomScreen);
    app->start();
    delete app;

    ctr::core::exit();
    return 0;
}
