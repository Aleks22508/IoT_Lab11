// =====================================================================
// Lab 11 – Arrays, Loops and JSON  (STARTER FILE)
// IoT I – Dawson College – Electrical Engineering Technology
//
// Build this program one part at a time, following the lab procedure.
// Each comment below marks where the code from the procedure goes.
// =====================================================================
#include <Arduino.h>
#include <ArduinoJson.h>   // added with lib_deps in platformio.ini

// ----- Pins ----------------------------------------------------------
// Replace each ___ with the GPIO number from the tables in Part II.
#define BUTTON_PIN  32   // push button (to GND)
#define POT_PIN     34   // potentiometer wiper (analog input)
// The four LED pins are stored in an array (Global variables, Part III).

// ----- Global variables ----------------------------------------------
// Part III – LED pins array

const int LED_PINS[4] = {16, 17, 18, 19};
const int NUM_LEDS = 4;
const int STEP_TIME = 200;

// Part IV – samples array

const int NUM_SAMPLES = 10;
int samples[NUM_SAMPLES];

// ----- Helper functions ----------------------------------------------
// Part III – showLevel()

void showLevel(int level)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (i < level)
    {
      digitalWrite(LED_PINS[i], HIGH);
    }
    else
    {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
}

// Part IV – takeSamples(), printSamples(), getAverage(),
//           getMinimum(), getMaximum()

void takeSamples()
{
  for (int i = 0; i < NUM_SAMPLES; i++)
  {
    samples[i] = analogRead(POT_PIN);
    delay(50);
  }
}

void printSamples()
{
  for (int i = 0; i < NUM_SAMPLES; i++)
  {
    Serial.print("samples[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(samples[i]);
  }
}

float getAverage()
{
  long sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++)
  {
    sum = sum + samples[i];
  }
  return (float)sum / NUM_SAMPLES;
}

int getMinimum()
{
  int smallest = samples[0];
  for (int i = 1; i < NUM_SAMPLES; i++)
  {
    if (samples[i] < smallest)
    {
      smallest = samples[i];
    }
  }
  return smallest;
}


int getMaximum()
{
  int largest = samples[0];
  for (int i = 1; i < NUM_SAMPLES; i++) {
    if (samples[i] > largest) {
      largest = samples[i];
    }
  }
  return largest;
}

// Part V – sendReport()


// Part IV – runMeasurement()

void runMeasurement()
{
  takeSamples();

  float average = getAverage();
  int minimum = getMinimum();
  int maximum = getMaximum();

  int level = map((int)average, 0, 4096, 0, NUM_LEDS + 1);
  showLevel(level);

  printSamples();
  Serial.print("Average: ");   Serial.println(average);
  Serial.print("Minimum: ");   Serial.println(minimum);
  Serial.print("Maximum: ");   Serial.println(maximum);
  Serial.print("Level: ");     Serial.println(level);
}

// Part V – handleCommand() and checkSerial()


void setup()
{
  Serial.begin(115200);

  // Inputs and outputs

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    pinMode(LED_PINS[i], OUTPUT);
  }

  Serial.println("Lab 11, Arrays, Loops and JSON");

}

void loop()
{

  // Part III – LED patterns (for loops)


  // Part IV – Wait for the button, then measure (while loops)

Serial.println("Press the button to measure...");

while (digitalRead(BUTTON_PIN) == HIGH)
{
  delay(10);
}
delay(50);

runMeasurement();

while (digitalRead(BUTTON_PIN) == LOW)
{
  delay(10);

}
  delay(50);
}