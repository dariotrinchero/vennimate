/**
 * @file    circles.c
 * @brief   Animation exhibiting arrangements of 4 circles in affine plane.
 *
 * Implementation of functions to animate between arrangements of 4 circles in
 * the affine plane.
 *
 * @author  D. Trinchero (dario.trinchero@pm.me)
 * @date    2020-05-31
 */

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "circles.h"
#include "random.h"

/* --- user-set parameters -------------------------------------------------- */

#define CIRCLE_PTS 250
#define SCALE      14.5
#define ALPHA      0.27f
#define FRAMERATE  60

double animDuration = 2.7;
double nonLinearity = 18;

/* --- precomputed constants ------------------------------------------------ */

unsigned int refreshMillis;
unsigned int animFrames;

/* --- animation trackers --------------------------------------------------- */

unsigned int currGroupIdx = 0;
unsigned int currAnimFrame = 0;

/* --- initialization routines ---------------------------------------------- */

void circInit(void) {
	unsigned int i, j, k, tmp;
	int idx;
	double avCoord;

	// subtract average group position
	for (i = 0 ; i < NUM_GROUPS; i++) {
		for (k = 0; k < 2; k++) {
			avCoord = 0;
			for (j = 0; j < 4; j++) avCoord += circleGroups[i][j][k];
			for (j = 0; j < 4; j++) circleGroups[i][j][k] -= avCoord / 4.0;
		}
	}
	
	// initialize & Fisher-Yates shuffle circle group order
	for (i = 0; i < NUM_GROUPS; i++) groupOrder[i] = i;
	for (i = 0; i < NUM_GROUPS - 1; i++) {
		idx = rnd_int32(i, NUM_GROUPS);
		tmp = groupOrder[idx];
		groupOrder[idx] = groupOrder[i];
		groupOrder[i] = tmp;
	}
}

void animInit(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA);

	glutCreateWindow("Circles");
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE); // TODO (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)?

	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glDisable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 0.0);
}

/* --- animation routines --------------------------------------------------- */

void drawCircle(double cx, double cy, double r) {
	unsigned int i;
	double theta = 2 * M_PI / CIRCLE_PTS;
	double c = cos(theta), s = sin(theta);
	double x = r, y = 0;
	double t;

	glBegin(GL_TRIANGLE_FAN);
	glColor4f(1, 1, 1, ALPHA);
	for (i = 0; i < CIRCLE_PTS; i++) {
		glVertex2f(x + cx, y + cy);
		// apply rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}

double animEase(double t, double nonLinearity) {
	if (t < 0.5) return 0.5 * pow(2 * t, nonLinearity);
	else return 1 - 0.5 * pow(2 * (1 - t), nonLinearity);
}

void animDisplay(void) {
	double interpolateStep;
	unsigned int nextGroupIdx;
	double (*currGroup)[3], (*nextGroup)[3];

	glClear(GL_COLOR_BUFFER_BIT);

	interpolateStep = animEase(currAnimFrame / (double) animFrames, nonLinearity);
	nextGroupIdx = (currGroupIdx + 1) % NUM_GROUPS;
	currGroup = circleGroups[groupOrder[currGroupIdx]];
	nextGroup = circleGroups[groupOrder[nextGroupIdx]];

	for (int j = 0; j < 4; j++) {
		drawCircle(
			currGroup[j][0] * (1 - interpolateStep) + nextGroup[j][0] * interpolateStep,
			currGroup[j][1] * (1 - interpolateStep) + nextGroup[j][1] * interpolateStep,
			currGroup[j][2] * (1 - interpolateStep) + nextGroup[j][2] * interpolateStep
		);
	}

	currAnimFrame = (currAnimFrame + 1) % animFrames;
	if (!currAnimFrame) currGroupIdx = nextGroupIdx;

	glutSwapBuffers(); // double-buffering for smoother animation
}

void animReshape(GLsizei width, GLsizei height) {
	double aspect = width / (double) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);

	if (width <= height) {
		gluOrtho2D(-SCALE, SCALE, -aspect * SCALE, aspect * SCALE);
	} else {
		gluOrtho2D(-aspect * SCALE, aspect * SCALE, -SCALE, SCALE);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// TODO control animFrames & nonLinearity with keys
void animKeyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27: // esc
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
	}
}

void animTimer(int value) {
	glutPostRedisplay();
	glutTimerFunc(refreshMillis, animTimer, 0);
}

/* --- main method ---------------------------------------------------------- */

int main(int argc, char *argv[]) {
	// calculate precomputed constants
	refreshMillis = 1000 / FRAMERATE;
	animFrames = animDuration * FRAMERATE;

	// run initialization functions
	glutInit(&argc, argv);
	rnd_init();
	circInit();
	animInit();

	// register functions & enter main loop
	glutReshapeFunc(animReshape);
	glutKeyboardFunc(animKeyboard);
	glutDisplayFunc(animDisplay);
	glutTimerFunc(0, animTimer, 0);
	glutMainLoop();
	return EXIT_SUCCESS;
}
