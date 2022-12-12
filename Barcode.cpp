//
// Created by xw on 2022-11-25.
//

#include "Barcode.h"

using namespace cv;
std::array<uint8_t,24> b;
std::array<uint8_t,24>BarCodeDetectAndDecode(const cv::Mat &input_image){
    Mat  cameraMatrix,disCoeffs,image_tmp;
    Mat image_src=input_image;

    cv::FileStorage fs_readD("../Src.yaml", cv::FileStorage::READ);
    fs_readD["cameraMatrix"] >> cameraMatrix;
    fs_readD["distCoeffs"] >> disCoeffs;
    fs_readD.release();

    cv::undistort(image_src, image_tmp, cameraMatrix, disCoeffs);

    std::vector<Point2f> initialcorners(4);
    initialcorners[0] = Point (500,137);
    initialcorners[1] = Point(2285,195);
    initialcorners[2] = Point(691,807);
    initialcorners[3] = Point(1991,849);//it is decided by the result above

    std::vector<Point2f> finalcorners(4);
    finalcorners[0] = Point (2000,200);
    finalcorners[1] = Point (3700,200);
    finalcorners[2] = Point (2000,1000);
    finalcorners[3] = Point (3700,1000);
    Mat m= getPerspectiveTransform(initialcorners,finalcorners);
    Mat img_final,img_final1,final;
    warpPerspective(image_tmp,img_final,m,Size(6000,3000) );
    final=img_final(Rect(1400,160,2500,750));

    Mat gray;
    cvtColor(final, gray, COLOR_BGR2GRAY);

    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
    int width = gray.cols;
    int height = gray.rows;
    uchar *raw = (uchar *)gray.data;
    zbar::Image  imageZbar(width, height, "Y800", raw, width * height);
    // 扫描相应的图像imageZbar(imageZbar是zbar::Image类型，存储着读入的图像)
    scanner.scan(imageZbar); //扫描条码
    zbar::Image::SymbolIterator symbol = imageZbar.symbol_begin();
    if (imageZbar.symbol_begin() == imageZbar.symbol_end())
    {
        std::cout<<"error"<<std::endl;
    }
    for (; symbol != imageZbar.symbol_end(); ++symbol)
    {
        for(int i=0;i<symbol->get_data().size();i++){
            b[i]=(uint8_t)(symbol->get_data()[i]);
        }
    }
    return b;
}


