// codigo estacionamiento 
// ANDRES OBREGON MORALES Y JOHAN STEVEN GRUESO 

#include <iostream>
#include <malloc.h>
using namespace std;

struct parqueadero{

char modelo[30];
char tipo[30];
char placa1[30];
char placa2[30];
parqueadero *sig;
};

parqueadero *cab, *aux, *aux2;

int registrar(){
    aux = (struct parqueadero *)malloc(sizeof(struct parqueadero));
    cout<<"Ingrese el tipo de vehiculo ""1 para carros y 0 para motos"<<endl;
    cin >> aux->tipo;
    
    if(aux->tipo[0]!='1' && aux->tipo[0]!='0'){
        cout<<"Intente de nuevo con 1 para carros y 0 para motos" <<endl;
        free(aux);
        return 0;
    }
    cout<<"ingrese la placa del vehiculo"<<endl;
    cin>> aux->placa1;

    cout<<"ingrese el tipo de vehiculo (carro/moto)"<<endl;
    cin>> aux->modelo;
    if(cab == NULL){
        cab = aux;
        aux ->sig = NULL;
    }
    else{
        aux -> sig = cab;
        cab = aux;
    }
}
int mostrarCarro(){
    aux = cab;
    while(aux!=NULL){
            cout<<"La placa del carro es:"<<endl;
            if(aux->tipo[0]=='1'){
                cout<<aux->placa1<<endl;
            }
            aux = aux ->sig;
    }
    return 0;
}
int mostrarMoto(){
    aux = cab;
    while(aux != NULL) {
        cout<<"la placa de la moto es:"
        <<endl;
        if(aux->tipo[0] == '0'){
            cout<<aux->placa2<<endl;
        }
        aux = aux->sig;
    }
    return 0;
}


int eliminar(){
    int sel, carros;
    char placa1_1[30], placa2_1[30];
    cout<<"¿que desea retirar?"<<endl;
    cout<<"1 carro 2 moto"<<endl;
    cin >> sel;
    
    if(sel==1){
        cout<<"ingrese la placa delcarro"<<endl;
        cin >> placa1_1;
        aux = cab;
        while(aux != NULL && aux->placa1!= placa1_1){
            aux2 = aux;
            aux = aux->sig;
            carros++;
        }
        cout<<"se movieron "<<carros<<"carros"<<endl;
        if(aux == NULL) {
            cout<<"no se encontro el carro con dicha placa" <<endl;
            return 0;
        }
        else{
        if(aux2 == NULL) {
            cab = aux->sig;
        }
            else{
                aux2->sig = aux->sig;
            }
            free(aux);
            cout<<"el carro con placa "<<placa1_1<<" fue retirado"<<endl;
        }
     }

    else if(sel == 2){ 
        cout << "Ingrese la placa de la moto: ";
        cin >> placa2_1;
        aux = cab;
        aux2 = NULL; 
        while(aux != NULL && aux->placa2 != placa2_1){
            aux2 = aux;
            aux = aux->sig;
        }
        if(aux == NULL) {
            cout << "No se encontró la moto con dicha placa" << endl;
            return 0;
        }
        else{
            if(aux2 == NULL) {
                cab = aux->sig;
            }
            else{
                aux2->sig = aux->sig;
            }
            free(aux); // Se libera la memoria del nodo eliminado
            cout << "La moto con placa " << placa2_1 << " fue retirada" << endl;
        }
    }
    else{
        cout << "Opción no válida" << endl;
    }

    return 0;

}

int devegando (){
int carro, moto;
float totalmoto, totalcarro, total;
totalcarro=(carro*1000)+(carro*100);
totalmoto = (moto*500)+(moto*50);
total = totalcarro + totalmoto;
cout<<"Carros:" <<totalcarro<<"$"<<"\nmotos: "<<totalmoto<<"$"<<"\nTotal:" <<total<< "$" <<endl;
}
int main() {
int opc;
do{
    cout<<"1 registrar"<<endl;
    cout<<"2 mostrar carro"<<endl;
    cout<<"3 Mostrar moto"<<endl;
    cout<<"4 eliminar vehiculo"<<endl;
    cout<<"5 calcular devegando"<<endl;
    cout<<"6 salir"<<endl;
    cin>>opc;
    switch(opc) {
        case 1: registrar(); break;
        case 2: mostrarCarro(); break;
        case 3: mostrarMoto(); break;
        case 4: eliminar(); break;
        case 5: devegando(); break;
    }

    }while(opc!=6);

    return 0;

}
