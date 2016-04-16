#include "Draw.h"

Draw::Draw(){
    setCamera(TV1);

    floor.setScale(btVector3(15, 0.05, 13));
    floor.setColor(Pixel(0.1, 0.1, 0.1));
    floor.setPosition(btVector3(0, 0, 0));

    goal[0].setScale(btVector3(1, 0.05, 4));
    goal[0].setColor(Pixel(0.1, 0.1, 0.1));
    goal[0].setPosition(btVector3(-16, 0, 0));

    goal[1].setScale(btVector3(1, 0.05, 4));
    goal[1].setColor(Pixel(0.1, 0.1, 0.1));
    goal[1].setPosition(btVector3(16, 0, 0));

    goalW[0][0].setScale(btVector3(1, 1.5, 0.05));
    goalW[0][0].setColor(Pixel(0.07, 0.07, 0.07));
    goalW[0][0].setPosition(btVector3(16, 0, 4));

    goalW[0][1].setScale(btVector3(1, 1.5, 0.05));
    goalW[0][1].setColor(Pixel(0.07, 0.07, 0.07));
    goalW[0][1].setPosition(btVector3(16, 0, -4));

    goalW[0][2].setScale(btVector3(0.05, 1.5, 4));
    goalW[0][2].setColor(Pixel(0.07, 0.07, 0.07));
    goalW[0][2].setPosition(btVector3(17, 0, 0));

    goalW[1][0].setScale(btVector3(1, 1.5, 0.05));
    goalW[1][0].setColor(Pixel(0.07, 0.07, 0.07));
    goalW[1][0].setPosition(btVector3(-16, 0, 4));

    goalW[1][1].setScale(btVector3(1, 1.5, 0.05));
    goalW[1][1].setColor(Pixel(0.07, 0.07, 0.07));
    goalW[1][1].setPosition(btVector3(-16, 0, -4));

    goalW[1][2].setScale(btVector3(0.05, 1.5, 4));
    goalW[1][2].setColor(Pixel(0.07, 0.07, 0.07));
    goalW[1][2].setPosition(btVector3(-17, 0, 0));

    walls[0].setScale(btVector3(15, 1.5, 0.1));
    walls[0].setColor(Pixel(0.07, 0.07, 0.07));
    walls[0].setPosition(btVector3(0, 0, 13));

    walls[1].setScale(btVector3(15, 1.5, 0.1));
    walls[1].setColor(Pixel(0.07, 0.07, 0.07));
    walls[1].setPosition(btVector3(0, 0, -13));

    walls[2].setScale(btVector3(0.1, 1.5, 4.5));
    walls[2].setColor(Pixel(0.07, 0.07, 0.07));
    walls[2].setPosition(btVector3(15, 0, 8.5));

    walls[3].setScale(btVector3(0.1, 1.5, 4.5));
    walls[3].setColor(Pixel(0.07, 0.07, 0.07));
    walls[3].setPosition(btVector3(15, 0, -8.5));

    walls[4].setScale(btVector3(0.1, 1.5, 4.5));
    walls[4].setColor(Pixel(0.07, 0.07, 0.07));
    walls[4].setPosition(btVector3(-15, 0, 8.5));

    walls[5].setScale(btVector3(0.1, 1.5, 4.5));
    walls[5].setColor(Pixel(0.07, 0.07, 0.07));
    walls[5].setPosition(btVector3(-15, 0, -8.5));

    // linha central
    lines[0].setScale(btVector3(0.07, 0.07, 13));
    lines[0].setColor(Pixel(0.9, 0.9, 0.9));
    lines[0].setPosition(btVector3(0, 0, 0));


    // gol
    lines[1].setScale(btVector3(1.5, 0.07, 0.07));
    lines[1].setColor(Pixel(0.9, 0.9, 0.9));
    lines[1].setPosition(btVector3(13.5, 0, -7));

    lines[2].setScale(btVector3(1.5, 0.07, 0.07));
    lines[2].setColor(Pixel(0.9, 0.9, 0.9));
    lines[2].setPosition(btVector3(13.5, 0, 7));

    lines[3].setScale(btVector3(0.07, 0.07, 7));
    lines[3].setColor(Pixel(0.9, 0.9, 0.9));
    lines[3].setPosition(btVector3(12, 0, 0));

    // a
    lines[4].setScale(btVector3(1.5, 0.07, 0.07));
    lines[4].setColor(Pixel(0.9, 0.9, 0.9));
    lines[4].setPosition(btVector3(-13.5, 0, -7));

    lines[5].setScale(btVector3(1.5, 0.07, 0.07));
    lines[5].setColor(Pixel(0.9, 0.9, 0.9));
    lines[5].setPosition(btVector3(-13.5, 0, 7));

    lines[6].setScale(btVector3(0.07, 0.07, 7));
    lines[6].setColor(Pixel(0.9, 0.9, 0.9));
    lines[6].setPosition(btVector3(-12, 0, 0));
}

