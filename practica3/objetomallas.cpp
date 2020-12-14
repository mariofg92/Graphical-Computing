#include "objetoMallas.h"


/*Constructores*/
objetoMallas::objetoMallas(objetoVertices &objVert, vector<int> & car)
{
    objetoVert=objVert;
    insertarCaras(car);

}

objetoMallas::objetoMallas(vector<float> &vertices, vector<int> & car){
    objetoVert.introducirVertices(vertices);

    insertarCaras(car);

}

/*Modificadores*/
void objetoMallas::insertarCaras(vector<int> & car){
    caras.resize(car.size()/3);


    for(unsigned int i=0; i<caras.size();i++){
        caras[i]._0=car[i*3+0];
        caras[i]._1=car[i*3+1];
        caras[i]._2=car[i*3+2];
    }
}

void objetoMallas::insertarVertices(vector<_vertex3f> & verti){
    objetoVert.introducirVertices(verti);
}


void objetoMallas::insertarVertices(vector<float>& ver){
    objetoVert.introducirVertices(ver);
}

void objetoMallas::introducirCaras(vector<_vertex3ui>& car){
     caras=car;
}


/*Dibujado*/

void objetoMallas::draw_vertices(){
    objetoVert.draw_vertices();
}


void objetoMallas::draw_aristas(){
    glColor3f(0,0,0);

    _vertex3f ad1,ad2,ad3;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin( GL_TRIANGLES ) ;
    for(unsigned int i= 0 ; i < caras.size() ; i++ ){
        ad1=objetoVert.get(caras[i]._0);
        ad2=objetoVert.get(caras[i]._1);
        ad3=objetoVert.get(caras[i]._2);

        glVertex3f(ad1.x,ad1.y,ad1.z) ;
        glVertex3f(ad2.x,ad2.y,ad2.z) ;
        glVertex3f(ad3.x,ad3.y,ad3.z) ;
    }
    glEnd() ;
}



void objetoMallas::draw_caras(float a,float b, float c){
    glColor3f(a,b,c);

    _vertex3f ad1,ad2,ad3;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin( GL_TRIANGLES ) ;


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for(unsigned int i= 0 ; i < caras.size() ; i++ ){
        ad1=objetoVert.get(caras[i]._0);
        ad2=objetoVert.get(caras[i]._1);
        ad3=objetoVert.get(caras[i]._2);

        glVertex3f(ad1.x,ad1.y,ad1.z) ;
        glVertex3f(ad2.x,ad2.y,ad2.z) ;
        glVertex3f(ad3.x,ad3.y,ad3.z) ;
    }
    glEnd() ;
}



void objetoMallas::draw_ajedrez(){
    glColor3f(1,0,0);
    _vertex3f ad1,ad2,ad3;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin( GL_TRIANGLES ) ;



    for(unsigned int i= 0 ; i < caras.size() ; i++ ){
        if(i%2){
                glColor3f(1,0,0);
        }
        else{
            glColor3f(0,1,0);
        }

        ad1=objetoVert.get(caras[i]._0);
        ad2=objetoVert.get(caras[i]._1);
        ad3=objetoVert.get(caras[i]._2);

        glVertex3f(ad1.x,ad1.y,ad1.z) ;
        glVertex3f(ad2.x,ad2.y,ad2.z) ;
        glVertex3f(ad3.x,ad3.y,ad3.z) ;
    }
    glEnd() ;

}


