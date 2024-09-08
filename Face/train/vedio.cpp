#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    VideoCapture cap(0);
    if (!cap.IsOpened())
    {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }
    Mat img;

    int i = 1;
    while (1)
    {
        char key = waitKey(100);
        cap >> img;
        imshow("vedio", img);
        string filename = format("/home/china/photo/%d.jpg", i);
        switch (key)
        {
        case 'p':
            i++;
            if (imwrite(filename, img))
            {
                cout << "save image " << filename << endl;
            }
            imshow("photo", img);
            waitKey(500);
            destroyWindow("photo");
            break;
        default:
            break;
        }
    }

    return 0;
}
