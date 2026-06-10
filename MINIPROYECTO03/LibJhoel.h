// Materia: Programación I, Paralelo 4
// Grupo: 3.
// Autor: Jhoel Marco Machicado Flores .
// Fecha creación: 1-06-2026
// Nombre del miniproyecto : Sistema de Inventario y Ventas - Farmacias Chávez

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

// Estructura del producto
struct structProducto
{
    int codigo;
    char nombre[30];
    int cantidadInicial;
    double precioUnitario;
};

// Esta funcion revisa si el codigo ya existe en PRODUCTOS.BIN
bool CodigoExiste(string nombreArchivoBinario, int codigoBuscado)
{
    ifstream archivo;
    structProducto producto;
    bool existe = false;

    archivo.open(nombreArchivoBinario, ios::binary);

    if (archivo.good())
    {
        while (archivo.read((char*)&producto, sizeof(structProducto)))
        {
            if (producto.codigo == codigoBuscado)
            {
                existe = true;
            }
        }
    }

    archivo.close();

    return existe;
}

// Esta funcion revisa si el nombre del producto ya existe
bool NombreExiste(string nombreArchivoBinario, char nombreBuscado[30])
{
    ifstream archivo;
    structProducto producto;
    bool existe = false;

    archivo.open(nombreArchivoBinario, ios::binary);

    if (archivo.good())
    {
        while (archivo.read((char*)&producto, sizeof(structProducto)))
        {
            if (strcmp(producto.nombre, nombreBuscado) == 0)
            {
                existe = true;
            }
        }
    }

    archivo.close();

    return existe;
}

// PUNTO 1: Adicionar producto
void AdicionarProducto(string nombreArchivoBinario)
{
    ofstream archivo;
    structProducto producto;

    system("cls");

    cout << "ADICIONAR PRODUCTO" << endl;

    cout << "Ingrese codigo del producto: ";
    cin >> producto.codigo;

    // Validacion 1: el codigo no debe repetirse
    if (CodigoExiste(nombreArchivoBinario, producto.codigo))
    {
        cout << endl;
        cout << "Error: ese codigo ya existe." << endl;
        return;
    }

    cin.ignore();

    cout << "Ingrese nombre del producto: ";
    cin.getline(producto.nombre, 30);

    // Validacion 2: el nombre no debe repetirse
    if (NombreExiste(nombreArchivoBinario, producto.nombre))
    {
        cout << endl;
        cout << "Error: ese nombre de producto ya existe." << endl;
        return;
    }

    cout << "Ingrese cantidad inicial: ";
    cin >> producto.cantidadInicial;

    cout << "Ingrese precio unitario: ";
    cin >> producto.precioUnitario;

    archivo.open(nombreArchivoBinario, ios::binary | ios::app);

    if (archivo.good())
    {
        archivo.write((char*)&producto, sizeof(structProducto));

        cout << endl;
        cout << "Producto registrado correctamente." << endl;
    }
    else
    {
        cout << "Error: no se pudo abrir el archivo " << nombreArchivoBinario << endl;
    }

    archivo.close();
}

// PUNTO 2: Procesar ventas y listar resultados
void ProcesarVentasYListarResultados(string nombreArchivoBinario, string nombreArchivoTexto)
{
    ifstream archivoVentas;
    fstream archivoProductos;

    string ci;
    string nombreCliente;
    string codigoTexto;
    string cantidadTexto;

    int codigoVenta;
    int cantidadVenta;

    system("cls");

    archivoVentas.open(nombreArchivoTexto);

    if (!archivoVentas.good())
    {
        cout << "Error: no se pudo abrir el archivo " << nombreArchivoTexto << endl;
        return;
    }

    cout << "PROCESAR VENTAS Y LISTAR RESULTADOS" << endl;
    cout << endl;

    cout << fixed << setprecision(2);

    cout << left << setw(10) << "CODIGO"
         << setw(25) << "NOMBRE PRODUCTO"
         << setw(15) << "CANT. INICIAL"
         << setw(10) << "PRECIO"
         << setw(15) << "CANT. VENDIDA"
         << setw(12) << "TOTAL Bs."
         << "ESTADO" << endl;

    while (getline(archivoVentas, ci, ';'))
    {
        getline(archivoVentas, nombreCliente, ';');
        getline(archivoVentas, codigoTexto, ';');
        getline(archivoVentas, cantidadTexto);

        codigoVenta = stoi(codigoTexto);
        cantidadVenta = stoi(cantidadTexto);

        archivoProductos.open(nombreArchivoBinario, ios::binary | ios::in | ios::out);

        if (!archivoProductos.good())
        {
            cout << "Error: no se pudo abrir el archivo " << nombreArchivoBinario << endl;
            archivoVentas.close();
            return;
        }

        structProducto producto;
        bool encontrado = false;

        while (archivoProductos.read((char*)&producto, sizeof(structProducto)))
        {
            if (producto.codigo == codigoVenta)
            {
                encontrado = true;

                int cantidadInicialAntes = producto.cantidadInicial;
                double totalVenta = cantidadVenta * producto.precioUnitario;

                cout << left << setw(10) << producto.codigo
                     << setw(25) << producto.nombre
                     << setw(15) << cantidadInicialAntes
                     << setw(10) << producto.precioUnitario
                     << setw(15) << cantidadVenta
                     << setw(12) << totalVenta;

                if (producto.cantidadInicial >= cantidadVenta)
                {
                    producto.cantidadInicial = producto.cantidadInicial - cantidadVenta;

                    archivoProductos.seekp(-(int)sizeof(structProducto), ios::cur);

                    archivoProductos.write((char*)&producto, sizeof(structProducto));

                    cout << "Venta realizada";
                }
                else
                {
                    cout << "Stock insuficiente";
                }

                cout << endl;
            }
        }

        if (encontrado == false)
        {
            cout << left << setw(10) << codigoVenta
                 << setw(25) << "NO EXISTE"
                 << setw(15) << 0
                 << setw(10) << 0
                 << setw(15) << cantidadVenta
                 << setw(12) << 0
                 << "Producto no encontrado" << endl;
        }

        archivoProductos.close();
    }

    archivoVentas.close();

    cout << endl;
    cout << "Proceso de ventas terminado." << endl;
}
