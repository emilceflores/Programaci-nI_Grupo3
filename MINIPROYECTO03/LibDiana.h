// Materia: Programación I, Paralelo 4
// Grupo: 3.
// Autor: Diana Ninoska Vasquez Benitez.
// Fecha creación: 27-05-2026
// Nombre del miniproyecto : Sistema de Inventario y Ventas - Farmacias Chávez

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void BuscarProductoPorCodigo(string nombreArchivoBinario, int codigoBuscar)
{
    ifstream archivo;
    structProducto producto; 
    bool encontrado = false;
    system("cls");

    archivo.open(nombreArchivoBinario, ios::binary);

    if (archivo.good())
    {
        while (archivo.read((char*) &producto, sizeof(structProducto)))
        {
            if (producto.codigo == codigoBuscar)
            {
                cout << "\nPRODUCTO ENCONTRADO" << endl;
                cout << "==================" << endl;
                cout << "Codigo:          " << producto.codigo << endl;
                cout << "Nombre:          " << producto.nombre << endl;
                cout << "Stock Inicial:   " << producto.cantidadInicial << endl;
                cout << "Precio Unitario: " << producto.precioUnitario << " Bs." << endl;
                encontrado = true;
            }
        }

        if (!encontrado)
        {
            cout << "\nEl producto con codigo [" << codigoBuscar << "] no existe en el inventario." << endl;
        }
    }
    else
    {
        cout << "Error: No se pudo abrir el archivo de inventario " << nombreArchivoBinario << endl;
    }

    archivo.close();
}

void AdicionarVentaManual(string nombreArchivoTexto)
{
    ofstream archivo; //EScribir en el archivo
    
    long int ci;
    char nombreCliente[30];
    int codigoProducto;
    int cantidadComprada;

    cout << "ADICIONAR VENTA MANUAL" << endl;
    cout << "======================" << endl;
    
    cout << "Ingrese CI del Cliente: "; 
    cin >> ci;
    cin.ignore();
    
    cout << "Ingrese Nombre del Cliente: ";
    cin.getline(nombreCliente, 30);
    
    cout << "Ingrese el codigo del producto: ";
    cin >> codigoProducto;
    
    cout << "Ingrese la cantidad comprada: ";
    cin >> cantidadComprada;

    archivo.open(nombreArchivoTexto, ios::app); 

    if (archivo.good()) 
    {
        archivo << ci << ";" << nombreCliente << ";" << codigoProducto << ";" << cantidadComprada << endl;
        cout << endl;
        cout << "\tSe ha registrado la venta manual correctamente" << endl;
        
    }
    else
    {
        cout << "Error no se pudo abrir o crear el archivo " << nombreArchivoTexto << endl;
    }
     archivo.close();
}