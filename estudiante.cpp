// CODIGO ARBOL REGISTRO DE ESTUDIANTES 
// ANDRES OBREGON MORALES Y JOHAN STEVEN GRUESO 


#include <iostream>
#include <malloc.h>

using namespace std;

struct nodo {
    int val = 0;
    int codigo;
    char nom[30];
    char apell[30];
    char ano[30];
    char mes[30];
    char fecha_naci[30];
    nodo *izq;
    nodo *der;
};

nodo *raiz = NULL,*raiz2 = NULL, *aux = NULL, *aux2 = NULL, *aux3 = NULL;

int posicionar() {
    if (aux->ano < aux2->ano) {
        if (aux2->izq != NULL) {
            aux2 = aux2->izq;
            posicionar();
        } else {
            aux2->izq = aux;
        }
    } else if (aux->ano > aux2->ano) {
        if (aux2->der != NULL) {
            aux2 = aux2->der;
            posicionar();
        } else {
            aux2->der = aux;
        }
    }
    return 0;
}

int posicionar2() {
    if (aux->codigo < aux2->codigo) {
        if (aux2->izq != NULL) {
            aux2 = aux2->izq;
            posicionar2();
        } else {
            aux2->izq = aux;
        }
    } else if (aux->codigo > aux2->codigo) {
        if (aux2->der != NULL) {
            aux2 = aux2->der;
            posicionar2();
        } else {
            aux2->der = aux;
        }
    }
    return 0;
}

int registrar() {
    aux = (struct nodo *)malloc(sizeof(struct nodo));
    if (aux != NULL) {
        cout << "Ingrese el codigo del estudiante:" << endl;
        cin >> aux->codigo;
        cout << "Ingrese el nombre:" << endl;
        cin >> aux->nom;
        cout << "Ingrese el apellido:" << endl;
        cin >> aux->apell;
        cout << "Ingrese el ano de nacimiento:" << endl;
        cin >> aux->ano;
        cout << "Ingrese el mes de nacimiento:" << endl;
        cin >> aux->mes;
        cout << "Ingrese el dia:" << endl;
        cin >> aux->fecha_naci;

        aux -> izq = aux -> der = NULL;
        if (raiz == NULL) {
            raiz = aux;
            aux2 = raiz;
            
        } 
        else {
            aux2 = raiz;
            posicionar();
        }// creamos el segundo posicionar 
        if (raiz2 == NULL){
            raiz2 = aux;
            aux2 = raiz;
            //free(aux);
        }
        else{
        aux2 = raiz2;
            posicionar2();
        }
    }
    return 0;
}

int preorden(nodo *aux3) {
    if (aux3 != NULL) {
        cout << "Codigo: " << aux3->codigo << endl;
        preorden(aux3->izq);
        preorden(aux3->der);
    }
    return 0;
}

// preorden 2 
int preorden2(nodo *aux3) {
    if (aux3 != NULL) {
        cout << "ano: " << aux3->ano << endl;
        preorden2(aux3->izq);
        preorden2(aux3->der);
    }
    return 0;
}

int inorden(nodo *aux3) {
    if (aux3 != NULL) {
        inorden(aux3->izq);
        cout << aux3->codigo << endl;
        inorden(aux3->der);
    }
    return 0;
}
// inorden 2

int inorden2(nodo *aux3) {
    if (aux3 != NULL) {
        inorden2(aux3->izq);
        cout<<aux3 ->ano <<endl;
        inorden2(aux3->der);
    }
    return 0;
}

int postorden(nodo *aux3) {
    if (aux3 != NULL) {
        postorden(aux3->izq);
        postorden(aux3->der);
        cout << "Codigo: " << aux3->codigo << endl;
    }
    return 0;
}
// postorden 2
int postorden2(nodo *aux3) {
    if (aux3 != NULL) {
        postorden2(aux3->izq);
        postorden2(aux3->der);
        cout << "ano: " << aux3->ano << endl;
    }
    return 0;
}

