#include "Rasterizer.h"
#include "DisplayWindow.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/random.hpp"


const int width = 1280;
const int height = 720;

class Pipeline {
public:
    Pipeline(int width, int height) :
    rasterizer(width, height), window(width, height), width(width), height(height) {

    };

    

private:
    Rasterizer rasterizer;
    DisplayWindow window;

    int width, height;
};

int main() {

    Rasterizer rasterizer{width, height};
    DisplayWindow window{width, height};

    glm::vec3 point{0.0f, 0.0f, 0.0f};

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

/*
 *
*

    TriangleDC triangle {
        .a = {400, 500, 1, 255, 0, 0},
        .b = {200, 300, 1, 0, 255, 0},
        .c = {600, 100, 1, 0, 0, 255}
    };

    TriangleDC triangle2 {
        .a = {400, 700, 1, 255, 0, 0},
        .b = {100, 200, 1, 0, 255, 0},
        .c = {300, 50, 1, 0, 0, 255}
    };

 */