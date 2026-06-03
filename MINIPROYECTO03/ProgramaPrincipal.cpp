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
    int cantidadInicial;
    double precioUnitario;
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
    cout << "  FARMACIAS CHAVEZ\n";
    cout << "1. Adicionar producto\n";
    cout << "2. Procesar ventas y listar resultados\n";
    cout << "3. Salir\n";
    cout << "Elija una opcion: ";
}

int main() 
{
    int opcion;

    do 
    {
        mostrarmenu();
        cin >> opcion;
    } 
    while (opcion != 3);

    return 0;
}
