//
// Created by xw on 2022-11-25.
//
#include"QRcode.h"

std::array<uint8_t,7> a;
std::array<uint8_t ,7>QRcodeDetectAndDecode(const cv::Mat &input_image) {
    //加载图片解码

    cv::Ptr<cv::wechat_qrcode::WeChatQRCode> detector;
    std::string detect_prototxt = "../detect.prototxt";
    std::string detect_caffe_model = "../detect.caffemodel";
    std::string sr_prototxt = "../sr.prototxt";
    std::string sr_caffe_model = "../sr.caffemodel";
    //pay attention to the path above

    cv::Mat input = input_image;
    try {
        detector =cv:: makePtr<cv::wechat_qrcode::WeChatQRCode>(detect_prototxt, detect_caffe_model,
                                                        sr_prototxt, sr_caffe_model);
    }
    catch (const std::exception &e) {
        std::cout <<
             "\n---------------------------------------------------------------\n"
             "Failed to initialize WeChatQRCode.\n"
             "Please, download 'detector.*' and 'sr.*' from\n"
             "https://github.com/WeChatCV/opencv_3rdparty/tree/wechat_qrcode\n"
             "and put them into the current directory.\n"
             "---------------------------------------------------------------\n";
        std::cout << e.what() ;
    }

    std::vector<cv::Mat> corners;
    std::vector<std::string> info = detector->detectAndDecode(input, corners);//
    std::string infomation;
    infomation= std::accumulate(info.begin(),info.end(),infomation);
    for(int i=0;i<infomation.size();i++){
        a[i]=(uint8_t)(infomation[i]);
    }
    return a;
}




