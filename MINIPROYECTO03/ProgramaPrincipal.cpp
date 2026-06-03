#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

struct structProducto 
{
    int codigo;
    char nombre[30];
    int cantidadinicial;
    double preciounitario;
};

bool codigoexiste(int codigobuscado) 
{
    ifstream archivo("PRODUCTOS.BIN", ios::binary);

    structProducto producto;

    while (archivo.read((char*)&producto, sizeof(producto))) 
    {
        if (producto.codigo == codigobuscado) 
        {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void mostrarmenu() 
{
    cout << " FARMACIAS CHAVEZ";
    cout << "1. Adicionar producto";
    cout << "2. Procesar ventas y listar resultados";
    cout << "3. Salir";
    cout << "Elija una opcion: ";
}

int main() 
{
    int opcion;
    do 
    {
        mostrarmenu();
        cin >> opcion;

        if (opcion == 1) 
        {
            cout << "\nAqui se adicionara un producto";

        } 
        else if (opcion == 2) 
        {
            cout << "\nAqui se procesaran las ventas";

        } 
        else if (opcion == 3) 
        {
            cout << "\nSaliendo del programa";

        } 
        else 
        {
            cout << "\nOpcion incorrecta";
        }

    } while (opcion != 3);

    return 0;
}
