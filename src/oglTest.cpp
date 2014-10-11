#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

#define PI 3.14159

void initGL();
void setCameraLoc(float xPos, float yPos, float zPos, float targetX, float targetY, float targetZ);
void initLights();
void drawCube(GLfloat movelocX, GLfloat movelocY, GLfloat movelocZ);
void showInfo();
void display();


/* Constant Variables */
const char programTitle[] = "3D OpenGL & PCL Reconstruction";
const int screenWidth = 640;
const int screenHeight = 480;
const int fontHeight = 20;
const int refreshMills     = 10;    // refresh interval in milliseconds
const GLfloat yPos  = 0.0f;
const GLfloat r  = 15.0f;
const int pboCount = 2;
const int colorChannelCount = 4;
const int dataSize = screenWidth*screenHeight*colorChannelCount;
const int depthDataSize = screenWidth*screenHeight;
const GLenum pixelFormat = GL_BGRA;

/* Global Variables */
int glutWindowID;
void *font = GLUT_BITMAP_8_BY_13;
GLfloat xPos  = 0.0f;
GLfloat zPos  = 0.0f;
GLfloat alpha = 0.0f;
bool pboUsed;
GLuint pboIds[pboCount]; //PBO IDs
GLubyte* colorBuffer = 0;
GLubyte* depthBuffer = 0;
bool singleRun = false;




/*-----------------------------------------------------------------------*/
/* Initialize OpenGL Graphics */
void initGL()
{
    glShadeModel(GL_SMOOTH);                // Enable smooth shading
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  // 4-byte pixel alignment
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glEnable(GL_DEPTH_TEST);    // Enable depth testing for z-culling
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    
    glDepthFunc(GL_LEQUAL);     // Set the type of depth-test
    
    glClearColor(0, 0, 0, 1);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    initLights();
    //showInfo();
}

/*-----------------------------------------------------------------------*/
/* Camera Setting Function */
void setCameraLoc(float xPos, float yPos, float zPos,
                  float targetX, float targetY, float targetZ)
{
glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
glLoadIdentity();               // Reset the model-view matrix
gluLookAt(xPos, yPos, zPos,
          targetX, targetY, targetZ,
          0, 1, 0);
}


/*-----------------------------------------------------------------------*/
/* Light Setting Function */
void initLights()
{
    // set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light
    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);
    
    // position the light
    float lightPos[4] = {0, 0, 20, 1}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    glEnable(GL_LIGHT0);// MUST enable each light source after configuration
}


/*-----------------------------------------------------------------------*/
void drawString(const char *str, int x, int y, float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);
    
    glColor4fv(color);          // set text color
    glRasterPos2i(x, y);        // place text position
    
    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}


