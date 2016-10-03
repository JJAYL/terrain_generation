#include <GL/glut.h> 
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define X_RESOLUTION 512
#define Y_RESOLUTION 288
#define MAX_HEIGHT 3
/* Global variables */

float camera_angle_degrees = 0;
float camera_position_x, camera_position_y, camera_position_z;
float center_x, center_y, center_z;
float camera_angle_radians;
GLsizei height[X_RESOLUTION][Y_RESOLUTION]; //heights must be pregenerated so that random heights don't get generated in real time

 
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
 
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
   glLoadIdentity();                 // Reset the model-view matrix
   glTranslatef(-1.5f, 0.0f, -7.0f);  // Move right and into the screen
   //glLoadIdentity();                  // Reset the model-view matrix
   //glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen
   glTranslatef(camera_position_x, camera_position_y, camera_position_z);
   GLsizei triangle_x = 0, triangle_y = 0, triangle_z;
   gluLookAt (camera_position_x, camera_position_y, camera_position_z, X_RESOLUTION/2, Y_RESOLUTION/2 , MAX_HEIGHT, 0.0f, 1.0f, 0.0f);
   //gluLookAt (camera_position_x, camera_position_y, camera_position_z, center_x, center_y , center_z, 0.0f, 1.0f, 0.0f);

   glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
 
      // Right
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
 
      // Back
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f, -1.0f, -1.0f);
 
      // Left
      glColor3f(1.0f,0.0f,0.0f);       // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f,0.0f,1.0f);       // Blue
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glColor3f(0.0f,1.0f,0.0f);       // Green
      glVertex3f(-1.0f,-1.0f, 1.0f);
   glEnd();   // Done drawing the pyramid

   for(int i = 0; i < X_RESOLUTION; i++)
   {
      for(int j = 0; j < Y_RESOLUTION; j++)
      {

        glPushMatrix();
        glClearColor (1.0, 1.0, 1.0, 1.0);
        glColor3f(1.0f, 0.0f, 0.0f);
        //triangle_z = 0;
        glBegin (GL_LINE_LOOP);
        glVertex3f(i, height[i][j], j );
        glVertex3f(i, height[i][j+1], j + 1); 
        glVertex3f(i + 1, height[i+1][j+1], j + 1); 
        glEnd();

      }      
   }

   //glFlush ();
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity(); 
   glutSwapBuffers(); 
   glutPostRedisplay();
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
   gluPerspective(90.0f, aspect, 0.1f, 100.0f);
}

void keyboard (unsigned char key, int x, int y)
{
  switch (key)
  {
    case 27:
      exit (0);
    break;
    case 'w':
    case 'W':
      camera_position_y = camera_position_y + 0.1;
      break;
    case 'a':
    case 'A':
      camera_position_x = camera_position_x - 0.1;
      break;
    case 's':
    case 'S':
      camera_position_y = camera_position_y - 0.1;
      break;
    case 'd':
    case 'D':
      camera_position_x = camera_position_x + 0.1;
      break;
    case 'q':
    case 'Q':
      camera_position_z = camera_position_z - 0.1;
      break;
    case 'e':
    case 'E':
      camera_position_z = camera_position_z + 0.1;
      break;
    default:
    break;
  }
  glutPostRedisplay();
}

void arrow_keys (int key, int x, int y)
{
  switch (key)
  {
    case GLUT_KEY_UP:
      camera_position_y = camera_position_y + 1;

        break;
    case GLUT_KEY_DOWN:
      camera_position_y = camera_position_y - 1;
        break;
    case GLUT_KEY_LEFT:
      camera_position_x = camera_position_x - 1;
        break;
    case GLUT_KEY_RIGHT:
      camera_position_x = camera_position_x + 1;
        break;
    default:
        break;
  }
  glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
  srand(time(NULL));
  
  for(int i = 0; i < X_RESOLUTION; i++)
  {
     for(int j = 0; j < Y_RESOLUTION; j++)
     {
         height[i][j] = rand() % MAX_HEIGHT;
     }
  }
   
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(X_RESOLUTION, Y_RESOLUTION);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("Terrain Generation");          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutSpecialFunc(arrow_keys);
   glutKeyboardFunc(keyboard);
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
