from flask import *
import threading
from ultralytics import *
import cv2
import time

app=Flask(__name__)

model = YOLO("C:\\Users\\webde\\OneDrive\\Desktop\\project_waste\\pycharm\\try1.pt")

threshold = 0.4

dat=""
check_flag=0
uid=0


@app.route('/test', methods=['GET', 'POST'])
def test():
    global dat,check_flag
    val = request.get_data().decode('utf-8')
    print(val)
    check_flag=0
    if val == "A":
        thread = threading.Thread(target=detect)
        thread.start()

    res = "None"
    if dat:
        res = dat
        dat = ""
    return res


def main():
    threading.Thread(target=connect).start()



def detect():
    global dat, check_flag, uid
    while check_flag == 0:
        start_time = time.time()
        cap = cv2.VideoCapture(1)  # Open camera

        if not cap.isOpened():
            print("Error: Camera not found or cannot be opened.")
            return  # Exit the function if the camera fails to open

        frame = None  # Initialize frame variable

        while time.time() - start_time < 15:
            ret, frame = cap.read()
            if not ret:  # If reading fails, break the loop
                print("Error: Failed to capture frame.")
                break
            cv2.imshow('Live Detection', frame)
            cv2.waitKey(1)

        if frame is not None:
            cv2.imwrite("Captured_image.jpg", frame)

        cap.release()  # Release the camera
        cv2.destroyAllWindows()

        if frame is None:
            print("Error: No frame captured, skipping detection.")
            return  # Skip the rest of the function

        frame = cv2.imread("Captured_image.jpg")

        results = model(frame)[0]

        for result in results.boxes.data.tolist():
            x1, y1, x2, y2, score, class_id = result

            if score > threshold:
                cv2.rectangle(frame, (int(x1), int(y1)), (int(x2), int(y2)), (0, 255, 0), 4)
                cv2.putText(frame, results.names[int(class_id)].upper(), (int(x1), int(y1 - 10)),
                            cv2.FONT_HERSHEY_SIMPLEX, 1.3, (0, 255, 0), 3, cv2.LINE_AA)
                res = results.names[int(class_id)]
                print(res)
                if res == "paper":
                    dat = "A"
                elif res in ["metal"]:
                    dat = "C"
                elif res in ["plastic"]:
                    dat = "D"
                else:
                    dat = "B"
            else:
                dat = "B"

            check_flag = 1


def connect():
    app.run(host='0.0.0.0', port=5000)

if __name__=="__main__":
    main()
