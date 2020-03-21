#define Out1 2

int state;

void setup() {
    state = HIGH;
    pinMode(Out1, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    state = !state;
    digitalWrite(Out1, state);
    digitalWrite(LED_BUILTIN, state);
    delay(500);
}