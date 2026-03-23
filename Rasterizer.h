//
// Created by yashwanth on 3/15/26.
//

#pragma once

#include "RendererWireframe.h"
#include "TGAImage.h"

#include "Types.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};


class Rasterizer {
public:
    Rasterizer(int width, int height);
    ~Rasterizer();
    TGAImage& get_frame_buffer();

    void clear_frame_buffer();
    void render_wireframe(const std::string& model);
    void render_triangle(TriangleDC& tri);
    void render_triangle_filled(const Triangle& tri);
    void render_line_simple(VertexDC &line_a, VertexDC &line_b, TGAColor color=red);

private:

    TriangleDC ndc_to_device(const Triangle& tri) {
        TriangleDC tr;

        Vector pos= tri.a.position;
        Vector color= tri.a.color;

        tr.a.position.x = pos.x * width;
        tr.a.position.y = pos.y * height;
        tr.a.color.x = color.x * 255;
        tr.a.color.y = color.y * 255;
        tr.a.color.z = color.z * 255;

        pos = tri.b.position;
        color= tri.b.color;

        tr.b.position.x = pos.x * width;
        tr.b.position.y = pos.y * height;
        tr.b.color.x = color.x * 255;
        tr.b.color.y = color.y * 255;
        tr.b.color.z = color.z * 255;

        pos = tri.c.position;
        color= tri.c.color;

        tr.c.position.x = pos.x * width;
        tr.c.position.y = pos.y * height;
        tr.c.color.x = color.x * 255;
        tr.c.color.y = color.y * 255;
        tr.c.color.z = color.z * 255;

        return tr;
    }

private:
    int width;
    int height;
    TGAImage frame_buffer;
    RendererWireframe renderer_wireframe;
};

