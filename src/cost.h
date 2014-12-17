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
#include "config.h"

class Cost
{
public:
    void mean_std(cv::Mat& prob);
    double c2_test(cv::Mat& prob, int i, int j, int classe);
    double c2_potts(cv::Mat& prob, int i, int j, int classe);
    double c1(int i, int j, int classe);
    double compute(cv::Mat& prob, int i, int j, int classe);

private:
    double mean_[5];
    double std_[5];
};

#endif /* defined(__markov__cost__) */
