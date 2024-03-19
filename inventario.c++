//Integrantes:
//Andres Oregon Mmorales 
//Johan Steven Grueso Cetter


#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

struct Producto {
    int id;
    string producto;
    int cantidad;
    double precio;
    Producto* next;

    Producto(int id, const string& producto, int cantidad, double precio) : 
    id(id), producto(producto), cantidad(cantidad), precio(precio), next(nullptr) {}
};

class Inventario {
private:
    Producto* inventario;

public:
    Inventario() : inventario(nullptr) {}

    void registrarProducto(int id, const string& producto, int cantidad, double precio) {
        Producto* nuevoProducto = new Producto(id, producto, cantidad, precio);
        if (!inventario) {
            inventario = nuevoProducto;
        } else {
            Producto* temp = inventario;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = nuevoProducto;
        }
        cout << "Producto registrado exitosamente." << endl;
    }

    void mostrarInventario() {
        cout << "Inventario:" << endl;
        Producto* temp = inventario;
        while (temp) {
            cout << "ID: " << temp->id;
            cout << ", Producto: " << temp->producto;
            cout << ", Cantidad: " << temp->cantidad;
            cout << ", Precio por unidad: $" << temp->precio << endl;
            temp = temp->next;
        }
    }

    void buscarProductoPorId(int id) {
        Producto* temp = inventario;
        while (temp) {
            if (temp->id == id) {
                cout << "ID: " << temp->id << endl;
                cout << "Producto: " << temp->producto << endl;
                cout << "Cantidad: " << temp->cantidad << endl;
                cout << "Precio por unidad: $" << temp->precio << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Producto no encontrado." << endl;
    }

    void eliminarProducto(int id) {
        if (!inventario) {
            cout << "El inventario está vacio. No se pueden eliminar productos." << endl;
            return;
        }

        Producto* temp = inventario;
        Producto* prev = nullptr;

        while (temp && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << "Producto no encontrado." << endl;
            return;
        }

        if (!prev) {
            inventario = temp->next;
        } else {
            prev->next = temp->next;
        }

        delete temp;
        cout << "Producto eliminado exitosamente." << endl;
    }

    double calcularValorTotalInventario() {
        double total = 0.000;
        Producto* temp = inventario;
        while (temp) {
            total += temp->cantidad * temp->precio;
            temp = temp->next;
        }
        return total;
    }

    double calcularPromedioPrecios() {
        if (!inventario) return 0.0;

        double sumaPrecios = 0.0;
        int count = 0;
        Producto* temp = inventario;
        while (temp) {
            sumaPrecios += temp->precio;
            count++;
            temp = temp->next;
        }
        return sumaPrecios / count;
    }

    void venderProducto(int id, int cantidad) {
        Producto* temp = inventario;
        Producto* prev = nullptr;
       
        while (temp) {
            if (temp->id == id) {
                if (temp->cantidad >= cantidad) {
                    double totalPagar = cantidad * temp->precio;
                    temp->cantidad -= cantidad;
                    cout << "Venta realizada. Total a pagar: $" << totalPagar << endl;
                } else {
                    cout << "No hay suficientes productos para realizar la venta." << endl;
                }
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Producto no encontrado." << endl;
    }
};

int main() {
    Inventario inventario;
    int opcion;

    do {
        cout << "-----------------------" <<endl;
        cout << "          menu         " <<endl;
        cout << "-----------------------" <<endl;
        cout << "1. Registrar Producto" <<endl;
        cout << "2. Mostrar Inventario" <<endl;
        cout << "3. Buscar Producto por ID" <<endl;
        cout << "4. Eliminar Producto "<<endl;
        cout << "5. Calcular Valor Total del Inventario" <<endl;
        cout << "6. Calcular Promedio de Precios" <<endl;
        cout << "7. Vender Productos"<<endl;
        cout << "8. Salir\n" <<endl;

        cout << "Ingrese la opcion deseada: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int id, cantidad;
                double precio;
                string producto;
                
                cout << "Ingrese el ID del producto: ";
                cin >> id;
                
                cout << "Ingrese el nombre del producto: ";
                cin.ignore();
                getline(cin, producto);
                
                cout << "Ingrese la cantidad: ";
                cin >> cantidad;
                
                cout << "Ingrese el precio por unidad: ";
                cin >> precio;
                inventario.registrarProducto(id, producto, cantidad, precio);
                break;
            }
            case 2:
                inventario.mostrarInventario();
                break;
            
            case 3: {
                int id;
                cout << "Ingrese el ID del producto: ";
                cin >> id;
                inventario.buscarProductoPorId(id);
                break;
            }
            
            case 4: {
                int id;
                cout << "Ingrese el ID del producto a eliminar: ";
                cin >> id;
                inventario.eliminarProducto(id);
                break;
            }
           
            case 5:
                cout << "Valor total del inventario: $" << inventario.calcularValorTotalInventario() << endl;
                break;
            
            case 6:
                cout << "Promedio de precios: $" << inventario.calcularPromedioPrecios() << endl;
                break;
            
            case 7: {
                int id, cantidad;
                cout << "Ingrese el ID del producto a vender: ";
                cin >> id;
                
                cout << "Ingrese la cantidad a vender: ";
                cin >> cantidad;
                inventario.venderProducto(id, cantidad);
                break;
            }
            case 8:
                cout << "Gracias, vuelva pronto." << endl;
                break;
            default:
                cout << "Opcion no existente. Por que la demora?" << endl;
        }
    } while (opcion != 8);

    return 0;
}
