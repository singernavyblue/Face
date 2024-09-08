#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include <opencv2/face/facerec.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace cv;
using namespace cv::face;
using namespace std;

void read_csv(string filename, vector<Mat> &images, vector<int> &labels, char separator = ';')
{
    ifstream file(filename.c_str(), ifstream::in);
    if (!file)
    {
        cout << "No valid input file was given, please check the given filename." << endl;
        exit(1);
    }
    string line, path, classlabel;
    while (getline(file, line))
    {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlable);
        if (!path.empty() && !classlabel.empty())
        {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

int main(int argc, char const *argv[])
{
    string fd = "at.txt";
    // 存储人脸数据以及标签
    vector<Mat> images;
    vector<int> labels;

    read_csv(fd, images, labels); // 读取路径以及标签

    if (image.size() <= 1)
    {
        cout << "Error: too little images" << endl;
        exit(1);
    }

    Ptr<FaceRecgnizer> model1 = EigenFaceRecgnizer::create();
    model1->train(images, labels);
    model1->save("eigenface.xml");

    Ptr<FaceRecgnizer> model2 = FishFaceRecgnizer::create();
    model2->train(images, labels);
    model2->save("fishface.xml");

    Ptr<FaceRecgnizer> model3 = LBPHFaceRecgnizer::create();
    model3->train(images, labels);
    models->save("lbph.xml");

    return 0;
}
