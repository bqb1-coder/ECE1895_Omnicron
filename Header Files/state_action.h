#ifndef STATE_ACTION_H
#define STATE_ACTION_H

enum class State : uint8_t {
  WAITING,
  INIT,
  VERIFY,
  CMD,
  EXEC,
  COUNT
};

enum class Action : uint8_t {
  NONE,
  VOLUME,
  IDOLS,
  COUNT
};

#endif