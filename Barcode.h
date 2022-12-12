//
// Created by xw on 2022-11-25.
//

#ifndef UNTITLED_BARCODE_H
#define UNTITLED_BARCODE_H


#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include<opencv2/barcode.hpp>
#include<opencv2/imgproc.hpp>
#include <string>
#include <numeric>
#include<vector>
#include "zbar.h"


std::array<uint8_t,24>BarCodeDetectAndDecode(const cv::Mat &input_image);

#endif //UNTITLED_BARCODE_H
