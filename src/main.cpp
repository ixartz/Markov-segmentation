#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "random.h"
#include "convert.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " image" << std::endl;
        return EXIT_FAILURE;
    }

    cv::Mat img = cv::imread(argv[1]);
    cv::Mat prob(img.size(), CV_8UC1, cv::Scalar(255));
    cv::Mat output(img.size(), CV_8UC3, cv::Scalar(255, 255, 255));

    random_image(prob);
    convert(prob, output);

    cv::imshow("Display image", output);

    cv::waitKey(0);

    return EXIT_SUCCESS;
}
