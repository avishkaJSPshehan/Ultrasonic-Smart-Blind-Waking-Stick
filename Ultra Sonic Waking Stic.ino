// Pin definitions
const int trigPin_1 = 2;
const int echoPin_1 = 5;
const int trigPin_2 = 3;
const int echoPin_2 = 6;
const int trigPin_3 = 4;
const int echoPin_3 = 7;
const int motorPin = 11;
const int buzzer = 10;

// Function to initialize pin modes and serial communication
void setup() {
    pinMode(trigPin_1, OUTPUT); 
    pinMode(echoPin_1, INPUT);
    pinMode(trigPin_2, OUTPUT); 
    pinMode(echoPin_2, INPUT);
    pinMode(trigPin_3, OUTPUT); 
    pinMode(echoPin_3, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(motorPin, OUTPUT);

    Serial.begin(9600);
}

// Main loop function
void loop() {
    int sensor_1 = get_distance(trigPin_1, echoPin_1);
    int sensor_2 = get_distance(trigPin_2, echoPin_2);
    int sensor_3 = get_distance(trigPin_3, echoPin_3);

    check_and_actuate(sensor_1, "1 working => ");
    check_and_actuate(sensor_2, "2 working => ");
    check_and_actuate(sensor_3, "3 working => ");
}

// Function to measure distance using ultrasonic sensor
int get_distance(int trig_pin, int echo_pin) {
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);

    long duration = pulseIn(echo_pin, HIGH);
    int distance = duration * 0.034 / 2;

    return distance;
}

// Function to check distance and actuate motor and buzzer if within threshold
void check_and_actuate(int distance, const char* message) {
    if (distance < 30) {
        Serial.print(message);
        Serial.println(distance);

        tone(buzzer, 1000);
        analogWrite(motorPin, 255);
        delay(300);
        noTone(buzzer);
        analogWrite(motorPin, 0);
    }
}
