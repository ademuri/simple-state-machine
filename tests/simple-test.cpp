#include "gtest/gtest.h"

// Arduino compatibility
uint32_t millis_ = 0;

uint32_t millis() {
  return millis_;
}

#include "../src/state-manager.h"
#include "../src/state.h"

enum class Events {
  kTimer,
  kForceOn,
};

struct Context {};

TEST(SimpleTest, does_not_crash) {
  bool output = false;

  State<Context, Events>* on = new State<Context, Events>("on", {}, [&output](Context* context, bool state_changed) {
    output = true;
    return 1;
  });

  State<Context, Events>* off = new State<Context, Events>("off", {}, [&output](Context* context, bool state_changed) {
    output = false;
    return 1;
  });

  on->transitions[Events::kTimer] = off;
  on->transitions[Events::kForceOn] = State<Context, Events>::NO_CHANGE;

  off->transitions[Events::kTimer] = on;
  off->transitions[Events::kForceOn] = on;

  StateManager<Context, Events, Events::kTimer>* state_manager;
  state_manager = new StateManager<Context, Events, Events::kTimer>(off, new Context());

  bool expected_output = false;
  for (int i = 0; i < 100000; i++) {
    state_manager->Run();
    EXPECT_EQ(output, expected_output) << "iteration: " << i;
    expected_output = !expected_output;
    millis_ += 2;
  }
}
