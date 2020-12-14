#include"objetoSilla.h"

#include<cmath>

objetoSilla::objetoSilla(){

    //Inicializamos el cubo
    vector<float> Vertices;
    Vertices.resize(12);
    Vertices[0]=0;//x
    Vertices[1]=1.0;//y
    Vertices[2]=0;//z

    Vertices[3]=0.5;//x
    Vertices[4]=1.0;//y
    Vertices[5]=0;//z


    Vertices[6]=0.5;//x
    Vertices[7]=0;//y
    Vertices[8]=0;//z

    Vertices[9]=0;//x
    Vertices[10]=0;//y
    Vertices[11]=0;//z
    cubo.insertarVertices(Vertices);
    cubo.modeladorotacion(4);


    //Inicializamos el cilindro
    //Usamos los mismos vertices del perfil para generarlo

    cilindro.insertarVertices(Vertices);
    cilindro.modeladorotacion(20);

    //Inicializamos el cono truncado

    Vertices.resize(12);
    Vertices[0]=0;//x
    Vertices[1]=1;//y
    Vertices[2]=0;//z

    Vertices[3]=0.5;//x
    Vertices[4]=1;//y
    Vertices[5]=0;//z


    Vertices[6]=1;//x
    Vertices[7]=0;//y
    Vertices[8]=0;//z

    Vertices[9]=0;//x
    Vertices[10]=0;//y
    Vertices[11]=0;//z

    conoTruncado.insertarVertices(Vertices);
    conoTruncado.modeladorotacion(20);
}


void objetoSilla::drawPata(char modo){
    glPushMatrix();

    glScalef(2.5,1,2.5);
    switch(modo){
        case 'p':
            conoTruncado.draw_vertices();
            break;
        case 's':
            conoTruncado.draw_caras(0,0,0);
            break;
        case 'a':
            conoTruncado.draw_ajedrez();
            break;
        case 'l':
            conoTruncado.draw_aristas();
            break;
    }
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(1.5,1,1.5);
    switch(modo){
        case 'p':
            cilindro.draw_vertices();
            break;
        case 's':
            cilindro.draw_caras(0,0,0);
            break;
        case 'a':
            cilindro.draw_ajedrez();
            break;
        case 'l':
            cilindro.draw_aristas();
            break;
    }
    glPopMatrix();
}

void objetoSilla::drawResorte(char modo){

    glPushMatrix();
    glScalef(0.75,2.5,0.75);
    switch(modo){
        case 'p':
            cilindro.draw_vertices();
            break;
        case 's':
            cilindro.draw_caras(0.6,0.6,0.6);
            break;
        case 'a':
            cilindro.draw_ajedrez();
            break;
        case 'l':
            cilindro.draw_aristas();
            break;
    }
    glPopMatrix();

}


void objetoSilla::drawAsiento(char modo){

    glPushMatrix();
    glScalef(7,0.75,7);
    switch(modo){
        case 'p':
            cubo.draw_vertices();
            break;
        case 's':
            cubo.draw_caras(0.7,0.1,0.1);
            break;
        case 'a':
            cubo.draw_ajedrez();
            break;
        case 'l':
            cubo.draw_aristas();
            break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.25, 0, 2.25);
    glScalef(2,0.5,2);
    switch(modo){
        case 'p':
            cubo.draw_vertices();
            break;
        case 's':
            cubo.draw_caras(0,0,0);
            break;
        case 'a':
            cubo.draw_ajedrez();
            break;
        case 'l':
            cubo.draw_aristas();
            break;
    }
    glPopMatrix();

}


void objetoSilla::drawRespaldo(char modo){

    glPushMatrix();
    glScalef(0.5,2,2);
    glRotatef(45, 0,1,0);
    
    switch(modo){
        case 'p':
            cubo.draw_vertices();
            break;
        case 's':
            cubo.draw_caras(0,0,0);
            break;
        case 'a':
            cubo.draw_ajedrez();
            break;
        case 'l':
            cubo.draw_aristas();
            break;
    }
    glPopMatrix();

    glPushMatrix();
    glScalef(0.75,5,5);
    glTranslatef(0,0.4,0);
    glRotatef(45,0,1,0);
    switch(modo){
        case 'p':
            cubo.draw_vertices();
            break;
        case 's':
            cubo.draw_caras(0.7,0.1,0.1);
            break;
        case 'a':
            cubo.draw_ajedrez();
            break;
        case 'l':
            cubo.draw_aristas();
            break;
    }
    glPopMatrix();

}


void objetoSilla::drawTodo(double alturaResorte, double gradosResorte, double gradosRespaldo, char modo){
    glPushMatrix();
        glRotatef(45,0,1,0);
        drawPata(modo);

        glTranslatef(0,alturaResorte,0);
        glRotatef(gradosResorte, 0,1,0);
        drawResorte(modo);
        
        glTranslatef(0,2.5,0);
        drawAsiento(modo);

        glRotatef(-45,0,1,0);
        glTranslatef(3.75,0.5,0);

        glRotatef(gradosRespaldo, 0,0,1);
        drawRespaldo(modo);

    glPopMatrix();
}

void objetoSilla::draw(double & alturaResorte, double  &gradosResorte, double &gradosRespaldo, char modo){
    if(alturaResorte>2){
        alturaResorte=2;
    }
    else if(alturaResorte<0){
        alturaResorte=0;
    }

    if(gradosRespaldo<-30){
        gradosRespaldo=-30;
    }
    else if(gradosRespaldo>0){
        gradosRespaldo=0;
    }

    drawTodo(alturaResorte, gradosResorte, gradosRespaldo, modo);
}


