#include <iostream>
#include <string>

// OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// 直方图均衡化
void histogram(const unsigned char *src_data,
               unsigned char *dst_data,
               const int img_row,
               const int img_col)
               
{
    const int img_size = img_row * img_col;
    const double img_size_inv = 1.0 / (double)(img_size);

    int pixel_map[256] = {0};
    for (size_t i = 0; i < img_size; ++i)
    {
        unsigned char &pixel_value = dst_data[i];
        pixel_map[pixel_value]++;
    }
    double pixel_ratio[256] = {0.0};
    double sum_ratio = 0.0;
    for (size_t i = 0; i < 256; ++i)
    {
        sum_ratio += (double)pixel_map[i] * img_size_inv;
        pixel_ratio[i] = sum_ratio;
    }

    memset(dst_data, 0, img_size * sizeof(dst_data[0]));
    for (size_t i = 0; i < img_size; ++i)
    {
        int temp_value = src_data[i];
        // int result_value = (int)(pixel_ratio[temp_value] * temp_value);
        int result_value = (int)(pixel_ratio[temp_value] * 255 + 0.5);
        dst_data[i] = result_value;
    }
    
    return;
}

int main()
{
    std::string img_path = "../image/test.jpg";
    cv::Mat img_src = cv::imread(img_path);
    if (img_src.empty())
    {
        std::cout << "img_src is empty.\n";
        return 0;
    }
    cv::Mat img_gray;
    cv::cvtColor(img_src, img_gray, cv::COLOR_BGR2GRAY);
    
    cv::Mat img_opencv = img_gray.clone();
    cv::equalizeHist(img_gray, img_opencv);

    cv::Mat img_me = img_gray.clone();

    const int img_height = img_gray.rows;
    const int img_width = img_gray.cols;
    const unsigned char *src_data = img_gray.data;
    unsigned char *dst_data = img_me.data;

    histogram(src_data, dst_data, img_height, img_width);

	cv::namedWindow("src");
	cv::imshow("src", img_gray);

	cv::namedWindow("opencv");
	cv::imshow("opencv", img_opencv);

	cv::namedWindow("me");
	cv::imshow("me", img_me);

	cv::waitKey(0);

    std::cout << "done\n";
    return 0;
}
