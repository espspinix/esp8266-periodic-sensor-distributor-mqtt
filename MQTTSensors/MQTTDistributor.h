#include "MQTTClient.h"

struct MQTTInstruction {
  const char * address;
  SensorSampler * module;
  int variable;
};

class MQTTDistributor {
  int distributionFrequency = 2000;
  unsigned long previousMillis = 0;

  MQTTInstruction * instructions;
  int instructionsCount;

  public: MQTTDistributor(MQTTInstruction * myInstructions, int instructionsLength) {
    instructions = myInstructions;
    instructionsCount = instructionsLength / sizeof(MQTTInstruction);
  }

  void update() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis < distributionFrequency) {
      return;
    }

    for(int instructionId = 0; instructionId < instructionsCount;instructionId++) {
      MQTTInstruction instruction = instructions[instructionId];

      const char * address = instruction.address;
      SensorSampler * module = instruction.module;
      int variable = instruction.variable;

      if (!MQTTClient::publish(address, module->get(variable).c_str())) {
        return;
      }
    }

    previousMillis = currentMillis;
  }
};
