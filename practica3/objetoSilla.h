#ifndef OBJETOSILLA_H
#define OBJETOSILLA_H

#include "objetomallas.h"
#include <vector>

class objetoSilla{
    private:
        objetoMallas cubo;
        objetoMallas cilindro;
        objetoMallas conoTruncado;

    public:
        objetoSilla();

        void drawPata(char modo);

        void drawResorte(char modo);

        void drawAsiento(char modo);
    

        void drawRespaldo(char modo);

        void drawTodo(double alturaResorte, double gradosResorte, double gradosRespaldo, char modo);

        //Metodo final de dibujo (controla los grados de libertad)
        void draw(double & alturaResorte, double  &gradosResorte, double &gradosRespaldo, char modo);
};






#endif
