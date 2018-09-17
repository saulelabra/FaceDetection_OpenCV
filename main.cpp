#include <iostream>
#include "FaceDetector.h"

int main()
{
  string imagen;
  string classifierName = "haarcascade_frontalface_default.xml";
  vector<Rect> faces;

  cout << "Coloque su imagen en la carpeta del codigo e introduzca el nombre incluyendo extension" << endl;
  cin >> imagen;

  FaceDetector detector1(imagen, classifierName);
  detector1.detectnShow();
  faces = detector1.detectnReturn();

  cout << "id\tx\ty\tWidth\tHeight" << endl;
  for(int i=0; i<faces.size(); i++)
  {
    cout << i << "\t" << faces[i].x << "\t" << faces[i].y << "\t" << faces[i].width << "\t" << faces[i].height << endl;
  }

  waitKey(0);
  return 0;
}
