//**************************************************************************
// Práctica 2
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "user_code.h"
#include "objetoSilla.h"

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//Variables usadas para la representacion
vector<float> vertices;
vector<int> caras;
_file_ply archi;
int aux;

objetoSilla silla;
objetoMallas ply, revolucion;

char modo='l';
int objeto=3;
double alturaResorte=0;
double gradosResorte=0;
double gradosRespaldo=0;


//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
    switch (modo) {
    case 'p':
        switch(objeto){
            case 1:
                ply.draw_vertices();
            break;
            case 2:
                revolucion.draw_vertices();
            break;
            case 3:
                silla.draw(alturaResorte,gradosResorte,gradosRespaldo,modo);
            break;
        }
        break;
    case 'l':
        switch(objeto){
            case 1:
                ply.draw_aristas();
            break;
            case 2:
                revolucion.draw_aristas();
            break;
            case 3:
                silla.draw(alturaResorte,gradosResorte,gradosRespaldo,modo);
            break;
        }
        break;
    case 's':
        switch(objeto){
            case 1:
                ply.draw_caras(0,0.5,0);
            break;
            case 2:
                revolucion.draw_caras(0,0.5,0);
            break;
            case 3:
                silla.draw(alturaResorte,gradosResorte,gradosRespaldo,modo);
            break;
        }
        break;
    case 'a':
        switch(objeto){
            case 1:
                ply.draw_ajedrez();
            break;
            case 2:
                revolucion.draw_ajedrez();
            break;
            case 3:
                silla.draw(alturaResorte,gradosResorte,gradosRespaldo,modo);
            break;
            }
        break;
    default:
        break;
    }
}



//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
    switch(Tecla1){
        case 'q':
            exit(0);
            break;
        case 'p':
            modo='p';
            break;
        case 'l':
            modo='l';
            break;
        case 's':
            modo='s';
            break;
        case 'a':
            modo='a';
            break;
        case '1':
            objeto=1;
            break;
        case '2':
            objeto=2;
            break;
        case '3':
            objeto=3;
            break;
         case 'C':
            alturaResorte += 0.2;
            break;
       case 'c':
            alturaResorte -= 0.2;
            break;
       case 'X':
            gradosResorte += 10;
            break;
       case 'x':
            gradosResorte -= 10;
            break;
       case 'Z':
            gradosRespaldo += 5;
            break;
       case 'z':
            gradosRespaldo -= 5;
            break;
        default:
            break;

    }

    glutPostRedisplay();
  
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_F1:Observer_distance*=1.2;break;
	case GLUT_KEY_F2:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
//Inicializmos el objeto leido del ply y el generado por revolución
aux = archi.open("beethoven.ply");
aux = archi.read(vertices, caras);
ply.insertarVertices(vertices);
ply.insertarCaras(caras);

vertices.clear();
caras.clear();

aux = archi.open("eje.ply");
aux = archi.read(vertices, caras);
revolucion.insertarVertices(vertices);
revolucion.insertarCaras(caras);
revolucion.modeladorotacion(20);

// se inicalizan la ventana y los planos de corte
Window_width=.5;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=7*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Práctica 1");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    cout << "Tecla p: Visualizar en modo puntos\nTecla l: Visualizar en modo lineas/aristas\nTecla s: Visualizar en modo solido\nTecla a: Visualizar en modo ajedrez";
    cout << "\nTecla 1: Activar objeto PLY cargado\nTecla 2: Activar objeto por revolucion\nTecla 3: Activar objeto jerarquico\nTecla Z/z: modifica primer grado de libertad del modelo jerarquico (aumenta/dismi- nuye)";
    cout << "\nTecla X/x: modifica segundo grado de libertad del modelo jerarquico (aumenta/dis- minuye)\nTecla C/c: modifica tercer grado de libertad del modelo jerarquico (aumenta/dismi- nuye)\n\n\n";

    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
