#include <iostream>
#include <string>

// OpenCV
#include <opencv2/opencv.hpp>

int main()
{
    std::string img_path = "../image/suns.jpg";
    cv::Mat img_src = cv::imread(img_path);
    if (img_src.empty())
    {
        std::cout << "img_src is empty.\n";
        return 0;
    }

	cv::namedWindow("image");
	cv::imshow("image", img_src);
	cv::waitKey(0);

    std::cout << "done\n";
    return 0;
}
