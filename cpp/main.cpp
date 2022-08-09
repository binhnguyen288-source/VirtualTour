#include <cstdint>
#include <cmath>
#include <algorithm>

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


extern "C" void viewerQuery(
    std::uint8_t* dst, 
    int dstWidth, int dstHeight, float theta0, float phi0, float hfov,
    std::uint8_t const* cubemap, int nCubeSide
) {

    float const aspectRatio = (float)dstHeight / dstWidth;
    float const f           = std::tan(hfov / 2);
    float const vfov        = 2 * std::atan(aspectRatio * f);
    float const incY        = 2 * f / dstWidth;

    using std::cos;
    using std::sin;

    const float Rot[9] = {
        cos(phi0) * cos(theta0), -sin(theta0), sin(phi0) * cos(theta0),
        cos(phi0) * sin(theta0), cos(theta0), sin(phi0) * sin(theta0),
        -sin(phi0), 0, cos(phi0)
    };


    for (int i = 0; i < dstHeight; ++i) {
        const float XonPlane = aspectRatio * f * (2.0f * i / dstHeight - 1.0f);
        float YonPlane = -f; // initial Yonplane
        constexpr float ZonPlane = 1;

              float Rotx = XonPlane * Rot[0] + YonPlane * Rot[1] + ZonPlane * Rot[2];
              float Roty = XonPlane * Rot[3] + YonPlane * Rot[4] + ZonPlane * Rot[5];
        const float Rotz = XonPlane * Rot[6] + YonPlane * Rot[7] + ZonPlane * Rot[8];

        for (int j = 0; j < dstWidth; ++j) {


            auto [srci, srcj] = mapsToCube(Rotx, Roty, Rotz);

            const int ii = std::clamp(srci * nCubeSide, 0.0f, nCubeSide - 1.0f);
            const int jj = std::clamp(srcj * nCubeSide, 0.0f, 6 * nCubeSide - 1.0f);

            std::copy_n(&cubemap[4 * (nCubeSide * jj + ii)], 4, &dst[4 * (i * dstWidth + j)]);
            
            Rotx += incY * Rot[1];
            Roty += incY * Rot[4];

        }
    }

}