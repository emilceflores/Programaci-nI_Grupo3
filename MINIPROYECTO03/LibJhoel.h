// Materia: Programacion I, Paralelo 4
// Grupo: 3.
// Autor: Jhel Marco Machicado Flores.
// Fecha creacion: 1-06-2026
// Nombre del miniproyecto : Sistema de Inventario y Ventas - Farmacias Chavez

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

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
    ifstream archivo("PRODUCTOS.BIN", ios::binary); // abrir lectura binaria
    structProducto producto;

    while (archivo.read((char*)&producto, sizeof(producto)))
    {
        if (producto.codigo == codigobuscado)
        {
            archivo.close(); // cerrar archivo
            return true;
        }
    }

    archivo.close(); // cerrar archivo
    return false;
}

// Verifica si el nombre ya existe en PRODUCTOS.BIN
bool nombreexiste(char nombrebuscado[])
{
    ifstream archivo("PRODUCTOS.BIN", ios::binary); // abrir lectura binaria
    structProducto producto;

    while (archivo.read((char*)&producto, sizeof(producto)))
    {
        if (strcmp(producto.nombre, nombrebuscado) == 0)
        {
            archivo.close(); // cerrar archivo
            return true;
        }
    }

    archivo.close(); // cerrar archivo
    return false;
}

// =========================================================================
// OPCION 1: Adicionar Producto
void adicionarProducto()
{
    ofstream archivo;
    structProducto nuevoProducto;

    cout << "ADICIONAR PRODUCTO" << endl;
    cout << "==================" << endl;

    cout << "Ingrese el codigo del producto: ";
    cin >> nuevoProducto.codigo;

    if (codigoexiste(nuevoProducto.codigo))
    {
        cout << "\nERROR: El codigo ya existe en el inventario." << endl;
        return; // sale si el codigo ya existe
    }

    cin.ignore(); // limpia el buffer
    cout << "Ingrese el nombre del producto: ";
    cin.getline(nuevoProducto.nombre, 30);

    if (nombreexiste(nuevoProducto.nombre))
    {
        cout << "\nERROR: El nombre del producto ya existe en el inventario." << endl;
        return; // sale si el nombre ya existe
    }

    cout << "Ingrese la cantidad inicial: ";
    cin >> nuevoProducto.cantidadInicial;

    cout << "Ingrese el precio unitario (Bs.): ";
    cin >> nuevoProducto.precioUnitario;

    archivo.open("PRODUCTOS.BIN", ios::binary | ios::app); // abre para añadir 

    if (archivo.good())
    {
        archivo.write((char*)&nuevoProducto, sizeof(nuevoProducto)); // escribe el struct
        cout << "\nProducto adicionado correctamente." << endl;
    }
    else
    {
        cout << "Error: No se pudo abrir el archivo de productos." << endl;
    }

    archivo.close(); // cierra escritura binaria
}

// =========================================================================
// FUNCIONES AUXILIARES PARA LA OPCION 2 (agrupa ventas )
void agregarVenta(int codigoVenta, int cantidadVenta, int codigos[], int cantidades[], int &n)
{
    for (int i = 0; i < n; i++)
    {
        if (codigos[i] == codigoVenta)
        {
            cantidades[i] = cantidades[i] + cantidadVenta; // acumula la cantidad
            return;
        }
    }

    codigos[n] = codigoVenta; // agrega nuevo codigo al arreglo
    cantidades[n] = cantidadVenta; // agrega nueva cantidad al arreglo
    n++; // incrementa el tamaño ocupado
}

int buscarCantidadVendida(int codigoProducto, int codigos[], int cantidades[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (codigos[i] == codigoProducto)
        {
            return cantidades[i]; // devuelve total vendido
        }
    }
    return 0; // devuelve cero si no se vendio nada
}

// =========================================================================
// OPCION 2: Procesar Ventas y Listar Resultados
void procesarVentas()
{
    structProducto productos[100];
    int totalProductos = 0;

    // 1. LEER EL INVENTARIO (Solo lectura)
    ifstream archivoProductos("PRODUCTOS.BIN", ios::binary); // solo lectura binaria
    if (!archivoProductos)
    {
        cout << "\nNo se pudo abrir el archivo PRODUCTOS.BIN o esta vacio.\n";
        return;
    }

    while (archivoProductos.read((char*)&productos[totalProductos], sizeof(structProducto)))
    {
        totalProductos++; // cuenta productos leidos
    }
    archivoProductos.close(); // cierra lectura binaria

    // 2. LEER LAS VENTAS ACUMULADAS EN EL TXT
    int codigosVendidos[100] = {0}; // inicializado en cero
    int cantidadesVendidas[100] = {0}; // inicializado en cero
    int totalVentas = 0;

    ifstream ventas("VENTAS.txt"); // solo lectura
    if (!ventas)
    {
        cout << "\nNo hay ventas registradas en VENTAS.txt para procesar.\n";
        return;
    }

    string ci;
    string nombreCliente;
    string codigoTexto;
    string cantidadTexto;

    // Lee las filas delimitadas por punto y coma
    while (getline(ventas, ci, ';'))
    {
        getline(ventas, nombreCliente, ';');
        getline(ventas, codigoTexto, ';');
        getline(ventas, cantidadTexto);

        int codigoVenta = stoi(codigoTexto); // convierte a entero
        int cantidadVenta = stoi(cantidadTexto); // convierte a entero

        agregarVenta(codigoVenta, cantidadVenta, codigosVendidos, cantidadesVendidas, totalVentas); // agrupa datos
    }
    ventas.close(); // cierra lectura de texto

    // 3. MOSTRAR EL REPORTE 
    cout << "\nREPORTE DE VENTAS PROCESADAS" << endl;
    cout << "=======================================================================================" << endl;
    cout << left
         << setw(10) << "CODIGO"
         << setw(25) << "NOMBRE PRODUCTO"
         << setw(15) << "CANT. INICIAL"
         << setw(10) << "PRECIO"
         << setw(15) << "CANT. VENDIDA"
         << setw(12) << "TOTAL (Bs)"
         << endl;
    cout << "=======================================================================================\n";

    for (int i = 0; i < totalProductos; i++)
    {
        // Busca si el codigo en ventas en el artivo.txt
        int cantidadVendida = buscarCantidadVendida(productos[i].codigo, codigosVendidos, cantidadesVendidas, totalVentas);

        if (cantidadVendida > 0)
        {
            int cantidadAntes = productos[i].cantidadInicial; // stock inicial intacto
            double totalDinero = cantidadVendida * productos[i].precioUnitario; // operacion matematica

            // Muestra los resultados calculados directamente en consola
            cout << left
                 << setw(10) << productos[i].codigo
                 << setw(25) << productos[i].nombre
                 << setw(15) << cantidadAntes // muestra stock inicial fijo
                 << setw(10) << fixed << setprecision(2) << productos[i].precioUnitario
                 << setw(15) << cantidadVendida // muestra cantidad vendida agrupada
                 << setw(12) << fixed << setprecision(2) << totalDinero
                 << endl;
        }
    }

    cout << "\nReporte visual generado con exito.\n";
}
