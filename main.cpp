#include "Rasterizer.h"
#include "DisplayWindow.h"

const int width = 1280;
const int height = 720;

int main() {

    Rasterizer rasterizer{width, height};
    DisplayWindow window{width, height};

    Triangle ndc_triangle {
        .a = {0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        .b = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
        .c = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}
    };

    while (!window.should_close()) {
        window.update();
        rasterizer.clear_frame_buffer();
        rasterizer.render_triangle_filled(ndc_triangle);
        auto& img = rasterizer.get_frame_buffer();
        img.flip_vertically();
        window.present(img);
    }
}
