float PULSE_FREQUENCY = 10.0;

float CARRIER_FREQUENCY = 10000.0;
float CARRIER_DUTY_CYCLE = 0.5;

float ON_OFF_FREQUENCY = 0.1;
float ON_OFF_DUTY_CYCLE = 0.05;

float MODULATION_INDEX = 1.0;

int output_pin = 6;

float duty_cycle = 0.5;

float getPulseValue(unsigned long time, float frequency, float duty_cycle);

void setup()
{
  Serial.begin(9600);
  pinMode(output_pin, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'w') {
      // Increase PULSE_FREQUENCY
      PULSE_FREQUENCY += 1.0;
    } else if (command == 's') {
      if (PULSE_FREQUENCY >= 1)
      {
        // Decrease PULSE_FREQUENCY
        PULSE_FREQUENCY -= 1.0;
      }
    } else if (command == 'd') {
      // Increase duty cycle
      duty_cycle += 0.1;
      if (duty_cycle > 1.0) {
        duty_cycle = 1.0; // Ensure duty cycle is within valid range
      }
    } else if (command == 'a') {
      // Decrease duty cycle
      duty_cycle -= 0.1;
      if (duty_cycle < 0.0) {
        duty_cycle = 0.0; // Ensure duty cycle is within valid range
      }
    }
  }

  float current_time = micros();
  float pulse_signal = getPulseValue(current_time, PULSE_FREQUENCY, duty_cycle);
  float carrier_signal = getPulseValue(current_time, CARRIER_FREQUENCY, CARRIER_DUTY_CYCLE);
  float on_off_signal = getPulseValue(current_time, ON_OFF_FREQUENCY, ON_OFF_DUTY_CYCLE);
  float modulated_signal = pulse_signal * (1 + MODULATION_INDEX * carrier_signal);

  modulated_signal = modulated_signal*on_off_signal;
  int pwm_value = map(modulated_signal, 0, 1 + MODULATION_INDEX, 0, 254);

  Serial.print("Pulse Frequency: ");
  Serial.print(PULSE_FREQUENCY, 1); // Display one decimal place
  Serial.print(" Hz, Duty Cycle: ");
  Serial.print(duty_cycle, 1); // Display one decimal place
  Serial.println(on_off_signal);

  analogWrite(output_pin, pwm_value);
}


float getPulseValue(unsigned long time, float frequency, float duty_cycle) {
  unsigned long periodMicros = round(1000000.0 / frequency);
  unsigned long highTimeMicros = round(periodMicros * duty_cycle);

  unsigned long currentTimeWithinPeriod = time % periodMicros;

  if (currentTimeWithinPeriod < highTimeMicros) {
    return 1.0; // High level during pulse
  } else {
    return 0.0; // Low level outside of pulse
  }
}
