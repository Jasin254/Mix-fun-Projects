import cv2
import numpy as np
import dlib
import math
import joblib

# Load the pre-trained facial landmark detector from dlib
detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")

# Load the pre-trained machine learning model for mood classification
model = joblib.load("mood_classifier_model.pkl")

# Define a function to extract the relevant facial features from the facial landmarks
def extract_features(face_landmarks):
    # Extract the coordinates of the eyes, nose, and mouth
    left_eye = face_landmarks[36:42]
    right_eye = face_landmarks[42:48]
    nose = face_landmarks[27:36]
    mouth = face_landmarks[48:68]

    # Calculate the eye aspect ratio (EAR) to detect if the eyes are open or closed
    left_ear = eye_aspect_ratio(left_eye)
    right_ear = eye_aspect_ratio(right_eye)

    # Calculate the mouth aspect ratio (MAR) to detect if the mouth is open or closed
    mar = mouth_aspect_ratio(mouth)

    # Combine the EAR and MAR values into a feature vector
    features = [left_ear, right_ear, mar]
    return features

# Define a function to calculate the eye aspect ratio (EAR)
def eye_aspect_ratio(eye):
    # Calculate the Euclidean distances between the vertical eye landmarks
    A = math.dist(eye[1], eye[5])
    B = math.dist(eye[2], eye[4])

    # Calculate the Euclidean distance between the horizontal eye landmarks
    C = math.dist(eye[0], eye[3])

    # Calculate the eye aspect ratio (EAR)
    ear = (A + B) / (2 * C)
    return ear

# Define a function to calculate the mouth aspect ratio (MAR)
def mouth_aspect_ratio(mouth):
    # Calculate the Euclidean distances between the vertical mouth landmarks
    A = math.dist(mouth[2], mouth[10])
    B = math.dist(mouth[4], mouth[8])
    C = math.dist(mouth[0], mouth[6])

    # Calculate the mouth aspect ratio (MAR)
    mar = (A + B) / (2 * C)
    return mar

# Define the mood categories and their corresponding labels
mood_categories = ["angry", "disgust", "fear", "happy", "neutral", "sad", "surprise"]

# Define the video capture device
cap = cv2.VideoCapture(0)

# Loop through the video frames
while True:
    # Capture the current frame
    ret, frame = cap.read()

    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect the faces in the grayscale frame
    faces = detector(gray)

    # Loop through each face in the frame
    for face in faces:
        # Use the facial landmark detector to detect the landmarks in the face
        landmarks = predictor(gray, face)

        # Extract the relevant facial features from the landmarks
        features = extract_features([(landmark.x, landmark.y) for landmark in landmarks.parts()])

        # Use the machine learning model to classify the mood based on the features
        prediction = model.predict(np.array(features).reshape(1, -1))[0]

        # Display the mood label on the frame
        label = mood_categories[prediction]
        cv2.putText(frame,
                        label, (face.left(), face.bottom() + 25), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

    # Draw a rectangle around the face
    cv2.rectangle(frame, (face.left(), face.top()), (face.right(), face.bottom()), (0, 0, 255), 2)

    # Draw circles at the locations of the facial landmarks
    for landmark in landmarks.parts():
        cv2.circle(frame, (landmark.x, landmark.y), 2, (0, 255, 0), -1)

# Display the frame
cv2.imshow("Frame", frame)

# Check if the user has pressed the "q" key to quit
if cv2.waitKey(1) & 0xFF == ord("q"):
    break
Release the video capture device and close all windows
cap.release()
cv2.destroyAllWindows()
