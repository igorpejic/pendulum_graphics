#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

typedef struct {
    bool rotate;
    double angle;
    int direction;
} RotateParam;

vector<map<char, RotateParam>> rotate_axis = {
    {{'x', {false, 0.0, 0}}, {'y', {false, 0.0, 0}}, {'z', {false, 0.0, 0}}}, 
    {{'x', {false, 0.0, 0}}, {'y', {false, 0.0, 0}}, {'z', {false, 90.0, 0}}}
    };

void drawCube()
{
    glPushMatrix();
        glBegin(GL_QUADS);

        //prednja
        glNormal3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glNormal3f(0, 0, 0);
        glVertex3f(3, 0, 0);
        glNormal3f(1, 0, 0);
        glVertex3f(3, 1, 0);
        glNormal3f(0, 0, 0);
        glVertex3f(0, 1, 0);

        //desna
        glVertex3f(3, 0, 0);
        glVertex3f(3, 0, 3);
        glVertex3f(3, 1, 3);
        glVertex3f(3, 1, 0);

        //gornja
        glVertex3f(0, 1, 0);
        glVertex3f(3, 1, 0);
        glVertex3f(3, 1, 3);
        glVertex3f(0, 1, 3);

        //lijeva
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 3);
        glVertex3f(0, 1, 3);
        glVertex3f(0, 1, 0);

        //straznja
        glVertex3f(0, 0, 3);
        glVertex3f(3, 0, 3);
        glVertex3f(3, 1, 3);
        glVertex3f(0, 1, 3);

        //donja
        glVertex3f(0, 0, 0);
        glVertex3f(3, 0, 0);
        glVertex3f(3, 0, 3);
        glVertex3f(0, 0, 3);
        glEnd();
    glPopMatrix();
}
void drawSphere(void) {
    glutSolidSphere(1.0, 30, 30);
}
bool keyStates[256];
bool animate = 1;

void keyPressed (unsigned char key, int /*x*/, int /*y*/) 
{
    keyStates[key] = true; 
    cout<<key<<" key pressed"<<endl;
}

void keyUp (unsigned char key, int /*x*/, int /*y*/) 
{
    keyStates[key] = false;
    return;
}


void keyOperations () 
{
    if (keyStates[27] == true) {
        exit(0);
    } else if (keyStates['q'] == true) {
        rotate_axis[0]['y'].rotate = rotate_axis[0]['z'].rotate = false;
        rotate_axis[0]['x'].rotate = true;
    } else if (keyStates['w'] == true) {
        rotate_axis[0]['x'].rotate = rotate_axis[0]['z'].rotate = false;
        rotate_axis[0]['y'].rotate = true;
    } else if (keyStates['e'] == true) {
        rotate_axis[0]['x'].rotate = rotate_axis[0]['y'].rotate = false;
        rotate_axis[0]['z'].rotate = true;
    } else if (keyStates['b'] == true) {
        rotate_axis[1]['y'].rotate = rotate_axis[1]['z'].rotate = false;
        rotate_axis[1]['x'].rotate = true;
    } else if (keyStates['n'] == true) {
        rotate_axis[1]['x'].rotate = rotate_axis[1]['z'].rotate = false;
        rotate_axis[1]['y'].rotate = true;
    } else if (keyStates['m'] == true) {
        rotate_axis[1]['x'].rotate = rotate_axis[1]['y'].rotate = false;
        rotate_axis[1]['z'].rotate = true;
    } else if (keyStates['s'] == true) {
        animate = true;
    } else if (keyStates['x'] == true) {
        animate = false;
    }
}

vector<vector<float>> trail(1, vector<float>(16));

int i = 0;

