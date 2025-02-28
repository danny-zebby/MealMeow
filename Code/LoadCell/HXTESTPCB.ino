byte GAIN;		// amplification factor
long OFFSET = 0;	// used for tare weight
float SCALE = 1;
const int DOUT = PIN_PA4;
const int PD_SCK = PIN_PA5;

bool is_ready() {
	return digitalRead(DOUT) == LOW;
}

#if FAST_CPU
uint8_t shiftInSlow(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
    uint8_t value = 0;
    uint8_t i;

    for(i = 0; i < 8; ++i) {
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(1);
        if(bitOrder == LSBFIRST)
            value |= digitalRead(dataPin) << i;
        else
            value |= digitalRead(dataPin) << (7 - i);
        digitalWrite(clockPin, LOW);
        delayMicroseconds(1);
    }
    return value;
}
#define SHIFTIN_WITH_SPEED_SUPPORT(data,clock,order) shiftInSlow(data,clock,order)
#else
#define SHIFTIN_WITH_SPEED_SUPPORT(data,clock,order) shiftIn(data,clock,order)
#endif

void begin(byte dout, byte pd_sck) {
	pinMode(pd_sck, OUTPUT);
	pinMode(dout, INPUT);
	GAIN = 1;
}

void wait_ready(unsigned long delay_ms) {
	while (!(digitalRead(DOUT) == LOW)) {
		delay(delay_ms);
	}
}

long read() {

	// Wait for the chip to become ready.
	wait_ready(0);

	// Define structures for reading data into.
	unsigned long value = 0;
	uint8_t data[3] = { 0 };
	uint8_t filler = 0x00;

	#if HAS_ATOMIC_BLOCK
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {

	#elif IS_FREE_RTOS
	portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
	portENTER_CRITICAL(&mux);

	#else
	// Disable interrupts.
	noInterrupts();
	#endif

	// Pulse the clock pin 24 times to read the data.
	data[2] = SHIFTIN_WITH_SPEED_SUPPORT(DOUT, PD_SCK, MSBFIRST);
	data[1] = SHIFTIN_WITH_SPEED_SUPPORT(DOUT, PD_SCK, MSBFIRST);
	data[0] = SHIFTIN_WITH_SPEED_SUPPORT(DOUT, PD_SCK, MSBFIRST);

	// Set the channel and the gain factor for the next reading using the clock pin.
	for (unsigned int i = 0; i < GAIN; i++) {
		digitalWrite(PD_SCK, HIGH);
		#if ARCH_ESPRESSIF
		delayMicroseconds(1);
		#endif
		digitalWrite(PD_SCK, LOW);
		#if ARCH_ESPRESSIF
		delayMicroseconds(1);
		#endif
	}

	#if IS_FREE_RTOS
	// End of critical section.
	portEXIT_CRITICAL(&mux);

	#elif HAS_ATOMIC_BLOCK
	}

	#else
	// Enable interrupts again.
	interrupts();
	#endif

	// Replicate the most significant bit to pad out a 32-bit signed integer
	if (data[2] & 0x80) {
		filler = 0xFF;
	} else {
		filler = 0x00;
	}

	// Construct a 32-bit signed integer
	value = ( static_cast<unsigned long>(filler) << 24
			| static_cast<unsigned long>(data[2]) << 16
			| static_cast<unsigned long>(data[1]) << 8
			| static_cast<unsigned long>(data[0]) );

	return static_cast<long>(value);
}

long read_average(byte times) {
	long sum = 0;
	for (byte i = 0; i < times; i++) {
		sum += read();
		// Probably will do no harm on AVR but will feed the Watchdog Timer (WDT) on ESP.
		// https://github.com/bogde/HX711/issues/73
		delay(0);
	}
	return sum / times;
}


void tare() {
  byte times = 10;
	double sum = read_average(times);
  OFFSET = sum;
}

float get_units(byte times) {
	return (read_average(times) -OFFSET)/ SCALE;
}


void setup() {
  pinMode(PIN_PD3, OUTPUT);
  pinMode(PIN_PD1, OUTPUT);

  // Serial.begin(9600);
  // Serial.println("HX711 Demo");
  // Serial.println("Initializing the scale");

  begin(DOUT, PD_SCK);
  SCALE = 221.66;
  tare();               // reset the scale to 0

  // Serial.println("Readings:");
}

void loop() {
  if(is_ready()){
    digitalWrite(PIN_PD1, LOW); 
    int read = get_units(3);
    if(read > 200){
      digitalWrite(PIN_PD3, HIGH); 
    }
    else{
      digitalWrite(PIN_PD3, LOW); 
    }
    delay(500);
  }else{
    digitalWrite(PIN_PD1, HIGH); 
  }
}