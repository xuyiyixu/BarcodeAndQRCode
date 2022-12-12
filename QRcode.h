//
// Created by xw on 2022-11-25.
//

#ifndef UNTITLED_QRCODE_H
#define UNTITLED_QRCODE_H

#include <opencv2/wechat_qrcode.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include<opencv2/imgproc.hpp>
#include<unistd.h>
#include <array>
#include <numeric>
#include<string>

std::array<uint8_t ,7>QRcodeDetectAndDecode(const cv::Mat &input_image);


#endif //UNTITLED_QRCODE_H
