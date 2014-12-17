//
//  cost.cpp
//  markov
//
//  Created by ixi on 16/12/14.
//
//

#include "cost.h"

void Cost::mean_std(cv::Mat& img, cv::Mat& prob)
{
    double sum[5];
    double sum2[5];
    double count[5];

    for (int k = 0; k < 3; ++k)
    {
        for (int l = 0; l < 5; ++l)
        {
            sum[l] = 0.;
            sum2[l] = 0.;
            count[l] = 0.;
        }

        for (int i = 0; i < img.rows; ++i)
        {
            for (int j = 0; j < img.cols; ++j)
            {
                sum[prob.at<uchar>(i, j)] += img.at<cv::Vec3b>(i, j)[k];
                sum2[prob.at<uchar>(i, j)] += img.at<cv::Vec3b>(i, j)[k] *
                                              img.at<cv::Vec3b>(i, j)[k];

                count[prob.at<uchar>(i, j)] += 1;
            }
        }

        for (int l = 0; l < 5; ++l)
        {
            mean_[k][l] = sum[l] / count[l];
            std_[k][l] = sqrt(sum2[l] / count[l] - mean_[k][l] * mean_[k][l]);
        }
    }
}

double Cost::c2_test(cv::Mat& img, int i, int j, int classe)
{
    if (img.at<cv::Vec3b>(i, j) == Config::colors[classe])
        return - Config::beta;
    else
        return Config::beta;
}

double Cost::c2_potts(cv::Mat& img, int i, int j, int classe)
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

double Cost::c1(cv::Mat& img, int i, int j, int classe)
{
    double cost = 0.;

    for (int k = 0; k < 3; ++k)
    {
        cost += pow(img.at<cv::Vec3b>(i, j)[k] - mean_[k][classe], 2) /
                2 * pow(std_[k][classe], 2) +
                log(sqrt(2 * M_PI) * std_[k][classe]);
    }

    return cost;
}

double Cost::compute(cv::Mat& img, int i, int j, int classe)
{
    return c1(img, i, j, classe) - c2_potts(img, i, j, classe);
}