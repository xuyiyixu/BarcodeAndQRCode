//  在引入opencv或opencv头文件时，不需要将core等包一个一个引入，（在opencv3之后）只需引用下面这一个。
#include <opencv2/opencv.hpp>
#include <iostream>
#include "QRcode.h"
#include<string>
#include"Barcode.h"
#include "ImageCorrection.h"
#include <vector>

#include <zbar.h>

//#include"Barcode.h"
using namespace cv;
using namespace std;

int main() {
    Mat  cameraMatrix,disCoeffs,image_tmp;
    Mat image_src=imread("../photos/C_9.jpg");
    Mat image_src11=imread("../photos/C_7.jpg");
    Mat Image=imread("../photos/img.png");
    cv::FileStorage fs_readD("../Src.yaml", cv::FileStorage::READ);
    fs_readD["cameraMatrix"] >> cameraMatrix;
    fs_readD["distCoeffs"] >> disCoeffs;
    fs_readD.release();

    cv::undistort(image_src, image_tmp, cameraMatrix, disCoeffs);


    vector<Point2f> initialcorners(4);
    initialcorners[0] = Point (500,137);
    initialcorners[1] = Point(2285,195);
    initialcorners[2] = Point(691,807);
    initialcorners[3] = Point(1991,849);//it is decided by the result above

    vector<Point2f> finalcorners(4);
    finalcorners[0] = Point (2000,200);
    finalcorners[1] = Point (3700,200);
    finalcorners[2] = Point (2000,1000);
    finalcorners[3] = Point (3700,1000);
    Mat m= getPerspectiveTransform(initialcorners,finalcorners);
    Mat img_final,img_final1,final;
    warpPerspective(image_tmp,img_final,m,Size(6000,3000) );
    warpPerspective(image_src11,img_final1,m,Size(6000,3000));
    final=img_final(Rect(1400,160,2500,750));

    Mat gray;
    cvtColor(Image, gray, COLOR_BGR2GRAY);

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
        cout << "查询条码失败，请检查图片！" << endl;
    }
    for (; symbol != imageZbar.symbol_end(); ++symbol)
    {
        cout << "类型：" << endl << symbol->get_type_name() << endl << endl;
        cout << "条码：" << endl << symbol->get_data() << endl << endl;
    }
//    Mat gaussian;
//    GaussianBlur(gray, gaussian, Size(3, 3), 0);
//    Mat sobel;
//    Sobel(gaussian,sobel,CV_32F,1,0,3);
//    Sobel(gaussian,sobel,CV_32F,1,0,3);
//    convertScaleAbs(sobel,sobel);
//    blur(sobel,sobel,Size(5,5));
//    Mat thresh;
//    threshold(sobel, thresh, 40, 255, THRESH_BINARY_INV | THRESH_OTSU);
//
//    Mat open;
//    Mat structure = getStructuringElement(MORPH_RECT, Size(8, 8), Point(-1, -1));
//    Mat getStructuringElement(int shape, Size esize, Point anchor = Point(-1, -1));
//
//    morphologyEx(thresh, open, CV_MOP_OPEN, structure);
//    imshow("open", open);

//    Mat close;
//    morphologyEx(open, close, CV_MOP_CLOSE, structure);
//    erode(close,close,structure);
////    imshow("1",close);
//    dilate(close,close,structure);
//    dilate(close,close,structure);
//    imshow("close", close);
//    waitKey(0);
//    vector<vector<Point>> contours;
//    vector<Vec4i> hierarchy;
//    findContours(close,contours,hierarchy,RETR_CCOMP,CHAIN_APPROX_SIMPLE,Point());
    //RETR_EXTERNAL：表示只提取最外面的轮廓；
    //
    //RETR_LIST：表示提取所有轮廓并将其放入列表；
    //
    //RETR_CCOMP:表示提取所有轮廓并将组织成一个两层结构，其中顶层轮廓是外部轮廓，第二层轮廓是“洞”的轮廓；
    //
    //RETR_TREE：表示提取所有轮廓并组织成轮廓嵌套的完整层级结构。

//    for(int i=0;i<contours.size();i++){
//        double TempArea = fabs(contourArea(contours[i]));//计算轮廓的面积
//        if (TempArea > 2000&&TempArea<60000)//轮廓面积大于1000认为是条形码
//        {
//            Rect rect = boundingRect(contours[i]);//计算点集的矩形边界
//            rectangle(final, rect, Scalar(255), 2);//画出矩形
//            Mat image_roi = gray(rect);//根据轮廓画出Roi区域
//            Mat image_scan;
//            image_roi.copyTo(image_scan);//将Roi区域的图像复制到新的变量中
//            zbar::ImageScanner scanner;
//            scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
//
//            int width = image_scan.cols;
//            int height = image_scan.rows;
//            // 在Zbar中进行扫描时候，需要将OpenCV中的Mat类型转换为（uchar *）类型，raw中存放的是图像的地址；对应的图像需要转成Zbar中对应的图像zbar::Image
//            uchar *raw = (uchar *)gray.data;
//            zbar::Image  imageZbar(width, height, "Y800", raw, width * height);
//            // 扫描相应的图像imageZbar(imageZbar是zbar::Image类型，存储着读入的图像)
//            scanner.scan(imageZbar); //扫描条码
//            zbar::Image::SymbolIterator symbol = imageZbar.symbol_begin();
//            if (imageZbar.symbol_begin() == imageZbar.symbol_end())
//            {
//                cout << "查询条码失败，请检查图片！" << endl;
//            }
//            for (; symbol != imageZbar.symbol_end(); ++symbol)
//            {
//                cout << "类型：" << endl << symbol->get_type_name() << endl << endl;
//                cout << "条码：" << endl << symbol->get_data() << endl << endl;
//            }
//        }



//    imshow("  ",image_tmp);
    // get the corners of 4 angles and =Point()we assume that we have already done this
    //ANOTHER WAY:ingore all of these ,just use one particular point set to replace it, big enough





    barcode::BarcodeDetector bardet;
    Mat corners; //返回的检测框的四个角点坐标，如果检测到N个条码，那么维度应该是[N][4][2]
    std::vector<std::string> decoded_info; //返回的解码结果，如果解码失败，则为空string
    std::vector<barcode::BarcodeType> decoded_format; //返回的条码类型，如果解码失败，则为BarcodeType::NONE
    bardet.detectAndDecode(Image, decoded_info, decoded_format, corners);//
    namedWindow("final",0);
    resizeWindow("final",640,480);
    cv::imshow("final", final);
    namedWindow("final1",0);
    resizeWindow("gray",640,480);
    cv::imshow("final1", gray);
    cv::waitKey(0);





    std::cout<<1;

}