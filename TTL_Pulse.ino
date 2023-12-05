float PULSE_FREQUENCY = 10.0
float CARRIER_FREQUENCY 5000.0
float MODULATION_INDEX = 1.0
int output_pin = 13;

int sin_func(float freq);

void setup()
{
  pinMode(output_pin, OUTPUT);
}

void loop()
{
  int carrier_signal = 1 + sin_func(CARRIER_FREQUENCY); // here I'm defining the carrier signal as a sine wave
  int pulse_signal = 1 + sin_func(PULSE_FREQUENCY); // here I'm defining the pulse signal as a sine wave
  int modulated_signal = pulse_signal * (1+MODULATION_INDEX*carrier_signal); // here I'm defining the modulated signal 
  analogWrite(output_pin, modulated_signal)
}


int sin_func(float freq)
{
  int signal = sin(2*PI*freq*millis()/10000);
  return signal
}















