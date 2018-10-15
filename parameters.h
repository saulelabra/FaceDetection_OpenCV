#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
using namespace cv;

typedef struct parameters{
  vector <CascadeClassifier> classifiers;

  //detectMultiScale
  double scaleFact;
  int validNeighbors;
  int minWidth;
  int maxWidth;
}parameters;
