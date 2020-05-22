#pragma once

#include <cmath>
#include <opencv2/opencv.hpp>
#include <utility>

namespace seamcarving {
    template <typename T, typename R>
    class SobelOperator {
       public:
        SobelOperator() = default;

        T derivateByX(cv::Mat& src, std::pair<T, T> pixel);
        T derivateByY(cv::Mat& src, std::pair<T, T> pixel);
        T getPixelMagnitute(cv::Mat& src, std::pair<T, T> pixel);
        // todo compute direction
    };

    template <typename T, typename R>
    T seamcarving::SobelOperator<T, R>::derivateByX(cv::Mat& src, std::pair<T, T> pixel) {
        auto x_coordinate = pixel.second, y_coordinate = pixel.first;
        T result = 0;
        result += src.at<R>(y_coordinate - 1, x_coordinate - 1);
        result += 2 * src.at<R>(y_coordinate - 1, x_coordinate);
        result += src.at<R>(y_coordinate - 1, x_coordinate + 1);
        result -= src.at<R>(y_coordinate + 1, x_coordinate - 1);
        result -= 2 * src.at<R>(y_coordinate + 1, x_coordinate);
        result -= src.at<R>(y_coordinate + 1, x_coordinate + 1);
        return result;
    }

    template <typename T, typename R>
    T SobelOperator<T, R>::derivateByY(cv::Mat& src, std::pair<T, T> pixel) {
        auto x_coordinate = pixel.second, y_coordinate = pixel.first;
        T result = 0;
        result += src.at<R>(y_coordinate - 1, x_coordinate - 1);
        result += 2 * src.at<R>(y_coordinate, x_coordinate - 1);
        result += src.at<R>(y_coordinate + 1, x_coordinate - 1);
        result -= src.at<R>(y_coordinate - 1, x_coordinate + 1);
        result -= 2 * src.at<R>(y_coordinate, x_coordinate + 1);
        result -= src.at<R>(y_coordinate + 1, x_coordinate + 1);
        return result;
    }
    template <typename T, typename R>
    T SobelOperator<T, R>::getPixelMagnitute(cv::Mat& src, std::pair<T, T> pixel) {
        auto derivate_x = derivateByX(src, pixel), derivate_y = derivateByY(src, pixel);
        return static_cast<T>(sqrt(derivate_x * derivate_x + derivate_y + derivate_y));
    }
}  // namespace seamcarving