nodo* ubicar(nodo *aux3, int aguja) {
    if (aux3 == NULL) {
        return NULL;
    }
    if (aux3->codigo == aguja) {
        aux = aux3;
        return aux3; 
    }
    nodo* Izquierda = NULL;
    nodo* Derecha = NULL;
    if (aux3->izq != NULL) {
        Izquierda = ubicar(aux3->izq, aguja);
    } 
    if (aux3->der != NULL) {        
        Derecha = ubicar(aux3->der, aguja);
    }
    
    if (Izquierda != NULL) {
        return Izquierda;
    }    
    else {
         return Derecha;
    }

}
int ubicarpadre(nodo *padre){
    if ((padre->izq != NULL)&&(padre->izq!=aux)) {
        ubicarpadre(padre->izq);
    }
    if(padre->izq == aux){
        aux2 = padre;
    }
    if ((padre->der!=NULL)&&(padre->der!=aux)){
        ubicarpadre(padre->der);
    }
     if(padre->der == aux){
        aux2 = padre;
    }
    return 0;
}
int casouno(nodo* padre) {
    if (padre != NULL) {
        if (padre->izq == aux) {
            padre->izq = NULL;
        } else if (padre->der == aux) {
            padre->der = NULL;
        }
    }
    free(aux);
    return 0;
}

int casodos(nodo* padre) {
     nodo* hijo;
    if (aux->izq != NULL) {
        hijo = aux->izq;
    } else {
         hijo = aux->der;
    }
    if (padre != NULL) {
        if (padre->izq == aux) {
            padre->izq = hijo;
        } else if (padre->der == aux) {
            padre->der = hijo;
        }
    } else {
        raiz = hijo;
    }
    free(aux);
    return 0;
}

int casotres() {
    nodo* padre = aux;
    nodo* sucesor = aux->der;
    while (sucesor->izq != NULL) {
        padre = sucesor;
        sucesor = sucesor->izq;
    }
    aux->codigo = sucesor->codigo;
    if (padre == aux) {
        aux->der = sucesor->der;
    } else {
        padre->izq = sucesor->der;
    }
    free(sucesor);
    return 0;
}

int eliminarnodo() {
    int buscar;
    cout << "Digite el codigo del estudiante que desea eliminar" << endl;
    cin >> buscar;
    aux = ubicar(raiz, buscar);
    if (aux == NULL) {
        cout << "El estudiante con el codigo " << buscar << " no se encuentra en el arbol." << endl;
        return 0;
    }
    if (aux->izq == NULL && aux->der == NULL) {
        casouno(aux2);
        cout<<"estudiante eliminado"<<endl;
    } else if (aux->izq != NULL && aux->der != NULL) {
        casotres();
        cout<<"estudiante eliminado"<<endl;
    } else {
        casodos(aux2);
        cout<<"estudiante eliminado"<<endl;
    }
    return 0;
}

int main() {
    int opcion;
    do {
        cout << "-------------------------------" << endl;
        cout << "Bienvenido, sistema de registro" << endl;
        cout << "-------------------------------" << endl;

        cout << "Ingrese una opcion: " << endl;


        cout << "1  Registrar estudiante" << endl;
        cout << "2  Posicionar" << endl;
        cout << "3  Preorden" << endl;
        cout << "4  Inorden" << endl;
        cout << "5  Postorden" << endl;
        cout << "6  preorden 2" << endl;
        cout << "7  inorden 2" << endl;
        cout << "8  postorden 2" << endl;
        cout << "9  eliminar" << endl;
        cout << "10 Salir" << endl;
        cin >> opcion;

         switch(opcion){
            case 1: registrar(); break;
            case 2: posicionar(); break;
            case 3: preorden(raiz); break;
            case 4: inorden(raiz); break;
            case 5: postorden(raiz); break;
            case 6: preorden2(raiz2); break;
            case 7: inorden2(raiz2); break;
            case 8: postorden2(raiz2); break;
            case 9: eliminarnodo(); break;
            case 10:     
                cout << "Saliendo del programa..." << endl;
                break;
            default:
            
            cout << "opcion invalida." << endl;
            break;
        }

    } while (opcion != 10);

    return 0;
}
