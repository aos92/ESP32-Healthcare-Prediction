# ESP32 Healthcare Prediction

This project demonstrates how to deploy a machine learning model on an ESP32 to make healthcare-related predictions based on input data received from the Serial Monitor. The model is built using the Random Forest algorithm in scikit-learn and converted to C code using `microMLgen`.

## Features

- Receives input data via Serial Monitor (Age, Height, Weight, BMI).
- Predicts a class based on the input data using a RandomForest model.
- Displays the predicted class in a readable format on the Serial Monitor.

## Components

- ESP32
- Arduino IDE

## Prerequisites

- Install [Arduino IDE](https://www.arduino.cc/en/software).
- Install ESP32 board in Arduino IDE. Follow the instructions [here](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).
- Install `microMLgen` for model conversion. Follow the instructions [here](https://github.com/eloquentarduino/micromlgen).

## How to Use

1. **Clone the repository:**

   ```bash
   git clone https://github.com/yourusername/your-repo-name.git
   cd your-repo-name
   ```

2. **Open the project in Arduino IDE:**

   Open `your-sketch.ino` in Arduino IDE.

3. **Prepare your model:**

   - Train your machine learning model using scikit-learn. Here's an example of training a Random Forest model:

     ```python
     import pandas as pd
     from sklearn.ensemble import RandomForestClassifier
     from sklearn.model_selection import train_test_split
     from sklearn.metrics import accuracy_score
     from micromlgen import port

     # Read data from CSV
     data = pd.read_csv('dataset.csv')

     # Separate features and labels
     X = data[['Age', 'Weight', 'Height', 'Bmi']]
     y = data['Category']

     # Split data into training and testing sets
     X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

     # Initialize and train the Random Forest model
     model = RandomForestClassifier(n_estimators=100, random_state=42)
     model.fit(X_train, y_train)

     # Evaluate the model
     y_pred = model.predict(X_test)
     accuracy = accuracy_score(y_test, y_pred)
     print(f'Accuracy: {accuracy}')

     # Convert the model to C code using micromlgen
     c_code = port(model, classmap={0: 'Underweight', 1: 'Overweight', 2: 'Obese Class 1', 3: 'Obese Class 2', 4: 'Obese Class 3'})
     print(c_code)

     # Save the model to a file named 'model.h'
     with open('model.h', 'w') as f:
          f.write(c_code)

     ```

   - Convert the trained model to C code using `microMLgen` as shown above.
   - Save the generated model code as `model.h` and place it in the same directory as your `.ino` file.

4. **Upload the code to ESP32:**

   Connect your ESP32 to your computer and upload the code using Arduino IDE.

5. **Open Serial Monitor:**

   Open the Serial Monitor from Arduino IDE (set the baud rate to 115200).

6. **Enter the data:**

   Enter the input data (Age, Height, Weight, BMI) in the Serial Monitor. The ESP32 will read the data, make a prediction, and display the predicted class.

## Example

```cpp
#include <Arduino.h>
#include "model.h" // Include file model.h

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait until Serial Monitor opens
  }

  Serial.println("Enter data for prediction (Age, Height, Weight, BMI):");

  // Create model object
  Eloquent::ML::Port::RandomForest model;

  // Loop to receive input from Serial Monitor
  while (Serial.available() == 0) {
    ; // Wait until data is available
  }

  // Read input from Serial Monitor
  float age, height, weight, bmi;
  if (Serial.available() > 0) {
    age = Serial.parseFloat();
    height = Serial.parseFloat();
    weight = Serial.parseFloat();
    bmi = Serial.parseFloat();
  }

  // Display data to be predicted
  Serial.print("Data to be predicted: ");
  Serial.print("Age: ");
  Serial.print(age);
  Serial.print(", Height: ");
  Serial.print(height);
  Serial.print(", Weight: ");
  Serial.print(weight);
  Serial.print(", BMI: ");
  Serial.println(bmi);

  // Predict class
  float data[] = {age, height, weight, bmi};
  int predictedClass = model.predict(data);

  // Convert class to readable label
  const char* predictedLabel = model.idxToLabel(predictedClass);

  // Display prediction result
  Serial.print("Predicted class: ");
  Serial.println(predictedLabel);
}

void loop() {
  // Leave loop empty as we only want to predict once in setup
}
```

## Simulation

You can also simulate this project using [Wokwi](https://wokwi.com). Here's the link to the simulation: [Wokwi Simulation](https://wokwi.com/projects/400719706545722369).

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

