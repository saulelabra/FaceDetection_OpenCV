#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string.h>
#include <vector>
#include <windows.h>
#include <tuple>

using namespace std;
using namespace cv;

typedef struct parameters_FacDet{
  vector <string> classifiers_location;

  //detectMultiScale
  double scaleFact;
  int validNeighbors;
  int minWidth;
  int maxWidth;
}parameters_FacDet;
