#include <cmath>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "Operators/SobelOperator.h"

template <typename T>
T getMin(T a, T b) {
    return std::min(a, b);
}

template <typename T>
T getMin(T a) {
    return a;
}

template <typename T, typename... Args>
T getMin(T a, Args... args) {
    return std::min(a, getMin(args...));
}

int main() {
    std::string image_path = "../images/corsica01.jpg";
    cv::Mat input_image = cv::imread(image_path, cv::IMREAD_COLOR);
    cv::Mat bw_input_image, energy_mat, cumulative_mat;
    uint16_t INPUT_COLS = input_image.cols, INPUT_ROWS = input_image.rows;
    int previous_min_col = 0;
    // # compute energy map via Sobel operator
    for (uint16_t seam = 0; seam < 200; ++seam) {
        energy_mat = cv::Mat::zeros(input_image.size(), CV_8UC1);
        cumulative_mat = cv::Mat::zeros(input_image.size(), CV_16UC1);
        cv::cvtColor(input_image, bw_input_image, cv::COLOR_BGR2GRAY);
        auto sobelOperator = seamcarving::SobelOperator<int, uchar>();
        for (int row = 1; row < INPUT_ROWS - 1; ++row) {
            for (int col = 1; col < INPUT_COLS - 1; ++col) {
                energy_mat.at<uchar>(row, col) = sobelOperator.getPixelMagnitute(bw_input_image, {row, col});
            }
        }
        cv::normalize(energy_mat, energy_mat, 0, 255, cv::NORM_MINMAX, CV_8UC1);

        // # now compute cumulative mat
        for (int col = 1; col < INPUT_COLS - 1; col++) {
            cumulative_mat.at<u_int16_t>(INPUT_ROWS - 2, col) =
                static_cast<uint16_t>(energy_mat.at<uchar>(INPUT_ROWS - 2, col));
        }

        for (int row = INPUT_ROWS - 2; row > 0; --row) {
            for (int col = 2; col < INPUT_COLS - 2; ++col) {
                cumulative_mat.at<u_int16_t>(row, col) =
                    static_cast<uint16_t>(energy_mat.at<uchar>(row, col))
                    + getMin(cumulative_mat.at<uint16_t>(row + 1, col - 1),
                        cumulative_mat.at<uint16_t>(row + 1, col),
                           cumulative_mat.at<uint16_t>(row + 1, col + 1));
            }
            // edge case
            cumulative_mat.at<u_int16_t>(row, 1) = cumulative_mat.at<u_int16_t>(row, 2);
            cumulative_mat.at<u_int16_t>(row, INPUT_COLS - 2) = cumulative_mat.at<u_int16_t>(row, INPUT_COLS - 3);
        }

        // cv::normalize(cumulative_mat, cumulative_mat, 0, 255,cv::NORM_MINMAX, CV_8UC1);
        // cv::imshow("Cumulative image", cumulative_mat);
        // cv::waitKey(10);
        int col_index = 1;
        int minimal_value = cumulative_mat.at<uint16_t>(1, col_index);
        for (int col = col_index + 1; col < INPUT_COLS - 1; ++col) {
            int current_value = cumulative_mat.at<uint16_t>(1, col);
            if (col != previous_min_col && col != previous_min_col + 1 && col != previous_min_col - 1 &&
                minimal_value > current_value) {
                col_index = col;
                minimal_value = current_value;
            }
        }

        previous_min_col = col_index;
        input_image.at<cv::Vec3b>(0, INPUT_COLS - 1) = {0, 0, 0};
        input_image.at<cv::Vec3b>(INPUT_ROWS - 1, INPUT_COLS - 1) = {0, 0, 0};
        for (int row = 1; row < INPUT_ROWS - 2; ++row) {
            input_image.at<cv::Vec3b>(row, INPUT_COLS - 1) = {0, 0, 0};
            for (int col = col_index; col < INPUT_COLS - 1; col++) {
                input_image.at<cv::Vec3b>(row, col) = input_image.at<cv::Vec3b>(row, col + 1);
            }

            minimal_value = cumulative_mat.at<uint16_t>(row + 1, col_index);
            if (col_index != INPUT_COLS - 1 && minimal_value > cumulative_mat.at<uint16_t>(row + 1, col_index + 1)) {
                minimal_value = cumulative_mat.at<uint16_t>(row + 1, col_index + 1);
                col_index = col_index + 1;
            }

            if (col_index != 1 && minimal_value > cumulative_mat.at<uint16_t>(row + 1, col_index - 1)) {
                col_index -= 1;
            }
        }
        INPUT_COLS -= 1;
    }

    cv::imshow("Small", input_image);
    cv::waitKey(0);
    return 0;
}
