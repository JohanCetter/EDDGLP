#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct pasajeros {
    char nom[50];
    char apellido[50];
    int DNI;
    int a; // Matricula del barco
    pasajeros *sig;
};

pasajeros *cab = NULL;

struct Barcos {
    char nomBarco[30];
    char Lugar[30];
    int Precio = 0;
    int espacio = 0;
    char matriculaParcial[3]; 
    int Matricula = 0;
    int Dia = 0, Mes = 0, Anio = 0;
    int total = 0;
    int Identificador = 0;
    Barcos *izq = NULL;
    Barcos *der = NULL;
    int altura = 0;
};

Barcos *Raiz = NULL, *aux = NULL;

int buscarBarco;

void generarIdentificador(Barcos *barco) {
    string identificador = "";
    identificador += barco->matriculaParcial;
    identificador += to_string(barco->Anio);
    identificador += (barco->Mes < 10 ? "0" : "") + to_string(barco->Mes);
    identificador += (barco->Dia < 10 ? "0" : "") + to_string(barco->Dia);
    barco->Identificador = stoi(identificador);
}

int registrar() {
    int MatriculaParcial;
    aux = (Barcos *)malloc(sizeof(Barcos));

    cout << "Ingrese la matricula: ";
    cin >> MatriculaParcial;
    aux->Matricula = MatriculaParcial;

    if (MatriculaParcial < 10) {
        cout << "Intentelo nuevamente con un numero mayor a 10" << endl;
        free(aux);
        return 1; 
    }

    snprintf(aux->matriculaParcial, sizeof(aux->matriculaParcial), "%02d", MatriculaParcial);

    cout << "Ingrese el nombre del barco (No dejar espacios en el nombre): ";
    cin >> aux->nomBarco;
    cout << "Ingrese la capacidad de la embarcacion: ";
    cin >> aux->espacio;
    cout << "Ingrese el destino del viaje: ";
    cin >> aux->Lugar;
    cout << "Ingrese el precio a pagar: ";
    cin >> aux->Precio;
    cout << "Ingrese el año en que viaja: ";
    cin >> aux->Anio;
    cout << "Ingrese el mes en que viaja: ";
    cin >> aux->Mes;
    cout << "Ingrese el dia en que viaja: ";
    cin >> aux->Dia;

    generarIdentificador(aux);
    return 0;
}

int ObtenerAltura(Barcos *a) {
    if (a == NULL) {
        return 0;
    }
    return a->altura;
}

int mayor(int ai2, int ai3) {
    return (ai2 > ai3) ? ai2 : ai3;
}

Barcos *RotarDerecha(Barcos *y) {
    Barcos *x = y->izq;
    Barcos *ai4 = x->der;

    x->der = y;
    y->izq = ai4;

    y->altura = mayor(ObtenerAltura(y->izq), ObtenerAltura(y->der)) + 1;
    x->altura = mayor(ObtenerAltura(x->izq), ObtenerAltura(x->der)) + 1;

    return x;
}

Barcos *RotarIzquierda(Barcos *x) {
    Barcos *y = x->der;
    Barcos *ai4 = y->izq;

    y->der = x;
    x->izq = ai4;

    x->altura = mayor(ObtenerAltura(x->izq), ObtenerAltura(x->der)) + 1;
    y->altura = mayor(ObtenerAltura(y->izq), ObtenerAltura(y->der)) + 1;

    return y;
}

int ObtenerBalance(Barcos *ai5) {
    if (ai5 == NULL) {
        return 0;
    }
    return ObtenerAltura(ai5->izq) - ObtenerAltura(ai5->der);
}

Barcos *insertar(Barcos *nodo) {
    if (nodo == NULL) {
        cout << "Insertando nueva embarcacion: " << aux->nomBarco << " con identificador: " << aux->Identificador << endl;
        return aux;
    }
    if (aux->Identificador < nodo->Identificador) {
        nodo->izq = insertar(nodo->izq);
    }
    else if (aux->Identificador > nodo->Identificador) {
        nodo->der = insertar(nodo->der);
    }
    else {
        return nodo;
    }

    nodo->altura = 1 + mayor(ObtenerAltura(nodo->izq), ObtenerAltura(nodo->der));

    int balance = ObtenerBalance(nodo);

    if (balance > 1 && aux->Identificador < nodo->izq->Identificador) {
        return RotarDerecha(nodo);
    }

    if (balance < -1 && aux->Identificador > nodo->der->Identificador) {
        return RotarIzquierda(nodo);
    }

    if (balance > 1 && aux->Identificador > nodo->izq->Identificador) {
        nodo->izq = RotarIzquierda(nodo->izq);
        return RotarDerecha(nodo);
    }

    if (balance < -1 && aux->Identificador < nodo->der->Identificador) {
        nodo->der = RotarDerecha(nodo->der);
        return RotarIzquierda(nodo);
    }

    return nodo;
}

void inorden(Barcos *c) {
    if (c != NULL) {
        inorden(c->izq);
        cout << "1. Nombre del barco: " << c->nomBarco << "\n2. Destino del viaje: " << c->Lugar << "\n3. Precio del viaje: " << c->Precio << " $\n4. Matricula: " << c->Matricula
             << "\n5. Fecha de salida: " << c->Dia << "/" << c->Mes << "/" << c->Anio << "\n6. Capacidad maxima: " << c->espacio << "\n7. Identificador: " << c->Identificador << endl;
        inorden(c->der);
    }
}

Barcos* buscar(Barcos *nodo, int matricula) {
    if (nodo == NULL || nodo->Matricula == matricula) {
        return nodo;
    }
    if (nodo->Matricula < matricula) {
        return buscar(nodo->der, matricula);
    }
    return buscar(nodo->izq, matricula);
}

