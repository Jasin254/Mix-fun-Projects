#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/shape_predictor.h>
#include <svm.h>

// Define the maximum number of facial landmarks
#define MAX_LANDMARKS 68

// Define the mood categories and their corresponding labels
char* mood_categories[] = {"angry", "disgust", "fear", "happy", "neutral", "sad", "surprise"};

// Load the pre-trained facial landmark detector from dlib
dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
dlib::shape_predictor predictor;

// Load the pre-trained machine learning model for mood classification
svm_model* model;

// Define a function to extract the relevant facial features from the facial landmarks
void extract_features(dlib::full_object_detection landmarks, double* features) {
    // Extract the coordinates of the eyes, nose, and mouth
    int left_eye[6] = {36, 37, 38, 39, 40, 41};
    int right_eye[6] = {42, 43, 44, 45, 46, 47};
    int nose[9] = {27, 28, 29, 30, 31, 32, 33, 34, 35};
    int mouth[20] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67};

    // Calculate the eye aspect ratio (EAR) to detect if the eyes are open or closed
    double left_ear = eye_aspect_ratio(landmarks, left_eye, 6);
    double right_ear = eye_aspect_ratio(landmarks, right_eye, 6);

    // Calculate the mouth aspect ratio (MAR) to detect if the mouth is open or closed
    double mar = mouth_aspect_ratio(landmarks, mouth, 20);

    // Combine the EAR and MAR values into a feature vector
    features[0] = left_ear;
    features[1] = right_ear;
    features[2] = mar;
}

// Define a function to calculate the eye aspect ratio (EAR)
double eye_aspect_ratio(dlib::full_object_detection landmarks, int* eye, int n) {
    // Calculate the Euclidean distances between the vertical eye landmarks
    double A = sqrt(pow(landmarks.part(eye[1]).x() - landmarks.part(eye[5]).x(), 2) + pow(landmarks.part(eye[1]).y() - landmarks.part(eye[5]).y(), 2));
    double B = sqrt(pow(landmarks.part(eye[2]).x() - landmarks.part(eye[4]).x(), 2) + pow(landmarks.part(eye[2]).y() - landmarks.part(eye[4]).y(), 2));

    // Calculate the Euclidean distance between the horizontal eye landmarks
    double C = sqrt(pow(landmarks.part(eye[0]).x() - landmarks.part(eye[3]).x(), 2) + pow(landmarks.part(eye[0]).y() - landmarks.part(eye[3]).y(), 2));

    // Calculate the
// eye aspect ratio (EAR)
double ear = (A + B) / (2 * C);
  return ear;
}

// Define a function to calculate the mouth aspect ratio (MAR)
double mouth_aspect_ratio(dlib::full_object_detection landmarks, int* mouth, int n) {
// Calculate the Euclidean distances between the vertical mouth landmarks
double A = sqrt(pow(landmarks.part(mouth[2]).x() - landmarks.part(mouth[10]).x(), 2) + pow(landmarks.part(mouth[2]).y() - landmarks.part(mouth[10]).y(), 2));
double B = sqrt(pow(landmarks.part(mouth[3]).x() - landmarks.part(mouth[9]).x(), 2) + pow(landmarks.part(mouth[3]).y() - landmarks.part(mouth[9]).y(), 2));
double C = sqrt(pow(landmarks.part(mouth[4]).x() - landmarks.part(mouth[8]).x(), 2) + pow(landmarks.part(mouth[4]).y() - landmarks.part(mouth[8]).y(), 2));
  // Calculate the Euclidean distances between the horizontal mouth landmarks
double D = sqrt(pow(landmarks.part(mouth[0]).x() - landmarks.part(mouth[6]).x(), 2) + pow(landmarks.part(mouth[0]).y() - landmarks.part(mouth[6]).y(), 2));
double E = sqrt(pow(landmarks.part(mouth[1]).x() - landmarks.part(mouth[5]).x(), 2) + pow(landmarks.part(mouth[1]).y() - landmarks.part(mouth[5]).y(), 2));

// Calculate the mouth aspect ratio (MAR)
double mar = (A + B + C) / (3 * D + E);

return mar;
}

// Define a function to classify the mood based on the extracted features
char* classify_mood(double* features) {
// Create an SVM node to hold the feature vector
struct svm_node* node = (struct svm_node*) malloc((3 + 1) * sizeof(struct svm_node));
node[0].index = 1;
node[0].value = features[0];
node[1].index = 2;
node[1].value = features[1];
node[2].index = 3;
node[2].value = features[2];
node[3].index = -1;
  // Predict the mood label using the SVM model
double mood_label = svm_predict(model, node);

// Return the corresponding mood category label
return mood_categories[(int) mood_label];
