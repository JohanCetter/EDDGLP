#include <iostream>
#include <malloc.h>
#include <string> // Para usar std::string y std::to_string

using namespace std;

struct pasajeros {
    char nom[50];
    char apellido[50];
    int DNI;
    int a;
    pasajeros *sig;
};

pasajeros *cab = NULL, *auxi1 = NULL, *auxi2 = NULL;

struct Barcos {
    char nomBarco[30];
    char Lugar[30];
    int Precio = 0;
    int espacio = 0;
    char matriculaParcial[3]; // Espacio para dos caracteres y el terminador nulo
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
char concatenar;

void generarIdentificador(Barcos *barco) {
    string identificador = "";

    // Convertir los dos primeros caracteres de la matrícula a string
    identificador += barco->matriculaParcial[0];
    identificador += barco->matriculaParcial[1];

    // Agregar el año
    identificador += to_string(barco->Anio);

    // Agregar el mes (con ceros a la izquierda si es necesario)
    if (barco->Mes < 10) {
        identificador += "0";
    }
    identificador += to_string(barco->Mes);

    // Agregar el día (con ceros a la izquierda si es necesario)
    if (barco->Dia < 10) {
        identificador += "0";
    }
    identificador += to_string(barco->Dia);

    // Convertir la cadena completa a un número entero
    barco->Identificador = stoi(identificador);
}

int registrar() {
    int MatriculaParcial = 0;
    aux = (struct Barcos *)malloc(sizeof(struct Barcos));

    cout << "Ingrese la matricula: ";
    cin >> MatriculaParcial;
    aux->Matricula = MatriculaParcial;

    if (MatriculaParcial < 10) {
        cout << "Intentelo nuevamente con un numero mayor a 10" << endl;
        free(aux); // Liberar memoria antes de retornar
        return registrar();
    }

    // Convertir la matrícula parcial a dos caracteres
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

    generarIdentificador(aux); // Generar identificador para el nuevo barco

    return 0;
}

// BALANCEO
int ObtenerAltura(struct Barcos *a) {
    if (a == NULL) {
        return 0;
    }
    return a->altura;
}

int mayor(int ai2, int ai3) {
    return (ai2 > ai3) ? ai2 : ai3;
}

struct Barcos *RotarDerecha(struct Barcos *y) {
    struct Barcos *x = y->izq;
    struct Barcos *ai4 = x->der;

    x->der = y;
    y->izq = ai4;

    y->altura = mayor(ObtenerAltura(y->izq), ObtenerAltura(y->der)) + 1;
    x->altura = mayor(ObtenerAltura(x->izq), ObtenerAltura(x->der)) + 1;

    return x;
}

struct Barcos *RotarIzquierda(struct Barcos *x) {
    struct Barcos *y = x->der;
    struct Barcos *ai4 = y->izq;

    y->der = x;
    x->izq = ai4;

    x->altura = mayor(ObtenerAltura(x->izq), ObtenerAltura(x->der)) + 1;
    y->altura = mayor(ObtenerAltura(y->izq), ObtenerAltura(y->der)) + 1;

    return y;
}

int ObtenerBalance(struct Barcos *ai5) {
    if (ai5 == NULL) {
        return 0;
    }
    return ObtenerAltura(ai5->izq) - ObtenerAltura(ai5->der);
}

struct Barcos *insertar(struct Barcos *nodo) {
    if (nodo == NULL) {
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

int inorden(struct Barcos *c) {
    if (c != NULL) {
        inorden(c->izq);
        cout << "1. Nombre del barco: " << c->nomBarco << "\n2. Destino del viaje: " << c->Lugar << "\n3. Precio del viaje: " << c->Precio << " $\n4. Matricula: " << c->Matricula << "\n5. Fecha de salida: " << c->Dia << "/" << c->Mes << "/" << c->Anio << "\n6. Capacidad maxima: " << c->espacio << "\n7. Identificador: " << c->Identificador << endl;
        inorden(c->der);
    }
    return 0;
}

Barcos* buscar(struct Barcos *nodo, int matricula) {
    if (nodo == NULL || nodo->Matricula == matricula) {
        return nodo;
    }
    if (nodo->Matricula < matricula) {
        return buscar(nodo->der, matricula);
    }
    return buscar(nodo->izq, matricula);
}

int Buscar() {
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
    return 0;
}

int registrarPasajero() {
    Barcos *barco = buscar(Raiz, buscarBarco);
    if (barco == NULL) {
        cout << "No hay Barcos" << endl;
        return 0;
    }

    if (cab == NULL) {
        cab = (struct pasajeros *)malloc(sizeof(struct pasajeros));
        cout << "Ingrese su nombre: ";
        cin >> cab->nom;
        cout << "Ingrese su apellido: ";
        cin >> cab->apellido;
        cout << "Ingrese su cedula: ";
        cin >> cab->DNI;
        cab->a = barco->Matricula;

        if (barco->espacio > barco->total) {
            barco->total = barco->total + 1;
        } else {
            cout << "Ya no hay tickets disponibles" << endl;
            free(cab); // Liberar memoria antes de retornar
            return registrarPasajero();
        }

        cab->sig = NULL;
        return 0;
    } else {
        auxi1 = (struct pasajeros *)malloc(sizeof(struct pasajeros));
        cout << "Ingrese su nombre: ";
        cin >> auxi1->nom;
        cout << "Ingrese su apellido: ";
        cin >> auxi1->apellido;
        cout << "Ingrese su cedula: ";
        cin >> auxi1->DNI;
        auxi1->a = barco->Matricula;

        if (barco->espacio > barco->total) {
            barco->total = barco->total + 1;
        } else {
            cout << "Ya no hay tickets disponibles" << endl;
            free(auxi1); // Liberar memoria antes de retornar
            return registrarPasajero();
        }

        auxi1->sig = NULL;
        auxi2 = cab;

        while (auxi2->sig != NULL) {
            auxi2 = auxi2->sig;
        }

        auxi2->sig = auxi1;
    }
    return 0;
}

int MostrarPasajeros() {
    if (cab == NULL) {
        cout << "No hay pasajeros registrados" << endl;
        return 0;
    }
    auxi1 = cab;
    while (auxi1 != NULL) {
        if (auxi1->a == buscarBarco) {
            cout << "Nombre: " << auxi1->nom << " " << auxi1->apellido << endl;
            cout << "Numero de DNI: " << auxi1->DNI << endl;
        }
        auxi1 = auxi1->sig;
    }
    return 0;
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
                registrar();
                Raiz = insertar(Raiz);
                break;
            case 2:
                cout << "Ingrese la matricula del barco a buscar: ";
                cin >> buscarBarco;
                Buscar();
                break;
            case 3:
                inorden(Raiz);
                cout << endl;
                break;
            case 4:
                // eliminar
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