/*Generacion a traves de perfiles*/
void objetoMallas::modeladorotacion(int lados){
    bool tapaInferior=false,tapaSuperior=false;   
    _vertex3f supe,infe;
    int puntosNoTapa,acceso=0,max,puntosTapas=0,modulo,carastapas=0;
    double anguloAux,angulo,radio,cont=0;
    vector<vector<int> > aux;

    vector<_vertex3f> perfil = objetoVert.getVector();
    vector<_vertex3f> verticesnuevos;
    vector<_vertex3f> perfilgirar;

    max=puntosNoTapa=perfil.size();

    anguloAux=(3.14*2)/lados;

    if(perfil[perfil.size()-1].x==0){
        tapaSuperior=true;
        supe=perfil[perfil.size()-1];
        acceso=1;
        puntosTapas++;
    }
    if(perfil[0].x==0){
        tapaInferior=true;
        infe=perfil[0];
        max--;
        puntosTapas++;
    }

    puntosNoTapa-=puntosTapas;

    perfilgirar.resize(puntosNoTapa);

    /*PERFIL A GIRAR*/
    for(;acceso<max;acceso++){
        perfilgirar[cont]=perfil[acceso];
        cont++;
    }

    verticesnuevos.resize(lados*perfilgirar.size()+puntosTapas);

    acceso=0;

    /*GENERACION DE VERTICES*/
    for(int i=0;i<lados;i++){
        angulo=anguloAux*i;
        for(int j=perfilgirar.size()-1;j>=0;j--){
           radio=sqrt(perfilgirar[j].x*perfilgirar[j].x+perfilgirar[j].z*perfilgirar[j].z);
           verticesnuevos[acceso].x=radio*cos(angulo);
           verticesnuevos[acceso].z=radio*sin(angulo);
           verticesnuevos[acceso].y=perfilgirar[j].y;
           acceso++;
        }
    }

    //Añado vertices de las tapas
    if(tapaSuperior){
        carastapas=lados;
        verticesnuevos[acceso]=supe;
        acceso++;
    }
    if(tapaInferior){
        carastapas+=lados;
        verticesnuevos[acceso]=infe;
        acceso++;
    }

    objetoVert.introducirVertices(verticesnuevos);



    //GENERACION DE CARAS
    acceso=0;
    caras.resize((2*lados*(perfilgirar.size()-1) ) +carastapas);
    normalesCaras.resize((2*lados*(perfilgirar.size()-1) ) +carastapas);
    normalesVertices.resize(verticesnuevos.size());

    modulo=lados*perfilgirar.size();

    for(unsigned int i=0;i<perfilgirar.size()-1; i++){
        for(int j=0;j<lados;j++){
            caras[acceso]._0=(j*perfilgirar.size()+i)%modulo;
            caras[acceso]._1=((j+1)*perfilgirar.size()+i)%modulo;
            caras[acceso]._2=(j*perfilgirar.size()+i+1)%modulo;

            acceso++;

            caras[acceso]._0=((j+1)*perfilgirar.size()+i)%modulo;
            caras[acceso]._1=((j+1)*perfilgirar.size()+1+i)%modulo;
            caras[acceso]._2=(j*perfilgirar.size()+i+1)%modulo;


            acceso++;
        }
    }



    if(tapaSuperior){
        for(int i=0; i<lados;i++){
            caras[acceso]._0=(((i+1)*perfilgirar.size())-1)%modulo;
            caras[acceso]._1=(((i+2)*perfilgirar.size())-1)%modulo;
            caras[acceso]._2=verticesnuevos.size()-1;
            acceso++;

        }
    }

    if(tapaInferior && !tapaSuperior){
        for(int i=0; i<lados;i++){
            caras[acceso]._0=((i)*perfilgirar.size())%modulo;
            caras[acceso]._1=((i+1)*perfilgirar.size())%modulo;
            caras[acceso]._2=verticesnuevos.size()-1;

            acceso++;
        }
    }
    else if(tapaInferior && tapaSuperior){
        for(int i=0; i<lados;i++){
            caras[acceso]._0=((i)*perfilgirar.size())%modulo;
            caras[acceso]._1=((i+1)*perfilgirar.size())%modulo;
            caras[acceso]._2=verticesnuevos.size()-2;
            acceso++;
        }
    }


    /*printf("Vertices perfil %i\n",(int)perfil.size());
    printf("Caras generadas %i\n",(int)caras.size());
    printf("Vertices generados %i\n",(int)verticesnuevos.size());*/
}

