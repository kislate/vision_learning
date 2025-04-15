### `Mat` 类型的构造函数:
`type`:
- CV_8UC1: 8位无符号单通道;
- CV_8UC3: 8位无符号三通道;
- CV_32FC1: 32位浮点数单通道;
```cpp
    Mat::Mat() // 无参数构造:
    Mat::Mat(int rows, int cols, int type)
    Mat::Mat(Size size, int type)// 大小为size
    Mat::Mat(int rows, int cols, int type, const Scalar& s)// 初始化所有元素的值;
    Mat::Mat(Size size, int type, const Scalar& s)

    Mat::Mat(const Mat& m) //将m赋值给创建的的对象
    // 注意: 数据不会复制, 共用图像数据;
    Mat::Mat(int rows, int cols, int type, void*data, size_t step=AUTO_STEP)// 直接使用data所指的内存, 图像的行步长👉step指定
    Mat::Mat(Size size, int type, void* data, size_t step = AUTO_STEP)// 同上;
    Mat::Mat(const Mat& m, const Rect& roi)// 创建图像为m的一部分, 具体范围由roi指定, 不会进行复制操作, 新图像与m共用图像数据;
    Mat::Mat(const Mat&m, const Range& rowRange, const Range& colRange)
    // 后者指定范围
```

`Opencv`中有模板类`Vec`, 预定义了一些小向量, 可以用来矩阵元素的表达
### 像素值读写:
- `at` 函数:
```cpp
    uchar value = grayim.at<uchar>(i, j);// 读出
    grayim.at<uchar>(i, j) = 128;// 赋值
```

#### 下面是一个对图像进行遍历(创建了两个图像, 分别是单通道的grayim和3个通道的colorim, 然后赋值)
```cpp
#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(void)
{
    Mat grayim(600, 800, CV_8UC1);
    Mat colorim(600, 800, CV_8UC3);

    // 遍历所有像素, 并设置像素值
    for(int i = 0; i < grayim.rows; ++i)
        for(int j = 0; j < grayim.cols; ++j)
            grayim.at<uchar>(i, j) = (i+j) % 255;
    // 遍历所有像素, 并设置像素值
    for(int i = 0; i <colorim.rows; ++i)
        for(int j = 0; j < colorim.cols; ++j)
        {
            Vec3b pixel;
            pixel[0] = i % 255; // Blue;
            pixel[1] = j % 255; // Green;
            Pixel[2] = 0; // Red;
            colorim.at<Vec3b>(i, j) = pixel;
        }
    // 显示结果
    imshow("grayim", grayim);
    imshow("colorim", colorim);
}
```
