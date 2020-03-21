const int PIN_OFFSET = 2; // The lowest value pin we're using
const int POSITIVE = 1;
const int NEGATIVE = 0;
const int OFF = -1;
const int PINS = 3; // How many pins we are using in the Charlieplex

// The Charlieplexed pin pattern for each LED
const int LEDS = 6;
int leds[LEDS][PINS] = {
    {POSITIVE, NEGATIVE, OFF},
    {NEGATIVE, POSITIVE, OFF},
    {OFF, POSITIVE, NEGATIVE},
    {OFF, NEGATIVE, POSITIVE},
    {POSITIVE, OFF, NEGATIVE},
    {NEGATIVE, OFF, POSITIVE}
};

// Our current position for looping through the LEDs
int position = 0;

void setup() {
}

void loop() {
    delay(2); // Pause ever so slightly to cater for slow response of some LEDs
    
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
        if (leds[position][i] == OFF) {
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