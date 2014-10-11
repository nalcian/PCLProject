#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <math.h>
#define PI 3.14159


/* Global variables */
char programTitle[] = "3D OpenGL & PCL Reconstruction";

int refreshMills     = 10;    // refresh interval in milliseconds
GLfloat xPos  = 0.0f;
GLfloat yPos  = 0.0f;
GLfloat zPos  = 0.0f;
GLfloat r     = 15.0f;
GLfloat alpha = 0.0f;

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //background color: black and opaque
    glClearDepth(1.0f);                   //background depth to farthest
    glEnable(GL_DEPTH_TEST);              // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);               // Set the type of depth-test
    glShadeModel(GL_SMOOTH);              // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
/* Draw Cube Function */
void drawCube(GLfloat movelocX, GLfloat movelocY, GLfloat movelocZ)
{
    glPushMatrix();
    glTranslatef(movelocX, movelocY, movelocZ); //Move right and into the screen
    glBegin(GL_QUADS);                      //Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);
    // Bottom face (y = -1.0f)
    glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    // Front face  (z = 1.0f)
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    // Back face (z = -1.0f)
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    // Left face (x = -1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    // Right face (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();
    glPopMatrix();
}

/* Handler for window-repaint event. Called back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    
    //Calc Camera
    xPos = r*cos(alpha);
    zPos = r*sin(alpha);
    
    // Calculate the camera position using the distance and angles
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    // Render a color-cube consisting of 6 quads with different colors
    glLoadIdentity();                 // Reset the model-view matrix
    gluLookAt(xPos, yPos, zPos,
              0, 0, 0,
              0, 1, 0);
    drawCube(-2.0,0.0,0.0);
    drawCube(2.0 ,0.0,0.0);
    drawCube(0.0,2.0,0.0);
    drawCube(0.0,-2.0,0.0);
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
    alpha += 0.01f;
}

/* Called back when timer expired [NEW] */
void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

/* Handler for window re-size event. Called back when the window first appears and
 whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    
    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);
    
    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(640, 480);     // Set the window's initial width & height
    glutInitWindowPosition(50, 50);   // Position the window's initial top-left corner
    glutCreateWindow(programTitle);   // Create window with the given title
    glutDisplayFunc(display);         // Callback handler for window re-paint event
    glutReshapeFunc(reshape);         // Callback handler for window re-size event
    initGL();                         // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);       // First timer call immediately
    glutMainLoop();                   // Enter the infinite event-processing loop
    return 0;
}