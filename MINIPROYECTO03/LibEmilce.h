// Materia: Programación I, Paralelo 4
// Grupo: 3.
// Autor: Emilce Jael Flores Gutierrez.
// Fecha creación: 01-06-2026
// Nombre del miniproyecto : Sistema de Inventario y Ventas - Farmacias Chávez

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void ModificarProducto()
{
    structProducto producto;
    fstream archivo;
    int codigoBuscado;

    // indica si se encontró el producto
    bool encontrado = false;

    cout << "MODIFICAR PRODUCTO" << endl;
    cout << "==================" << endl;

    cout << "Ingrese el codigo del producto a modificar: ";
    cin >> codigoBuscado;

    // Abrir el archivo en modo BINARIA para leer y escribir al mismo tiempo
    archivo.open("PRODUCTOS.BIN", ios::in | ios::out | ios::binary);

    // Verificar si el archivo se abrió correctamente
    if (archivo.good())
    {
        // Leer los registros del archivo y buscar el producto
        while (archivo.read((char*)&producto, sizeof(structProducto)) && !encontrado)
        {
            // Verificar si el código ingresado coincide con el código del producto
            if (producto.codigo == codigoBuscado)
            {
                encontrado = true;

                // Mostrar los datos actuales del producto
                cout << "\nPRODUCTO ENCONTRADO" << endl;
                cout << "------------------------" << endl;
                cout << "Codigo: " << producto.codigo << endl;
                cout << "Nombre: " << producto.nombre << endl;
                cout << "Cantidad Inicial: " << producto.cantidadInicial << endl;
                cout << "Precio Unitario: " << producto.precioUnitario << endl;
                cout << "------------------------" << endl;

                // Mover el puntero de escritura al inicio del registro encontrado
                archivo.seekp(-sizeof(structProducto), ios::cur);

                // Limpiar el buffer de teclado
                cin.ignore();

                // Ingresar los nuevos datos del producto
                cout << "\nIngrese el nuevo nombre: ";
                cin.getline(producto.nombre, 30);

                cout << "Ingrese el nuevo precio unitario: ";
                cin >> producto.precioUnitario;

                // Escribir los nuevos datos en el archivo binario
                archivo.write((char*)&producto, sizeof(structProducto));

                cout << "\nProducto modificado correctamente." << endl;
            }
        }

        // Verificar si no se encontró el producto
        if (!encontrado)
        {
            cout << "\nProducto no encontrado." << endl;
        }

        // Cerrar el archivo
        archivo.close();
    }
    else
    {
        cout << "Error: No se pudo abrir el archivo PRODUCTOS.BIN" << endl;
    }
}