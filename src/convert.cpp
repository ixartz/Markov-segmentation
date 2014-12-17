//
//  convert.cpp
//  markov
//
//  Created by ixi on 17/12/14.
//
//

#include "convert.h"

void convert(cv::Mat& prob, cv::Mat& output)
{
    for (int i = 0; i < prob.rows; ++i)
    {
        for (int j = 0; j < prob.cols; ++j)
        {
            output.at<cv::Vec3b>(i, j) = Config::colors[prob.at<uchar>(i, j)];
        }
    }
}