#include "FaceDetector_opt.h"
#include <windows.h>

int main()
{
  //Variable declaration
  int option;
  parameters_FacDet settings;
  vector <string> pathsToClassif;

  //Image file
  string fileName;
  Mat img;
  vector<Rect> detected_faces;
  vector<Rect> real_faces;
  vector<Rect> largest_face;

  largest_face.resize(1);

  //Video fileName
  VideoCapture video;
  vector<vector<Rect>> faces_video;
  vector<Rect> temporal;

  //path of classifiers to train algorithm
  pathsToClassif.push_back("C:/Users/quiqu/Downloads/OpenCV_pruebas/imgLoadnDisp/classifiers/haarcascade_frontalface_default.xml");
  pathsToClassif.push_back("C:/Users/quiqu/Downloads/OpenCV_pruebas/imgLoadnDisp/classifiers/haarcascade_frontalface_alt.xml");
  pathsToClassif.push_back("C:/Users/quiqu/Downloads/OpenCV_pruebas/imgLoadnDisp/classifiers/haarcascade_frontalface_alt2.xml");
  pathsToClassif.push_back("C:/Users/quiqu/Downloads/OpenCV_pruebas/imgLoadnDisp/classifiers/haarcascade_frontalface_alt_tree.xml");

  //Define settings in struct "settings"
  settings.classifiers_location = pathsToClassif;
  settings.scaleFact = 1.2;
  settings.validNeighbors = 1;
  settings.minWidth = 60;
  settings.maxWidth = 60;

  //Intitialize detector with settings
  FaceDetector_opt detector(settings);

  //Ask for data in CLI
  cout << "Bienvenido al demo de detección de rostros" << endl;

  do{
    cout << "Introduzca la opcion deseada:" << endl << endl;

    cout << "(1) Detectar rostro de imagen" << endl;
    cout << "(2) Detectar rostro de video" << endl;
    cout << "(3) Detectar rostro de camara" << endl << endl;
    cout << "(0) Salir" << endl;

    cin >> option;

    switch (option)
    {
      case 1: //Detect from image file
        cout << "Introduzca el nombre de la imagen (con extension)" << endl;
        cin >> fileName;

        img = imread(fileName, 1);
        detected_faces = detector.detect_faces(&img);
        //detector.show_faces(&img, detected_faces);

        real_faces = detector.ignore_false_positives(&img, detected_faces);
        cout << "Devolvió vector sin falsos positivos" << endl;

        largest_face[0] = detector.get_largest_face(real_faces);

        //detector.show_faces(&img, detected_faces, real_faces, largest_face[0]);
        //waitKey(0);

        detector.show_faces(&img, largest_face);
        waitKey(0);

        /*
        //temporal
        detected_faces = detector.detect_faces(&img, 1);
        //eliminar FP, seleccionar uno, y ese rostro meterlo a un vector de uno
        detector.show_faces(&img, detected_faces);

        //temporal
        detected_faces = detector.detect_faces(&img, 2);
        //eliminar FP, seleccionar uno, y ese rostro meterlo a un vector de uno
        detector.show_faces(&img, detected_faces);

        //temporal
        detected_faces = detector.detect_faces(&img, 3);
        //eliminar FP, seleccionar uno, y ese rostro meterlo a un vector de uno
        detector.show_faces(&img, detected_faces);
        */

        break;
      case 2: //Detect from video file
        cout << "Introduzca el nombre del video (con extension)" << endl;
        cin >> fileName;
        video.open(fileName);

        //If vide isn't openc
        if(!video.isOpened())
        {
            cout<<"Error: The file/stream couldn't open"<<endl;
        }
        else
        {
            while(true)
            {
              Mat frame;
              video >> frame;
              if(frame.empty())
              {
                break;
              }
              else
              {
                resize(frame, frame, Size(), 0.30, 0.30);
                temporal = detector.detect_faces(&frame);
                real_faces = detector.ignore_false_positives(&frame, temporal);
                largest_face[0] = detector.get_largest_face(real_faces);
                detector.show_faces(&frame, largest_face);
                waitKey(1);

                if(GetAsyncKeyState( VK_ESCAPE ) & 0x8000)
                  break;
              }
            }
            destroyAllWindows();
            video.release();
        }
        break;
      case 3: //Detect from camera stream
      cout << "Usando la cámara del dispositivo" << endl;
      video.open(0);

      //If vide isn't openc
      if(!video.isOpened())
      {
          cout<<"Error: The file/stream couldn't open"<<endl;
      }
      else
      {
          while(true)
          {
            Mat frame;
            video >> frame;
            if(frame.empty())
            {
              break;
            }
            else
            {
              resize(frame, frame, Size(), 0.50, 0.50);
              temporal = detector.detect_faces(&frame);
              faces_video.push_back(temporal);
              detector.show_faces(&frame,temporal);
              waitKey(1);
              if(GetAsyncKeyState( VK_ESCAPE ) & 0x8000)
                break;
            }
          }
          destroyAllWindows();
          video.release();
      }
        break;
    }

    cout << endl << endl;
  }while(option != 0);

  return 0;
}
