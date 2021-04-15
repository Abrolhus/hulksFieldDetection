#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
#define REDCHROMATICITYTHRESHOLD0 0.37
#define LOWERGREENCHROMATICITYTHRESHOLD 0.4
#define UPPERGREENCHROMATICITYTHRESHOLD 0.43
#define BLUECHROMATICITYTHRESHOLD 0.38
// #define BLUECHROMATICITYTHRESHOLD 0.47

float getChromaticity(uchar channelColor, Vec3b color){
    return channelColor/(float)(color[0] + color[1] + color[2]);
}

int main(int argc, const char** argv){
    VideoCapture cap = VideoCapture(argv[1]);
    VideoWriter videoWritter = VideoWriter();
    Mat frame;
    cap >> frame;
    videoWritter.open("video.avi", CV_FOURCC('M','J','P','G'), 30, Size(frame.cols, frame.rows));
    while(cap.read(frame)){ // note que eu estou lendo o frame na condicao do while
        for (size_t i = 0; i < frame.cols; i++) {
            for (size_t j = 0; j < frame.rows; j++) {
                auto pixelColor = frame.at<Vec3b>(j, i);
                if(getChromaticity(pixelColor[0], pixelColor) > BLUECHROMATICITYTHRESHOLD)
                    continue;
                if(getChromaticity(pixelColor[2], pixelColor) > REDCHROMATICITYTHRESHOLD0)
                    continue;
                if(getChromaticity(pixelColor[1], pixelColor) >= LOWERGREENCHROMATICITYTHRESHOLD)
                    // if(getChromaticity(pixelColor[1], pixelColor) <= UPPERGREENCHROMATICITYTHRESHOLD)
                    frame.at<Vec3b>(j, i) = {255, 0, 100};
            }
        }
        imshow("ai ai (dor)", frame);
        videoWritter.write(frame);
        // if(waitKey(1.0/30*1000) >= 0) break; // cada frame duraria 17ms, input do teclado para a reproducao do  video
        // if(waitKey(1.0/30*1000) >= 0) break; // cada frame duraria 17ms, input do teclado para a reproducao do  video
        waitKey();
    }

    return 0;

    Mat inputImg = imread(argv[1]);
    Mat hsvImg, segmentedImg, segmentedBGRimg;
    cvtColor(inputImg, hsvImg, COLOR_BGR2HSV);
    segmentedImg = inputImg.clone();

    for (size_t i = 0; i < inputImg.cols; i++) {
        for (size_t j = 0; j < inputImg.rows; j++) {
            auto pixelColor = inputImg.at<Vec3b>(j, i);
            if(getChromaticity(pixelColor[0], pixelColor) > BLUECHROMATICITYTHRESHOLD)
                continue;
            if(getChromaticity(pixelColor[2], pixelColor) > REDCHROMATICITYTHRESHOLD0)
                continue;
            if(getChromaticity(pixelColor[1], pixelColor) >= LOWERGREENCHROMATICITYTHRESHOLD)
                // if(getChromaticity(pixelColor[1], pixelColor) <= UPPERGREENCHROMATICITYTHRESHOLD)
                segmentedImg.at<Vec3b>(j, i) = {255, 0, 100};
        }
    }
    imshow("vai", segmentedImg);
    waitKey();
    waitKey();
    return 0;
}
