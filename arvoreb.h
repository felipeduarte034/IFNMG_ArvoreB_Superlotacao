#ifndef ARVOREB_H
#define ARVOREB_H

#include <iostream>
using namespace std;

class Nodo;
class IInfo //Retorna informações da Inserção
{
public:
    bool isBreak;
    bool isInsert;
    Nodo *dir;
    int mediana;
    IInfo()
    {
        isBreak = false;
        isInsert = false;
        dir = NULL;
        mediana = 0;
    }
};

class Nodo
{
private:
    int *chaves;   //#chaves[t-1, 2t-1]
    Nodo **filhos; //#filhos[2t+1] - vetor de ponteiros
    int len;       //quantidade de chaves no nodo
    int maxf;      //quantidade maxima de filhos

    bool insertChave(int k)
    {
        int i = len;                        //quantidade de chaves no nodo
        while (i >= 1 && k < chaves[i - 1]) //enquanto k < chave na ultima posiçao
        {
            chaves[i] = chaves[i - 1]; //mover a chave para a direita
            i = i - 1;
        }
        chaves[i] = k;
        len = len + 1;
        return true;
    }
    int insertChaveGetPos(int k)
    {
        int i = len;                        //quantidade de chaves no nodo
        while (i >= 1 && k < chaves[i - 1]) //enquanto k < chave na ultima posiçao
        {
            chaves[i] = chaves[i - 1]; //mover a chave para a direita
            i = i - 1;
        }
        chaves[i] = k;
        len = len + 1;
        return i;
    }
    bool removeChave(int position)
    {
        if (len < 1 || position < 0 || position >= len)
            return false;

        int i = position; //quantidade de chaves no nodo
        while (i < len)   //enquanto k < chave na ultima posiçao
        {
            chaves[i] = chaves[i + 1]; //mover a chave para a esquerda
            i = i + 1;
        }
        len = len - 1;
        return true;
    }
    bool setChave(int position, int k)
    {
        if (len < 1 || position < 0 || position >= len)
            return false;
        chaves[position] = k;
        return true;
    }
    int removeChaveInPos(int position)
    {
        if (len < 1 || position < 0 || position >= len)
            return 0;
        int n = chaves[position];
        int i = position; //quantidade de chaves no nodo
        while (i < len)   //enquanto k < chave na ultima posiçao
        {
            chaves[i] = chaves[i + 1]; //mover a chave para a esquerda
            i = i + 1;
        }
        len = len - 1;
        return n;
    }
    int getIndice(int k)
    {
        int i = 0;      //quantidade de chaves no nodo
        while (i < len) //enquanto k < chave na ultima posiçao
        {
            if (k == chaves[i])
                return i;
            i = i + 1;
        }
        return -1;
    }
    int removeFirstChave()
    {
        if (len < 1)
            return 0;
        int p = 0;
        int n = chaves[p];
        removeChave(p);
        return n;
    }
    int removeLastChave()
    {
        if (len < 1)
            return 0;
        int p = len - 1;
        int n = chaves[p];
        removeChave(p);
        return n;
    }

public:
    bool isFolha = false;
    bool isRaiz = false;
    Nodo(int t) //t --> grau minimo
    {
        maxf = 2 * t + 1;
        chaves = new int[2 * t]; //aloca (2*t) posições para folha superlotar
        filhos = new Nodo *[2 * t + 1];
        len = 0;
        for (int i = 0; i < maxf; i++)
            filhos[i] = NULL;
    }
    bool is_folha()
    {
        for (int i = 0; i < maxf; i++)
        {
            if (filhos[i] != NULL)
                return false;
        }
        return true;
    }
    void print() //printa as chaves em sequencia separadas por virgula
    {
        for (int i = 0; i < len; i++)
        {
            cout << chaves[i];
            if (i < (len - 1))
                cout << " ";
        }
    }
    friend class ArvoreB;
};

class RInfo //Retorna informações da Remoção
{
public:
    Nodo *n;
    int num;
    int i;
    int deep;
    RInfo()
    {
        n = NULL;
        num = -1;
        i = -1;
        deep = -1;
    }
    RInfo(Nodo *_nodo, int _num, int _i, int _deep)
    {
        n = _nodo;
        num = _num;
        i = _i;
        deep = _deep;
    }
    void print()
    {
        cout << "RINFO --> num: " << num << "  i: " << i << "  deep: " << deep << "  n: ";
        n->print();
        cout << " \n";
    }
};

