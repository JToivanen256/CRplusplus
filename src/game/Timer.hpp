#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
public:
  Timer(float duration);
  void start();
  void reset();

  float getRemainingTime() const;

private:
  float elapsedTime_;
  float duration_;
};

#endif