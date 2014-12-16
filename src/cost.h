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

float c2_test(cv::Mat& img, int i, int j, cv::Vec3b& classe);
float c2_potts(cv::Mat& img, int i, int j, cv::Vec3b& classe);
float c1(int i, int j, cv::Vec3b& classe);
float cost(cv::Mat& img, int i, int j, cv::Vec3b& classe);

#endif /* defined(__markov__cost__) */
