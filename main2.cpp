#include "FaceDetector_opt.h"

using namespace std;

int main()
{
  //settings and image reading variables
  string imgName;
  Mat img;
  parameters settings;
  vector <CascadeClassifier> classifiersMain;

  //Classifiers to train algorithm
  CascadeClassifier frontal_default;

  //Loading classifiers
  frontal_default.load("C:/Users/quiqu/Downloads/OpenCV_pruebas/imgLoadnDisp/classifiers/haarcascade_frontalface_default.xml");

  //Configure ClassifiersMain vector
  classifiersMain.push_back(frontal_default);

  //Settings input parameters in struct
  settings.classifiers = classifiersMain;
  settings.scaleFact = 1.1;
  settings.validNeighbors = 2;
  settings.minWidth = 10;
  settings.maxWidth = 10;

  //Initialize detector
  FaceDetector_opt detector(settings);

  //Ask the data in CLI
  cout << "Input image file name (with extension)" << endl;
  cout << "Harold.jpg" << endl;
  imgName = "Harold.jpg";

  //Input the image as pointer to Mat
  img = imread(imgName, 1);
  detector.detectnShow(&img);

  return 0;
};
