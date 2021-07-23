void updatePosition(void){
  // Read current state
  currStateA = digitalRead(outputA);
  currStateB = digitalRead(outputB);

  // Update position if pulse has occured
  if (currStateA != prevStateA){
    // TODO: update direction based on mounting
    if (currStateB!= currStateA){
      blindsPosition++;
    }
    else {
      blindsPosition--;
    }
  }
  // Update previous state with current state
  prevStateA=currStateA;
}