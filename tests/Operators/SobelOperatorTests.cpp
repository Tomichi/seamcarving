#include "../src/Operators/SobelOperator.h"
#include "gtest/gtest.h"

// Derivate constant function
TEST(sobelOperator, test1) {
    auto testMat = cv::Mat(3, 3, CV_8UC1);
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            testMat.at<uchar>(y, x) = 1;
        }
    }
    auto sobelOperator = seamcarving::SobelOperator<int, uchar>();
    auto point = std::pair<int, int>(1, 1);
    int derivate_x = sobelOperator.derivateByX(testMat, point);
    int derivate_y = sobelOperator.derivateByY(testMat, point);
    int magnitude = sobelOperator.getPixelMagnitute(testMat, point);
    EXPECT_EQ(derivate_x, 0);
    EXPECT_EQ(derivate_y, 0);
    EXPECT_EQ(magnitude, 0);
}
