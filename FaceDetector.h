#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string.h>

using namespace std;
using namespace cv;

class FaceDetector
{
private:
  //General variables
  string picName;
  string face_cascade_name;
  CascadeClassifier face_cascade;
  Mat img;
  Mat imgGray;
  vector<Rect> faces;
  Point pt1;
  Point pt2;

  //CLAHE (Contrast Limited Adaptive Histogram Equalization) variables
  Ptr<CLAHE> clahe;

  //detectMultiScale variables
  double scaleFact;
  int validNeighbors;
  int minWidth;
  int minHeight;

  vector<int> rectColor;

public:
  FaceDetector()
  {
    scaleFact = 1.1;
    validNeighbors = 4;
    minWidth = 10;
    minHeight = 10;
    rectColor.push_back(255);
    rectColor.push_back(0);
    rectColor.push_back(0);

    clahe = createCLAHE();
    clahe->setClipLimit(2);
  }

  FaceDetector(string inImg, string inClassifier)
  {
    //Receiving location of image and Classifier
    picName = inImg;
    face_cascade_name = inClassifier;
    scaleFact = 1.1;
    validNeighbors = 4;
    minWidth = 10;
    minHeight = 10;
    rectColor.push_back(255);
    rectColor.push_back(0);
    rectColor.push_back(0);

    clahe = createCLAHE();
    clahe->setClipLimit(2);
  }

  void settingsDetect(double scaleFactIn, int validNeighborsIn, int minWidthIn, int minHeightIn)
  {
    scaleFact = scaleFactIn;
    validNeighbors = validNeighborsIn;
    minWidth = minWidthIn;
    minHeight = minHeightIn;

    clahe = createCLAHE();
    clahe->setClipLimit(4);
  }

  void settingsCLAHE(int clipLimitIn)
  {
    clahe->setClipLimit(clipLimitIn);
  }

  void setImgnClassifier(string inImg, string inClassifier)
  {
    picName = inImg;
    face_cascade_name = inClassifier;

    return;
  }

  int detect()
  {
    //Loading image and face cascade classifier
    face_cascade.load(face_cascade_name);
    img = imread(picName, 1);

    if(!img.empty() && !face_cascade.empty())
    {
      //Converting into gray scale and improving contrast
      cvtColor(img, imgGray, CV_BGR2GRAY);
      clahe->apply(imgGray, imgGray);

      //Detecting faces
      face_cascade.detectMultiScale(imgGray, faces, scaleFact, validNeighbors, 0|CV_HAAR_SCALE_IMAGE, Size(minWidth, minHeight));
      return 0;

    }else{
      cout << "Image or classifier not found: " << picName << "\t" << face_cascade_name << endl;
      return -1;
    }
  }

  void detectnShow()
  {
    if(detect() == 0)
    {
      for(size_t i=0; i<faces.size(); i++)
      {
        //Drawing rectangle on image
        pt1.x = faces[i].x;
        pt1.y = faces[i].y;
        pt2.x = faces[i].x + faces[i].width;
        pt2.y = faces[i].y + faces[i].height;

        rectangle(img, pt1, pt2, Scalar(rectColor[0], rectColor[1], rectColor[2]));
      }
      //Display window with image
      namedWindow("Face Detection", WINDOW_AUTOSIZE);//Generating window
      namedWindow("Equalized", WINDOW_AUTOSIZE);
      imshow("Face Detection", img);//Showing image
      imshow("Equalized", imgGray);
    }else{
      return;
    }
  }

  vector<Rect> detectnReturn()
  {
    detect();

    return faces;
  }

};
