#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " image" << std::endl;
        return EXIT_FAILURE;
    }

    cv::Mat img = cv::imread(argv[1]);

    cv::imshow("Display image", img);

    return EXIT_SUCCESS;
}
