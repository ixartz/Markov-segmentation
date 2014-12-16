//
//  simulated-annealing.cpp
//  markov
//
//  Created by ixi on 15/12/14.
//
//

#include "simulated-annealing.h"

void simulated_annealing(cv::Mat img)
{
    std::mt19937 eng_(time(NULL));
    std::uniform_real_distribution<uint32_t> ureal_dist_;

    double delta_global_enery;
    double temperature = 10000;

    do
    {
        delta_global_enery = 0.;

        for (int i = 0; i < img.rows; ++i)
        {
            for (int j = 0; j < img.cols; ++j)
            {
                /*
                if (delta <= 0. ||
                    exp(-delta / temperature) > ureal_dist_(eng_))
                {

                }
                */
            }
        }

        temperature *= 0.95;
    }
    while (delta_global_enery > 10);
}