//
//  cost.cpp
//  markov
//
//  Created by ixi on 16/12/14.
//
//

#include "cost.h"

float c2_test(cv::Mat& img, int i, int j, cv::Vec3b& classe)
{
    if (img.at<cv::Vec3b>(i, j) == classe)
        return - Config::beta;
    else
        return Config::beta;
}

float c2_potts(cv::Mat& img, int i, int j, cv::Vec3b& classe)
{
    double cost = 0.;

    if (i > 0)
        cost += c2_test(img, i - 1, j, classe);

    if (i < img.rows - 1)
        cost += c2_test(img, i + 1, j, classe);

    if (j > 0)
        cost += c2_test(img, i, j - 1, classe);

    if (j < img.cols - 1)
        cost += c2_test(img, i, j + 1, classe);

    return cost;
}

float c1(int i, int j, cv::Vec3b& classe)
{

}

float cost(cv::Mat& img, int i, int j, cv::Vec3b& classe)
{
    return c1(i, j, classe) - c2_potts(img, i, j, classe);
}