void display()
{

    for (auto& i: rotate_axis) {
        for (auto& kv: i) {
            if(kv.second.rotate) {
                if(kv.first == 'x' || kv.first == 'z') {
                    if (i['x'].angle + i['z'].angle >= 90 || i['x'].angle + i['z'].angle <= -90) {
                        kv.second.direction = (kv.second.direction + 1) % 2;
                    }
                    if (kv.second.direction == 0) {
                        kv.second.angle += 1;
                    } else if (kv.second.direction == 1) {
                        kv.second.angle -= 1;
                    }
                } else {
                    kv.second.angle = (int)(kv.second.angle + 1) % 360;
                }

            }
        }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearColor (0.3, 0.3, 0.3, 0.0);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glRotatef(180, 1, 0, 0);
    glColor3f(0, 0.5, 0);
    glPushMatrix();
        glTranslatef(0.0, 0.0, -1.9);
        glScalef(0.04, 0.04, 0.04);
    glPushMatrix();
        glPushMatrix();
            glTranslatef(-1.5, 0.0, -1.5);
            drawCube();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0, -1.0, 0);
            for (auto& kv: rotate_axis[0]) {
                glRotatef(kv.second.angle, (float)kv.first == 'x', (float)kv.first == 'y', (float)kv.first == 'z');
            }
            glColor3f(1, 1, 0);
            drawSphere();
            glPushMatrix();
                GLUquadricObj *obj = gluNewQuadric();
                glTranslatef(0, -1.0, 0);

                glPushMatrix();
                    glRotatef(90, 1.0, 0, 0);
                    gluDisk(obj, 0.0, 1.0, 30, 30);
                    gluCylinder(obj, 1.0, 1, 3, 30, 30);
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(0, -3.0, 0);
                    glPushMatrix();
                        glRotatef(-90, 1.0, 0, 0);
                        gluDisk(obj, 0.0, 1.0, 30, 30);
                    glPopMatrix();

                    /* 2nd constellation */

                    glColor3f(0, 1, 0);
                    glPushMatrix();
                        glTranslatef(0, -1.0, 0);

                        for (auto& kv: rotate_axis[1]) {
                            glRotatef(kv.second.angle, (float)kv.first == 'x', (float)kv.first == 'y', (float)kv.first == 'z');
                        }
                        drawSphere();
                        glPushMatrix();
                            glTranslatef(0, -1.0, 0);
                            glPushMatrix();
                                glRotatef(90, 1.0, 0, 0);
                                gluDisk(obj, 0.0, 1.0, 30, 30);
                                gluCylinder(obj, 1.0, 1, 3, 30, 30);
                            glPopMatrix();
                            glPushMatrix();
                                glPushMatrix();
                                    glTranslatef(0, -3.0, 0);
                                    glRotatef(-90, 1.0, 0, 0);
                                    gluDisk(obj, 0.0, 1.0, 30, 30);
                                    i++;
                                    vector<float> tmp (16);
                                    trail.push_back(tmp);
                                    glGetFloatv(GL_MODELVIEW_MATRIX, &trail[i][0]);
                                glPopMatrix();
                            glPopMatrix();
                        glPopMatrix();
                    glPopMatrix(); /* end 2nd constellation */
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPopMatrix();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.545, 0.0, 0.0);
    for(int j = 0; j < i-1; j++){
        //glLoadMatrixf(trail[j]);
        //glVertex3f(0.0, 0.0, 0.0);
        //cout << trail[j][12] << ", " <<  trail[j][13] << ", " << trail[j][14] << "," << endl;
        
        glVertex3f(trail[j][12], trail[j][13], trail[j][14]);
        
    }
    glEnd();
    glutSwapBuffers();        
}

void displayPrepare(void) {
    display();
}

void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 90.0
     
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,90.0);
 
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void idleFunc(void)
{
    keyOperations();
    if (animate) {
        displayPrepare();
    }
    return;
}

void initLight()
{
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 };
   GLfloat cyan[] = {0.f, .8f, .8f, 1.f};

   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { .5, 1.0, 1.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
   glEnable(GL_COLOR_MATERIAL);

}
void init(void) 
{
    initLight();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //gluLookAt(0.0,0.0,34.0, // camera
    //0.0,0.0,-1.0, // where
    //0.0f,1.0f,0.0f); // up vector

}

int main (int argc, char **argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    //double buffering used to avoid flickering problem in animation
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    // window size
    glutInitWindowSize(500,500);
    // create the window 
    glutCreateWindow("Pendulum");
    init();

    //glEnable(GL_DEPTH_CLAMP); //dont cut out clip plane

    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);  //---> only wireframe
    //Assign  the function used in events
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayPrepare);
    glutIdleFunc(idleFunc);

    glutKeyboardFunc(keyPressed); 
    glutKeyboardUpFunc(keyUp);

    glutMainLoop();
    return 0;
}
