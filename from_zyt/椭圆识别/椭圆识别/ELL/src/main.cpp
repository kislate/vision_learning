#include <iostream>
 
#include "opencv2/imgproc.hpp"
#include "opencv2/ximgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;
using namespace cv::ximgproc;

//设定膨胀与闭操作的元素大小
const int dilate_element_len=3,close_element_len=7;
cv::Mat element_clo = getStructuringElement(cv::MORPH_RECT, cv::Size(close_element_len, close_element_len));
cv::Mat element_dil = getStructuringElement(cv::MORPH_RECT, cv::Size(dilate_element_len, dilate_element_len));
//设定Canny边缘检测的阈值
const int canny_thresh_min=100,canny_thresh_max=100;
int main(int argc, char** argv)
{
    //Mat src = imread("/mnt/e/aaa/el6.png");
    Mat src = imread("/mnt/e/aaa/el4.png"),image,canny;
    vector<Vec6d> ellipses;

 
    if( src.empty() )
    {
        return -1;
    }
    resize(src, src, Size(640, 480));
    cvtColor(src, image, COLOR_BGR2GRAY);
    cv::medianBlur(image, image, 7);
    //GaussianBlur(image, image, Size(3,3), 0);
    //新加入canny边缘检测
    cv::Canny(image, canny, canny_thresh_min, canny_thresh_max);
    imshow("canny",canny);
    //cv::dilate(canny,canny,element_dil);
    cv::Mat output_ellipses;
    output_ellipses.create(0, 6, 6);  // 空矩阵，类型设为CV_32FC6

    try {
        // 调用findEllipses
        cv::ximgproc::findEllipses(canny, output_ellipses, 1.0, 0.4, 2.0);

        // 输出检测到的椭圆
        std::cout << "Detected ellipses: " << std::endl;
        for (int i = 0; i < output_ellipses.rows; i++) {
            cv::Vec6f ellipse_1 = output_ellipses.at<cv::Vec6f>(i);
            std::cout << "Ellipse " << i + 1 << ": ["
                      << ellipse_1[0] << ", " << ellipse_1[1] << ", " << ellipse_1[2] << ", "
                      << ellipse_1[3] << ", " << ellipse_1[4] << ", " << ellipse_1[5] << "]" << std::endl;
            cv::ellipse(src,
                        cv::Point(cvRound(ellipse_1[0]), cvRound(ellipse_1[1])),
                        cv::Size(cvRound(ellipse_1[2]), cvRound(ellipse_1[3])),
                        (ellipse_1[5]*180/3.1415926535), 0, 360,
                        cv::Scalar(0, 0, 255), 2);
        }
        
    } catch (const cv::Exception &e) {
        std::cerr << "OpenCV Error: " << e.what() << std::endl;
        return -1;
    }
    //cv::dilate(image,image,element_dil);
    //cv::morphologyEx(image,image,cv::MORPH_CLOSE,element_clo);

    //waitKey();
    
    imshow("EdgeDrawing result", src);
    waitKey();
    return 0;
}