void Buscar() {
    Barcos *resultado = buscar(Raiz, buscarBarco);
    if (resultado != NULL) {
        cout << "-------------- Embarcacion registrada --------------" << endl;
        cout << "Nombre de la embarcacion: " << resultado->nomBarco << endl;
        cout << "Destino del viaje: " << resultado->Lugar << endl;
        cout << "Precio del viaje: $" << resultado->Precio << endl;
        cout << "Matricula: " << resultado->Matricula << endl;
        cout << "Fecha de salida: " << resultado->Dia << "/" << resultado->Mes << "/" << resultado->Anio << endl;
        cout << "Numero de pasajeros: " << resultado->espacio << endl;
        cout << "Identificador: " << resultado->Identificador << endl;
        cout << "------------------------------------------------" << endl;
    } else {
        cout << "Embarcacion no encontrada" << endl;
    }
}

void registrarPasajero() {
    pasajeros *nuevoPasajero = (pasajeros *)malloc(sizeof(pasajeros));

    cout << "Ingrese el nombre del pasajero: ";
    cin >> nuevoPasajero->nom;
    cout << "Ingrese el apellido del pasajero: ";
    cin >> nuevoPasajero->apellido;
    cout << "Ingrese el DNI del pasajero: ";
    cin >> nuevoPasajero->DNI;
    nuevoPasajero->a = buscarBarco;
    nuevoPasajero->sig = cab;
    cab = nuevoPasajero;

    cout << "Pasajero registrado exitosamente en el barco con matricula: " << buscarBarco << endl;
}

void MostrarPasajeros() {
    if (cab == NULL) {
        cout << "No hay pasajeros registrados" << endl;
        return;
    }
    pasajeros *auxi1 = cab;
    bool hayPasajeros = false;
    while (auxi1 != NULL) {
        if (auxi1->a == buscarBarco) {
            cout << "Nombre: " << auxi1->nom << " " << auxi1->apellido << endl;
            cout << "Numero de DNI: " << auxi1->DNI << endl;
            hayPasajeros = true;
        }
        auxi1 = auxi1->sig;
    }
    if (!hayPasajeros) {
        cout << "No hay pasajeros registrados en el barco con matricula " << buscarBarco << endl;
    }
}

Barcos *eliminar(Barcos *raiz, int identificador) {
    if (raiz == NULL) {
        return raiz;
    }

    if (identificador < raiz->Identificador) {
        raiz->izq = eliminar(raiz->izq, identificador);
    } else if (identificador > raiz->Identificador) {
        raiz->der = eliminar(raiz->der, identificador);
    } else {
        if (raiz->izq == NULL || raiz->der == NULL) {
            Barcos *temp = raiz->izq ? raiz->izq : raiz->der;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else { 
                *raiz = *temp; 
            }
            free(temp);
        } else {
            Barcos *temp = raiz->der;
            while (temp->izq != NULL) {
                temp = temp->izq;
            }
            raiz->Identificador = temp->Identificador;
            raiz->der = eliminar(raiz->der, temp->Identificador);
        }
    }

    if (raiz == NULL) {
        return raiz;
    }

    raiz->altura = 1 + mayor(ObtenerAltura(raiz->izq), ObtenerAltura(raiz->der));

    int balance = ObtenerBalance(raiz);

    if (balance > 1 && ObtenerBalance(raiz->izq) >= 0) {
        return RotarDerecha(raiz);
    }
    if (balance > 1 && ObtenerBalance(raiz->izq) < 0) {
        raiz->izq = RotarIzquierda(raiz->izq);
        return RotarDerecha(raiz);
    }
    if (balance < -1 && ObtenerBalance(raiz->der) <= 0) {
        return RotarIzquierda(raiz);
    }
    if (balance < -1 && ObtenerBalance(raiz->der) > 0) {
        raiz->der = RotarDerecha(raiz->der);
        return RotarIzquierda(raiz);
    }

    return raiz;
}

void eliminarnodo() {
    int identificador;
    cout << "Digite el identificador del barco que desea eliminar: ";
    cin >> identificador;
    Raiz = eliminar(Raiz, identificador);
    cout << "Barco eliminado exitosamente" << endl;
}

int main() {
    int sel;
    do {
        cout << "------------------------------" << endl;
        cout << "Bienvenido, registro de viajes" << endl;
        cout << "------------------------------" << endl;

        cout << "1. Registrar embarcacion" << endl;
        cout << "2. Buscar embarcacion" << endl;
        cout << "3. Mostrar embarcacion" << endl;
        cout << "4. Eliminar embarcacion" << endl;
        cout << "5. Registrar pasajeros" << endl;
        cout << "6. Mostrar pasajeros" << endl;
        cout << "7. Salir" << endl;

        cout << "Elija una opcion: ";
        cin >> sel;

        switch (sel) {
            case 1:
                if (registrar() == 0) {
                    Raiz = insertar(Raiz);
                }
                break;
            
            case 2:
                cout << "Ingrese la matricula del barco a buscar: ";
                cin >> buscarBarco;
                Buscar();
                break;
            
            case 3:
                if (Raiz != NULL) {
                    inorden(Raiz);
                } else {
                    cout << "No hay embarcaciones registradas." << endl;
                }
                cout << endl;
                break;  
            
            case 4: 
                eliminarnodo(); 
                break;
                
            case 5:
                cout << "Ingrese la matricula del barco donde se va a registrar: ";
                cin >> buscarBarco;
                registrarPasajero();
                break;
            
            case 6:
                cout << "Ingrese la matricula del barco para mostrar pasajeros: ";
                cin >> buscarBarco;
                MostrarPasajeros();
                break;
        }
    } while (sel != 7);

    return 0;
}
