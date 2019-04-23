#include <iostream>
#include "arvoreb.h"
#include "commands.h"
using namespace std;

//ALUNOS: Luiz Felipe Duarte e João Kevin

int main(int argc, char const *argv[])
{
    RunCommandsInTreeB();
    return 0;

    //TESTE MANUAL
    ArvoreB treeb(3);
    treeb.imprimir();
    treeb.inserir(10);
    treeb.imprimir();
    treeb.inserir(20);
    treeb.imprimir();
    treeb.inserir(30);
    treeb.imprimir();
    treeb.inserir(15);
    treeb.imprimir();
    treeb.inserir(5);
    treeb.imprimir();
    //treeb.removerFirst();
    //treeb.removerLast();
    
    treeb.inserir(40);
    treeb.imprimir();
    treeb.inserir(50);
    treeb.imprimir();
    treeb.inserir(1);
    treeb.imprimir();
    treeb.inserir(3);
    treeb.imprimir();

    /*treeb.remover(1);
    treeb.imprimir();
    treeb.remover(50);
    treeb.imprimir();
    treeb.remover(15);
    treeb.imprimir();
    treeb.remover(3);
    treeb.imprimir();
    treeb.remover(10);
    treeb.imprimir();*/
    
    treeb.inserir(60);
    treeb.imprimir();
    treeb.inserir(70);
    treeb.imprimir();
    treeb.inserir(7);
    treeb.imprimir();
    treeb.inserir(13);
    treeb.imprimir();
    treeb.inserir(23);
    treeb.imprimir();
    treeb.inserir(25);
    treeb.imprimir();
    treeb.inserir(27);
    treeb.imprimir();
    treeb.inserir(33);
    treeb.imprimir();
    treeb.inserir(-100);
    treeb.imprimir();
    treeb.inserir(-200);
    treeb.imprimir();

    /*treeb.remover(10);
    treeb.imprimir();
    treeb.remover(13);
    treeb.imprimir();*/

    /*treeb.remover(50);
    treeb.imprimir();
    treeb.remover(60);
    treeb.imprimir();*/

    treeb.remover(23);
    treeb.imprimir();
    treeb.remover(40);
    treeb.imprimir();
    treeb.remover(33);
    treeb.imprimir();
    treeb.remover(13);
    treeb.imprimir();
    treeb.remover(5);
    treeb.imprimir();
    treeb.remover(60);
    treeb.imprimir();
    treeb.remover(-100);
    treeb.imprimir();
    treeb.remover(-200);
    treeb.imprimir();
    treeb.remover(1);
    treeb.imprimir();
    treeb.remover(3);
    treeb.imprimir();
    treeb.remover(20);
    treeb.imprimir();
    treeb.remover(15);
    treeb.imprimir();
    treeb.remover(50);
    treeb.imprimir();
    treeb.remover(70);
    treeb.imprimir();
    //treeb.printRaiz();
    treeb.remover(7);
    treeb.imprimir();
    //treeb.remover(25);
    //treeb.imprimir();
    //treeb.printRaiz();
    treeb.remover(27);
    treeb.imprimir();
    treeb.remover(10);
    treeb.imprimir();
    treeb.remover(25);
    treeb.imprimir();
    treeb.remover(30);
    treeb.imprimir();
    treeb.remover(0);
    treeb.imprimir();

    return 0;
}
