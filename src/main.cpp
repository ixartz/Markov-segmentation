#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "simulated-annealing.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " input output" << std::endl;
        return EXIT_FAILURE;
    }

    cv::Mat img = cv::imread(argv[1]);
    simulated_annealing(img);

    cv::imwrite(argv[2], img);

    return EXIT_SUCCESS;
}
