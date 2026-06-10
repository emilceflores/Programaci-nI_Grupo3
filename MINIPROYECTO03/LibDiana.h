// Materia: Programación I, Paralelo 4
// Grupo: 3.
// Autor: Diana Ninoska Vasquez Benitez.
// Fecha creación: 27-05-2026
// Nombre del miniproyecto : Sistema de Inventario y Ventas - Farmacias Chávez

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void BuscarProductoPorCodigo()
{
    ifstream archivo;  //Leer archivo

    structProducto producto; 
    int codigoBuscar;
    bool encontrado = false;

    cout << "BUSQUEDA DE PRODUCTOS" << endl;
    cout << "=====================" << endl;
    cout << "Ingrese el codigo de producto a buscar: ";
    cin >> codigoBuscar;

    archivo.open("PRODUCTOS.BIN", ios::binary);

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
        cout << "Error: No se pudo abrir el archivo de inventario PRODUCTOS.BIN" << endl;
    }
    archivo.close(); 
}

void AdicionarVentaManual()
{
    ifstream archivoLectura;   // solo para LEER PRODUCTOS.BIN
    ofstream archivoEscritura;  // para ESCRIBIR en VENTAS.txt
    
    structProducto producto;
    int codigoProducto;
    int cantidadComprada;
    bool productoExiste = false;

    long int ci;
    char nombreCliente[30];

    cout << "ADICIONAR VENTA MANUAL" << endl;
    cout << "======================" << endl;
    
    cout << "Ingrese CI del Cliente: "; 
    cin >> ci;
    cin.ignore(); // Limpia el buffer
    
    cout << "Ingrese Nombre del Cliente: ";
    cin.getline(nombreCliente, 30);

    //Pedir el codigo del producto y verificar si existe
    cout << "Ingrese el codigo del producto: ";
    cin >> codigoProducto;

    archivoLectura.open("PRODUCTOS.BIN", ios::binary); // Abrimos para LEER archivo binario
    if (archivoLectura.good())
    {
        while (archivoLectura.read((char*)&producto, sizeof(structProducto)))
        {
            if (producto.codigo == codigoProducto)
            {
                productoExiste = true;
                break;    //se encontro el producto, salimos del ciclo de lectura
            }
        }
    }
    
    archivoLectura.close(); // Cerramos la lectura 
    // si el producto no existe, detenemos el proceso de inmediato
    if (!productoExiste)
    {
        cout << "\nERROR: El codigo [" << codigoProducto << "] no existe en el inventario." << endl;
        return; // devolvemos el mensaje 
    }

    cout << "Ingrese la cantidad comprada: ";
    cin >> cantidadComprada;

    // opcion 5 , registrar la transacción en el archivo.txt
    archivoEscritura.open("VENTAS.txt", ios::app); // Abrimos exclusivamente para ESCRIBIR/AÑADIR

    if (archivoEscritura.good())
    {
        // seguimos el orden 
        archivoEscritura << ci << ";" << nombreCliente << ";" << codigoProducto << ";" << cantidadComprada << endl;
        cout << "\tSe ha registrado la venta manual correctamente" << endl;
    }
    else
    {
        cout << "Error: No se pudo abrir o crear el archivo de ventas (VENTAS.txt)" << endl;
    }
    archivoEscritura.close(); // Cierre 
}