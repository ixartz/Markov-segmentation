//
//  simulated-annealing.cpp
//  markov
//
//  Created by ixi on 15/12/14.
//
//

#include "simulated-annealing.h"

void simulated_annealing(cv::Mat& img)
{
    std::mt19937 eng(time(NULL));
    std::uniform_int_distribution<uint32_t> uint_dist;
    std::uniform_real_distribution<double> ureal_dist;

    double delta_global_enery;
    double delta;
    double temperature = 10000;
    int new_classe;
    Cost c;

    cv::Mat prob(img.size(), CV_8UC1, cv::Scalar(255));
    cv::Mat output(img.size(), CV_8UC3, cv::Scalar(255, 255, 255));

    random_image(prob);
    convert(prob, output);

    cv::imshow("Display image", output);
    cv::waitKey(0);

    c.mean_std();

    /*
    do
    {
        cv::imshow("Display image", output);
        cv::waitKey(0);

        delta_global_enery = 0.;
        c.mean_std(output, prob);

        // k avoids the influence by neighborhood
        for (int k = 0; k < 2; ++k)
        {
            for (int i = 0; i < prob.rows; ++i)
            {
                for (int j = k; j < prob.cols; j += 2)
                {
                    new_classe = uint_dist(eng) % 5;
                    delta = c.compute(output, i, j, new_classe) -
                    c.compute(output, i, j, prob.at<uchar>(i, j));

                    if (delta <= 0. ||
                        exp(-delta / temperature) >= ureal_dist(eng))
                    {
                        delta_global_enery += fabs(delta);
                        prob.at<uchar>(i, j) = new_classe;
                        convert(prob, output);
                    }
                }
            }
        }

        temperature *= 0.95;
    }
    while (delta_global_enery > 10);
    */
}