void updatePosition(void){
  // Read current state
  currStateA = digitalRead(OUTPUT_A);
  currStateB = digitalRead(OUTPUT_B);

  // Update position if pulse has occurred
  if (currStateA != prevStateA){
    if (currStateB!= currStateA){
      blindsPosition--;
    }
    else {
      blindsPosition+=0.95;
    }
  }
  // Update previous state with current state
  prevStateA=currStateA;
}