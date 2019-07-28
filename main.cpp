#include<windows.h>
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include <stdlib.h>
#include<iostream>
#include<math.h>
#include <sstream>
#include<string.h>

using namespace std;

//Prototypes
void SetValues();                                               //set input values to struct
void drawBitmapText(char *string, float x, float y, float z);   //draw text on the window
float CalcPoints(float k,float w,float A,float phi,float x);    //calculate points
void displayAxes();                                             //display axes on the window for the waves
void permanentText();                                           //permanent texts such as wave equation
void changingText(int y1, int y2,int y3);                       //changing text such as amplitude value
void display();                                                 //main function to display points
void Loop(int val);                                             //loop control
void specialKeys(int key,int x, int y);                         //special key uses

struct wave
{
    float k,w,A,phi;
}w1,w2,wRes;

float time = 0;
int speed = 150;

bool play = true;

int main(int argc, char *argv[])
{
    SetValues();
    glutInit(&argc,argv);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_SINGLE);
    glutCreateWindow("SuperPosition of Waves");
    //initial function call
    glutDisplayFunc(display);
    //key functions
    glutSpecialFunc(specialKeys);
    //Loop call i.e run the function
    Loop(0);
    glutMainLoop();
    return 0;
}

void SetValues(){
    cout<<"k is for ,w is the angular velocity, A is the amplitude, phi is the phase angle\n put the value as below for best visualization"<<endl<<endl<<endl;
    cout<<"k between 0.5 to 10, w between 1 to 20, A between 10 to 100"<<endl<<endl<<endl;
    cout<<"Input the values of k, w, A, phi for wave 1"<<endl<<endl;
    cin>>w1.k>>w1.w>>w1.A>>w1.phi;
    cout<<"The wave equation of wave 1 will be:"<<endl<<endl;
    cout<<w1.A<<" sin("<<w1.w<<"*t + "<<w1.k<<" * x + "<<w1.phi<<")"<<endl<<endl<<endl;

    cout<<"Input the values of k, w, A, phi for wave 2"<<endl<<endl<<endl;
    cin>>w2.k>>w2.w>>w2.A>>w2.phi;
    cout<<"The wave equation of wave 1 will be:"<<endl<<endl;
    cout<<w2.A<<" sin("<<w2.w<<"*t + "<<w2.k<<" * x + "<<w2.phi<<")"<<endl;
    /*
    w1.k=10;
    w1.w=10;
    w1.A=100;
    w1.phi = 0;

    w2.k=5;
    w2.w=10;
    w2.A=100;
    w2.phi=180;
*/
    wRes.phi = w1.phi+w2.phi;
}

