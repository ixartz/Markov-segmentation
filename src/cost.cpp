//
//  cost.cpp
//  markov
//
//  Created by ixi on 16/12/14.
//
//

#include "cost.h"

void Cost::mean_std(cv::Mat& prob)
{
    double count[5];

    for (int k = 0; k < 5; ++k)
        count[k] = 0.;

    for (int i = 0; i < prob.rows; ++i)
    {
        for (int j = 0; j < prob.cols; ++j)
        {
            count[prob.at<uchar>(i, j)] += 1;
        }
    }

    for (int k = 0; k < 5; ++k)
    {
        mean_[k] = count[k] / (prob.rows * prob.cols);
        std_[k] = sqrt(count[k] / (prob.rows * prob.cols) -
                       mean_[k] * mean_[k]);
    }
}

double Cost::c2_test(cv::Mat& prob, int i, int j, int classe)
{
    if (prob.at<uchar>(i, j) == classe)
        return - Config::beta;
    else
        return Config::beta;
}

double Cost::c2_potts(cv::Mat& prob, int i, int j, int classe)
{
    double cost = 0.;

    if (i > 0)
        cost += c2_test(prob, i - 1, j, classe);

    if (i < prob.rows - 1)
        cost += c2_test(prob, i + 1, j, classe);

    if (j > 0)
        cost += c2_test(prob, i, j - 1, classe);

    if (j < prob.cols - 1)
        cost += c2_test(prob, i, j + 1, classe);

    return cost;
}

double Cost::c1(int i, int j, int classe)
{

}

double Cost::compute(cv::Mat& prob, int i, int j, int classe)
{
    return c1(i, j, classe) + c2_potts(prob, i, j, classe);
}