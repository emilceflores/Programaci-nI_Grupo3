// Materia: Programación I, Paralelo 4
// Grupo: 3.
// Autor: Jhoel Marco Machicado Flores .
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

// Verifica si el nombre del producto ya existe en PRODUCTOS.BIN
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

// PUNTO 1: Adiciona productos al archivo PRODUCTOS.BIN
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

    cout << "Producto guardado correctamente.\n";
}

// Acumula las ventas cuando el mismo codigo aparece varias veces en VENTAS.txt
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

// Busca la cantidad vendida de un producto por su codigo
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

// PUNTO 2: Procesa VENTAS.txt, lista resultados y actualiza stock
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

    string ci;
    string nombreCliente;
    string codigoTexto;
    string cantidadTexto;

    // Lee el archivo VENTAS.txt separado por punto y coma
    while (getline(ventas, ci, ';'))
    {
        getline(ventas, nombreCliente, ';');
        getline(ventas, codigoTexto, ';');
        getline(ventas, cantidadTexto);

        int codigoVenta = stoi(codigoTexto);
        int cantidadVenta = stoi(cantidadTexto);

        agregarVenta(codigoVenta, cantidadVenta, codigos, cantidades, n);
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
         << setw(12) << "TOTAL Bs."
         << setw(20) << "ESTADO"
         << endl;

    cout << "====================================================================================================\n";

    while (archivo.read((char*)&producto, sizeof(producto)))
    {
        int cantidadVendida = buscarCantidadVendida(producto.codigo, codigos, cantidades, n);

        if (cantidadVendida > 0)
        {
            int cantidadAntes = producto.cantidadInicial;
            double total = cantidadVendida * producto.precioUnitario;

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

                archivo.seekp(-int(sizeof(producto)), ios::cur);
                archivo.write((char*)&producto, sizeof(producto));
                archivo.seekg(archivo.tellp());
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
    }

    archivo.close();

    cout << "\nVentas procesadas correctamente.\n";
}
