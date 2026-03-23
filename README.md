<img width="1112" height="762" alt="image" src="https://github.com/user-attachments/assets/c1b97a54-0003-4ca3-8690-ddb7ce0a9cd2" />
Built a custom CPU-based rasterizer from scratch, with support for color interpolation along vertices.

The main formula for calculating the pixels that belog to the triangle is given by:
<br/>
```cpp
static float signed_area(const TriangleDC& tri){
    return 0.5f * ( tri.x1*( tri.y2 - tri.y3 ) + tri.x2*( tri.y3 - tri.y1 ) + tri.x3*( tri.y1 - tri.y2 ) );
}
```

For every point P, we calculate the singed area of a triangle that is formed by two of the triangle points and the point P, like: 
```cpp
area(A, B, P)
area(P, B, C)
area(A, P, C)
```

if the sum of the area equals to the `area(A, B, C)` then we confirm that the point P belongs to the traingle and we light it up using interpolation values.

In modern GPUs, these simple operations are done in parallel thus achieving high throughput.

Working on this mini-project gave me a lot of insights on how GPUs work.
