#include <bits/stdc++.h>
using namespace std;

typedef struct no{
    char letra;
    struct no *dir, *esq;

    no(char letra){
        this->letra = letra;
        this->dir = NULL;
        this->esq = NULL;
    }
}no;

no * insereTree(no *raiz, char letra){
    /* Função que insere um novo elemento na árvore */
    if(raiz == NULL){
        raiz = new no(letra);

    }else if(letra < raiz->letra){
        raiz->esq = insereTree(raiz->esq, letra);
    }else{
        raiz->dir = insereTree(raiz->dir, letra);
    }
    return raiz;
}

vector <char> takeWhile(vector <char> s, char c){
    /* Função que retorna um vetor com os elementos do vetor s até o primeiro elemento que não seja igual a c */
    vector <char> v;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == c){
            break;
        }
        v.push_back(s[i]);
    }
    return v;
}

vector <char> dropWhile(vector <char> s, char c){
    /* Função que retorna um vetor com os elementos do vetor s a partir do primeiro elemento que seja igual a c */
    vector <char> v;
    int i;
    for(i = 0; i < s.size(); i++){
        if(s[i] == c){
            break;
        }
    }
    for(int j = i+1; j < s.size(); j++){
        v.push_back(s[j]);
    }
    return v;
}

no * recriaTree(vector <char> &prefixa, vector <char> &infixa){
    /* Função que recria a árvore a partir de um vetor de prefixa e infixa */

    no *raiz = NULL;
    vector <char> dir, esq;
    
    if(prefixa.size() == 0 || infixa.size() == 0){
        return NULL;
    }

    char c = prefixa[0];
    prefixa.erase(prefixa.begin());

    raiz = new no(c);
    esq = takeWhile(infixa, c);
    dir = dropWhile(infixa, c);

    raiz->esq = recriaTree(prefixa, esq);
    raiz->dir = recriaTree(prefixa, dir);

    return raiz;
}

void printPostfix(no *raiz){
    /* Função que imprime a árvore em ordem postfixa */
    if(raiz == NULL){
        return;
    }
    printPostfix(raiz->esq);
    printPostfix(raiz->dir);
    cout << raiz->letra;
}

void destroyTree(no *raiz){
    /* Função que destroi a árvore */
    if(raiz == NULL){
        return;
    }
    destroyTree(raiz->esq);
    destroyTree(raiz->dir);
    delete raiz;
}

int main(){
    
    vector <char> prefixa, infixa;
    prefixa = {'A', 'B', 'C', 'D', 'E', 'F'};
    infixa = {'C', 'B', 'A', 'E', 'D', 'F'};

    printPostfix(recriaTree(prefixa, infixa));
    cout << endl;
    destroyTree(recriaTree(prefixa, infixa));
    return 0;
}