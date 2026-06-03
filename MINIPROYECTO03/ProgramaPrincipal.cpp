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
