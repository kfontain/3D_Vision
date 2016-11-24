#ifndef CONVERT_H
#define CONVERT_H

#include "include.h"

cv::Mat qImage2Mat(QImage &img, int format);
cv::Mat qImage2Mat(QImage &img, bool swap);
QImage mat2QImage(cv::Mat &mat, QImage::Format format);
QImage mat2QImage(cv::Mat &mat, bool swap);

#endif // CONVERT_H

