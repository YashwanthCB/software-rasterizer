#pragma once

struct VectorDC {
    union {
        struct {
            int x, y, z;
        };
        struct {
            int r, g, b;
        };
    };
    VectorDC operator*(const float factor) const{
        return {(int)(x*factor), (int)(y*factor), (int)(z*factor)};
    }

    VectorDC operator+(const VectorDC v) const {
        return {x+v.x, y+v.y, z+v.z};
    }

};

struct VertexDC {
    VectorDC position;
    VectorDC color;
};

struct TriangleDC {
    union {
        struct {
            VertexDC a, b, c;
        };
        struct {
            int x1, y1, z1;
            int r1, g1, b1;
            int x2, y2, z2;
            int r2, g2, b2;
            int x3, y3, z3;
            int r3, g3, b3;
        };
    };
};


struct Vector {
    float x, y, z;
};

struct Vertex {
    Vector position;
    Vector color;
};

struct Triangle {
    Vertex a, b, c;
};