/*
    O sistema de coordenadas do OpenCV é diferente do sistema de coordenadas do OpenGL,
    por isso é necessário tratar a entrada para desenhar de maneira correta
*/
btVector3 Draw::handlePosition(btVector3 openCV){
    btVector3 openGL;

    openGL.x = (openCV.x - (CAM_WIDTH/2.0))/20.0;
    openGL.y = openCV.z;
    openGL.z = (openCV.y - (CAM_HEIGHT/2.0))/20.0;

    return openGL;
}

void Draw::setCamera(int idCamera){
    this->idCamera = idCamera;

    switch(idCamera){
        case TOP:{
            glCam.setOrientation(btVector3(90, 0, 0));
            glCam.setPosition(btVector3(0, -28, 0));
        }break;
        case TV1:{
            glCam.setOrientation(btVector3(60, 0, 0));
            glCam.setPosition(btVector3(0, -20, -15));
        }break;
        case TV2:{

        }break;
        case BACK:{

        }break;
        case FRONT:{

        }break;
        case TEAM1:{

        }break;
        case TEAM2:{

        }break;
        case TEAM3:{

        }break;
        case ADV1:{

        }break;
        case ADV2:{

        }break;
        case ADV3:{

        }break;  
        case BALL:{

        }break;
    }
}

void Draw::positionCam(){
	glRotatef(glCam.orientation.x, 1, 0, 0);
    glRotatef(glCam.orientation.y, 0, 1, 0);
    glRotatef(glCam.orientation.z, 0, 0, 1);
    glTranslatef(glCam.position.x, glCam.position.y, glCam.position.z);
}

void Draw::drawWorld(vector<Robot> robot, btVector3 b){
    glRigidBody ball;
    ball.setPosition(b);
    ball.setColor(Pixel(1, 0.4, 0.1));

    positionCam();
    drawField();

    for(int i = 0 ; i < robot.size() ; i++){
        drawRobot(robot.at(i));
    }

    drawBall(b);
}

void Draw::drawField(){
	drawCube(floor);
    drawCube(walls[0]);
    drawCube(walls[1]);
    drawCube(walls[2]);
    drawCube(walls[3]);
    drawCube(walls[4]);
    drawCube(walls[5]);
    drawCube(goal[0]);
    drawCube(goal[1]);
    drawCube(goalW[0][0]);
    drawCube(goalW[0][1]);
    drawCube(goalW[0][2]);
    drawCube(goalW[1][0]);
    drawCube(goalW[1][1]);
    drawCube(goalW[1][2]);
    drawCube(lines[0]);
    drawCube(lines[1]);
    drawCube(lines[2]);
    drawCube(lines[3]);
    drawCube(lines[4]);
    drawCube(lines[5]);
    drawCube(lines[6]);
}


