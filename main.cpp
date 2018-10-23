#include "FaceDetector_opt.h"

using namespace std;

int main()
{
  //settings and image/video reading variables
  string imgName;
  Mat img;
  parameters_FacDet settings;
  vector <string> pathsToClassif;
  VideoCapture video;

  //path of classifiers to train algorithm
  pathsToClassif.push_back("C:/Users/quiqu/Downloads/OpenCV_pruebas/imgLoadnDisp/classifiers/haarcascade_frontalface_default.xml");

  //Define settings in struct "settings"
  settings.classifiers_location = pathsToClassif;
  settings.scaleFact = 1.1;
  settings.validNeighbors = 2;
  settings.minWidth = 10;
  settings.maxWidth = 10;

  //Initialize detector
  FaceDetector_opt detector(settings);

  //Configure video file

  /*video.open("sam.mp4");

  while(true)
  {
    Mat frame;

    video >> frame;


    if(frame.empty())
    {
      cout << "No se cargaron los frames" << endl;
      break;
    }

    imshow("Frame", frame);

    if(waitKey(27) >= 0)
    {
      cout << "Escape pressed" << endl;
      break;
    }
  }
  */

  video.open("Sam.mp4");
  //vector<vector<Rect>> prueba;

  //prueba = detector.detect_faces_video(&video);

  //cout << "Devolvió el vector" << endl;
  detector.detect_faces_video_show(&video);

  /*
  //Ask the data in CLI
  cout << "Input image file name (with extension)" << endl;
  cout << "Harold.jpg" << endl;
  imgName = "Harold.jpg";

  //Input the image as pointer to Mat
  img = imread(imgName, 1);
  cout << "Se guardó la imagen en el Mat (main)" << endl;

  vector<Rect> detected_faces = detector.detect_faces(&img);

  cout << "Se detectaron las caras y se regresó el vector" << endl;

  detector.detect_faces_show(&img);
  */

  return 0;
};
