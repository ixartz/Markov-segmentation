//
//  cost.cpp
//  markov
//
//  Created by ixi on 16/12/14.
//
//

#include "cost.h"

Cost::Cost()
{
    for (int i = 0; i < NB_COLORS; ++i)
    {
        covariance_[i].zeros();
        inv_covariance_[i].zeros();
    }
}

void Cost::compute_mean_variance_(cv::Mat& image, int classe)
{
    double sum;
    double sum2;

    for (int k = 0; k < 3; ++k)
    {
        sum = 0;
        sum2 = 0;

        for (int i= 0; i < image.rows; ++i)
        {
            for (int j = 0; j < image.cols; ++j)
            {
                sum += image.at<cv::Vec3b>(i, j)[k];
                sum2 += image.at<cv::Vec3b>(i, j)[k] *
                        image.at<cv::Vec3b>(i, j)[k];
            }
        }

        mean_[classe](k) = sum / (image.cols * image.rows);
        covariance_[classe](k, k) = (sum2 - (sum * sum) / (image.cols * image.rows))
                                    / (image.cols * image.rows);
    }
}

void Cost::compute_covariance_(cv::Mat& image, int classe)
{
    double sum[3] = { 0, 0, 0};

    for (int i= 0; i < image.rows; ++i)
    {
        for (int j = 0; j < image.cols; ++j)
        {
            sum[0] += (image.at<cv::Vec3b>(i, j)[0] - mean_[classe](0)) *
                      (image.at<cv::Vec3b>(i, j)[1] - mean_[classe](1));
            sum[1] += (image.at<cv::Vec3b>(i, j)[0] - mean_[classe](0)) *
                      (image.at<cv::Vec3b>(i, j)[2] - mean_[classe](2));
            sum[2] += (image.at<cv::Vec3b>(i, j)[1] - mean_[classe](1)) *
                      (image.at<cv::Vec3b>(i, j)[2] - mean_[classe](2));
        }
    }

    covariance_[classe](0, 1) = sum[0] / (image.cols * image.rows);
    covariance_[classe](0, 2) = sum[1] / (image.cols * image.rows);
    covariance_[classe](1, 2) = sum[2] / (image.cols * image.rows);

    covariance_[classe](1, 0) = covariance_[classe](0, 1);
    covariance_[classe](2, 0) = covariance_[classe](0, 2);
    covariance_[classe](2, 1) = covariance_[classe](1, 2);
}

void Cost::init()
{
    cv::Mat image;
    boost::filesystem::directory_iterator end;

    std::string input_dir(std::string(PROJECT_SRC_DIR) + "/classe");
    int classe = 0;

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

                compute_mean_variance_(image, classe);
                compute_covariance_(image, classe);

                inv_covariance_[classe] = arma::inv(covariance_[classe]);

                ++classe;
            }
        }
    }
}

double Cost::c2_test(cv::Mat& prob, int i, int j, int classe)
{
    if (prob.at<uchar>(i, j) == classe)
        return - Config::beta;
    else
        return Config::beta;
}

double Cost::c2_potts(cv::Mat& prob, int i, int j, int classe)
{
    double cost = 0.;

    if (i > 0)
        cost += c2_test(prob, i - 1, j, classe);

    if (i < prob.rows - 1)
        cost += c2_test(prob, i + 1, j, classe);

    if (j > 0)
        cost += c2_test(prob, i, j - 1, classe);

    if (j < prob.cols - 1)
        cost += c2_test(prob, i, j + 1, classe);

    return cost;
}

double Cost::c1(cv::Mat& img, int i, int j, int classe)
{
    arma::vec3 x;
    x(0) = img.at<cv::Vec3b>(i, j)[0];
    x(1) = img.at<cv::Vec3b>(i, j)[1];
    x(2) = img.at<cv::Vec3b>(i, j)[2];

    arma::vec3 m = (x - mean_[classe]);
    arma::mat out = trans(m) * inv_covariance_[classe] * m;

    return log(sqrt(2.0 * M_PI * arma::det(covariance_[classe]))) +
           0.5 * out[0];
}

double Cost::compute(cv::Mat& img, int i, int j, int classe, cv::Mat& prob)
{
    return c1(img, i, j, classe) + c2_potts(prob, i, j, classe);
}