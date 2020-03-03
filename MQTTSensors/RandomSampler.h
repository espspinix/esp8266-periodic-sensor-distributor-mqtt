#include "SensorSampler.h"

class RandomSampler : public SensorSampler {
  int value;
  int minRandom;
  int maxRandom;

  public:
  enum Variables { VALUE };
  const char * name = "Random";

  RandomSampler(int myMin = 0, int myMax = 100) : SensorSampler(2000) {
    minRandom = myMin;
    maxRandom = myMax;
  }

  String get(int variable) {
    switch(variable) {
      case VALUE:
        return String(value);
    }

    return "";
  }

  const char * getName() {
    return name;
  }

  int readVariables() {
    value = random(minRandom, maxRandom);

    return true;
  }
};
