#include <state-manager.h>

enum class Events {
  kTimer,
  kButton,
};

struct Context {};

StateManager<Context, Events, Events::kTimer>* state_manager;

static const int kLedPin = 13;
static const int kButtonPin = 0;
static const uint32_t kDelay = 1000;

void setup() {
  pinMode(kLedPin, OUTPUT);
  pinMode(kButtonPin, INPUT_PULLUP);

  State<Context, Events>* on = new State<Context, Events>("on", {}, [](Context* context, bool state_changed) {
    digitalWrite(kLedPin, HIGH);
    return kDelay;
  });

  State<Context, Events>* off = new State<Context, Events>("off", {}, [](Context* context, bool state_changed) {
    digitalWrite(kLedPin, LOW);
    return kDelay;
  });

  on->transitions[Events::kTimer] = off;
  on->transitions[Events::kButton] = State<Context, Events>::NO_CHANGE;

  off->transitions[Events::kTimer] = on;
  off->transitions[Events::kButton] = on;
}

void loop() {
  // Note: button uses a pullup resistor, so value is low when button is pressed.
  if (!digitalRead(kButtonPin)) {
    state_manager->HandleEvent(Events::kButton);
  }
  state_manager->Run();

  // Crude debounce for the button
  delay(10);
}
