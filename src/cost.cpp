//
//  cost.cpp
//  markov
//
//  Created by ixi on 16/12/14.
//
//

#include "cost.h"

void Cost::mean_std()
{
    cv::Mat image;
    boost::filesystem::directory_iterator end;

    std::string input_dir(std::string(PROJECT_SRC_DIR) + "/classe");

    if (boost::filesystem::exists(input_dir)
        && boost::filesystem::is_directory(input_dir))
    {
        for (boost::filesystem::directory_iterator it(input_dir);
             it != end; ++it)
        {
            if (it->path().extension() == ".png")
            {
                std::cout << it->path().filename() << std::endl;
                image = cv::imread(it->path().string(), CV_LOAD_IMAGE_COLOR);
            }
        }
    }
}

double Cost::c2_test(cv::Mat& img, int i, int j, int classe)
{
    if (img.at<cv::Vec3b>(i, j) == Config::colors[classe])
        return - Config::beta;
    else
        return Config::beta;
}

double Cost::c2_potts(cv::Mat& img, int i, int j, int classe)
{
    double cost = 0.;

    if (i > 0)
        cost += c2_test(img, i - 1, j, classe);

    if (i < img.rows - 1)
        cost += c2_test(img, i + 1, j, classe);

    if (j > 0)
        cost += c2_test(img, i, j - 1, classe);

    if (j < img.cols - 1)
        cost += c2_test(img, i, j + 1, classe);

    return cost;
}

double Cost::c1(cv::Mat& img, int i, int j, int classe)
{
    double cost = 0.;

    for (int k = 0; k < 3; ++k)
    {
        cost += pow(img.at<cv::Vec3b>(i, j)[k] - mean_[k][classe], 2) /
                2 * pow(std_[k][classe], 2) +
                log(sqrt(2 * M_PI) * std_[k][classe]);
    }

    return cost;
}

double Cost::compute(cv::Mat& img, int i, int j, int classe)
{
    return c1(img, i, j, classe) - c2_potts(img, i, j, classe);
}