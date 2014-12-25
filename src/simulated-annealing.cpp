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
    double temperature = Config::initial_temperature;
    int new_classe;
    Cost c;

    cv::Mat prob(img.size(), CV_8UC1, cv::Scalar(255));
    cv::Mat output(img.size(), CV_8UC3, cv::Scalar(255, 255, 255));

    cv::cvtColor(img, img, CV_RGB2Luv);

    random_image(prob);
    convert(prob, output);

    c.init();

    do
    {
        //cv::imshow("Display image", output);
        //cv::waitKey(0);

        delta_global_enery = 0.;

        // k avoids the influence by neighborhood
        for (int k = 0; k < 2; ++k)
        {
            for (int i = 0; i < prob.rows; ++i)
            {
                for (int j = k; j < prob.cols; j += 2)
                {
                    new_classe = uint_dist(eng) % NB_COLORS;
                    delta = c.compute(img, i, j, new_classe, prob) -
                            c.compute(img, i, j, prob.at<uchar>(i, j), prob);

                    if (delta <= 0. ||
                        exp(-delta / temperature) >= ureal_dist(eng))
                    {
                        delta_global_enery += fabs(delta);
                        prob.at<uchar>(i, j) = new_classe;
                    }
                }
            }
        }

        convert(prob, output);
        temperature *= Config::temperature_decrease;
    }
    while (delta_global_enery > Config::min_change);

    img = output;
}