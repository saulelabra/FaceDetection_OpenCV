#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string.h>

using namespace cv;
using namespace std;

int main()
{
  string picName;
  string face_cascade_Classifier = "haarcascade_frontalface_default.xml";
  CascadeClassifier face_cascade;//Classifier para entrenar al algoritmo

  face_cascade.load(face_cascade_Classifier);

  cout << "Coloque su imagen en la carpeta del codigo e introduzca el nombre incluyendo extension" << endl;
  cin >> picName;

  //la imagen se debe de leer en ByN para el algoritmo (Haar Cascade)
  Mat img = imread(picName, 1);//Se lee la imagen a color

  Mat imgGray;
  cvtColor(img, imgGray, CV_BGR2GRAY);//Se convierte la imagen a GRAYSCALE
  equalizeHist(imgGray, imgGray);//Equalizando el histograma (mayor contraste)

  //Detectando el rostro
  vector<Rect> faces;
  face_cascade.detectMultiScale(imgGray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));

  //Dibujando el rectángulo
  Point pt1(faces[0].x, faces[0].y);
  Point pt2(faces[0].x + faces[0].width, faces[0].y + faces[0].height);
  rectangle(img, pt1, pt2, Scalar(255, 0, 0), 5);

  namedWindow("Imagen chula", WINDOW_AUTOSIZE);//Se crea una ventana
  imshow("Imagen chula", img);//Se muestra la imagen

  waitKey(0);
  return 0;

}
