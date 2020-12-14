//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"
#include "file_ply_stl.h"
#include <cmath>

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
	glColor3f(0,0,0);
    glPointSize(4);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);

    int color=0; //variable usada para modo ajedrez
    switch(mode){
	case 0: //Vertices
		glBegin(GL_POINTS);
		for (unsigned i=0;i<Vertices.size();i = i + 3){
        	glVertex3f(Vertices[i], Vertices[i+1], Vertices[i+2]);
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

    case 4:
        glBegin(GL_LINES); // auxiliar para semicirculo
        for (unsigned i=0; i<Caras.size()-2; i++){
            int cara = Caras[i];
            glVertex3f(Vertices[cara*3], Vertices[cara*3 + 1], Vertices[cara*3 + 2]);
            //glVertex3f(Vertices[cara*3 + 6], Vertices[cara*3 + 7], Vertices[cara*3 + 8]);
        }
        break;

    case 5:
        glBegin(GL_LINES); // auxiliar para semicirculo
        for (unsigned i=0; i<Caras.size()-1; i++){
            int cara = Caras[i];
            glVertex3f(Vertices[cara*3], Vertices[cara*3 + 1], Vertices[cara*3 + 2]);
            glVertex3f(Vertices[cara*3 + 3], Vertices[cara*3 + 4], Vertices[cara*3 + 5]);
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

void DibujarPly(char *File_name, int mode){
	Figura nueva;
	_file_ply archi;
	int aux;

	aux = archi.open(File_name);
	aux = archi.read(nueva.vertices, nueva.caras);

	draw_mode(nueva.vertices, nueva.caras, mode);	
}

void GeneraSemicirculo(float radio, int n_cord_vertices, vector<float> &Vertices, vector<int> &Caras){
    // 2D EC. general circulo con cento en origen: x^2 + y^2 = r^2 --> y = sqrt(r^2 - x^2)

    float incremento = radio / (n_cord_vertices/2); //porque por cada valor de x salen 2 de y
    float x, y;
    int numero_cara=0;

    vector<float> aux;

    for(x=0; x<= radio; x=x+incremento){

        //primer punto
        Vertices.push_back(x);
        y = sqrt(radio*radio - x*x);
        Vertices.push_back(y);
        Vertices.push_back(0); //z siempre vale 0

        Caras.push_back(numero_cara);


        /*//punto espejo
        aux.push_back(x);
        aux.push_back(-y);
        aux.push_back(0); //z siempre vale 0*/

        /*Caras.push_back((n_cord_vertices - 1) - numero_cara);

        numero_cara++;*/

    }

    for(int i=aux.size()-1; i >= 0; i=i-3){ //Volcado de los puntos espejo al vector de vertices
        Vertices.push_back(aux[i-2]);
        Vertices.push_back(aux[i-1]);
        Vertices.push_back(aux[i-0]);
    }

}

void PintaSemicirculo(float radio, int n_cord_vertices){
    vector<float> Ver;
    vector<int> Caras;
    GeneraSemicirculo(radio, n_cord_vertices, Ver, Caras);

    draw_mode(Ver, Caras, 5);
}

void GenerarPorRevolucion(Figura &nueva, int divisiones, int d_mode){

    const double PI=3.14159265;
    int giros = divisiones,cont=0;
    int n_cord_vertices=nueva.vertices.size();
    nueva.vertices.reserve(n_cord_vertices*giros);

    for(int i=1;i<giros;i++){
        float angulo=(i*2*PI)/giros;
        float coseno=cos(angulo);
        float seno=sin(angulo);
        for(int j=0;j<n_cord_vertices;j = j+3){
            nueva.vertices.push_back(nueva.vertices[j]*coseno);
            nueva.vertices.push_back(nueva.vertices[j+1]);
            nueva.vertices.push_back(nueva.vertices[j]*seno);
        }
    }
    //Añadimos los puntos centrales de la tapa inferior y superior al final
    nueva.vertices.push_back(0);
    nueva.vertices.push_back(nueva.vertices[1]);
    nueva.vertices.push_back(0);

    nueva.vertices.push_back(0);
    nueva.vertices.push_back(nueva.vertices[n_cord_vertices -2]);
    nueva.vertices.push_back(0);

    n_cord_vertices=nueva.vertices.size();
    int n_vertices = n_cord_vertices / 3;
    int n_vertices_perfil = n_vertices / giros; // Y sobran los 2 ultimos puntos que son comunes a todos los perfiles.

    /*Orden de los vertices en sentido contrario a las agujas del reloj. Hay que tener en cuenta que en el vector los vertices están ordenados
    desde la parte inferior a la superior*/
    for(int i=0;i<giros;i++){
        //Tapa inferior
        nueva.caras.push_back(n_vertices - 2); //pto central inferior
        nueva.caras.push_back(i*n_vertices_perfil % (n_vertices - 2)); //primer punto del perfil = pto más infeior del perfil
        nueva.caras.push_back((i*n_vertices_perfil + n_vertices_perfil) % (n_vertices-2)); //primer punto del perfil contiguo
    }

    for(int i=0;i<giros;i++){
        
        //Tapa superior
        nueva.caras.push_back(n_vertices - 1); //pto central superior
        nueva.caras.push_back((i*n_vertices_perfil + 2 * n_vertices_perfil - 1) % (n_vertices-2)); //ultimo punto del perfil contiguo
        nueva.caras.push_back((i*n_vertices_perfil + n_vertices_perfil - 1) % (n_vertices - 2)); //ultimo punto del perfil = pto más superior del perfil
    }

    for(int i=0;i<giros;i++){

        //Caras entre perfiles
        for(int j=0; j<n_vertices_perfil-1; j++){
            //Cara inferior entre 4 ptos, 2 puntos del perfil actual y uno del siguiente
            nueva.caras.push_back(i*n_vertices_perfil + j);
            nueva.caras.push_back((i*n_vertices_perfil + j +1) % (n_vertices-2));
            nueva.caras.push_back((i*n_vertices_perfil + n_vertices_perfil + j+1) % (n_vertices-2));

            //Cara superior entre 4 ptos, 1 punto del pelfil actual y 2 del siguiente
            nueva.caras.push_back(i*n_vertices_perfil + j);
            nueva.caras.push_back((i*n_vertices_perfil + n_vertices_perfil + j+1) % (n_vertices-2));
            nueva.caras.push_back((i*n_vertices_perfil + n_vertices_perfil + j) % (n_vertices-2));
        }
    }
    
}

//Devuelve un vector con las normales de los vertices donde v[i] = normal[vertice_i].x, v[i+1] = normal[vertice_i].y, v[i+2] = normal[vertice_i].z
vector<float> GenerarNormalVertices(const vector<float> & cord_vertices, const vector<int> & caras){

    vector<float> cord_normal;
    vector<float> sumatoria_modulos;
    //vector<int> numero_caras_x_vertice;

    float[3] ab, bc, p_vectorial;
    float modulo_p_vectorial;

    //Inicializamos a 0 todas las normales, los modulos y el nº de caras por vertice.
    for(int i = 0; i < (cord_vertices.size() / 3); i++){
        cord_normal.push_back(0.0);
        cord_normal.push_back(0.0);
        cord_normal.push_back(0.0);

        sumatoria_modulos.push_back(0.0);

        numero_caras_x_vertice.push_back(0);
    }

    for(int n=0; n < caras.size(); n = n +3){
        ab[0] = cord_vertices[3*n] - cord_vertices[3*(n+1)]; //b - a
        ab[1] = cord_vertices[3*n +1] - cord_vertices[3*(n+1) +1];
        ab[2] = cord_vertices[3*n +2] - cord_vertices[3*(n+1) +2];

        bc[0] = cord_vertices[3*(n+1)] - cord_vertices[3*(n+2)]; //c - b
        bc[1] = cord_vertices[3*(n+1) +1] - cord_vertices[3*(n+2) +1];
        bc[3] = cord_vertices[3*(n+1) +2] - cord_vertices[3*(n+2) +2];

        p_vectorial[0] = ab[1]*bc[2] - (ab[2]*bc[1]);
        p_vectorial[1] = ab[2]*bc[0] - (ab[0]*bc[2]);
        p_vectorial[2] = ab[0]*bc[1] - (ab[1]*bc[0]);

        //Para cada pto perteneciente a la cara hacemos sumatoria de la normal de la cara actual
        //Primer pto de la cara
        cord_normal[3*(caras[n])] += p_vectorial[0]; //Accedemos a la cord X del primervertice  de la cara n y le añadimos la cord X de la normal de la cara
        cord_normal[3*(caras[n])+1] += p_vectorial[1];
        cord_normal[3*(caras[n])+2] += p_vectorial[2];
        //Seungdo pto de la cara
        cord_normal[3*(caras[n+1])] += p_vectorial[0];
        cord_normal[3*(caras[n+1])+1] += p_vectorial[1];
        cord_normal[3*(caras[n+1])+2] += p_vectorial[2];
        //Tercer pto de la cara
        cord_normal[3*(caras[n+2])] += p_vectorial[0];
        cord_normal[3*(caras[n+2])+1] += p_vectorial[1];
        cord_normal[3*(caras[n+2])+2] += p_vectorial[2];

        //normalizamos el producto vectorial resultante y lo añadimos a la sumatoria de esos vertices de la cara
        modulo_p_vectorial = sqrt((p_vectorial[0]*p_vectorial[0]) + (p_vectorial[1]*p_vectorial[1]) + (p_vectorial[2]*p_vectorial[2]));
        sumatoria_modulos[caras[n]] += modulo_p_vectorial;
        sumatoria_modulos[caras[n+1]] += modulo_p_vectorial;
        sumatoria_modulos[caras[n+2]] += modulo_p_vectorial;
        
        //Aumentamos el nº de caras al que pertenecen los vertices de esa cara
        /*numero_caras_x_vertice[caras[n]]++;
        numero_caras_x_vertice[caras[n+1]]++;
        numero_caras_x_vertice[caras[n+2]]++;*/
    }

    //Calculamos el vector normal al vertice como la sumatoria de los p_vectoriales de las caras comunes al punto entre sus modulos.
    for (int n = 0; n < cord_normal.size(); n = n + 3)
    {
        cord_normal[n] /= sumatoria_modulos[n/3];
        cord_normal[n+1] /= sumatoria_modulos[n/3];
        cord_normal[n+2] /= sumatoria_modulos[n/3];
    }

    return cord_normal;

}




