//
//  config.h
//  markov
//
//  Created by ixi on 16/12/14.
//
//

#ifndef __markov__config__
#define __markov__config__

#include <opencv2/opencv.hpp>

class Config
{
public:
    // Fond relief, Fond, Batiment, Eau, Noir
    static cv::Vec3b colors[5];
    static constexpr double beta = 2.5;
};

#endif /* defined(__markov__config__) */
