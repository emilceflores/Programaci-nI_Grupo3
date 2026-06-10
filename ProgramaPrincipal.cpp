//PROGRAMA PRINCIPAL
#include <iostream>
#include "LibDiana.h"
#include "LibJhoel.h"
#include "LibEmilce.h"

using namespace std;

void Mostrarmenu();
int main() 
{
    Mostrarmenu();

    return 0;
} 
void Mostrarmenu()
{
    int opcion=0 ;
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
        cin>>opcion;

        switch(opcion)
        {
            case 1:
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                ModificarProducto();
                break;

            case 5:
                break;
            
            default:
                if (opcion !=0)
                {
                    cout<<"Opcion no valida."<<endl;
                    system("pause");
                }
                break;
                
        }
    } while (opcion != 0);
    system("cls");
    
}

    