void Draw::drawCube(glRigidBody pos){
    GLfloat vertices[] =
    {
        -1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
        1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
        -1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
        -1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
    };

    GLfloat colors[72];

    for(int i = 0 ; i < 72 ; i = i + 3){
        colors[i] = pos.color.rgb[0];
        colors[i+1] = pos.color.rgb[1];
        colors[i+2] = pos.color.rgb[2];
    }

    glPushMatrix();
        glRotatef(pos.orientation.x, 1, 0, 0);
        glRotatef(pos.orientation.y, 0, 1, 0);
        glRotatef(pos.orientation.z, 0, 0, 1);
        glTranslatef(pos.position.x, pos.position.y, pos.position.z);
        glScalef(pos.scale.x, pos.scale.y, pos.scale.z);
        
        //We have a color array and a vertex array 
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        //Send data : 24 vertices 
        glDrawArrays(GL_QUADS, 0, 24);

        //Cleanup states 
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

void Draw::drawSphere(double r, int lats, int longs){
    int i, j;

    for(i = 0; i <= lats; i++){
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glColor3f(1, 0.4, 0.1);
        glBegin(GL_QUAD_STRIP);

        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}

void Draw::drawBall(btVector3 b){
    btVector3 position = handlePosition(b);
    //position.show();
    glPushMatrix();
        glTranslatef(position.x, position.y+0.15, position.z);
        glScalef(0.47, 0.47, 0.47);
        drawSphere(1, 10, 10);
    glPopMatrix();
}

void Draw::drawRobot(Robot robot){
    btVector3 position = handlePosition(robot.getPosition());
    //position.show();
    btVector3 orientation = robot.getOrientation();
    btVector3 scale = btVector3(0.8, 0.8, 0.8);
    Pixel colorTeam = robot.getColorTeam();
    Pixel colorRobot = robot.getColorRobot();

    GLfloat vertices[] =
    {
        -1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
        1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
        -1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
        -1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
    };

    GLfloat colors[72];

    for(int i = 0 ; i < 72 ; i = i + 3){
        colors[i] = 0.03;
        colors[i+1] = 0.03;
        colors[i+2] = 0.03;
    }

    glPushMatrix();

        glTranslatef(position.x, position.y+0.8, position.z);
        glRotatef(orientation.x, 1, 0, 0);
        glRotatef(orientation.y, 0, 1, 0);
        glRotatef(orientation.z, 0, 0, 1);
        glScalef(scale.x, scale.y, scale.z);
        
        //We have a color array and a vertex array 
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        //Send data : 24 vertices 
        glDrawArrays(GL_QUADS, 0, 24);

        //Cleanup states 
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);

        scale = btVector3(0.4, 0.4, 0.4);

        glPushMatrix();  
            position = btVector3(-0.4, 0.7, -0.4);
            //colorTeam.show();
            for(int i = 0 ; i < 72 ; i = i + 3){
                colors[i] = colorTeam.rgb[0]/255.0;
                colors[i+1] = colorTeam.rgb[1]/255.0;
                colors[i+2] = colorTeam.rgb[2]/255.0;
            }

            glTranslatef(position.x, position.y, position.z);
            glScalef(scale.x, scale.y, scale.z);
            
            //We have a color array and a vertex array 
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, vertices);
            glColorPointer(3, GL_FLOAT, 0, colors);

            //Send data : 24 vertices 
            glDrawArrays(GL_QUADS, 0, 24);

            //Cleanup states 
            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
        glPopMatrix();

        glPushMatrix();  
            position = btVector3(0.4, 0.7, 0.4);
            //colorRobot.show();
            for(int i = 0 ; i < 72 ; i = i + 3){
                colors[i] = colorRobot.rgb[0]/255.0;
                colors[i+1] = colorRobot.rgb[1]/255.0;
                colors[i+2] = colorRobot.rgb[2]/255.0;
            }

            glTranslatef(position.x, position.y, position.z);
            glScalef(scale.x, scale.y, scale.z);
            
            //We have a color array and a vertex array 
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, vertices);
            glColorPointer(3, GL_FLOAT, 0, colors);

            //Send data : 24 vertices 
            glDrawArrays(GL_QUADS, 0, 24);

            //Cleanup states 
            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
        glPopMatrix();

    glPopMatrix();
}

void Draw::setTimePlay(bool timePlay){
    Pixel aux;
    this->timePlay = timePlay;

    if(timePlay){
        aux = goal[0].color;

        goal[0].setColor(goal[1].color);
        goal[1].setColor(aux);
    }else{
        aux = goal[0].color;

        goal[0].setColor(goal[1].color);
        goal[1].setColor(aux);
    }
}

void Draw::setColorGoal(int campo, Pixel color){
    goal[campo].setColor(Pixel(color.rgb[r]/255.0, color.rgb[g]/255.0, color.rgb[b]/255.0));
}