/*-----------------------------------------------------------------------*/
/* Draw Cube Function */
void drawCube(GLfloat movelocX, GLfloat movelocY, GLfloat movelocZ)
{
    glPushMatrix();
    glTranslatef(movelocX, movelocY, movelocZ); //Move right and into the screen
    glBegin(GL_QUADS); //Begin drawing the color cube with 6 quads
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


void toPerspective()
{
    // set viewport to be the entire window
    glViewport(0, 0, (GLsizei)screenWidth, (GLsizei)screenHeight);
    
    // set perspective viewing frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)(screenWidth)/screenHeight, 0.1f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip
    
    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void toOrtho()
{
    // set viewport to be the entire window
    glViewport((GLsizei)screenWidth, 0, (GLsizei)screenWidth, (GLsizei)screenHeight);
    
    // set orthographic viewing frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    
    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void printPixels(unsigned char* src, int width, int height, unsigned char* dst)
{
    if(!src || !dst)
        return;
    
    int valueR,valueG,valueB;
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
           
            
            valueR = *src;
            *dst = (unsigned char)valueR;
            ++src;
            ++dst;
            valueG = *src;
            *dst = (unsigned char)valueG;
            ++src;
            ++dst;
            valueB = *src;
            *dst = (unsigned char)valueB;
            ++src;
            ++dst;
            ++src;    // skip alpha
            ++dst;
            if(singleRun==true)
            {
                std::cout <<"(x,y)=("<<i<<","<<j <<") ->[R:"<<valueR<< ",G:"<<valueG<< ",B:"<<valueB<<"]"<<std::endl;
            }
        }
    }
}


/*-----------------------------------------------------------------------*/
/* Handler for window-repaint event. Called back when the window first appears and
 whenever the window needs to be re-painted. */
void display(){
    //Calc Camera Kinematics
    xPos = r*cos(alpha);
    zPos = r*sin(alpha);
    
    //Pixel Buffer Object Behavior
    static int shift = 0;
    static int index = 0;
    int nextIndex = 0; // pbo index used for next frame
    
    // increment current index first then get the next index
    // "index" is used to read pixels from a framebuffer to a PBO
    // "nextIndex" is used to process pixels in the other PBO
    index     = (index + 1) % 2;
    nextIndex = (index + 1) % 2;
    
    toPerspective(); // set to perspective on the left side of the window
    
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // Set Camera Properties
    setCameraLoc(xPos, 0, zPos, 0, 0, 0);
    
    //Draw the Original Cube
    drawCube(-4.0,0.0,0.0);
    drawCube(4.0 ,0.0,0.0);
    drawCube(0.0,4.0,0.0);
    drawCube(0.0,-4.0,0.0);
    
    // set the framebuffer to read
    glReadBuffer(GL_FRONT);
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pboIds[index]);
    glReadPixels(0, 0, screenWidth, screenHeight, pixelFormat, GL_UNSIGNED_BYTE, 0);
    // map the PBO that contain framebuffer pixels before processing it
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pboIds[nextIndex]);
    GLubyte* src = (GLubyte*)glMapBufferARB(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY_ARB);
    if(src)
    {
        // change brightness
        printPixels(src, screenWidth, screenHeight, colorBuffer);
        glUnmapBufferARB(GL_PIXEL_PACK_BUFFER_ARB);     // release pointer to the mapped buffer
        singleRun = false;
    }
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);
    // render to the framebuffer //////////////////////////
    glDrawBuffer(GL_BACK);
    toOrtho();
    glRasterPos2i(0, 0);
    glDrawPixels(screenWidth, screenHeight, pixelFormat, GL_UNSIGNED_BYTE, colorBuffer);
    
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
    alpha += 0.05f;
}


/*-----------------------------------------------------------------------*/
/* Called back when timer expired [NEW] */
void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}


// Initialize memory
void initMemory()
{
    colorBuffer = new GLubyte[dataSize];
    depthBuffer = new GLubyte[depthDataSize];
    memset(colorBuffer, 255, dataSize);
    memset(depthBuffer, 255, depthDataSize);
}


// Clear Shared Memory
void clearMemory()
{
    glDeleteBuffersARB(pboCount, pboIds);
}

/*-----------------------------------------------------------------------*/
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


void KeyboardEvent(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            // ESC pressed, exit the application
            glutDestroyWindow(glutWindowID);
            clearMemory();
            std::cout<<"Memory Cleared"<<std::endl;
            exit(0);
            break;
        case 'p':
            std::cout<<"Progress"<<std::endl;
            singleRun = true;
            break;
        default:
            break;
    }
}


/*-----------------------------------------------------------------------*/
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    initMemory();
    atexit(clearMemory);
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(screenWidth, screenHeight); // Set the window's initial width & height
    glutInitWindowPosition(5, 5);   // Position the window's initial top-left corner
    glutWindowID = glutCreateWindow(programTitle);   // Create window with the given title
    glutDisplayFunc(display);         // Callback handler for window re-paint event
    glutReshapeFunc(reshape);         // Callback handler for window re-size event
    initGL();                         // Our own OpenGL initialization
    // create 2 pixel buffer objects, you need to delete them when program exits.
    // glBufferDataARB with NULL pointer reserves only memory space.
    glGenBuffersARB(pboCount, pboIds);
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pboIds[0]);
    glBufferDataARB(GL_PIXEL_PACK_BUFFER_ARB, dataSize, 0, GL_STREAM_READ_ARB);
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pboIds[1]);
    glBufferDataARB(GL_PIXEL_PACK_BUFFER_ARB, dataSize, 0, GL_STREAM_READ_ARB);
    
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);
    glutTimerFunc(0, timer, 0);       // First timer call immediately
    glutKeyboardFunc(KeyboardEvent);
    glutMainLoop();                   // Enter the infinite event-processing loop
    return 0;
}