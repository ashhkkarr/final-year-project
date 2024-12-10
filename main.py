import cv2
import numpy as np
import tensorflow.lite as tflite

# Load the TFLite model
def load_model(model_path):
    interpreter = tflite.Interpreter(model_path=model_path)
    interpreter.allocate_tensors()
    return interpreter

# Preprocess the frame
def preprocess_frame(frame, input_shape):
    frame_resized = cv2.resize(frame, (input_shape[1], input_shape[2]))
    frame_normalized = frame_resized / 255.0
    return np.expand_dims(frame_normalized.astype(np.float32), axis=0)

# Postprocess the results
def postprocess_output(output_data):
    predicted_class = np.argmax(output_data)
    confidence = np.max(output_data)
    return predicted_class, confidence

# Main function
def main():
    model_path = "your_model.tflite"  # Update with your TFLite model path
    labels = ["Waste Type 1", "Waste Type 2", "Waste Type 3"]  # Update with your labels

    # Load model
    interpreter = load_model(model_path)

    # Get input and output details
    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()
    input_shape = input_details[0]['shape']

    # Start the webcam
    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        print("Error: Could not access the camera.")
        return

    print("Press 'q' to quit.")

    while True:
        ret, frame = cap.read()
        if not ret:
            print("Error: Failed to capture frame.")
            break

        # Preprocess the frame
        input_data = preprocess_frame(frame, input_shape)

        # Set the input tensor
        interpreter.set_tensor(input_details[0]['index'], input_data)

        # Run inference
        interpreter.invoke()

        # Get the output tensor
        output_data = interpreter.get_tensor(output_details[0]['index'])[0]

        # Postprocess the output
        predicted_class, confidence = postprocess_output(output_data)
        label = labels[predicted_class]

        # Display the result
        cv2.putText(frame, f"{label} ({confidence:.2f})", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        cv2.imshow("Waste Detection", frame)

        # Quit the loop
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Release the webcam and close windows
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
