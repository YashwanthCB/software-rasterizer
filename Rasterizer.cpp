//
// Created by yashwanth on 3/15/26.
//

#include "Rasterizer.h"
#include "Utils.h"

#include <array>
#include <algorithm>
#include <cmath>

Rasterizer::Rasterizer(int width, int height) :
    frame_buffer(width, height, TGAImage::RGB), width(width), height(height) {
}

Rasterizer::~Rasterizer() {
    /*frame_buffer.write_tga_file("framebuffer.tga");
    std::system("xdg-open framebuffer.tga");*/
}

TGAImage& Rasterizer::get_frame_buffer() {
    return frame_buffer;
}

void Rasterizer::clear_frame_buffer() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            frame_buffer.set(x, y, {0,0,0,0});
        }
    }
}

void Rasterizer::render_wireframe(const std::string &model) {
    Utils::load_wavefront(model);
}

void Rasterizer::render_triangle(struct TriangleDC &tri) {
    render_line_simple(tri.a, tri.b, red);
    render_line_simple(tri.b, tri.c, red);
    render_line_simple(tri.c, tri.a, red);
}

void Rasterizer::render_triangle_filled(const Triangle &ndc_tri) {
    TriangleDC tri = ndc_to_device(ndc_tri);
    int small_x = std::min(tri.a.position.x, std::min(tri.b.position.x, tri.c.position.x));
    int large_x = std::max(tri.a.position.x, std::max(tri.b.position.x, tri.c.position.x));
    int small_y = std::min(tri.a.position.y, std::min(tri.b.position.y, tri.c.position.y));
    int large_y = std::max(tri.a.position.y, std::max(tri.b.position.y, tri.c.position.y));

    float area = Utils::signed_area(tri);

    std::printf("area = %f\n", area);

    for (int x_pos = small_x; x_pos <= large_x; x_pos++) {
        for (int y_pos = small_y; y_pos <= large_y; y_pos++) {

            VertexDC P = {x_pos, y_pos, 1};

            float alpha = Utils::signed_area({P, tri.b, tri.c}) / area;
            float beta = Utils::signed_area({tri.a, P, tri.c}) / area;
            float gamma = Utils::signed_area({tri.a, tri.b, P}) / area;

            if ( alpha < 0 || beta < 0 || gamma < 0 ) {
                continue;
            }

            VectorDC vector_dc= tri.a.color*alpha + tri.b.color*beta + tri.c.color*gamma;
            TGAColor interpolated_color{};
            interpolated_color.bgra[0] = vector_dc.b;
            interpolated_color.bgra[1] = vector_dc.g;
            interpolated_color.bgra[2] = vector_dc.r;
            interpolated_color.bgra[3] = 255;
            printf("%f %f %f %d %d %d\n", alpha, beta, gamma, interpolated_color.bgra[0], interpolated_color.bgra[1], interpolated_color.bgra[2]);
            frame_buffer.set(x_pos, y_pos, interpolated_color);
        }
    }
}


void Rasterizer::render_line_simple(VertexDC &line_a, VertexDC &line_b, TGAColor color) {
    frame_buffer.set(line_a.position.x, line_a.position.y, color);

    int redraw_count = 0;

    for (float t = 0; t <= 1.0f; t+= 0.02f) {
        int lx = std::round(line_a.position.x + t * (line_b.position.x-line_a.position.x));
        int ly = std::round(line_a.position.y + t * (line_b.position.y-line_a.position.y));

        TGAColor pc = frame_buffer.get(lx, ly);
        if (pc.bgra[0] == 0 && pc.bgra[1] == 0 && pc.bgra[2] == 0) {

        }
        else {
            redraw_count++;
            std::printf("redraw at (%d, %d)\n", lx, ly);
        }
        frame_buffer.set(lx, ly, color);
    }
    std::printf("total_redraw_count = %d\n", redraw_count);

}