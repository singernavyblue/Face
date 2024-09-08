#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/face.hpp>
#include <opencv2/face/facerec.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>

using namespace cv;
using namespace cv::face;
using namespace std;
using namespace dlib;

int main(int argc, char **argv)
{
    VideoCapture *videoCap = new VideoCapture(0);

    CascadeClassifier face_cascade;
    face_cascade.load("haarcascade_frontalface_alt.xml"); // 加载脸部分类器

    videoCap->open(0); // 打开摄像头
    if (!videoCap->isOpened())
    {
        videoCap->release(); // 释放摄像头
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    cout << "open camera success" << endl;

    while (1)
    {
        Mat frame;
        videoCap->read(frame);

        if (frame.empty())
        {
            cout << "frame is empty" << endl;
            return -1;
        }
        // 灰度化处理 节省内存
        Mat frame_gray;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        // 按存储大小计算  压缩方式采用线性压缩
        resize(gray, frame_gray, frame.size(), 0, 0, CV_INTER_LINEAR);
        // 直方图均值化 让灰度图经过直方图函数处理 黑白分明
        equalizeHist(frame_gray, frame_gray);
        vector<Rect> faces;
        // 检测输入图像中不同大小的对象。检测到的对象将作为矩形列表返回
        face_cascade.detectMultiScale(frame_grey, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
        // CASCADE_SCALE_IMAGE : 正常比例检测

        Mat face;
        Point text_lb;

        for (int i = 0; i < faces.size(); i++)
        {
            // 绘制长方形
            face = gray(faces[i]);
            text_lb = Point(faces[i].x, faces[i].y);

            Rect rect(face[i].x, face[i].y, face[i].width, face[i].height);
            rectangle(frame, rect, Scalar(0, 255, 0), 2);

            // 人脸文字标注
            /*
            Point centerText(face[i].x + face[i].width / 2 - 40, face[i].y + face[i].height / 2 - 20);
            putText(frame, "face", centerText, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
            */
        }

        Mat face_test;

        int predictLBPH = 0;
        resize(face, face_test, Size(92, 112));
        predictLBPH = modelLbph->predict(face_test);

        int predictEigen = 0;
        resize(face, face_test, Size(92, 112));
        predictEigen = modelEigen->predict(face_test);

        int predictFisher = 0;
        resize(face, face_test, Size(92, 112));
        predictFisher = modelFisher->predict(face_test);

        if (predictEigen == 0 && predictLBPH == 0 || predictFisher == 0 && predictLBPH == 0 || predictEigen == 0 && predictFisher == 0)
        {
            string name = "wxh, 20214097";
            putText(frame, name, text_lb, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0))
        }
        if (predictEigen == 1 && predictLBPH == 1 || predictFisher == 1 && predictLBPH == 1 || predictEigen == 1 && predictFisher == 1)
        {
            string name = "sxx, 20214098";
            putText(frame, name, text_lb, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0))
        }
    }
}
