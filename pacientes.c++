#include <iostream>
#include <stdlib.h>
using namespace std;

struct nodo {
string nombre;
int cedula;
struct nodo *sig;
};

struct nodo *cab, *aux, *aux2;
void registrar(){
aux = new struct nodo;

cout << "¿Cual es el nombre del paciente? "<<endl;
cin.ignore();
getline(cin, aux->nombre);

cout << "¿Cual es el numero de cedula? "<<endl;
cin >> aux->cedula;
aux->sig = NULL;

if(cab==NULL){
    cab = aux;} 

else {

    aux2 = cab;

while(aux2->sig!=NULL) {
     aux2 = aux2->sig;
}
    aux2->sig = aux;
}
}
void mostrar(){

if(cab == NULL) {
    cout << "No hay pacientes." << endl;
return;
}

int contador = 1;
aux = cab;

while(aux != NULL) {
    cout << "Registro :" << contador << endl;
    cout << "Nombre: " << aux->nombre << endl << "Cedula: " << aux->cedula << endl
    << endl;
    aux = aux->sig;
    contador++;
}
}

int main() {
int opc = 0;

do {
    cout << "----------------" << endl;
    cout << "Menu de opciones" << endl;
    cout << "----------------" << endl;
    cout << "1- Registrar paciente" << endl;
    cout << "2- Ver pacientes " << endl;
    cout << "3- Salir" << endl;
    cout << "----------------" << endl;
cin >> opc;
switch (opc)
{

case 1:
    registrar();
break;

case 2:
     mostrar();
break;

case 3:
    cout << "------------------------" << endl;
    cout << "Gracias, vuela pronto..." << endl;
    cout << "------------------------" << endl;
    return 0;
break;

default:
    cout << "-----------------------------------------------------" << endl;
    cout << "La opción digitada no existe, intentelo de nuevo." << endl;
    cout << "-----------------------------------------------------" << endl;
break;
}
}
while
(opc !=3); 

return 0; 
}