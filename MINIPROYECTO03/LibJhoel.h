// Materia: Programación I, Paralelo 4
// Grupo: 3.
// Autor: Jhel Marco Machicado Flores.
// Fecha creación: 1-06-2026
// Nombre del miniproyecto : Sistema de Inventario y Ventas - Farmacias Chávez
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cstdio>

using namespace std;

// Estructura del producto
struct structProducto
{
    int codigo;
    char nombre[30];
    int cantidadInicial;
    double precioUnitario;
};

// Verifica si el codigo ya existe
bool codigoexiste(int codigobuscado)
{
    ifstream archivo;
    structProducto producto;
    bool existe = false;

    archivo.open("PRODUCTOS.BIN", ios::binary);

    if (archivo.good())
    {
        while (archivo.read((char*)&producto, sizeof(structProducto)))
        {
            if (producto.codigo == codigobuscado)
            {
                existe = true;
            }
        }
    }

    archivo.close();

    return existe;
}

// Verifica si el nombre ya existe
bool nombreexiste(char nombrebuscado[])
{
    ifstream archivo;
    structProducto producto;
    bool existe = false;

    archivo.open("PRODUCTOS.BIN", ios::binary);

    if (archivo.good())
    {
        while (archivo.read((char*)&producto, sizeof(structProducto)))
        {
            if (strcmp(producto.nombre, nombrebuscado) == 0)
            {
                existe = true;
            }
        }
    }

    archivo.close();

    return existe;
}

// PUNTO 1: Adicionar producto
void adicionarProducto()
{
    ofstream archivo;
    structProducto producto;

    cout << "ADICIONAR PRODUCTO" << endl;
    cout << "==================" << endl;

    cout << "Ingrese codigo del producto: ";
    cin >> producto.codigo;

    if (codigoexiste(producto.codigo))
    {
        cout << "\nError: El codigo ya existe." << endl;
    }
    else
    {
        cin.ignore();

        cout << "Ingrese nombre del producto: ";
        cin.getline(producto.nombre, 30);

        if (nombreexiste(producto.nombre))
        {
            cout << "\nError: El nombre ya existe." << endl;
        }
        else
        {
            cout << "Ingrese cantidad inicial: ";
            cin >> producto.cantidadInicial;

            cout << "Ingrese precio unitario: ";
            cin >> producto.precioUnitario;

            archivo.open("PRODUCTOS.BIN", ios::binary | ios::app);

            if (archivo.good())
            {
                archivo.write((char*)&producto, sizeof(structProducto));
                cout << "\nProducto registrado correctamente." << endl;
            }
            else
            {
                cout << "\nError: No se pudo abrir PRODUCTOS.BIN" << endl;
            }

            archivo.close();
        }
    }
}

// PUNTO 2: Procesar ventas y listar resultados
void procesarVentas()
{
    ifstream archivo;
    ofstream temporal;
    ifstream ventas;

    structProducto producto;

    int ci;
    char nombreCliente[30];
    int codigoVenta;
    int cantidadVenta;
    char separador;

    int cantidadVendida;
    int cantidadAntes;
    double total;

    archivo.open("PRODUCTOS.BIN", ios::binary);
    temporal.open("TEMP.BIN", ios::binary);

    if (archivo.good() && temporal.good())
    {
        cout << "\nREPORTE DE VENTAS" << endl;
        cout << "=================" << endl;

        cout << left
             << setw(10) << "CODIGO"
             << setw(25) << "NOMBRE PRODUCTO"
             << setw(15) << "CANT. INICIAL"
             << setw(10) << "PRECIO"
             << setw(15) << "CANT. VENDIDA"
             << setw(12) << "TOTAL Bs."
             << setw(20) << "ESTADO"
             << endl;

        cout << "====================================================================================================" << endl;

        while (archivo.read((char*)&producto, sizeof(structProducto)))
        {
            cantidadVendida = 0;

            ventas.open("VENTAS.txt");

            if (ventas.good())
            {
                while (ventas >> ci >> separador)
                {
                    ventas.getline(nombreCliente, 30, ';');

                    ventas >> codigoVenta >> separador;
                    ventas >> cantidadVenta;

                    ventas.ignore();

                    if (codigoVenta == producto.codigo)
                    {
                        cantidadVendida = cantidadVendida + cantidadVenta;
                    }
                }
            }
            else
            {
                cout << "\nNo se pudo abrir VENTAS.txt" << endl;
            }

            ventas.close();

            if (cantidadVendida > 0)
            {
                cantidadAntes = producto.cantidadInicial;
                total = cantidadVendida * producto.precioUnitario;

                if (cantidadVendida <= producto.cantidadInicial)
                {
                    producto.cantidadInicial = producto.cantidadInicial - cantidadVendida;

                    cout << left
                         << setw(10) << producto.codigo
                         << setw(25) << producto.nombre
                         << setw(15) << cantidadAntes
                         << setw(10) << fixed << setprecision(2) << producto.precioUnitario
                         << setw(15) << cantidadVendida
                         << setw(12) << fixed << setprecision(2) << total
                         << setw(20) << "Venta realizada"
                         << endl;
                }
                else
                {
                    cout << left
                         << setw(10) << producto.codigo
                         << setw(25) << producto.nombre
                         << setw(15) << cantidadAntes
                         << setw(10) << fixed << setprecision(2) << producto.precioUnitario
                         << setw(15) << cantidadVendida
                         << setw(12) << fixed << setprecision(2) << total
                         << setw(20) << "Stock insuficiente"
                         << endl;
                }
            }

            temporal.write((char*)&producto, sizeof(structProducto));
        }

        archivo.close();
        temporal.close();

        remove("PRODUCTOS.BIN");
        rename("TEMP.BIN", "PRODUCTOS.BIN");

        cout << "\nVentas procesadas correctamente." << endl;
    }
    else
    {
        cout << "\nError: No se pudo abrir PRODUCTOS.BIN o crear TEMP.BIN" << endl;

        archivo.close();
        temporal.close();
    }
}
