//
//  random.cpp
//  markov
//
//  Created by ixi on 05/12/14.
//
//

#include "random.h"

void random_image(cv::Mat img)
{
    std::mt19937 eng_(time(NULL));
    std::uniform_int_distribution<uint32_t> uint_dist_;

    // Fond relief, Fond, Batiment, Eau, Noir
    cv::Vec3b colors[5] = { cv::Vec3b(134, 103, 67),
                            cv::Vec3b(223, 174, 111),
                            cv::Vec3b(201, 69, 54),
                            cv::Vec3b(0, 0, 255),
                            cv::Vec3b(0, 0, 0) };

    for (int i = 0; i < img.rows; ++i)
    {
        for (int j = 0; j < img.cols; ++j)
        {
            img.at<cv::Vec3b>(i, j) = colors[uint_dist_(eng_) % 5];
        }
    }

}