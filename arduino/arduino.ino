const int PIN_OFFSET = 2; // The lowest value pin we're using
const int POSITIVE = 1;
const int NEGATIVE = 0;
const int OFF = -1;
const int PINS = 2; // How many pins we are using in the Charlieplex

// The Charlieplexed pin pattern for each LED
int leds[2][PINS] = {
    {POSITIVE, NEGATIVE},
    {NEGATIVE, POSITIVE}
};

// Our current position for looping through the LEDs
int position = 0;

void setup() {
}

void loop() {
    // Loop through all the pins
    for (size_t i = 0; i < (PINS - 0); i++)
    {
        // If the current LED requires this pin to be disabled, set it to an input
        if (leds[position][i] == OFF) {
            pinMode((PIN_OFFSET + i), INPUT);
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
    if (position >= PINS) {
        position = 0;
    }
}