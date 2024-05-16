// Replace the dirctory with your own
#include <D:\\Programs\\MinGW\\MinGW\\include\\GL/glut.h>

void init() {
    glEnable(GL_DEPTH_TEST); //3D
    glClearColor(0.0f, 0.3f, 0.0f, 1.0f); //green
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);
}

bool animationEnabled = false;
float animationAngle = 0.0f;    // Angle for animation
float bicycleX = 0.0f;          // Bicycle's x-coordinate
float rightWheelAngle = 0.0f;
float leftWheelAngle = 0.0f;
GLfloat bicycleRotation = 0.0f;   // Bicycle's rotation angle
float windowAngleFirstFloor = 0.0f;// Initially closed
float windowAngleSecondFloor = 0.0f;
void zoomCamera(unsigned char key, int x, int y);

void handleKeyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 'f': // Move forward
            bicycleX += 0.1f;
            break;
        case 'b': // Move backward
            bicycleX -= 0.1f;
            break;
        case 'r': // Steer right
            rightWheelAngle += 5.0f; // Adjust the angle as needed
            break;
        case 'l': // Steer left
            leftWheelAngle += 5.0f; // Adjust the angle as needed
            break;
    }
    glutPostRedisplay(); // Redraw the scene with the new transformations
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        animationEnabled = true;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        animationEnabled = false;
    }
}

// Function to handle key presses for windows
void window_keyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 'O': // Open the windows
            windowAngleFirstFloor = 90.0f; // Set the angle to fully open
            windowAngleSecondFloor = 90.0f;
            break;
        case 'C': // Close the windows
            windowAngleFirstFloor = 0.0f; // Set the angle to fully closed
            windowAngleSecondFloor = 0.0f;
            break;
    }
    glutPostRedisplay(); // Redraw the scene with updated angles
}

float doorAngle = 0.0f; // Initially, the door is closed
void door_keyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 'o': // Open the door
            doorAngle = 90.0f; // Set the angle to fully open
            break;
        case 'c': // Close the door
            doorAngle = 0.0f; // Set the angle to fully closed
            break;
    }
    glutPostRedisplay();// Redraw the scene with updated angles
}

void keyPress(unsigned char key, int x, int y){
    door_keyPress( key,  x,  y);
    window_keyPress( key,  x,  y);
    handleKeyPress( key,  x,  y);
    zoomCamera(key, x, y);
}

