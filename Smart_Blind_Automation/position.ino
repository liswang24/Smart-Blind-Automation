void updatePosition(void){
  // Read current state
  currStateA = digitalRead(outputA);
  currStateB = digitalRead(outputB);

  // Update position if pulse has occured
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