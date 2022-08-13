#include <cstdint>
#include <cmath>
#include <algorithm>
#include <opencv2/opencv.hpp>

static cv::Mat currentCubemap;
extern "C" void setCubemap(uchar* rawImageContent, int size) {

    cv::Mat image(1, size, CV_8U, rawImageContent);

    currentCubemap = cv::imdecode(image, cv::IMREAD_COLOR);

    cv::cvtColor(currentCubemap, currentCubemap, cv::COLOR_BGR2RGB);
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


template<typename T>
struct Vec3 {
    T x, y, z;
};

struct Mat3 {
    float m[9];

    Mat3 operator*(Mat3 const& other) const {
        Mat3 res;

        res.m[0] = m[0] * other.m[0] + m[1] * other.m[3] + m[2] * other.m[6];
        res.m[1] = m[0] * other.m[1] + m[1] * other.m[4] + m[2] * other.m[7];
        res.m[2] = m[0] * other.m[2] + m[1] * other.m[5] + m[2] * other.m[8];

        res.m[3] = m[3] * other.m[0] + m[4] * other.m[3] + m[5] * other.m[6];
        res.m[4] = m[3] * other.m[1] + m[4] * other.m[4] + m[5] * other.m[7];
        res.m[5] = m[3] * other.m[2] + m[4] * other.m[5] + m[5] * other.m[8];

        res.m[6] = m[6] * other.m[0] + m[7] * other.m[3] + m[8] * other.m[6];
        res.m[7] = m[6] * other.m[1] + m[7] * other.m[4] + m[8] * other.m[7];
        res.m[8] = m[6] * other.m[2] + m[7] * other.m[5] + m[8] * other.m[8];

        return res;
    }

    template<typename T>
    Vec3<float> operator*(Vec3<T> const& v) const {
        return {
            m[0] * v.x + m[1] * v.y + m[2] * v.z,
            m[3] * v.x + m[4] * v.y + m[5] * v.z,
            m[6] * v.x + m[7] * v.y + m[8] * v.z,
        };
    }
};



extern "C" void viewerQuery(
    std::uint8_t* dst, 
    int dstWidth, int dstHeight, float theta0, float phi0, float hfov
) {

    float const f           = std::tan(hfov / 2);
    const int nCubeSide     = currentCubemap.cols;

    using std::cos;
    using std::sin;


    const Mat3 RotZ{
        cos(theta0), -sin(theta0), 0,
        sin(theta0), cos(theta0) , 0,
        0          , 0           , 1
    };

    const Mat3 RotY{
        cos(phi0) , 0, sin(phi0),
        0         , 1, 0,
        -sin(phi0), 0, cos(phi0)
    };

    const Mat3 projection{
        2 * f / dstWidth, 0               , -f * dstHeight / dstWidth,
        0               , 2 * f / dstWidth, -f,
        0               , 0               , 1
    };

    const Mat3 transform = RotZ * RotY * projection;


    for (int i = 0; i < dstHeight; ++i) {
        for (int j = 0; j < dstWidth; ++j) {

            auto const [Rotx, Roty, Rotz] = transform * Vec3<int>{i, j, 1};


            auto [srci, srcj] = mapsToCube(Rotx, Roty, Rotz);

            const int ii = std::clamp(srci * nCubeSide, 0.0f, nCubeSide - 1.0f);
            const int jj = std::clamp(srcj * nCubeSide, 0.0f, 6 * nCubeSide - 1.0f);

            std::uint8_t*       dstPixelRGBA = &dst[4 * (i * dstWidth + j)];
            std::uint8_t const* srcPixelRGB = &currentCubemap.data[3 * (nCubeSide * jj + ii)];

            std::copy_n(srcPixelRGB, 3, dstPixelRGBA);
            dstPixelRGBA[3] = 255;

        }
    }

}