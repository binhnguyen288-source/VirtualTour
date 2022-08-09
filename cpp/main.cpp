#include "Utils.hpp"
#include <array>



RGBA* curCubeMap = nullptr;
int nCubeSide = 0;

extern "C" void jsCubeMap(std::uint8_t* src_data, std::uint8_t* dst_data, int nWidth, int nHeight) {
    
    RGBA* src = new RGBA(nWidth, nHeight);
    std::copy_n(src_data, 4 * nWidth * nHeight, src->data);
    delete curCubeMap;
    nCubeSide = nWidth / 2;
    curCubeMap = toCubeMap(*src);
    delete src;
    std::copy_n(curCubeMap->data, 4 * nCubeSide * 6 * nCubeSide, dst_data);

    
}

const int nThreads = 4;


extern "C" void viewerQuery(std::uint8_t* dst, int dstWidth, int dstHeight, float theta0, float phi0, float hfov) {

   

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

            const int ii = srci * nCubeSide;
            const int jj = srcj * nCubeSide;

            std::copy_n(curCubeMap->getCPixelRaw(jj, ii), 4, &dst[4 * (i * dstWidth + j)]);
            
            Rotx += incY * Rot[1];
            Roty += incY * Rot[4];

        }
    }





}