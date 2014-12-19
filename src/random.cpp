//
//  random.cpp
//  markov
//
//  Created by ixi on 05/12/14.
//
//

#include "random.h"

void random_image(cv::Mat& img)
{
    std::mt19937 eng_(time(NULL));
    std::uniform_int_distribution<uint32_t> uint_dist_;

    for (int i = 0; i < img.rows; ++i)
    {
        for (int j = 0; j < img.cols; ++j)
        {
            img.at<uchar>(i, j) = uint_dist_(eng_) % 7;
        }
    }

}