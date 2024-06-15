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