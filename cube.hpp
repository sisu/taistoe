
#ifndef CUBE_H
#define CUBE_H
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glext.h>


GLfloat qvertices[] = {1,1,1,  -1,1,1,  -1,-1,1,  1,-1,1,        // v0-v1-v2-v3
                      1,1,1,  1,-1,1,  1,-1,-1,  1,1,-1,        // v0-v3-v4-v5
                      1,1,1,  1,1,-1,  -1,1,-1,  -1,1,1,        // v0-v5-v6-v1
                      -1,1,1,  -1,1,-1,  -1,-1,-1,  -1,-1,1,    // v1-v6-v7-v2
                      -1,-1,-1,  1,-1,-1,  1,-1,1,  -1,-1,1,    // v7-v4-v3-v2
                      1,-1,-1,  -1,-1,-1,  -1,1,-1,  1,1,-1};   // v4-v7-v6-v5

#if 0
GLubyte qindices[] = {0,1,2,3,
                     4,5,6,7,
                     8,9,10,11,
                     12,13,14,15,
                     16,17,18,19,
                     20,21,22,23};
#endif
// normal array
GLfloat qnormals[] = {0,0,1,  0,0,1,  0,0,1,  0,0,1,             // v0-v1-v2-v3
                     1,0,0,  1,0,0,  1,0,0, 1,0,0,              // v0-v3-v4-v5
                     0,1,0,  0,1,0,  0,1,0, 0,1,0,              // v0-v5-v6-v1
                     -1,0,0,  -1,0,0, -1,0,0,  -1,0,0,          // v1-v6-v7-v2
                     0,-1,0,  0,-1,0,  0,-1,0,  0,-1,0,         // v7-v4-v3-v2
                     0,0,-1,  0,0,-1,  0,0,-1,  0,0,-1};        // v4-v7-v6-v5

static const float SENT = 2.3;
#if 0
//texture coord 
GLfloat qcolors[] = {
    //1,1,    1,0,  0,0,  0,1,           
    1,1,    1,0,  0,0,  0,1,           
    //1,1,    1,0,  0,0,  0,1,           
    SENT,1,    SENT,0,  0,0,  0,1,
    1,SENT,    1,0,  0,0,  0,SENT,           
    1,SENT,    1,0,  0,0,  0,SENT,           
    SENT,1,    SENT,0,  0,0,  0,1,           
    1,1,    1,0,  0,0,  0,1};
#endif

void drawcube() {
#if 0
void drawcube(float h=1)
{
    float f2 = h+0.05;
    for(int i = 0 ;i<24*2;i++)
    {
        if(colors[i]==SENT)
            colors[i]=f2;
    }
#endif

    // enable and specify pointers to vertex arrays
    glEnableClientState(GL_NORMAL_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glNormalPointer(GL_FLOAT, 0, qnormals);
    //glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, qvertices);
//    glTexCoordPointer(2,GL_FLOAT,0,qcolors);
//    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE,(GLvoid*) qindices);
	glDrawArrays(GL_QUADS, 0, 24);


    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    //glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
#if 0
    for(int i = 0 ;i<24*2;i++)
    {
        if(colors[i]==f2)
            colors[i]=SENT;
    }
#endif
}

#endif
