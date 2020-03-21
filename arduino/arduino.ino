const int PIN_OFFSET = 2; // The lowest value pin we're using
const int POSITIVE = 1;
const int NEGATIVE = 0;
const int OFF = -1;
const int PINS = 3; // How many pins we are using in the Charlieplex

// The Charlieplexed pin pattern for each LED
const int LEDS = 6;
int leds[LEDS][PINS] = {
    {POSITIVE, NEGATIVE, OFF}, // LED 1
    {NEGATIVE, POSITIVE, OFF}, // LED 2
    {OFF, POSITIVE, NEGATIVE}, // Lamp
    {OFF, NEGATIVE, POSITIVE}, // Streetlight
    {POSITIVE, OFF, NEGATIVE}, // LED 5
    {NEGATIVE, OFF, POSITIVE}  // LED 6
};

// Our current position for looping through the LEDs
int position = 0;

int states[LEDS] = {0, 0, 0, 0, 0, 0};
void control() {
    // LED 1 comes on immediately
    states[0] = 1;

    // LED 2 comes on after 2 seconds
    if (millis() > 2000) {
        states[1] = 1;
    }

    // Lamp comes on after 3 seconds
    if (millis() > 3000) {
        states[2] = 1;
    }

    // Streetlight comes on after a while
    if (random(10000) == 0) {
        states[3] = 1;
    }

    // LED 5 flashes randomly
    if (random(10000) == 0) {
        states[4] = !states[4];
    }

    // LED 6 flashes every 20 seconds
    if ((int)(millis() / 20000) % 2 == 0) {
        states[5] = 0;
    } else {
        states[5] = 1;
    }
}

void setup() {
    randomSeed(analogRead(0)); // Ensure randomness
}

void loop() {
    delay(2); // Pause ever so slightly to cater for slow response of some LEDs

    control();

    // Turn everything off
    for (size_t i = 0; i < PINS; i++)
    {
        pinMode((PIN_OFFSET + i), INPUT);
        digitalWrite((PIN_OFFSET + i), LOW);
    }
    
    // Loop through all the pins
    for (size_t i = 0; i < PINS; i++)
    {
        // If the current LED requires this pin to be disabled, set it to an input
        if (states[position] == 0 || leds[position][i] == OFF) {
            pinMode((PIN_OFFSET + i), INPUT);
            digitalWrite((PIN_OFFSET + i), LOW);
        }
        else {
            // Otherwise, set it high or low to power an LED
            pinMode((PIN_OFFSET + i), OUTPUT);
            if (leds[position][i] == POSITIVE) {
                digitalWrite((PIN_OFFSET + i), HIGH);
            } else {
                digitalWrite((PIN_OFFSET + i), LOW);
            }
        }
    }

    // Go to the next LED, or wrap round to the first one
    position++;
    if (position >= LEDS) {
        position = 0;
    }
}