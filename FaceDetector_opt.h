#include "parameters_FacDet.h"

class FaceDetector_opt
{
private:
  vector <CascadeClassifier> classifiers;
  double scaleFact;
  int validNeighbors;
  int minWidth;
  int maxWidth;

public:
  FaceDetector_opt(parameters_FacDet input)
  {
    //pass data from struct
    scaleFact = input.scaleFact;
    validNeighbors = input.validNeighbors;
    minWidth = input.minWidth;
    maxWidth = input.maxWidth;

    //load classifiers
    CascadeClassifier tmp;

    for(int i=0; i<input.classifiers_location.size(); i++)
    {
      tmp.load(input.classifiers_location[i]);
      classifiers.push_back(tmp);
    }
  }

  Rect single_face(vector<Rect> faces)
  {
    int largest_size, largest_size_i;
    largest_size_i = 0;
    largest_size = faces[0].width;

    for(int i=1; i<faces.size(); i++)
    {
      if(faces[i].width > largest_size)
      {
        largest_size = faces[i].width;
        largest_size_i = i;
      }
    }

    cout << "Largest: " << largest_size << "\t Index: " << largest_size_i << endl;
    //sort(faces.begin(), faces.end());

    for(int i=0; i<faces.size(); i++)
    {
        cout << "X: " << faces[i].x << " Y: " << faces[i].y << endl;
    }

    return faces[largest_size_i];
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

  Rect detect_show_single_face(Mat *img)
  {
    Point pt1, pt2;
    vector<Rect> faces = detect_faces(img);
    vector<int> rectColor;
    Rect face = single_face(faces);

    rectColor.push_back(255);
    rectColor.push_back(0);
    rectColor.push_back(0);

    pt1.x = face.x;
    pt1.y = face.y;
    pt2.x = face.x + face.width;
    pt2.y = face.y + face.height;

    cout << "width: " << face.width << endl;

    rectangle(*img, pt1, pt2, Scalar(rectColor[1], rectColor[0], rectColor[2]));

    //Display window with image
    namedWindow("Face Detection", WINDOW_AUTOSIZE);//Generating window
    imshow("Face Detection", *img);//Showing image

    waitKey(0);
    return face;
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

    //tmp
    Rect prueba = single_face(faces);

    pt1.x = prueba.x;
    pt1.y = prueba.y;
    pt2.x = prueba.x + prueba.width;
    pt2.y = prueba.y + prueba.height;

    cout << "width: " << prueba.width << endl;

    rectangle(*img, pt1, pt2, Scalar(rectColor[1], rectColor[0], rectColor[2]));

    //Display window with image
    namedWindow("Face Detection", WINDOW_AUTOSIZE);//Generating window
    imshow("Face Detection", *img);//Showing image

    waitKey(0);
  }

  vector<vector<Rect>> detect_faces_video(VideoCapture * capture)
  {
    vector<vector<Rect>> faces_video;

    //cout << "Se declaró el vector (detect_faces_video)" << endl;

    if(!capture->isOpened())
    {
      cout << "Error: The file/stream couldn't open" << endl;
    }else{
      while(true)
      {
        //cout << "Entra al while" << endl;
        Mat frame;

        *capture >> frame;

        //cout << "guarda el frame" << endl;

        if(frame.empty())
        {
          cout << "Frames couldn't load" << endl;
          break;
        }else{
          resize(frame, frame, Size(), 0.50, 0.50);
          faces_video.push_back(detect_faces(&frame));
        }
      }
    }
    return faces_video;
  }

  void detect_faces_video_show(VideoCapture * capture)
  {
    Mat frame;
    vector<Rect> faces;

    Point pt1, pt2;
    vector <int> rectColor;

    rectColor.push_back(255);
    rectColor.push_back(0);
    rectColor.push_back(0);

    while(true)
    {
      *capture >> frame;

      if(frame.empty())
      {
        cout << "Frames couldn't load" << endl;
        break;
      }else{
        resize(frame, frame, Size(), 0.50, 0.50);

        faces = detect_faces(&frame);

        for(size_t i=0; i<faces.size(); i++)
        {
          //Drawing rectangle on image
          pt1.x = faces[i].x;
          pt1.y = faces[i].y;
          pt2.x = faces[i].x + faces[i].width;
          pt2.y = faces[i].y + faces[i].height;

          rectangle(frame, pt1, pt2, Scalar(rectColor[0], rectColor[1], rectColor[2]));
        }

        //Display window with image
        imshow("Face Detection", frame);//Showing image
        waitKey(1);
      }
    }
  }

  tuple<Mat, Rect> detect_faces_cam(VideoCapture * capture)
  {
    tuple<Mat, Rect> captured_face;

    Mat frame;
    vector<Rect> faces;

    Point pt1, pt2;
    vector <int> rectColor;

    rectColor.push_back(255);
    rectColor.push_back(0);
    rectColor.push_back(0);

    while(true)
    {
      *capture >> frame;

      if(frame.empty())
      {
        cout << "Frames couldn't load" << endl;
        break;
      }else{
        resize(frame, frame, Size(), 0.50, 0.50);

        faces = detect_faces(&frame);

        for(size_t i=0; i<faces.size(); i++)
        {
          //Drawing rectangle on image
          pt1.x = faces[i].x;
          pt1.y = faces[i].y;
          pt2.x = faces[i].x + faces[i].width;
          pt2.y = faces[i].y + faces[i].height;

          rectangle(frame, pt1, pt2, Scalar(rectColor[0], rectColor[1], rectColor[2]));
        }

        //Display window with image
        imshow("Face Detection", frame);//Showing image

        waitKey(1);

        if(GetAsyncKeyState( VK_ESCAPE ) & 0x8000)
          break;

        if(GetAsyncKeyState( VK_SPACE ) & 0x8000)
        {
          return captured_face;
        }
      }
    }
  }
};
