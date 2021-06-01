// animation parameters
float scaleFactor = 2.5f;
int lerpDuration = 120; // # interpolation frames
float nonLinearity = 18; // 1: linear; >1: snappier transitions
float alpha = 100f; // 0-255

// animation trackers
int currGroup = 0; // incremented mod circleGroups.length
int currLerpFrame = 0; // incremented mod lerpDuration

void setup() {
  fullScreen();
  noCursor();
  smooth(8); // antialiasing
  ellipseMode(RADIUS);
  noStroke();
  fill(255f, alpha);

  // subtract average group position
  for (int i = 0 ; i < circleGroups.length; i++) {
    for (int k = 0; k < 2; k++) {
      float avCoord = 0f;
      for (int j = 0; j < 4; j++) avCoord += circleGroups[i][j][k];
      for (int j = 0; j < 4; j++) circleGroups[i][j][k] -= avCoord / 4;
    }
  }
  
  // Fisher-Yates shuffle circle group order
  for (int i = 0; i < circleGroups.length - 1; i++) {
    int idx = int(random(i, circleGroups.length));
    float[][] tmp = circleGroups[idx];
    circleGroups[idx] = circleGroups[i];
    circleGroups[i] = tmp;
  }
}

void draw() {
  float lerpStep = ease(currLerpFrame / (float) lerpDuration, nonLinearity);
  int nextGroup = (currGroup + 1) % circleGroups.length;
  
  background(0);
  translate(width / 2, height / 2);
  scale(scaleFactor);
  
  for (int j = 0; j < 4; j++) {
    circle(
      circleGroups[currGroup][j][0] * (1 - lerpStep) + circleGroups[nextGroup][j][0] * lerpStep,
      circleGroups[currGroup][j][1] * (1 - lerpStep) + circleGroups[nextGroup][j][1] * lerpStep,
      circleGroups[currGroup][j][2] * (1 - lerpStep) + circleGroups[nextGroup][j][2] * lerpStep
    );
  }
  text(currGroup + 1, 0, 0); // TODO debugging only
  
  currLerpFrame = (currLerpFrame + 1) % lerpDuration;
  if (currLerpFrame == 0) currGroup = nextGroup;
}

// non-linear interpolation
float ease(float p, float g) {
  if (p < 0.5) return 0.5 * pow(2 * p, g);
  else return 1 - 0.5 * pow(2 * (1 - p), g);
}
