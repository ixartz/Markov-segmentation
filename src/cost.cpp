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

    double sum;
    double sum2;
    double sum3;
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

                    mean_[k][classe] = sum / (image.cols * image.rows);
                    variance_[k][classe] = (sum2 - (sum*sum)/(image.cols * image.rows))/(image.cols * image.rows-1);
                }

                sum = sum2 = sum3 = 0;
                for (int i= 0; i < image.rows; ++i)
                {
                    for (int j = 0; j < image.cols; ++j)
                    {
                        // L-u covariance
                        sum += (image.at<cv::Vec3b>(i, j)[0]-mean_[0][classe])*(image.at<cv::Vec3b>(i, j)[1]-mean_[1][classe]);
                        // L-v covariance
                        sum2 += (image.at<cv::Vec3b>(i, j)[0]-mean_[0][classe])*(image.at<cv::Vec3b>(i, j)[2]-mean_[2][classe]);
                        // u-v covariance
                        sum3 += (image.at<cv::Vec3b>(i, j)[1]-mean_[1][classe])*(image.at<cv::Vec3b>(i, j)[2]-mean_[2][classe]);
                    }
                }

                covariance_[0][classe] = sum/(image.cols * image.rows);   // L-u covariance
                covariance_[1][classe] = sum2/(image.cols * image.rows);  // L-v covariance
                covariance_[2][classe] = sum3/(image.cols * image.rows);  // u-v covariance
                // Compute elements of inverse covariance matrix
                // element (1,1)
                invcov_[0][classe] = variance_[2][classe] * variance_[1][classe] - covariance_[2][classe]*covariance_[2][classe];

                // elements (1,2) and (2,1)
                invcov_[1][classe] = covariance_[1][classe] * covariance_[2][classe] - variance_[2][classe] * covariance_[0][classe];

                // elements (1,3) and (3,1)
                invcov_[2][classe] = covariance_[0][classe] * covariance_[2][classe] - variance_[1][classe] * covariance_[1][classe];

                // element (2,2)
                invcov_[3][classe] = variance_[2][classe] * variance_[0][classe] - covariance_[1][classe] * covariance_[1][classe];
                
                // elements (2,3) and (3,2)
                invcov_[4][classe] = covariance_[0][classe] * covariance_[1][classe] - variance_[0][classe] * covariance_[2][classe];
                
                // element (3,3)
                invcov_[5][classe] = variance_[1][classe] * variance_[0][classe] - covariance_[0][classe] * covariance_[0][classe];

                denom_[classe] =  variance_[0][classe] * variance_[1][classe] * variance_[2][classe] -
                variance_[2][classe] * covariance_[0][classe] * covariance_[0][classe] -
                variance_[1][classe] * covariance_[1][classe] * covariance_[1][classe] -
                variance_[0][classe] * covariance_[2][classe] * covariance_[2][classe] +
                covariance_[0][classe] * covariance_[1][classe] * covariance_[2][classe] * 2;

                if (denom_[classe] == 0)
                    denom_[classe] = 1e-10;
                for (int k=0; k<3; k++)
                {
                    if (covariance_[k][classe] == 0)
                        covariance_[k][classe] = 1e-10;
                    if (variance_[k][classe] == 0)
                        variance_[k][classe] = 1e-10;
                }

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
    double det;    // determinant of covariance matrix
    double gauss;  // exponential part of Gaussians

    det = variance_[0][classe]*variance_[1][classe]*variance_[2][classe] +
    2 * covariance_[0][classe]*covariance_[1][classe]*covariance_[0][classe] -
    covariance_[0][classe]*covariance_[0][classe]*variance_[2][classe] -
    covariance_[1][classe]*covariance_[1][classe]*variance_[1][classe] -
    covariance_[2][classe]*covariance_[2][classe]*variance_[0][classe];

    gauss = ((img.at<cv::Vec3b>(i, j)[0]-mean_[0][classe]) * invcov_[0][classe] +
             (img.at<cv::Vec3b>(i, j)[1]-mean_[1][classe]) * invcov_[1][classe] +
             (img.at<cv::Vec3b>(i, j)[2]-mean_[2][classe]) * invcov_[2][classe]) * (img.at<cv::Vec3b>(i, j)[0]-mean_[0][classe]) +
    ((img.at<cv::Vec3b>(i, j)[0]-mean_[0][classe]) * invcov_[1][classe] +
     (img.at<cv::Vec3b>(i, j)[1]-mean_[1][classe]) * invcov_[3][classe] +
     (img.at<cv::Vec3b>(i, j)[2]-mean_[2][classe]) * invcov_[4][classe]) * (img.at<cv::Vec3b>(i, j)[1]-mean_[1][classe]) +
    ((img.at<cv::Vec3b>(i, j)[0]-mean_[0][classe]) * invcov_[2][classe] +
     (img.at<cv::Vec3b>(i, j)[1]-mean_[1][classe]) * invcov_[4][classe] +
     (img.at<cv::Vec3b>(i, j)[2]-mean_[2][classe]) * invcov_[5][classe]) * (img.at<cv::Vec3b>(i, j)[2]-mean_[2][classe]);

    if (det==0)
        det = 1e-10;
    else if (det<0)
    {
        det = -det;
        //	  return - log(sqrt(2.0*3.141592653589793*det)) + 0.5 * (double)gauss / (double)denom[label];
    }
    return log(sqrt(2.0*3.141592653589793*det)) + 0.5 * (double)gauss / (double)denom_[classe];
}

double Cost::compute(cv::Mat& img, int i, int j, int classe, cv::Mat& prob)
{
    return c1(img, i, j, classe) + c2_potts(prob, i, j, classe);
}