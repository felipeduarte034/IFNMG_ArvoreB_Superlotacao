#ifndef ARVOREB_H
#define ARVOREB_H

#include <iostream>
using namespace std;

class Nodo;
class RInfo //Retorna informações
{
public:
    bool isBreak;
    bool isInsert;
    Nodo* esq;
    Nodo* dir;
    int mediana;
    RInfo()
    {
        isBreak=false;
        isInsert=false;
        esq=NULL;
        dir=NULL;
        mediana=0;
    }
};

class Nodo
{
private:
    int* chaves; //#chaves[t-1, 2t-1]
    Nodo** filhos; //#filhos[2t+1] - vetor de ponteiros
    int len; //quantidade de chaves no nodo
    int maxf; //quantidade maxima de filhos

    bool insertChave(int k)
    {
        int i=len; //quantidade de chaves no nodo
        while(i>=1 && k<chaves[i-1]) //enquanto k < chave na ultima posiçao
        {
            chaves[i] = chaves[i-1]; //mover a chave para a direita
            i = i-1;
        }
        chaves[i]=k;
        len = len+1;
        return true;
    }
    bool removeChave(int k)
    {
        return false;
    }
public:
    bool isFolha=false;
    bool isRaiz=false;
    Nodo(int t) //t --> grau minimo
    {
        maxf = 2*t;
        chaves = new int[2*t]; //aloca (2*t) posições para folha superlotar
        filhos = new Nodo*[2*t];
        len=0;
        for(int i=0; i<maxf; i++)
            filhos[i]=NULL;
    }
    bool is_folha()
    {
        for(int i=0; i<maxf; i++)
        {
            if(filhos[i]!=NULL)
                return false;
        }
        return true;
    }
    void print() //printa as chaves em sequencia separadas por virgula
    {
        for(int i=0; i<len; i++)
        {
            cout << chaves[i];
            if(i<(len-1)) cout << " ";
        }
    }

friend class ArvoreB;
};

