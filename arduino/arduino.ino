const int PIN_OFFSET = 2; // The lowest value pin we're using
const int POSITIVE = 1;
const int NEGATIVE = 0;
const int OFF = -1;
const int PINS = 4; // How many pins we are using in the Charlieplex
const int STREET_RELAY = 8; // Relay controlling street lights
const int CAR_PARK_RELAY = 9; // Relay controlling car park lights
const int FRONTINGTON_RELAY = 10; // Relay controlling Frontington platform lamps
const int AM_LED = 11; // LED indicating morning
const int PM_LED = 12; // LED indicating afternoon
const int BUTTON = 13; // Push button to cycle through times of day

const int TIME_FACTOR = 6000; // How long time takes

// The Charlieplexed pin pattern for each LED
const int LEDS = 12;
int leds[LEDS][PINS] = {
    {POSITIVE, NEGATIVE, OFF, OFF}, // 0: Museum
    {NEGATIVE, POSITIVE, OFF, OFF}, // 1: Engine shed
    {POSITIVE, OFF, NEGATIVE, OFF}, // 2: Booking hall
    {NEGATIVE, OFF, POSITIVE, OFF}, // 3: Model railway
    {OFF, POSITIVE, NEGATIVE, OFF}, // 4: Backwoods waiting room
    {OFF, NEGATIVE, POSITIVE, OFF}, // 5: Frontington Signal Box
    {POSITIVE, OFF, OFF, NEGATIVE}, // 6: House 1 upstairs
    {NEGATIVE, OFF, OFF, POSITIVE}, // 7: House 1 downstairs
    {OFF, POSITIVE, OFF, NEGATIVE}, // 8: House 2 upstairs
    {OFF, NEGATIVE, OFF, POSITIVE}, // 9: House 2 downstairs
    {OFF, OFF, POSITIVE, NEGATIVE}, // 10: Bungalow
    {OFF, OFF, NEGATIVE, POSITIVE}, // 11: ?
};

// Time of last button press
long lastButtonPress = 0;

// Our current position for looping through the LEDs
int position = 0;

// Initialise all LED states off
bool states[LEDS] = {false};
bool relays[3] {
    false, // 0: Street lights
    false, // 1: Car park
    false, // 2: Frontington station
};
// char report[32] = "";
// Time of day
int time = 2; // 0 = night; 1 = morning; 2 = day; 3 = evening

// Control the LEDs
void control() {
    switch (time) {
    case 0:
        night();
        break;
    case 1:
        morning();
        break;
    case 2:
        day();
        break;
    case 3:
        evening();
        break;
    }
}

void night() {
    // Museum off eventually
    if (states[0] && random(6 * TIME_FACTOR) == 0) {
        states[0] = false;
    }
    // Engine shed off eventually
    if (states[1] && random(5 * TIME_FACTOR) == 0) {
        states[1] = false;
    }
    // Booking hall off when everything else in Frontington is off
    if (!states[0] && !states[3] && !relays[1] && !relays[2] && random(2 * TIME_FACTOR) == 0) {
        states[2] = false;
    }
    // Model railway off eventually
    if (states[3] && random(5 * TIME_FACTOR) == 0) {
        states[3] = false;
    }
    // Backwoods waiting room off eventually
    if (states[4] && random(5 * TIME_FACTOR) == 0) {
        states[4] = false;
    }
    // Frontington SB off after engine shed
    if (states[5] && !states[1] && random(2 * TIME_FACTOR) == 0) {
        states[5] = false;
    }
    // House lights mostly off
    for (int i = 6; i <= 10; i++) {
        if (!states[i] && random(10 * TIME_FACTOR) == 0) {
            states[i] = true;
        }
        if (states[i] && random(4 * TIME_FACTOR) == 0) {
            states[i] = false;
        }
    }
    // Street lights on
    relays[0] = true;
    // Car park off when nearly everything else is off
    if (relays[1] && !relays[2] && !states[0] && !states[3] && random(2 * TIME_FACTOR) == 0) {
        relays[1] = false;
    }
    // Frontington platform off eventually
    if (relays[2] && !states[3] && random(2 * TIME_FACTOR) == 0) {
        relays[2] = false;
    }
}

