//PROGRAMA PRINCIPAL
#include <iostream>
#include "LibDiana.h"
#include "LibJhoel.h"
#include "LibEmilce.h"

using namespace std;

void Mostrarmenu()
{
    cout << "FARMACIAS CHAVEZ" << endl;
    cout << "================" << endl;
    cout << "1. Adicionar producto" << endl;
    cout << "2. Adicionar venta manual" << endl;
    cout << "3. Modificar producto" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() 
{
    int opcion;

    do 
    {
        system("cls");

        Mostrarmenu();
        cin >> opcion;
        switch(opcion)
        {
            case 1:
                break;

            case 2:
                break;

            case 3:
                ModificarProducto();
                system("pause");
                break;
        }

    } while(opcion != 0);

    return 0;
} 
    
