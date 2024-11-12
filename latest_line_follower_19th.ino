// File: line_follower_robot.ino

const int sensorPins[5] = {A0, A1, A2, A3, A4};
const int rightMotorForward = 10;
const int rightMotorBackward = 11;
const int leftMotorForward = 5;
const int leftMotorBackward = 6;

const int leftMotorSpeed = 70;
const int rightMotorSpeed = 70;
const int threshold = 600;

bool sensorValues[5];

void setup() {
    for (int i = 0; i < 5; i++) {
        pinMode(sensorPins[i], INPUT);
    }
    pinMode(rightMotorForward, OUTPUT);
    pinMode(rightMotorBackward, OUTPUT);
    pinMode(leftMotorForward, OUTPUT);
    pinMode(leftMotorBackward, OUTPUT);
}

void loop() {
    readSensors();
    controlMotors();
}

void readSensors() {
    for (int i = 0; i < 5; i++) {
        sensorValues[i] = analogRead(sensorPins[i]) < threshold;
    }
}

void controlMotors() {
    bool s1 = sensorValues[0]; // Rightmost sensor
    bool s2 = sensorValues[1];
    bool s3 = sensorValues[2]; // Center sensor
    bool s4 = sensorValues[3];
    bool s5 = sensorValues[4]; // Leftmost sensor

    if ((s3 && !s1 && !s2 && !s4 && !s5) ||  // Only center sensor detects black
        (s1 && s2 && s3 && s4 && s5) ||      // All sensors detect black (crossing)
        (!s1 && !s2 && !s3 && !s4 && !s5)) { // All sensors detect white (blank section)
        // Move forward
        moveForward();
    }
    else if (s2 && !s3 && !s4 && !s1 && !s5) {
        // Slight right adjustment if only the second sensor (A1) detects black
        turnSlightRight();
    }
    else if (s4 && !s3 && !s2 && !s1 && !s5) {
        // Slight left adjustment if only the fourth sensor (A3) detects black
        turnSlightLeft();
    }
    else if ((s2 && s3) || s2) {
        // Slight right
        turnSlightRight();
    }
    else if (s1) {
        // Sharp right
        turnSharpRight();
    }
    else if ((s3 && s4) || s4) {
        // Slight left
        turnSlightLeft();
    }
    else if (s5) {
        // Sharp left
        turnSharpLeft();
    }
    else {
        // Default action
        moveForward();
    }
}

void moveForward() {
    analogWrite(rightMotorForward, rightMotorSpeed);
    digitalWrite(rightMotorBackward, LOW);
    analogWrite(leftMotorForward, leftMotorSpeed);
    digitalWrite(leftMotorBackward, LOW);
}

void turnSlightRight() {
    analogWrite(rightMotorForward, rightMotorSpeed / 2);
    digitalWrite(rightMotorBackward, LOW);
    analogWrite(leftMotorForward, leftMotorSpeed);
    digitalWrite(leftMotorBackward, LOW);
}

void turnSharpRight() {
    analogWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, rightMotorSpeed / 2);
    analogWrite(leftMotorForward, leftMotorSpeed);
    digitalWrite(leftMotorBackward, LOW);
}

void turnSlightLeft() {
    analogWrite(rightMotorForward, rightMotorSpeed);
    digitalWrite(rightMotorBackward, LOW);
    analogWrite(leftMotorForward, leftMotorSpeed / 2);
    digitalWrite(leftMotorBackward, LOW);
}

void turnSharpLeft() {
    analogWrite(rightMotorForward, rightMotorSpeed);
    digitalWrite(rightMotorBackward, LOW);
    analogWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, leftMotorSpeed / 2);
}

void stopMotors() {
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
}
