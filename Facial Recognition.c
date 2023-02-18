#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // create a cascade classifier to detect faces
    CascadeClassifier face_cascade;
    face_cascade.load("haarcascade_frontalface_alt.xml");
    
    // open the camera
    VideoCapture cap(0);
    
    // check if the camera is open
    if (!cap.isOpened())
    {
        cout << "Error opening camera" << endl;
        return -1;
    }
    
    // loop to read frames from the camera
    while (true)
    {
        // read a frame from the camera
        Mat frame;
        cap.read(frame);
        
        // convert the frame to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        
        // detect faces in the frame
        vector<Rect> faces;
        face_cascade.detectMultiScale(gray, faces);
        
        // draw a rectangle around each face
        for (size_t i = 0; i < faces.size(); i++)
        {
            rectangle(frame, faces[i], Scalar(255, 0, 0), 2);
        }
        
        // show the frame
        imshow("Facial Recognition", frame);
        
        // wait for a key press
        if (waitKey(1) == 'q')
        {
            break;
        }
    }
    
    // release the camera
    cap.release();
    
    return 0;
}
