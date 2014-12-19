//
//  cost.h
//  markov
//
//  Created by ixi on 16/12/14.
//
//

#ifndef __markov__cost__
#define __markov__cost__

#include <opencv2/opencv.hpp>
#include <cmath>
#include <boost/filesystem.hpp>
#include "Settings.h"
#include "config.h"

class Cost
{
public:
    void mean_std();
    double c2_test(cv::Mat& prob, int i, int j, int classe);
    double c2_potts(cv::Mat& prob, int i, int j, int classe);
    double c1(cv::Mat& img, int i, int j, int classe);
    double compute(cv::Mat& img, int i, int j, int classe, cv::Mat& prob);

private:
    double mean_[3][7];
    double variance_[3][7];
    double covariance_[3][7];
    double invcov_[6][7];
    double denom_[7];
};

#endif /* defined(__markov__cost__) */
