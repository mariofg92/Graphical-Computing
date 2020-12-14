//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"
#include "file_ply_stl.h"

//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

void draw_cube()
{
    /*GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};

    glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (unsigned i=0;i<8;i++){
        glVertex3fv((GLfloat *) &Vertices[i]);
        }
    glEnd();*/

    GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};

    glColor3f(0,1,0);
    glPointSize(4);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    /*for (unsigned i=0;i<8;i++){
        glVertex3fv((GLfloat *) &Vertices[i]);
        }*/

    glVertex3fv((GLfloat *) &Vertices[3]);
    glVertex3fv((GLfloat *) &Vertices[0]);
    glVertex3fv((GLfloat *) &Vertices[1]);


    glVertex3fv((GLfloat *) &Vertices[3]);
    glVertex3fv((GLfloat *) &Vertices[1]);
    glVertex3fv((GLfloat *) &Vertices[2]);


    glVertex3fv((GLfloat *) &Vertices[2]);
    glVertex3fv((GLfloat *) &Vertices[1]);
    glVertex3fv((GLfloat *) &Vertices[5]);


    glVertex3fv((GLfloat *) &Vertices[2]);
    glVertex3fv((GLfloat *) &Vertices[5]);
    glVertex3fv((GLfloat *) &Vertices[6]);


    glVertex3fv((GLfloat *) &Vertices[6]);
    glVertex3fv((GLfloat *) &Vertices[5]);
    glVertex3fv((GLfloat *) &Vertices[4]);


    glVertex3fv((GLfloat *) &Vertices[6]);
    glVertex3fv((GLfloat *) &Vertices[4]);
    glVertex3fv((GLfloat *) &Vertices[7]);


    glVertex3fv((GLfloat *) &Vertices[7]);
    glVertex3fv((GLfloat *) &Vertices[4]);
    glVertex3fv((GLfloat *) &Vertices[0]);


    glVertex3fv((GLfloat *) &Vertices[7]);
    glVertex3fv((GLfloat *) &Vertices[0]);
    glVertex3fv((GLfloat *) &Vertices[3]);


    glVertex3fv((GLfloat *) &Vertices[2]);
    glVertex3fv((GLfloat *) &Vertices[6]);
    glVertex3fv((GLfloat *) &Vertices[7]);


    glVertex3fv((GLfloat *) &Vertices[2]);
    glVertex3fv((GLfloat *) &Vertices[7]);
    glVertex3fv((GLfloat *) &Vertices[3]);


    glVertex3fv((GLfloat *) &Vertices[5]);
    glVertex3fv((GLfloat *) &Vertices[1]);
    glVertex3fv((GLfloat *) &Vertices[0]);


    glVertex3fv((GLfloat *) &Vertices[5]);
    glVertex3fv((GLfloat *) &Vertices[0]);
    glVertex3fv((GLfloat *) &Vertices[4]);


    glEnd();
}

//**************************************************************************
// Funcion para dibujar vertices
//***************************************************************************

void draw_vertices(vector<float> &Vertices)
{
	glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (unsigned i=0;i<(Vertices.size()-2);i=i+3){
        glVertex3f(Vertices[i], Vertices[i+1], Vertices[i+2]);
    }
    glEnd();
}

void draw_mode(vector<float> &Vertices, vector<int> &Caras, int mode){
	//glClearColor(1, 1, 1, 1);
	glColor3f(1.0,0,0);
    glPointSize(4);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);

    int color=0; //variable usada para modo ajedrez
    switch(mode){
	case 0: //Vertices
		glBegin(GL_POINTS);
		for (unsigned i=0;i<Caras.size();i++){
    		int cara = Caras[i];
        	glVertex3f(Vertices[cara*3], Vertices[cara*3 + 1], Vertices[cara*3 + 2]);
    	}
		break;
	case 1: //Alambre
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_TRIANGLES);
		for (unsigned i=0;i<Caras.size();i++){
    		int cara = Caras[i];
        	glVertex3f(Vertices[cara*3], Vertices[cara*3 + 1], Vertices[cara*3 + 2]);
    	}
		break;
	case 2: //Solido
		glPolygonMode(GL_FRONT, GL_FILL);
		glBegin(GL_TRIANGLES);
		for (unsigned i=0;i<Caras.size();i++){
    		int cara = Caras[i];
        	glVertex3f(Vertices[cara*3], Vertices[cara*3 + 1], Vertices[cara*3 + 2]);
    	}
		break;
	case 3: //Ajedrez
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);

		glPolygonMode(GL_FRONT, GL_FILL);
		glBegin(GL_TRIANGLES);

		for (unsigned i=0;i<Caras.size();i++){
    		int cara = Caras[i];

    		if(i%3==0){
    			color++;
            }

            if (color%2==0){
                glColor3f(0, 1, 0);
            }else{
                glColor3f(1, 0, 0);
            }

        	glVertex3f(Vertices[cara*3], Vertices[cara*3 + 1], Vertices[cara*3 + 2]);
    	}
		break;

	default:
		glBegin(GL_POINTS);
        for (unsigned i=0;i<Caras.size();i++){
            int cara = Caras[i];
            glVertex3f(Vertices[cara*3], Vertices[cara*3 + 1], Vertices[cara*3 + 2]);
        }
        break;
	};


    glEnd();
}