void drawBitmapText(char *string, float x, float y, float z)
{
    char *c;
    glRasterPos3f(x/500.0, y/500.0, z/300.0);//define position on the screen where to draw text.

    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

float CalcPoints(float k,float w,float A,float phi,float x)
{
    return A * sin(((w*time) + k*x + phi)*(3.14/180));
}

void displayAxes(){
    //WAVE1
    //Y-axis
    glBegin(GL_LINES);
    glVertex2f(-250/300.0,(150+10+w1.A)/300.0);
    glVertex2f(-250/300.0,(150-10-w1.A)/300.0);
    glEnd();
    //X-axis
    glBegin(GL_LINES);
    glVertex2f(-250/300.0,150/300.0);
    glVertex2f(0/300.0,150/300.0);
    glEnd();

    //WAVE2
    //Y-axis
    glBegin(GL_LINES);
    glVertex2f(-250/300.0,-(150+10+w2.A)/300.0);
    glVertex2f(-250/300.0,-(150-10-w2.A)/300.0);
    glEnd();
    //X-axis
    glBegin(GL_LINES);
    glVertex2f(-250/300.0,-150/300.0);
    glVertex2f(0/300.0,-150/300.0);
    glEnd();

    //WAVE3
    //Y-axis
    glBegin(GL_LINES);
    glVertex2f(50/300.0,(w1.A+w2.A+20)/300.0);
    glVertex2f(50/300.0,-(w1.A+w2.A+20)/300.0);
    glEnd();
    //X-axis
    glBegin(GL_LINES);
    glVertex2f(250/300.0,0/300.0);
    glVertex2f(50/300.0,0/300.0);
    glEnd();
}

void permanentText(){
    char text[] = "Superposition of two waves";
    drawBitmapText(text, 200, 450, 0);
    stringstream wave1,wave2,option;
    wave1<<"Wave 1 = "<<w1.A<<" sin("<<w1.w<<"*t + "<<w1.k<<" * x + "<<w1.phi<<")";
    wave2<<"Wave 2 = "<<w2.A<<" sin("<<w2.w<<"*t + "<<w2.k<<" * x + "<<w2.phi<<")";
    option<<"Press F1 to pause/play, press F2 to decrease speed, F3 to increase speed, F4 to quit"<<endl;
    string wave1str = wave1.str();
    string wave2str = wave2.str();
    string optionstr = option.str();
    char text1[100],text2[100],optiontext[100];
    strcpy(text1,wave1str.c_str());
    strcpy(text2,wave2str.c_str());
    strcpy(optiontext,optionstr.c_str());
    drawBitmapText(text1, -500, 450, 0);
    drawBitmapText(text2, -500, 0, 0);
    drawBitmapText(optiontext, -475, -475, 0);
}

void changingText(int y1, int y2,int y3){
    stringstream text1,text2,text3;
    string textstr1,textstr2,textstr3;
    char textchar1[100],textchar2[100],textchar3[100];
    //for wave1
    glColor3f(0,1,0);

    text1<<"Wave 1 = "<<y1;
    textstr1 = text1.str();
    strcpy(textchar1,textstr1.c_str());
    drawBitmapText(textchar1,350,400,0);
    glEnd();
    glFlush();
    //for wave2
    glColor3f(1,0,0);
    text2<<"Wave 2 = "<<y2;
    textstr2 = text2.str();
    strcpy(textchar2,textstr2.c_str());
    drawBitmapText(textchar2,350,370,0);
    glEnd();
    glFlush();
    //for wave3
    glColor3f(0,0,1);
    text3<<"Wave 3 = "<<y3;
    textstr3 = text3.str();
    strcpy(textchar3,textstr3.c_str());
    drawBitmapText(textchar3,350,340,0);
    glEnd();
    glFlush();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer
    glLoadIdentity();	// Reset The Projection Matrix

    for(float x = 0 ; x < 200 ; x+=0.25)
    {
        float y1 = CalcPoints(w1.k,w1.w,w1.A,w1.phi,x);
        float y2 = CalcPoints(w2.k,w2.w,w2.A,w2.phi,x);
        float y3 = y1+y2;
        if(x==199.75){
            changingText(y1,y2,y3);
        }
        glColor3f(0,1,0);
        glBegin(GL_POINTS);
        glVertex2f((x-250)/300.0,(y1+150)/300.0);
        glEnd();
        glColor3f(1,0,0);
        glBegin(GL_POINTS);
        glVertex2f((x-250)/300.0,(y2-150)/300.0);
        glEnd();
        glColor3f(0,0,1);
        glBegin(GL_POINTS);
        glVertex2f((x+50)/300.0,y3/300.0);
        glEnd();
    }
    glColor3f(1, 1, 1);
    displayAxes();
    permanentText();
    glutSwapBuffers();

    glFlush();
}

void Loop(int val){
    if(play==true){
        display();
        time+=0.5;
    }
    glutTimerFunc(speed,Loop,0);
}

void specialKeys(int key,int x, int y){
    if(key == GLUT_KEY_F1){
        if(play ==  true){
            play = false;
        }
        else{
            play = true;
        }
    }
    else if(key == GLUT_KEY_F2){
        speed+=10;
    }
    else if(key == GLUT_KEY_F3){
        speed-=10;
    }
    else if(key == GLUT_KEY_F4){
        exit(0);
    }
}
