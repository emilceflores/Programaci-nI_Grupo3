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

void mostrarMenu() 
{
    cout << " SISTEMA FARMACIAS CHAVEZ";
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
        mostrarMenu();
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

    } 
        while (opcion != 3);

    return 0;
}
