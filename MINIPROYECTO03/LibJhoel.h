// Materia: Programación I, Paralelo 4
// Grupo: 3.
// Autor: Jhel Marco Machicado Flores.
// Fecha creación: 1-06-2026
// Nombre del miniproyecto : Sistema de Inventario y Ventas - Farmacias Chávez
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

// Estructura donde se guardan los datos de cada producto
struct structProducto
{
    int codigo;
    char nombre[30];
    int cantidadInicial;
    double precioUnitario;
};

// Verifica si el codigo ya existe en PRODUCTOS.BIN
bool codigoexiste(int codigobuscado)
{
    ifstream archivo("PRODUCTOS.BIN", ios::binary);
    structProducto producto;

    while (archivo.read((char*)&producto, sizeof(producto)))
    {
        if (producto.codigo == codigobuscado)
        {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

// Verifica si el nombre ya existe en PRODUCTOS.BIN
bool nombreexiste(char nombrebuscado[])
{
    ifstream archivo("PRODUCTOS.BIN", ios::binary);
    structProducto producto;

    while (archivo.read((char*)&producto, sizeof(producto)))
    {
        if (strcmp(producto.nombre, nombrebuscado) == 0)
        {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

// Punto 1: adiciona un producto al archivo binario
void adicionarProducto()
{
    structProducto producto;

    cout << "\nADICIONAR PRODUCTO\n";

    cout << "Codigo: ";
    cin >> producto.codigo;

    if (codigoexiste(producto.codigo))
    {
        cout << "Error: ese codigo ya existe.\n";
        return;
    }

    cin.ignore();

    cout << "Nombre del producto: ";
    cin.getline(producto.nombre, 30);

    if (nombreexiste(producto.nombre))
    {
        cout << "Error: ese nombre de producto ya existe.\n";
        return;
    }

    cout << "Cantidad inicial: ";
    cin >> producto.cantidadInicial;

    cout << "Precio unitario: ";
    cin >> producto.precioUnitario;

    ofstream archivo("PRODUCTOS.BIN", ios::binary | ios::app);

    archivo.write((char*)&producto, sizeof(producto));

    archivo.close();

    cout << "\nProducto guardado correctamente.\n";
}

// Acumula ventas del mismo codigo de producto
void agregarVenta(int codigoVenta, int cantidadVenta, int codigos[], int cantidades[], int &n)
{
    for (int i = 0; i < n; i++)
    {
        if (codigos[i] == codigoVenta)
        {
            cantidades[i] = cantidades[i] + cantidadVenta;
            return;
        }
    }

    codigos[n] = codigoVenta;
    cantidades[n] = cantidadVenta;
    n++;
}

// Busca la cantidad vendida de un producto
int buscarCantidadVendida(int codigoProducto, int codigos[], int cantidades[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (codigos[i] == codigoProducto)
        {
            return cantidades[i];
        }
    }

    return 0;
}

// Punto 2: procesa VENTAS.txt, muestra reporte y actualiza stock
void procesarVentas()
{
    ifstream ventas("VENTAS.txt");

    if (!ventas)
    {
        cout << "\nNo se pudo abrir el archivo VENTAS.txt\n";
        return;
    }

    int codigos[100];
    int cantidades[100];
    int n = 0;

    int ci;
    string nombreCliente;
    int codigoVenta;
    int cantidadVenta;
    char puntoComa;

    while (ventas >> ci >> puntoComa)
    {
        getline(ventas, nombreCliente, ';');

        ventas >> codigoVenta >> puntoComa >> cantidadVenta;

        agregarVenta(codigoVenta, cantidadVenta, codigos, cantidades, n);

        ventas.ignore(1000, '\n');
    }

    ventas.close();

    fstream archivo("PRODUCTOS.BIN", ios::binary | ios::in | ios::out);

    if (!archivo)
    {
        cout << "\nNo se pudo abrir el archivo PRODUCTOS.BIN\n";
        return;
    }

    structProducto producto;

    cout << "\nREPORTE DE VENTAS\n\n";

    cout << left
         << setw(10) << "CODIGO"
         << setw(25) << "NOMBRE PRODUCTO"
         << setw(15) << "CANT. INICIAL"
         << setw(10) << "PRECIO"
         << setw(15) << "CANT. VENDIDA"
         << setw(12) << "TOTAL(Bs)"
         << endl;

    cout << "=======================================================================================\n";

    while (archivo.read((char*)&producto, sizeof(producto)))
    {
        int cantidadVendida = buscarCantidadVendida(producto.codigo, codigos, cantidades, n);

        if (cantidadVendida > 0)
        {
            int cantidadAntes = producto.cantidadInicial;
            double total = cantidadVendida * producto.precioUnitario;

            cout << left
                 << setw(10) << producto.codigo
                 << setw(25) << producto.nombre
                 << setw(15) << cantidadAntes
                 << setw(10) << fixed << setprecision(2) << producto.precioUnitario
                 << setw(15) << cantidadVendida
                 << setw(12) << fixed << setprecision(2) << total
                 << endl;

            producto.cantidadInicial = producto.cantidadInicial - cantidadVendida;

            archivo.seekp(-int(sizeof(producto)), ios::cur);
            archivo.write((char*)&producto, sizeof(producto));
            archivo.seekg(archivo.tellp());
        }
    }

    archivo.close();

    cout << "\nVentas procesadas correctamente.\n";
}
