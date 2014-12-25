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

#define NB_COLORS 7

class Config
{
public:
    // Eau, fond, fond relief, bat1, bat2, rouge vif, zone
    static cv::Vec3b colors[NB_COLORS];
    static constexpr double beta = 0.2;
    static constexpr double initial_temperature = 4.0;
    static constexpr double temperature_decrease = 0.95;
    static constexpr double min_change = 2.5;
};

#endif /* defined(__markov__config__) */