void morning() {
    // Museum on after booking hall
    if (!states[0] && states[2] && random(3 * TIME_FACTOR) == 0) {
        states[0] = true;
    }
    // Engine shed on pretty early
    if (!states[1] && random(2 * TIME_FACTOR) == 0) {
        states[1] = true;
    }
    // Booking hall on pretty early
    if (!states[2] && random(3 * TIME_FACTOR) == 0) {
        states[2] = true;
    }
    // Model railway on after booking hall
    if (!states[3] && states[2] && random(3 * TIME_FACTOR) == 0) {
        states[3] = true;
    }
    // Backwoods on eventually
    if (!states[4] && random(6 * TIME_FACTOR) == 0) {
        states[4] = true;
    }
    // Frontington SB on after engine shed
    if (!states[5] && states[1] && random(2 * TIME_FACTOR) == 0) {
        states[5] = true;
    }
    // House lights mostly on
    for (int i = 6; i <= 10; i++) {
        if (!states[i] && random(1 * TIME_FACTOR) == 0) {
            states[i] = true;
        }
        if (states[i] && random(10 * TIME_FACTOR) == 0) {
            states[i] = false;
        }
    }
    // Street lights on
    relays[0] = true;
    // Car park on after booking hall
    if (!relays[1] && states[2] && random(2 * TIME_FACTOR) == 0) {
        relays[1] = true;
    }
    // Frontington platform on after booking hall
    if (!relays[2] && states[2] && random(3 * TIME_FACTOR) == 0) {
        relays[2] = true;
    }
}

void day() {
    // Museum on
    states[0] = true;
    // Engine shed on
    states[1] = true;
    // Booking hall on
    states[2] = true;
    // Model railway on
    states[3] = true;
    // Backwoods off
    if (states[4] && random(2 * TIME_FACTOR) == 0) {
        states[4] = false;
    }
    // Frontington SB off
    if (states[5] && random(2 * TIME_FACTOR) == 0) {
        states[5] = false;
    }
    // House lights off
    for (int i = 6; i <= 10; i++) {
        if (states[i] && random(2 * TIME_FACTOR) == 0) {
            states[i] = false;
        }
    }
    // Street lights off
    relays[0] = false;
    // Car park off
    if (relays[1] && random(2 * TIME_FACTOR) == 0) {
        relays[1] = false;
    }
    // Frontington platform off
    if (relays[2] && random(2 * TIME_FACTOR) == 0) {
        relays[2] = false;
    }
}

void evening() {
    // Museum on
    states[0] = true;
    // Engine shed on
    states[1] = true;
    // Booking hall on
    states[2] = true;
    // Model railway on
    states[3] = true;
    // Backwoods on
    if (!states[4] && random(4 * TIME_FACTOR) == 0) {
        states[4] = true;
    }
    // Frontington SB on
    if (!states[5] && random(1 * TIME_FACTOR) == 0) {
        states[5] = true;
    }
    // House lights mostly on
    for (int i = 6; i <= 10; i++) {
        if (!states[i] && random(2 * TIME_FACTOR) == 0) {
            states[i] = true;
        }
        if (states[i] && random(10 * TIME_FACTOR) == 0) {
            states[i] = false;
        }
    }
    // Street lights on
    relays[0] = true;
    // Car park on
    if (!relays[1] && random(2 * TIME_FACTOR) == 0) {
        relays[1] = true;
    }
    // Frontington platform on
    if (!relays[2] && random(1 * TIME_FACTOR) == 0) {
        relays[2] = true;
    }
}

// Run once when the Arduino boots up
void setup() {
    randomSeed(analogRead(0)); // Ensure randomness
    pinMode(CAR_PARK_RELAY, OUTPUT);
    pinMode(FRONTINGTON_RELAY, OUTPUT);
    pinMode(STREET_RELAY, OUTPUT);
    pinMode(AM_LED, OUTPUT);
    pinMode(PM_LED, OUTPUT);
    pinMode(BUTTON, INPUT);
    digitalWrite(AM_LED, HIGH);
    digitalWrite(PM_LED, HIGH);
}

// Run indefinitely
void loop() {
    delay(1); // Pause ever so slightly to cater for slow response of some LEDs

    // Advance time of day if button is pressed
    // int buttonPress = digitalRead(BUTTON);
    if (digitalRead(BUTTON) == HIGH && (lastButtonPress + 2000) < millis()) {
        lastButtonPress = millis();
        time++;
        if (time == 4) {
            time = 0;
        }
    }
    // Set time LEDs
    digitalWrite(AM_LED, ((time > 0 && time < 3) ? HIGH : LOW));
    digitalWrite(PM_LED, ((time > 1) ? HIGH : LOW));

    control();

    // Set relays
    digitalWrite(STREET_RELAY, (relays[0] ? LOW : HIGH));
    digitalWrite(CAR_PARK_RELAY, (relays[1] ? LOW : HIGH));
    digitalWrite(FRONTINGTON_RELAY, (relays[2] ? LOW : HIGH));

    // Turn all pins off
    for (size_t i = 0; i < PINS; i++)
    {
        pinMode((PIN_OFFSET + i), INPUT);
        digitalWrite((PIN_OFFSET + i), LOW);
    }
    
    // Loop through all the pins
    for (size_t i = 0; i < PINS; i++)
    {
        // If the current LED requires this pin to be disabled, set it to an input
        if (!states[position] || leds[position][i] == OFF) {
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