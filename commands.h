#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Info
{
public:
    string command;
    int value;
    Info(string cmd, int v)
    {
        command = cmd;
        value = v;
    }
};

Info* DecodificaInstrucao(string line)
{
    string command;
    int value;

    if(line=="imprime_arvore") //esse comando não possui espaço
        return new Info("imprime_arvore",0);

    size_t  pos = line.find(" ");
    command = line.substr(0,pos);
    value = atoi(line.substr(pos).c_str());

    return new Info(command,value);
}

//Codigo arquivo passado pelo terminal (./app < in.txt)
bool RunCommandsInTreeB()
{
    char line[50];
    int counter=0;
    int t=0;
    Info* info;
    ArvoreB* mytree;

    while(scanf("%[^\n]\n",line)==1)
    {
        //cout << line << endl;
        counter++;
        if(counter==1)
        {
            t = atoi(line);
            if(t<2)
            {
                cout << "Ops! o parametro GRAU_MIN tem que ser MAIOR ou IGUAL a 2." << endl;
                return false;
            }
            mytree = new ArvoreB(t);
            continue;   
        }
        //cout << "line " << counter << ": " << line << endl;

        info = DecodificaInstrucao(line);

        if(info->command=="insere")
        {
            mytree->inserir(info->value);
        }
        else if(info->command=="busca")
        {
            cout << info->value << ((mytree->buscar(info->value))?(" encontrado"):(" não encontrado")) << endl;
        }
        else if(info->command=="imprime_arvore")
        {
            mytree->imprimir();
        }
    }
    return true;
}

//Codigo com Arquivo
bool RunCommandsInTreeB(char* name_file)
{
    //char nameFile[20] = "in.txt";
    ifstream file;
    string line;
    int counter=0;
    int t=0;
    Info* info;
    ArvoreB* mytree;
    
    file.open(name_file,ios::out);
    if(!file.is_open())
    {
        cout << "ALERT! Nao foi possivel abrir o arquivo " << name_file << endl;
        return false;
    }

    while(getline(file,line))
    {
        counter++;
        if(counter==1)
        {
            t = atoi(line.c_str());
            if(t<2)
            {
                cout << "Ops! o parametro GRAU_MIN tem que ser MAIOR ou IGUAL a 2." << endl;
                return false;
            }
            mytree = new ArvoreB(t);
            continue;   
        }
        //cout << "line " << counter << ": " << line << endl;

        info = DecodificaInstrucao(line);

        if(info->command=="insere")
        {
            mytree->inserir(info->value);
        }
        else if(info->command=="busca")
        {
            cout << info->value << ((mytree->buscar(info->value))?(" encontrado"):(" não encontrado")) << endl;
        }
        else if(info->command=="imprime_arvore")
        {
            mytree->imprimir();
        }

        //if(counter==10)
        //    break;
    }
    
    file.close();
    return true;
}

#endif