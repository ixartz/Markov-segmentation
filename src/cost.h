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
#include <armadillo>
#include <cmath>
#include <boost/filesystem.hpp>
#include "Settings.h"
#include "config.h"

class Cost
{
public:
    Cost();
    void init();
    double c2_test(cv::Mat& prob, int i, int j, int classe);
    double c2_potts(cv::Mat& prob, int i, int j, int classe);
    double c1(cv::Mat& img, int i, int j, int classe);
    double compute(cv::Mat& img, int i, int j, int classe, cv::Mat& prob);

private:
    void compute_mean_variance_(cv::Mat& image, int classe);
    void compute_covariance_(cv::Mat& image, int classe);

private:
    arma::vec3 mean_[NB_COLORS];
    arma::mat33 covariance_[NB_COLORS];
    arma::mat33 inv_covariance_[NB_COLORS];
};

#endif /* defined(__markov__cost__) */
