#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct structProducto 
{
    int codigo;
    char nombre[30];
    int cantidadinicial;
    double preciounitario;
};

void mostrarMenu() 
{
    cout << " SISTEMA FARMACIAS CHAVEZ\n";
    cout << "1. Adicionar producto\n";
    cout << "2. Procesar ventas\n";
    cout << "3. Lista productos\n";
    cout << "4. Salir\n";
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
            cout << "\nse adicionara un producto";
        } 
        else if (opcion == 2) 
        {
            cout << "\nse procesaran las ventas";
        } 
        else if (opcion == 3) 
        {
            cout << "\nse listaran los productos";
        } 
        else if (opcion == 4) 
        {
            cout << "\nSaliendo del programa";
        } 
        else 
        {
            cout << "\nOpcion incorrecta";
        }

    } 
        while (opcion != 4);

    return 0;
}
