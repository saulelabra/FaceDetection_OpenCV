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

  vector<Rect> detect_faces(Mat *img)
  {
    Mat imgGray;//grayscale conversion
    Ptr<CLAHE> clahe;//Contrast Limit Adaptative Histogram Equalization
    vector<Rect> faces;

    clahe = createCLAHE();
    clahe->setClipLimit(4);

    if(!img->empty() && !classifiers.empty())
    {
      //Converting into gray scale and improving contrast
      cvtColor(*img, imgGray, CV_BGR2GRAY);
      clahe->apply(imgGray, imgGray);

      //Detecting faces
      classifiers[0].detectMultiScale(imgGray, faces, scaleFact, validNeighbors, 0|CV_HAAR_SCALE_IMAGE, Size(minWidth, maxWidth));
    }else{
      cout << "Image or classifier not found" << endl;
    }

    return faces;
  }

  void detect_faces_show(Mat *img)
  {
    Point pt1, pt2;
    vector <int> rectColor;
    vector <Rect> faces = detect_faces(img);

    rectColor.push_back(255);
    rectColor.push_back(0);
    rectColor.push_back(0);

    for(size_t i=0; i<faces.size(); i++)
    {
      //Drawing rectangle on image
      pt1.x = faces[i].x;
      pt1.y = faces[i].y;
      pt2.x = faces[i].x + faces[i].width;
      pt2.y = faces[i].y + faces[i].height;

      rectangle(*img, pt1, pt2, Scalar(rectColor[0], rectColor[1], rectColor[2]));
    }
    //Display window with image
    namedWindow("Face Detection", WINDOW_AUTOSIZE);//Generating window
    imshow("Face Detection", *img);//Showing image

    waitKey(0);
  }
};
