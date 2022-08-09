#pragma once
#include <cstdint>
#include <cmath>
#include <algorithm>
struct RGBA {
    std::uint8_t* data;
    int width, height;

    RGBA(int width, int height) : 
        data{new std::uint8_t[4 * width * height]}, 
        width{width}, height{height} {}
    
    RGBA(RGBA&& other) = delete;
    RGBA(RGBA const& other) = delete;
    RGBA& operator=(RGBA const& other) = delete;
    RGBA& operator=(RGBA&& other) = delete;

    ~RGBA() { delete[] data; }

    std::uint8_t const* getCPixelWrap(int row, int col) const {
        row  = std::clamp(row, 0, height - 1);
        col %= width;
        return &data[4 * (row * width + col)];
    }

    std::uint8_t const* getCPixelRaw(int row, int col) const {
        row = std::clamp(row, 0, height - 1);
        col = std::clamp(col, 0, width - 1);
        return &data[4 * (row * width + col)];
    }
    
    std::uint8_t* getPixel(int row, int col) {
        return &data[4 * (row * width + col)];
    }
};

static const float pi = std::acos(-1);

struct Vec3D {
    float x, y, z;
};


enum Face {
    LEFT,
    RIGHT,
    FRONT,
    BACK,
    TOP,
    BOTTOM
};

template<Face face>
Vec3D mapsToSpherical(float a, float b) {
    if constexpr (face == LEFT)
        return {1, a, b};
    if constexpr (face == FRONT)
        return {a, 1, b};
    if constexpr (face == RIGHT)
        return {-1, a, b};
    if constexpr (face == BACK)
        return {a, -1, b};
    if constexpr (face == TOP)
        return {a, b, 1};
    if constexpr (face == BOTTOM)
        return {a, b, -1};
}




inline std::pair<float, float> mapsToCube(float x, float y, float z) {


    float offset = 1;

    if (std::fabs(x) < std::fabs(y)) {
        std::swap(x, y);
        offset = 3;
    }

    if (std::fabs(x) < std::fabs(z)) {
        std::swap(x, z);
        if (offset < 2) std::swap(y, z);
        offset = 5;
    }

    float const norm = 1.0f / std::fabs(x);

    x *= norm;
    y *= norm;
    z *= norm;
    
    return {
        (1 + y) / 2,
        offset + (z - x) / 2,
    };
}
template<Face face>
void toCubeMapFace(RGBA const& src, RGBA& dst) {
    const int nCubeSide = src.width / 2;
    const int offsetJ = face * nCubeSide;
    for (int j = 0; j < nCubeSide; ++j) {
        for (int i = 0; i < nCubeSide; ++i) {
            auto [x, y, z] = mapsToSpherical<face>(2.0f * i / nCubeSide - 1.0f, 2.0f * j / nCubeSide - 1.0f);
            float theta = std::atan2(y, x);
            theta += theta < 0 ? 2 * pi : 0;
            const float phi = std::acos(z / std::sqrt(x * x + y * y + z * z));

            const float uf = theta * src.width / (2 * pi);
            const float vf = phi * src.height / pi;


            const int u = uf;
            const int v = vf;

            const float mu = uf - u;
            const float nu = vf - v;

            auto A = src.getCPixelWrap(v, u);
            auto B = src.getCPixelWrap(v, u + 1);
            
            auto C = src.getCPixelWrap(v + 1, u);
            auto D = src.getCPixelWrap(v + 1, u + 1);


            auto outPix = dst.getPixel(offsetJ + j, i);
            
            outPix[0] = A[0] * (1 - mu) * (1 - nu) + B[0] * mu * (1 - nu) + C[0] * (1 - mu) * nu + D[0] * mu * nu;
            outPix[1] = A[1] * (1 - mu) * (1 - nu) + B[1] * mu * (1 - nu) + C[1] * (1 - mu) * nu + D[1] * mu * nu;
            outPix[2] = A[2] * (1 - mu) * (1 - nu) + B[2] * mu * (1 - nu) + C[2] * (1 - mu) * nu + D[2] * mu * nu;
            outPix[3] = 255;
        }
    }

}

RGBA* toCubeMap(RGBA const& src) {
    
    int nCubeSide = src.width / 2;
    RGBA* dst = new RGBA(nCubeSide, 6 * nCubeSide);
    toCubeMapFace<LEFT>(src, *dst);
    toCubeMapFace<FRONT>(src, *dst);
    toCubeMapFace<RIGHT>(src, *dst);
    toCubeMapFace<BACK>(src, *dst);
    toCubeMapFace<TOP>(src, *dst);
    toCubeMapFace<BOTTOM>(src, *dst);
    return dst;
}