void drawDoor(float x, float y, float z, float angle) {
    glColor3f(0.3f, 0.2f, 0.2f); // Set the color of the door
    glPushMatrix();
    glTranslatef(x, y, z); // Move to the door's position
    glTranslatef(-0.05f, 0.0f, 0.0f); // Adjust pivot point to the left edge
    glRotatef(-angle, 0.0f, 1.0f, 0.0f); // Rotate around the y-axis
    glTranslatef(0.05f, 0.0f, 0.0f); // Move back to the original position
    glScalef(0.1f, 0.2f, 0.01f); // Scale to make it look like a door
    glutSolidCube(1.0f); // Draw a solid cube for the door
    glPopMatrix();

    // Draw Shadow for the door
    glColor3f(0.2f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(0.1f, 0.2f, 0);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawWindow(float x, float y, float z, float angle) {
    glColor3f(0.3f, 0.3f, 0.6f); // Set the color of the windows
    glPushMatrix();
    glTranslatef(x - 0.05f, y, z); // Adjust pivot point to the left edge
    glRotatef(-angle, 0.0f, 1.0f, 0.0f); // Rotate in the opposite direction
    glTranslatef(0.05f, 0.0f, 0.0f); // Move back to the original position
    glScalef(0.1f, 0.1f, 0.01f); // Scale to make it look like a window
    glutSolidCube(1.0f); // Draw a solid cube for the window
    glPopMatrix();

    // Draw Shadow for the window
    glColor3f(0.2f, 0.2f, 0.3f);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(0.1f, 0.1f, 0);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawGround() {
    glColor3f(0.6f, 0.6f, 0.6f); // Set the color of the ground
    glPushMatrix();
    glTranslatef(0.0f, -0.05f, 0.0f); // Position the ground slightly below the building base
    glScalef(3.0f, 0.1f, 3.0f); // Scale to make it flat and wide
    glutSolidCube(1.0f); // Draw a solid cube for the ground
    glPopMatrix();
}

void drawBicycle() {
    // Set the color of the bicycle frame to brown
    glColor3f(0.22f, 0.18f, 0.13f);

    // Draw the frame of the bicycle
    glPushMatrix();
    glTranslatef(bicycleX, 0.0f, 0.0f);
    glTranslatef(0.01f, 0.17f, 1.0f); // Position the bicycle frame
    glScalef(0.8f, 0.05f, 0.05f); // Scale to make it look like a frame
    glutSolidCube(0.5f); // Draw a solid cube for the frame
    glPopMatrix();


    // Set the color of the wheels to black
    glColor3f(0, 0, 0);

    // Draw the right wheel with rotation
    glPushMatrix();
    glTranslatef(bicycleX, 0.0f, 0.0f);
    glTranslatef(0.15f, 0.082f, 1.0f);
    glRotatef(rightWheelAngle, 0.0f, 1.0f, 0.0f); // Rotate the bicycle for steering
    glutSolidTorus(0.025f, 0.06f, 6, 20);
    glPopMatrix();

    // Draw the left wheel with rotation
    glPushMatrix();
    glTranslatef(bicycleX, 0.0f, 0.0f);
    glTranslatef(-0.15f, 0.082f, 1.0f);
    glRotatef(leftWheelAngle, 0.0f, 1.0f, 0.0f); // Rotate the bicycle for steering
    glutSolidTorus(0.025f, 0.06f, 6, 20);
    glPopMatrix();


    // Draw the handle of the bicycle
    glColor3f(0.22f, 0.18f, 0.13f);
    glPushMatrix();
    glTranslatef(bicycleX, 0.0f, 0.0f);
    glTranslatef(0.1f, 0.18f, 1.0); // Position the handle slightly higher to match the frame's new position
    glScalef(0.02f, 0.14f, 0.02f); // Scale to make it look like a handle
    glutSolidCube(0.9f); // Draw a solid cube for the handle
    glPopMatrix();

    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(bicycleX, 0.0f, 0.0f);
    glTranslatef(0.1f, 0.24f, 1.0f); // Position the handle slightly higher to match the frame's new position
    glScalef(0.02f, 0.02f, 0.1f); // Scale to make it look like a handle
    glutSolidCube(0.9f); // Draw a solid cube for the handle
    glPopMatrix();

    // Draw the seat of the bicycle
    glColor3f(0.16f, 0.20f, 0.27f);
    glPushMatrix();
    glTranslatef(bicycleX, 0.0f, 0.0f);
    glTranslatef(-0.15f, 0.2f, 1.0f); // Position the seat slightly higher to match the frame's new position
    glScalef(0.15f, 0.04f, 0.07f); // Scale to make it look like a seat
    glutSolidCube(1.0f); // Draw a solid cube for the seat
    glPopMatrix();
}

void drawBuilding() {
    drawGround();
    // Draw the first floor
    glColor3f(0.7f, 0.7f, 0.7f); // Set the color of the building
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f); // Move to the proper location
    glScalef(1.0f, 0.5f, 0.5f); // Scale size to make it look like the first floor
    glutSolidCube(1.0f); // Draw a solid cube
    glPopMatrix();

    // Draw a ledge between the first and second floors
    glColor3f(0.2f, 0.2f, 0.5f); // Set a different color for the ledge
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f); // Position the ledge between the first and second floors
    glScalef(1.02f, 0.05f, 0.52f); // Scale to make it look like a ledge
    glutSolidCube(1.0f); // Draw a solid cube for the ledge
    glPopMatrix();

    // Draw the second floor directly on top of the ledge
    glColor3f(0.7f, 0.7f, 0.7f); // Set the color of the second floor
    glPushMatrix();
    glTranslatef(0.0f, 0.55f, 0.0f); // Move directly above the ledge (adjusted position)
    glScalef(1.0f, 0.7f, 0.5f); // Scale to make it look like the second floor
    glutSolidCube(1.0f); // Draw a solid cube
    glPopMatrix();

    // Draw the roof
    glColor3f(0.2f, 0.2f, 0.5f); // Set the color of the roof
    glBegin(GL_QUADS);
    // Front face of the roof
    glVertex3f(-0.5f, 1.0f, 0.25f); // Bottom-left
    glVertex3f(0.5f, 1.0f, 0.25f); // Bottom-right
    glVertex3f(0.5f, 0.9f, 0.25f); // Top-right
    glVertex3f(-0.5f, 0.9f, 0.25f); // Top-left

    // Back face of the roof
    glVertex3f(-0.5f, 1.0f, -0.25f); // Bottom-left
    glVertex3f(0.5f, 1.0f, -0.25f); // Bottom-right
    glVertex3f(0.5f, 0.9f, -0.25f); // Top-right
    glVertex3f(-0.5f, 0.9f, -0.25f); // Top-left

    // Right side face of the roof
    glVertex3f(0.5f, 1.0f, 0.25f); // Bottom-left
    glVertex3f(0.5f, 1.0f, -0.25f); // Bottom-right
    glVertex3f(0.5f, 0.9f, -0.25f); // Top-right
    glVertex3f(0.5f, 0.9f, 0.25f); // Top-left

    // Left side face of the roof
    glVertex3f(-0.5f, 1.0f, 0.25f); // Bottom-left
    glVertex3f(-0.5f, 1.0f, -0.25f); // Bottom-right
    glVertex3f(-0.5f, 0.9f, -0.25f); // Top-right
    glVertex3f(-0.5f, 0.9f, 0.25f); // Top-left

    glEnd();

    // Draw the door
    drawDoor(-0.01f, 0.1f, 0.26f, doorAngle);

    // Draw two windows on the first floor
    for (int i = 0; i < 2; ++i) {
        drawWindow(-0.2f + i*0.4f, 0.25f, 0.26f, windowAngleFirstFloor);
    }
    // Draw two windows on the second floor
    for (int i = 0; i < 2; ++i) {
        drawWindow(-0.2f + i*0.4f, 0.7f, 0.26f, windowAngleSecondFloor);
    }

}

float cameraPosX = 2.0f;
float cameraPosY = 2.0f;
float cameraPosZ = 2.0f;
void updateCameraPosition(float x, float y, float z) {
    cameraPosX = x;
    cameraPosY = y;
    cameraPosZ = z;
}

void zoomCamera(unsigned char key, int x, int y){
    switch (key) {
        case 'z': // Zoom in
            updateCameraPosition(cameraPosX, cameraPosY, cameraPosZ - 0.1f);
            break;
        case 'Z': // Zoom out
            updateCameraPosition(cameraPosX, cameraPosY, cameraPosZ + 0.1f);
            break;
    }
    glutPostRedisplay(); // Redraw the scene with updated camera position
}

void update(int value) {
    if (animationEnabled) {
        animationAngle += 1.0f;

        if (animationAngle >= 360.0f){
            animationAngle = 0.0f;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(16, update, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPosX, cameraPosY, cameraPosZ,  // Camera position in World Space
              0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);

    drawBuilding();
    glPushMatrix();
    glRotatef(bicycleRotation, 0.0, 1.0, 0.0);
    drawBicycle();
    glPopMatrix();

    if (animationEnabled){
        bicycleRotation += 1.0;
    }
    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    // Prevent a divide by zero error by making height equal to one
    if (height == 0) {
        height = 1;
    }
    float aspect = (float)width / (float)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
// Add keyboard controls to move the camera
void specialKeyPress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            updateCameraPosition(cameraPosX - 0.1f, cameraPosY, cameraPosZ);
            break;
        case GLUT_KEY_RIGHT:
            updateCameraPosition(cameraPosX + 0.1f, cameraPosY, cameraPosZ);
            break;
        case GLUT_KEY_UP:
            updateCameraPosition(cameraPosX, cameraPosY + 0.1f, cameraPosZ);
            break;
        case GLUT_KEY_DOWN:
            updateCameraPosition(cameraPosX, cameraPosY - 0.1f, cameraPosZ);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Building Scene");
    init();
    // keyboard callback
    glutKeyboardFunc(keyPress);

    // mouse callback
    glutMouseFunc(mouse);

    glutTimerFunc(20, update, 0);

    // Set up the display and reshape callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    //specialKeyPress callback
    glutSpecialFunc(specialKeyPress);
    glutMainLoop();

    return 0;
}