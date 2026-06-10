#include <iostream>
#include "LibJhoel.h"
#include "LibDiana.h"
#include "LibEmilce.h"

using namespace std;

void Mostrarmenu(string archivoBinario,string archivoTexto);
int main() 
{
    
    string archivoBinario = "PRODUCTOS.BIN";
    string archivoTexto = "VENTAS.txt";
    system("chcp 65001");
    Mostrarmenu(archivoBinario,archivoTexto);

    return 0;
} 
void Mostrarmenu(string archivoBinario,string archivoTexto)
{
    int codigoBuscar= 0;
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

                cout << "BUSQUEDA DE PRODUCTOS" << endl;
                cout << "=====================" << endl;
                cout << "Ingrese el codigo de producto a buscar: ";
                cin >> codigoBuscar;
                
                BuscarProductoPorCodigo(archivoBinario, codigoBuscar);
                system("pause");

                break;

            case 4:
                ModificarProducto();
                break;

            case 5:

                AdicionarVentaManual(archivoTexto);
                system("pause");
                break;
            
            case 0:
                cout << "Saliendo del sistema de Farmacias Chávez..." << endl;
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

    