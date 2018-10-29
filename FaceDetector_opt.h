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
  FaceDetector_opt(parameters_FacDet input);

  Rect get_largest_face(vector<Rect> faces);

  vector<Rect> detect_faces(Mat *img);

  vector<Rect> detect_faces(Mat *img, int classifier_index);

  void show_faces(Mat *img, vector<Rect> faces);

  void show_faces(Mat *img, vector<Rect> detected_faces, vector<Rect> real_faces);

  void show_faces(Mat *img, vector<Rect> detected_faces, vector<Rect> real_faces, Rect largest_face);

  vector<Rect> ignore_false_positives(Mat * img, vector<Rect> original_det_faces, int tolerance);

  Rect select_additional_face(Mat * img);

  ~ FaceDetector_opt();
};
