#include "../src/Operators/SobelOperator.h"
#include "gtest/gtest.h"

TEST(SobelOperator, test1) {
auto testMat = cv::Mat::ones(3,3, CV_8UC1);
auto sobelOperator = seamcarving::SobelOperator<int, uchar>();
auto point = std::pair<int, int>(1,1);
EXPECT_EQ(sobelOperator.derivate_pixel_x(testMat, point, 0);
EXPECT_EQ(sobelOperator.derivate_pixel_y(testMat, point, 0);
EXPECT_EQ(sobelOperator.get_pixel_magnituted(testMat, point, 0);
}
