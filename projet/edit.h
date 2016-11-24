#ifndef EDIT_H
#define EDIT_H

#include <stdio.h>
#include <iostream>
#include "include.h"
#include "convert.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

void split(QImage src, cv::Mat* left, cv::Mat* right);
void sobel(cv::Mat src, cv::Mat* dst);
void sift(cv::Mat src, cv::Mat* dst);

#endif // EDIT_H