class ArvoreB
{
private:
    Nodo* raiz;
    void CreateRoot()
    {
        raiz = new Nodo(t);
        raiz->isFolha=true;
        raiz->isRaiz=true;
        raiz->len=0;
    }
    bool Search(Nodo* n, int k)
    {
        int i=0;
        while(i<n->len && k>n->chaves[i]) //ajusta o indice do filho
        {
            i+=1;
        }
        if(i<n->len && k==n->chaves[i]) //verica se a valor buscado está nas chaves do nodo
        {
            return true;
        }
        else if(n->is_folha()) //se for folha o elemento não está contido na arvore
        {
            return false;
        }
        return Search(n->filhos[i],k);
    }
    void Print(Nodo* n)
    {
        if(n->is_folha())
            n->print();
        for(int i=0; i<n->maxf; i++)
        {
            if(n->filhos[i] != NULL)
            {
                cout << "(";
                Print(n->filhos[i]);
                cout << ")";
                if(i < n->len)
                    cout << " " << n->chaves[i] << " ";
            }
        }
    }
    void BreakNodoRoot(Nodo* n)
    {
        int mediana = n->chaves[getIndMed(n->len)];

        Nodo* dir = new Nodo(t); //novo nodo irmão
        Nodo* s = new Nodo(t); //nova raiz
        n->isRaiz=false;
        //Nodo* esq = n;
        //raiz=s;
        s->isFolha=false;
        s->isRaiz=true;
        s->len=0;
        s->filhos[0]=n;
        raiz=s;
        int i=1;

        dir->isFolha=n->isFolha;
        for(int j=1; j<=(t); j++) //passa para dir as maiores chaves
        {
            dir->insertChave(n->chaves[j+(t-1)]);
        }
        if(!n->is_folha())
        {
            for(int j=dir->len, m=0; m<(dir->len+1); j--,m++)
            {
                dir->filhos[j] = n->filhos[j+t];
                n->filhos[j+t] = NULL;
            }
        }
        n->len=t-1; //ajusta a contagem de chaves para o nodo com as menores chaves

        for(int j=n->len+1; j<(i+1); j++)
        {
            n->filhos[j+1] = n->filhos[j]; //empurra os filhos para direita
        }
        s->filhos[i]=dir; //inserem dir como filho de n
        for(int j=n->len; j<i; j++)
        {
            n->chaves[j+1] = n->chaves[j];
        }
        s->chaves[i-1] = mediana;//sobe a mediana para a nova raiz
        s->len = s->len+1; //ajusta a contagem de chaves de n
    }
    RInfo* BreakNodo(Nodo* n, int i)
    {
        int mediana = n->chaves[getIndMed(n->len)];
        Nodo* dir = new Nodo(t);
        for(int j=1; j<=(t); j++) //passa para dir as maiores chaves
        {
            dir->insertChave(n->chaves[j+(t-1)]);
        }
        if(!n->is_folha())
        {
            for(int j=dir->len, m=0; m<(dir->len+1); j--,m++)
            {
                dir->filhos[j] = n->filhos[j+t];
                n->filhos[j+t] = NULL;
            }
        }
        n->len=t-1; //ajusta a contagem de chaves para o nodo com as menores chaves
        for(int j=n->len+1; j>i; j--) //inserem dir como filho de n
        {
            n->filhos[j+1] = n->filhos[j]; //empurra os filhos para direita
        }
        //n->filhos[i+1] = dir; //inserem dir como filho de n
        for(int j=n->len-1; j>=i; j--)
        {
            n->chaves[j+1] = n->chaves[j];
        }

        RInfo* rinfo = new RInfo();
        rinfo->isBreak=true;
        rinfo->dir = dir;
        rinfo->mediana = mediana;
        return rinfo;
    }
    RInfo* inserirMediana(Nodo* n, RInfo* info, int i)
    {
        RInfo* rinfo;
        bool isIserted = n->insertChave(info->mediana); //inseri a mediana no vetor de chaves

        for(int j=n->len+1; j>i; j--) //inserem dir como filho de n
        {
            if(j<n->maxf)
                n->filhos[j+1] = n->filhos[j]; //empurra os filhos para direita
        }
        n->filhos[i+1] = info->dir; //coloca o novo nodo dir, como filho
        if(n->len > (2*t-1)) //nodo superlotado
        {
            if(n->isRaiz)
            {
                BreakNodoRoot(n);
                rinfo = new RInfo();
                rinfo->isInsert = isIserted;
                return rinfo;
            }
            else
            {
                rinfo = BreakNodo(n, i);
                rinfo->isInsert = isIserted;
                return rinfo;
            }
        }
        rinfo = new RInfo();
        rinfo->isInsert = isIserted;
        return rinfo;
    }
    int getIndMed(int tam) //retorna o indice da mediana
    {
        if(tam%2==0) //numero par de chaves
            return (tam/2)-1;
        else //numero impar de chaves
            return tam/2;
    }
    RInfo* Insert(Nodo* n, int k)
    {
        RInfo* rinfo;
        bool isInserted=false;
        int i=n->len; //quantidade de chaves no nodo
        while(i>=1 && k<n->chaves[i-1]) //determina o filho de n
        {
            i-=1;
        }
        
        if(n->is_folha())
        {
            for(int j=0; j<n->len; j++)
            {
                if(k==n->chaves[j]) //Não inserir valor repetido.
                {
                    //cout << "ALERT! "<< k << " ja existe na TREE." << endl;
                    rinfo = new RInfo();
                    rinfo->isInsert=false;
                    return rinfo;
                }
            }

            isInserted = n->insertChave(k);
            if(n->len > (2*t-1)) //folha superlotada
            {
                if(n->isRaiz)
                {
                    BreakNodoRoot(n);
                    rinfo = new RInfo();
                    rinfo->isInsert = isInserted;
                    return rinfo;
                }
                else
                {
                    rinfo = BreakNodo(n,i);
                    rinfo->isInsert = isInserted;
                    return rinfo;
                }
            }
        }
        else
        {
            rinfo = Insert(n->filhos[i],k);
            if(rinfo->isBreak)
            {
                return inserirMediana(n,rinfo,i);
            }
        }
        rinfo = new RInfo();
        rinfo->isInsert = isInserted;
        return rinfo;
    }
public:
    int t; //grau minimo
    ArvoreB(int arg_grau_min)
    {
        t=arg_grau_min;
        CreateRoot();
        //cout << "(grau min) t = " << arg_grau_min << endl;
    }
    bool buscar(int valor)
    {
        if(raiz==NULL)
        {
            cout << "BUSCA não pode ser executada, RAIZ == NULL"<<endl;
            return false;
        }
        return Search(raiz,valor);
    }
    bool inserir(int valor)
    {
        //Insert2(valor);
        RInfo* info = Insert(raiz,valor);
        return info->isInsert;
    }
    void imprimir()
    {
        cout << "(";
        Print(raiz);
        cout << ")"<<endl;
    }
    void printRaiz()
    {
        cout << "[";
        raiz->print();
        cout << "]";
        cout << " ---> ";
        for(int i=0; i<raiz->maxf; i++)
        {
            cout << "(";
            if(raiz->filhos[i] != NULL)
                raiz->filhos[i]->print();
            cout << ")";
        }
        cout<<endl;
    }
    bool printNodoAndChild(Nodo* n)
    {
        if(n == NULL)
        {
            cout << "ALERT! printNodoAndChild(): n == NULL. ";
            return false;
        }
        cout << "Nodo: [";
        n->print();
        cout << "]";
        cout << " ---> ";
        for(int i=0; i<n->maxf; i++)
        {
            cout << "(";
            if(n->filhos[i] != NULL)
                n->filhos[i]->print();
            cout << ")";
        }
        cout<<endl;
        return true;
    }
};

#endif