class ArvoreB
{
private:
    Nodo *raiz;
    void CreateRoot()
    {
        raiz = new Nodo(t);
        raiz->isFolha = true;
        raiz->isRaiz = true;
        raiz->len = 0;
    }
    bool Search(Nodo *n, int k)
    {
        int i = 0;
        while (i < n->len && k > n->chaves[i]) //ajusta o indice do filho
        {
            i += 1;
        }
        if (i < n->len && k == n->chaves[i]) //verica se a valor buscado está nas chaves do nodo
        {
            return true;
        }
        else if (n->is_folha()) //se for folha o elemento não está contido na arvore
        {
            return false;
        }
        return Search(n->filhos[i], k);
    }
    void Print(Nodo *n)
    {
        if (n->is_folha())
            n->print();
        for (int i = 0; i < n->maxf; i++)
        {
            if (n->filhos[i] != NULL)
            {
                cout << "(";
                Print(n->filhos[i]);
                cout << ")";
                if (i < n->len)
                    cout << " " << n->chaves[i] << " ";
            }
        }
    }
    int getIndMed(int tam) //retorna o indice da mediana
    {
        if (tam % 2 == 0) //numero par de chaves
            return (tam / 2) - 1;
        else //numero impar de chaves
            return tam / 2;
    }
    void SplitNodoRoot(Nodo *n)
    {
        int m = getIndMed(n->len);
        int mediana = n->chaves[m];

        Nodo *dir = new Nodo(t); //novo nodo irmão
        Nodo *s = new Nodo(t);   //nova raiz
        n->isRaiz = false;
        s->isFolha = false;
        s->isRaiz = true;
        s->filhos[0] = n;   //insere n como filho da nova raiz
        s->filhos[1] = dir; //insere dir como filho da nova raiz
        raiz = s;

        int j = m + 1, d = 0;
        for (; j < n->maxf - 1; j++, d++) // passa da esq para a dir, as maiores chaves, a partir da mediana
        {
            dir->insertChave(n->chaves[j]);
            dir->filhos[d] = n->filhos[j];
            n->filhos[j] = NULL;
        }
        dir->filhos[d] = n->filhos[j];
        n->filhos[j] = NULL;
        n->len = t - 1; //ajusta a contagem de chaves para o nodo com as menores chaves
        s->insertChave(mediana);
    }
    IInfo *SplitNodo(Nodo *n, int i)
    {
        int m = getIndMed(n->len);
        int mediana = n->chaves[m];
        Nodo *dir = new Nodo(t);

        int j = m + 1, d = 0;
        for (; j < n->maxf - 1; j++, d++) // passa da esq para a dir, as maiores chaves, a partir da mediana
        {
            dir->insertChave(n->chaves[j]);
            dir->filhos[d] = n->filhos[j];
            n->filhos[j] = NULL;
        }
        dir->filhos[d] = n->filhos[j];
        n->filhos[j] = NULL;
        n->len = t - 1; //ajusta a contagem de chaves para o nodo com as menores chaves

        IInfo *rinfo = new IInfo();
        rinfo->isBreak = true;
        rinfo->dir = dir;
        rinfo->mediana = mediana;
        return rinfo;
    }
    IInfo *insertMediana(Nodo *n, IInfo *info, int i)
    {
        IInfo *rinfo;
        bool isIserted = n->insertChave(info->mediana); //inseri a mediana no vetor de chaves

        int j = n->maxf - 1;
        while (j > i) //empurra os filhos para direita, até chegar no indice da mediana.
        {
            n->filhos[j] = n->filhos[j - 1];
            j--;
        }
        n->filhos[i + 1] = info->dir; //coloca o novo nodo dir, como filho

        if (n->len > (2 * t - 1)) //nodo superlotado
        {
            if (n->isRaiz)
            {
                SplitNodoRoot(n);
                rinfo = new IInfo();
                rinfo->isInsert = isIserted;
                return rinfo;
            }
            else
            {
                rinfo = SplitNodo(n, i);
                rinfo->isInsert = isIserted;
                return rinfo;
            }
        }
        rinfo = new IInfo();
        rinfo->isInsert = isIserted;
        return rinfo;
    }
    IInfo *Insert(Nodo *n, int k)
    {
        IInfo *rinfo;
        bool isInserted = false;
        int i = n->len;                        //quantidade de chaves no nodo
        while (i >= 1 && k < n->chaves[i - 1]) //determina o filho de n
            i -= 1;

        if (n->is_folha())
        {
            for (int j = 0; j < n->len; j++)
            {
                if (k == n->chaves[j]) //Não inserir valor repetido.
                {
                    rinfo = new IInfo();
                    rinfo->isInsert = false;
                    return rinfo;
                }
            }

            isInserted = n->insertChave(k);
            if (n->len > (2 * t - 1)) //folha superlotada
            {
                if (n->isRaiz)
                {
                    SplitNodoRoot(n);
                    rinfo = new IInfo();
                    rinfo->isInsert = isInserted;
                    return rinfo;
                }
                else
                {
                    rinfo = SplitNodo(n, i);
                    rinfo->isInsert = isInserted;
                    return rinfo;
                }
            }
        }
        else
        {
            rinfo = Insert(n->filhos[i], k);
            if (rinfo->isBreak)
                return insertMediana(n, rinfo, i);
        }
        rinfo = new IInfo();
        rinfo->isInsert = isInserted;
        return rinfo;
    }
    bool validarNodoFolha2(Nodo *n, int i) //i --> indice do filho com len<(t-1)
    {
        //cout << "    validarNodoFolha(): ";
        imprimir();
        Nodo *f = NULL;
        Nodo *irmao = NULL;
        int tam, e;
        if (i > 0) //possui irmao a esquerda
        {
            f = n->filhos[i];
            irmao = n->filhos[i - 1];
            tam = irmao->len;
            if (tam > (t - 1))
            {
                //cout << "    irmao esq - tam: " << tam << endl;
                e = irmao->removeLastChave(); //ultima chave - antecessor
                //cout << "    e: " << e << endl;
                n->insertChave(e);
                e = n->removeChaveInPos(i);
                //cout << "    e: " << e << endl;
                f->insertChave(e);
                return true;
            }
        }
        else if (i < (2 * t)) //possui irmao a direita
        {
            f = n->filhos[i];
            irmao = n->filhos[i + 1];
            tam = irmao->len;
            if (tam > (t - 1))
            {
                //cout << "    irmao dir - tam: " << tam << endl;
                e = irmao->removeFirstChave(); //primeira chave - sucessor
                //cout << "    e: " << e << endl;
                n->insertChave(e);
                e = n->removeChaveInPos(i);
                //cout << "    e: " << e << endl;
                f->insertChave(e);
                return true;
            }
        }

        if (n->filhos[i]->len < (t - 1) && n->isRaiz && n->len == 1)
        {
            cout << "    nodo folha len=0 && raiz len=1  validarNodoFolha()" << endl;
            Nodo *esq = n->filhos[0];
            Nodo *dir = n->filhos[1];
            /*cout << "    esq: ";
            printNodoAndChild(esq);
            cout << "    dir: ";
            printNodoAndChild(dir);*/
            esq->insertChave(n->removeFirstChave());
            int j = 0, m = 0;
            for (; j < dir->len; j++, m++) //copia as chaves do DIR para ESQ
            {
                esq->insertChave(dir->chaves[j]);
                esq->filhos[m] = dir->filhos[j];
            }
            esq->filhos[m] = dir->filhos[j];
            raiz = esq;
            return true;
        }

        //cout << "    MESCLAR validarNodoFolha()  i: " << i << endl;
        f = n->filhos[i];
        if (i > 0) //possui irmao a esquerda
        {
            irmao = n->filhos[i - 1];
            //cout << "    possui irmao a esquerda: ";
            //printNodoAndChild(irmao);

            //if((i-1)<n->len)
            //    cout << "    pos valida n->chaves[i-1]: " << n->chaves[i-1] << endl;
            e = n->removeChaveInPos(i - 1);
            //cout << "    e: " << e << endl;
            irmao->insertChave(e);
            for (int j = 0; j < f->len; j++) //copia as chaves do F para IRMAO
            {
                irmao->insertChave(f->chaves[j]);
            }
            //n->filhos[i] = NULL;
            for (int j = i; j <= n->len; j++) //move os filhos para esquerda
            {
                //cout << "    j: " << j << "  n->len: " << n->len << endl;
                n->filhos[j] = n->filhos[j + 1];
            }
            n->filhos[n->len + 1] = NULL;
            return true;
        }
        else if (i < (2 * t)) //possui irmao a direita
        {
            irmao = n->filhos[i + 1];
            //cout << "    possui irmao a direita: ";
            //printNodoAndChild(irmao);

            //if((i+1)<n->len)
            //    cout << "    pos valida n->chaves[i]: " << n->chaves[i] << endl;
            e = n->removeChaveInPos(i);
            //cout << "    e: " << e << endl;
            irmao->insertChave(e);
            for (int j = 0; j < f->len; j++) //copia as chaves do F para IRMAO
            {
                irmao->insertChave(f->chaves[j]);
            }
            //n->filhos[i] = NULL;
            //printRaiz();
            for (int j = i; j <= n->len; j++) //move os filhos para esquerda
            {
                //cout << "    j: " << j << "  n->len: " << n->len << endl;
                n->filhos[j] = n->filhos[j + 1];
            }
            n->filhos[n->len + 1] = NULL;
            //printRaiz();
            return true;
        }
        return false;
    }
    bool validarNodoNaoFolha2(Nodo *n, int pos)
    {
        //doacaoDoFilhoParaNodoNaoFolha
        Nodo *f = n->filhos[pos]; //filho esq
        int tam = f->len, e, ind;
        if (tam > (t - 1)) //filho da esquerda pode doar
        {
            //cout << "    filho esq - tam: " << tam << endl;
            e = f->chaves[tam - 1]; //ultima chave - antecessor
            //cout << "    e: " << e << endl;
            n->insertChave(e);
            ind = f->getIndice(e);
            f->removeChave(ind);
            return true;
        }
        else
        {
            f = n->filhos[pos + 1]; //filho dir
            tam = f->len;
            if (tam > (t - 1)) //filho da dir pode doar
            {
                //cout << "    filho dir - tam: " << tam << endl;
                e = f->chaves[0]; //primeira chave - sucessor
                //cout << "    e: " << e << endl;
                n->insertChave(e);
                ind = f->getIndice(e);
                f->removeChave(ind);
                return true;
            }
        }

        if (n->isRaiz && n->len == 0) //se a raiz fica com 0 chaves, e nenhum filho puder doar, mesclar os dois filhos
        {
            cout << "    raiz len=0  validarNodoNaoFolha()" << endl;
            Nodo *esq = n->filhos[0];
            Nodo *dir = n->filhos[1];
            /*cout << "    esq: ";
            printNodoAndChild(esq);
            cout << "    dir: ";
            printNodoAndChild(dir);*/

            int j = 0, m = 0;
            for (; j < dir->len; j++, m++) //copia as chaves do DIR para ESQ
            {
                esq->insertChave(dir->chaves[j]);
                esq->filhos[m] = dir->filhos[j];
            }
            esq->filhos[m] = dir->filhos[j];
            raiz = esq;
            return true;
        }

        //cout << "    MESCLAR validarNodoNaoFolha()" << endl;
        //mesclar filhos
        f = n->filhos[pos];
        Nodo *irmao = n->filhos[pos + 1];
        for (int i = 0; i < irmao->len; i++) //copia as chaves do IRMAO para F
        {
            f->insertChave(irmao->chaves[i]);
        }
        for (int i = pos + 1; i <= n->len; i++) //move os filhos para esquerda
        {
            //cout << "    i: " << i << "  n->len: " << n->len << endl;
            n->filhos[i] = n->filhos[i + 1];
        }
        n->filhos[n->len + 1] = NULL;

        return false;
    }
    bool validarNodoFaxina(Nodo* n, int i) //i --> indice do filho com len<(t-1)
    {
        //cout << "    validarNodoFolha(): ";
        //imprimir();
        Nodo *f = NULL;
        Nodo *irmao = NULL;
        int tam, e;

        //!DOAÇÃO
        if (i > 0) //possui irmao a esquerda
        {
            f = n->filhos[i];
            irmao = n->filhos[i - 1];
            tam = irmao->len;
            if (tam > (t - 1))
            {
                //cout << "    irmao esq - tam: " << tam << endl;
                e = irmao->removeLastChave(); //ultima chave - antecessor
                //cout << "    e: " << e << endl;
                n->insertChave(e);
                e = n->removeChaveInPos(i);
                //cout << "    e: " << e << endl;
                //f->insertChave(e);
                int ind = f->insertChaveGetPos(e);

                //DESTINATARIO
                for (int j=f->len; j<=ind+1; j++) //move os filhos para direita
                {
                    //cout << "    j: " << j << "  ind+1: " << ind+1 << endl;
                    f->filhos[j+1] = f->filhos[j];
                }
                f->filhos[ind+1] = irmao->filhos[0]; //doação
                //REMETENTE
                for (int j=i; j<=irmao->len; j++) //move os filhos para esquerda
                {
                    //cout << "    j: " << j << "  irmao->len: " << irmao->len << endl;
                    //cout << "    j: (";
                    //irmao->filhos[j]->print();
                    //cout << ")    j+1: ";
                    //irmao->filhos[j+1]->print();
                    //cout << ")"<<endl;
                    irmao->filhos[j] = irmao->filhos[j+1];
                }
                irmao->filhos[irmao->len+1] = NULL;

                return true;
            }
        }
        if (i < (n->len)) //possui irmao a direita
        {
            //cout << "    AQUI! i: " << i << " ";
            //printNodoAndChild(n);
            f = n->filhos[i];
            irmao = n->filhos[i+1];
            tam = irmao->len;
            if (tam > (t - 1))
            {
                //cout << "    irmao dir - tam: " << tam << endl;
                e = irmao->removeFirstChave(); //primeira chave - sucessor
                //cout << "    e: " << e << endl;
                n->insertChave(e);
                e = n->removeChaveInPos(i);
                //cout << "    e: " << e << endl;
                //f->insertChave(e);
                int ind = f->insertChaveGetPos(e);
                
                //DESTINATARIO
                for (int j=f->len; j<=ind+1; j++) //move os filhos para direita
                {
                    //cout << "    j: " << j << "  ind+1: " << ind+1 << endl;
                    f->filhos[j+1] = f->filhos[j];
                }
                f->filhos[ind+1] = irmao->filhos[0]; //doação
                //REMETENTE
                for (int j=i; j<=irmao->len; j++) //move os filhos para esquerda
                {
                    //cout << "    j: " << j << "  irmao->len: " << irmao->len << endl;
                    //cout << "    j: (";
                    //irmao->filhos[j]->print();
                    //cout << ")    j+1: ";
                    //irmao->filhos[j+1]->print();
                    //cout << ")"<<endl;
                    irmao->filhos[j] = irmao->filhos[j+1];
                }
                irmao->filhos[irmao->len+1] = NULL;

                return true;
            }
        }

        //!MESCLAR
        //cout << "    MESCLAR validarNodoFolha()  i: " << i << endl;
        f = n->filhos[i];
        if (i > 0) //possui irmao a esquerda
        {
            irmao = n->filhos[i - 1];
            //cout << "    possui irmao a esquerda: ";
            //printNodoAndChild(irmao);

            //if((i-1)<n->len)
            //    cout << "    pos valida n->chaves[i-1]: " << n->chaves[i-1] << endl;
            e = n->removeChaveInPos(i - 1);
            //cout << "    e: " << e << endl;
            irmao->insertChave(e);
            for (int j = 0; j < f->len; j++) //copia as chaves do F para IRMAO
            {
                irmao->insertChave(f->chaves[j]);
            }
            //n->filhos[i] = NULL;
            for (int j = i; j <= n->len; j++) //move os filhos para esquerda
            {
                //cout << "    j: " << j << "  n->len: " << n->len << endl;
                n->filhos[j] = n->filhos[j + 1];
            }
            n->filhos[n->len + 1] = NULL;
            return true;
        }
        else if (i < (2 * t)) //possui irmao a direita
        {
            
            irmao = n->filhos[i + 1];
            //cout << "    possui irmao a direita: ";
            //printNodoAndChild(irmao);

            //if((i+1)<n->len)
            //    cout << "    pos valida n->chaves[i]: " << n->chaves[i] << endl;
            e = n->removeChaveInPos(i);
            //cout << "    e: " << e << endl;
            irmao->insertChave(e);
            for (int j = 0; j < f->len; j++) //copia as chaves do F para IRMAO
            {
                irmao->insertChave(f->chaves[j]);
            }
            //n->filhos[i] = NULL;
            //printRaiz();
            for (int j = i; j <= n->len; j++) //move os filhos para esquerda
            {
                //cout << "    j: " << j << "  n->len: " << n->len << endl;
                n->filhos[j] = n->filhos[j + 1];
            }
            n->filhos[n->len + 1] = NULL;
            //printRaiz();
            return true;
        }
        return false;
    }
    RInfo* RemoveAntecessor(Nodo *n, int i, int deep)
    {
        if (n->is_folha())
        {
            int num = n->removeLastChave();
            return new RInfo(n, num, i, deep);
        }
        int j = n->len; //chegar na folha, sempre descendo pela direita
        return RemoveAntecessor(n->filhos[j], j, deep + 1);
    }
    bool faxina(Nodo* n, Nodo* f, int pos, RInfo* rinfo, int deep)
    {
        //cout << "    faxina() " << endl;
        if( (rinfo->deep-1) == deep) //quando chegar o nodo pai
        {
            //cout << "    --> ";
            //printNodoAndChild(n);
            return validarNodoFolha(n,rinfo->i);
            //return true;
        }
        //int j = n->len;                        //quantidade de chaves no nodo
        //while (j >= 1 && rinfo->num < n->chaves[j - 1]) //determina o filho de n
        //    j -= 1;
        int j = n->len; //chegar na folha, sempre descendo pela direita
        bool resp = faxina(f,f->filhos[j],j,rinfo,deep+1);
        if (f->len < (t - 1))
        {
            //cout << "    f: ";
            //printNodoAndChild(f);
            //cout << "    n: ";
            //printNodoAndChild(n);
            validarNodoFaxina(n,pos);
            //printRaiz();
            return true;
        }
        return resp;
    }
    bool validarNodoNaoFolha(Nodo *n, int pos)
    {
        RInfo *rinfo = RemoveAntecessor(n->filhos[pos], pos, 1);
        int num = rinfo->num;
        n->setChave(pos, num);
        if (rinfo->n->len < (t - 1))
        {
            //cout <<  "\n     NODO FOLHA INVALIDO:  ";
            //printNodoAndChild(rinfo->n);
            //rinfo->print();
            faxina(n,n->filhos[pos],pos,rinfo,0);
        }
        return true;
    }
    bool validarNodoFolha(Nodo* n, int i) //i --> indice do filho com len<(t-1)
    {
        //cout << "    validarNodoFolha(): ";
        //imprimir();
        //cout << "    n: ";
        //printNodoAndChild(n);

        Nodo *f = NULL;
        Nodo *irmao = NULL;
        int tam, e;

        //!DOAÇÃO
        if (i > 0) //possui irmao a esquerda
        {
            f = n->filhos[i];
            irmao = n->filhos[i - 1];
            tam = irmao->len;
            if (tam > (t - 1))
            {
                //cout << "    irmao esq - tam: " << tam << endl;
                e = irmao->removeLastChave(); //ultima chave - antecessor
                //cout << "    e: " << e << endl;
                n->insertChave(e);
                e = n->removeChaveInPos(i);
                //cout << "    e: " << e << endl;
                f->insertChave(e);
                return true;
            }
        }

        //if (i < (2 * t)) //possui irmao a direita
        if (i < (n->len)) //possui irmao a direita
        {
            //cout << "    AQUI! i: " << i << " ";
            //printNodoAndChild(n);
            f = n->filhos[i];
            irmao = n->filhos[i+1];
            tam = irmao->len;
            if (tam > (t - 1))
            {
                //cout << "    irmao dir - tam: " << tam << endl;
                e = irmao->removeFirstChave(); //primeira chave - sucessor
                //cout << "    e: " << e << endl;
                n->insertChave(e);
                e = n->removeChaveInPos(i);
                //cout << "    e: " << e << endl;
                f->insertChave(e);
                return true;
            }
        }

        f = n->filhos[i];
        if(n->filhos[i]->len < (t-1) && n->isRaiz && n->len == 1)// se for a raiz com apenas uma chave
        {
            cout << "    ###########  nodo folha len=0 && raiz len=1  validarNodoFolha()" << endl;
            //printNodoAndChild(irmao);
            //cout << "    i: "<<i<<"  n: ";
            //printNodoAndChild(n);

            if((i-1)<n->len && i>0)
                cout << "    pos valida n->chaves[i-1]: " << n->chaves[i-1] << endl;

            if(i==0)
            {
                irmao = n->filhos[i+1]; //irmao da direita
                e = n->removeChaveInPos(i);
            }
            else
            {
                irmao = n->filhos[i - 1]; //irmao da esquerda
                e = n->removeChaveInPos(i - 1);
            }
            
            cout << "    e: " << e << endl;
            int pos = irmao->insertChaveGetPos(e);
            cout << "    pos: " << pos << endl;
            int j=0,m=pos+1;
            for (; j<f->len; j++,m++) //copia as chaves do F para IRMAO
            {
                //cout << "    j: " << j << "  f->chaves[j]: " << f->chaves[j] << endl;
                irmao->insertChave(f->chaves[j]);
                irmao->filhos[m] = f->filhos[j];
            }
            irmao->filhos[m] = f->filhos[j];
            //cout << "    --> imprimir(): ";
            //printNodoAndChild(irmao);
            //imprimir();
            irmao->isRaiz=true;
            raiz = irmao;
            //printRaiz();
            return true;
        }
        /*if(n->filhos[i]->len < (t-1) && n->isRaiz && n->len == 1)
        {
            cout << "    nodo folha len=0 && raiz len=1  validarNodoFolha()" << endl;
            Nodo* esq = n->filhos[0];
            Nodo* dir = n->filhos[1];
            //cout << "    esq: ";
            //printNodoAndChild(esq);
            //cout << "    dir: ";
            //printNodoAndChild(dir);
            esq->insertChave( n->removeFirstChave() );
            int j=0,m=0;
            for(; j<dir->len; j++,m++) //copia as chaves do DIR para ESQ
            {
                esq->insertChave(dir->chaves[j]);
                esq->filhos[m] = dir->filhos[j];
            }
            esq->filhos[m] = dir->filhos[j];
            raiz = esq;
            return true;
        }*/

        //!MESCLAR
        //cout << "    MESCLAR validarNodoFolha()  i: " << i << endl;
        f = n->filhos[i];
        if (i > 0) //possui irmao a esquerda
        {
            irmao = n->filhos[i - 1];
            //cout << "    possui irmao a esquerda: ";
            //printNodoAndChild(irmao);
            //printRaiz();

            //if((i-1)<n->len)
            //    cout << "    pos valida n->chaves[i-1]: " << n->chaves[i-1] << endl;
            e = n->removeChaveInPos(i - 1);
            //cout << "    e: " << e << endl;
            irmao->insertChave(e);
            for (int j=0; j<f->len; j++) //copia as chaves do F para IRMAO
            {
                //cout << "    j: " << j << "  f->chaves[j]: " << f->chaves[j] << endl;
                irmao->insertChave(f->chaves[j]);
            }
            //cout << "    --> imprimir(): ";
            //printNodoAndChild(irmao);
            //imprimir();
            //n->filhos[i] = NULL;
            for (int j = i; j <= n->len; j++) //move os filhos para esquerda
            {
                //cout << "    j: " << j << "  n->len: " << n->len << endl;
                n->filhos[j] = n->filhos[j + 1];
            }
            n->filhos[n->len + 1] = NULL;

            //cout << "    mesclar esq(): ";
            //imprimir();
            //printRaiz();
            return true;
        }
        else if (i < (2 * t)) //possui irmao a direita
        {
            
            irmao = n->filhos[i + 1];
            //cout << "    possui irmao a direita: ";
            //printNodoAndChild(irmao);

            //if((i+1)<n->len)
            //    cout << "    pos valida n->chaves[i]: " << n->chaves[i] << endl;
            e = n->removeChaveInPos(i);
            //cout << "    e: " << e << endl;
            irmao->insertChave(e);
            for (int j = 0; j < f->len; j++) //copia as chaves do F para IRMAO
            {
                irmao->insertChave(f->chaves[j]);
            }
            //n->filhos[i] = NULL;
            //printRaiz();
            for (int j = i; j <= n->len; j++) //move os filhos para esquerda
            {
                //cout << "    j: " << j << "  n->len: " << n->len << endl;
                n->filhos[j] = n->filhos[j + 1];
            }
            n->filhos[n->len + 1] = NULL;
            //printRaiz();
            return true;
        }
        return false;
    }
    int Remove(Nodo *n, int k)
    {
        int pos = n->getIndice(k); //se o indice retornado for maior que -1, a chave está no nodo
        if (pos >= 0)
        {
            //cout <<  "    Remove01  k: " << k << "  pos: " << pos<< "  n->len: " << n->len << "  ";
            //printNodoAndChild(n);
            if (!n->is_folha())
            {
                validarNodoNaoFolha(n, pos);
                return n->len;
            }
            n->removeChave(pos);
            //cout << "    Remove02  k: " << k << "  pos: " << pos<< "  n->len: " << n->len << "  ";
            //printNodoAndChild(n);
            return n->len;
        }

        if (n->is_folha()) //se o nodo atual é folha e o elemento não foi encontrado nele, entao o elemento não esta contido na arvore.
        {
            cout << k << " nao encotrado" << endl;
            return -1;
        }

        int i = n->len;                        //quantidade de chaves no nodo
        while (i >= 1 && k < n->chaves[i - 1]) //determina o filho de n
            i -= 1;
        int resp = Remove(n->filhos[i], k);

        if (resp >= (t - 1) || resp == -1)
            return resp;
        //cout << "    Resp: " << resp  << "  ";
        //printNodoAndChild(n->filhos[i]);
        validarNodoFolha(n, i); //receber doação ou fundir com irmão antecessor/sucessor respectivamente.
        return n->len;
    }

public:
    int t; //grau minimo
    ArvoreB(int arg_grau_min)
    {
        t = arg_grau_min;
        CreateRoot();
        //cout << "(grau min) t = " << arg_grau_min << endl;
    }
    bool buscar(int valor)
    {
        if (raiz == NULL)
        {
            cout << "BUSCA não pode ser executada, RAIZ == NULL" << endl;
            return false;
        }
        return Search(raiz, valor);
    }
    bool inserir(int valor)
    {
        IInfo *info = Insert(raiz, valor);
        return info->isInsert;
    }
    bool remover(int valor)
    {
        cout << "    remover(" << valor << ") " << endl;
        return Remove(raiz, valor);
    }
    void imprimir()
    {
        cout << "(";
        Print(raiz);
        cout << ")" << endl;
    }
    void printRaiz()
    {
        cout << "[";
        raiz->print();
        cout << "]";
        cout << " ---> ";
        for (int i = 0; i < raiz->maxf; i++)
        {
            cout << "(";
            if (raiz->filhos[i] != NULL)
                raiz->filhos[i]->print();
            cout << ")";
        }
        cout << endl;
    }
    bool printNodoAndChild(Nodo *n)
    {
        if (n == NULL)
        {
            cout << "ALERT! printNodoAndChild(): n == NULL. ";
            return false;
        }
        cout << "Nodo: [";
        n->print();
        cout << "]";
        cout << " ---> ";
        for (int i = 0; i < n->maxf; i++)
        {
            cout << "(";
            if (n->filhos[i] != NULL)
                n->filhos[i]->print();
            cout << ")";
        }
        cout << endl;
        return true;
    }
    void removerFirst()
    {
        raiz->removeFirstChave();
        imprimir();
    }
    void removerLast()
    {
        raiz->removeLastChave();
        imprimir();
    }
};

#endif