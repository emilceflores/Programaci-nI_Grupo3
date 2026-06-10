#include <iostream>
#include "LibJhoel.h"
#include "LibDiana.h"
#include "LibEmilce.h"

using namespace std;

void Mostrarmenu();

int main() 
{
    system("chcp 65001");
    Mostrarmenu();

    return 0;
} 

void Mostrarmenu()
{
    int opcion = 0;

    do
    {
        system("cls");

        cout << "FARMACIAS CHAVEZ" << endl;
        cout << "================" << endl;
        cout << "\t1. Adicionar producto" << endl;
        cout << "\t2. Procesar Ventas y Listar Resultados" << endl;
        cout << "\t3. Buscar producto por codigo" << endl;
        cout << "\t4. Modificar Atributos por producto" << endl;
        cout << "\t5. Adicionar Ventas Manuales" << endl;
        cout << "\t0. Salir" << endl;
        cout << "Seleccione una opcion: "; 
        cin >> opcion;

        switch(opcion)
        {
            case 1:
                adicionarProducto();
                system("pause");
                break;
            
            case 2:
                procesarVentas();
                system("pause");
                break;

            case 3:
                BuscarProductoPorCodigo();
                system("pause");
                break;

            case 4:
                ModificarProducto();
                system("pause");
                break;

            case 5:
                AdicionarVentaManual();
                system("pause");
                break;
            
            case 0:
                cout << "Saliendo del sistema de Farmacias Chávez..." << endl;
                break;
            
            default:
                if (opcion != 0)
                {
                    cout << "Opcion no valida." << endl;
                    system("pause");
                }
                break;
        }

    } while (opcion != 0);

    system("cls");
} 
