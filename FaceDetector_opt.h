#include "parameters.h"

class FaceDetector_opt
{
private:
  vector <CascadeClassifier> classifiers;
  double scaleFact;
  int validNeighbors;
  int minWidth;
  int maxWidth;

public:
  FaceDetector_opt(parameters input)
  {
    //pass data from struct
    classifiers = input.classifiers;
    scaleFact = input.scaleFact;
    validNeighbors = input.validNeighbors;
    minWidth = input.minWidth;
    maxWidth = input.maxWidth;
  }

  /*void detect(Mat *img)
  {
    Mat imgGray;

    if(!img->empty() && !classifiers.empty())
    {
      cvtColor(*img, imgGray)
    }
  }*/

  void detectnShow(Mat *img)
  {
    cout << "entró a la función" << endl;
    if(!img->empty() && !classifiers.empty())
    {
      cout << "el Mat y el arreglo no están vacíos" << endl;
    }
  }

  vector<Rect> detectnReturn()
  {

  }



};
