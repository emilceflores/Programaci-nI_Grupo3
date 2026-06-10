#include <iostream>   // Permite usar cout y cin para mostrar y pedir datos
#include <cstring>    // Permite usar strcmp para comparar nombres tipo char
#include <fstream>    // Permite trabajar con archivos ifstream, ofstream y fstream
#include <iomanip>    // Permite usar setw y setprecision para ordenar la tabla
#include <string>     // Permite usar variables tipo string

using namespace std;  // Evita escribir std::cout, std::cin, std::string

// Estructura que guarda los datos de un producto
struct structProducto 
{
    int codigo;              // Guarda el codigo del producto
    char nombre[30];         // Guarda el nombre del producto, maximo 29 caracteres
    int cantidadInicial;     // Guarda la cantidad o stock del producto
    double precioUnitario;   // Guarda el precio unitario del producto
};

// Funcion que verifica si un codigo ya existe en el archivo binario
bool CodigoExiste(string nombreArchivoBinario, int codigoBuscado)
{
    ifstream archivo;              // Creamos una variable para leer archivos
    structProducto producto;       // Creamos una variable producto para leer datos del archivo
    bool encontrado = false;       // Sirve para saber si se encontro el codigo

    archivo.open(nombreArchivoBinario, ios::binary); // Abrimos el archivo binario para lectura

    if (archivo.good()) // Verifica si el archivo se abrio correctamente
    {
        // Lee producto por producto desde el archivo
        while (archivo.read((char*)&producto, sizeof(structProducto)))
        {
            // Compara el codigo del producto con el codigo que estamos buscando
            if (producto.codigo == codigoBuscado)
            {
                encontrado = true; // Si lo encuentra, cambia encontrado a true
            }
        }
    }

    archivo.close(); // Cierra el archivo

    return encontrado; // Devuelve true si existe, false si no existe
}

// Funcion que verifica si el nombre del producto ya existe
bool NombreExiste(string nombreArchivoBinario, char nombreBuscado[30])
{
    ifstream archivo;             // Variable para leer el archivo
    structProducto producto;      // Variable para leer cada producto del archivo
    bool encontrado = false;      // Sirve para saber si el nombre fue encontrado

    archivo.open(nombreArchivoBinario, ios::binary); // Abre el archivo binario

    if (archivo.good()) // Verifica si el archivo se abrio correctamente
    {
        // Lee producto por producto desde el archivo
        while (archivo.read((char*)&producto, sizeof(structProducto)))
        {
            // strcmp compara dos textos tipo char
            // Si devuelve 0, significa que los nombres son iguales
            if (strcmp(producto.nombre, nombreBuscado) == 0)
            {
                encontrado = true; // Indica que el nombre ya existe
            }
        }
    }

    archivo.close(); // Cierra el archivo

    return encontrado; // Devuelve true si existe, false si no existe
}

// PUNTO 1: Funcion para adicionar producto
void AdicionarProducto(string nombreArchivoBinario)
{
    ofstream archivo;             // Variable para escribir en archivo
    structProducto producto;      // Variable para guardar los datos del producto

    system("cls"); // Limpia la pantalla

    cout << "ADICIONAR PRODUCTO" << endl; // Muestra titulo
    cout << "==================" << endl;  // Muestra linea decorativa

    cout << "Ingrese codigo del producto: "; // Pide el codigo
    cin >> producto.codigo;                 // Guarda el codigo ingresado

    // Verifica si el codigo ya existe en PRODUCTOS.BIN
    if (CodigoExiste(nombreArchivoBinario, producto.codigo))
    {
        cout << endl; // Salto de linea
        cout << "Error: El codigo ya existe en el inventario." << endl; // Mensaje de error
        return; // Sale de la funcion para no guardar un producto repetido
    }

    cin.ignore(); // Limpia el salto de linea que queda despues de ingresar el codigo

    cout << "Ingrese nombre del producto: "; // Pide el nombre del producto
    cin.getline(producto.nombre, 30);        // Guarda el nombre con espacios

    // Verifica si el nombre ya existe en el archivo binario
    if (NombreExiste(nombreArchivoBinario, producto.nombre))
    {
        cout << endl; // Salto de linea
        cout << "Error: El nombre del producto ya existe en el inventario." << endl; // Error
        return; // Sale de la funcion para no guardar nombres repetidos
    }

    cout << "Ingrese cantidad inicial: ";  // Pide la cantidad inicial
    cin >> producto.cantidadInicial;      // Guarda la cantidad inicial

    cout << "Ingrese precio unitario: ";   // Pide el precio unitario
    cin >> producto.precioUnitario;        // Guarda el precio unitario

    // Abre el archivo binario para agregar datos al final
    archivo.open(nombreArchivoBinario, ios::binary | ios::app);

    if (archivo.good()) // Verifica si el archivo se abrio correctamente
    {
        // Guarda todo el producto dentro del archivo binario
        archivo.write((char*)&producto, sizeof(structProducto));

        cout << endl; // Salto de linea
        cout << "\tProducto registrado correctamente." << endl; // Mensaje de confirmacion
    }
    else // Si el archivo no se pudo abrir
    {
        cout << "Error: No se pudo abrir o crear el archivo " << nombreArchivoBinario << endl;
    }

    archivo.close(); // Cierra el archivo
}

// PUNTO 2: Funcion para procesar ventas y listar resultados
void ProcesarVentasYListarResultados(string nombreArchivoBinario, string nombreArchivoTexto)
{
    ifstream archivoTexto;     // Variable para leer VENTAS.txt
    fstream archivoBinario;    // Variable para leer y modificar PRODUCTOS.BIN

    string ci;                 // Guarda el CI del cliente
    string nombreCliente;      // Guarda el nombre del cliente
    string codigoTexto;        // Guarda el codigo como texto
    string cantidadTexto;      // Guarda la cantidad como texto

    int codigosVendidos[100];       // Guarda los codigos vendidos
    int cantidadesVendidas[100];    // Guarda las cantidades vendidas
    int cantidadRegistros = 0;      // Cuenta cuantos productos diferentes fueron vendidos

    system("cls"); // Limpia la pantalla

    archivoTexto.open(nombreArchivoTexto); // Abre el archivo VENTAS.txt

    if (archivoTexto.good()) // Verifica si VENTAS.txt se abrio correctamente
    {
        // Lee el archivo de ventas linea por linea separando por punto y coma
        while (getline(archivoTexto, ci, ';'))
        {
            getline(archivoTexto, nombreCliente, ';'); // Lee el nombre del cliente
            getline(archivoTexto, codigoTexto, ';');   // Lee el codigo del producto como texto
            getline(archivoTexto, cantidadTexto);      // Lee la cantidad comprada como texto

            int codigoProducto = stoi(codigoTexto);      // Convierte el codigo de texto a entero
            int cantidadComprada = stoi(cantidadTexto);  // Convierte la cantidad de texto a entero

            bool codigoEncontrado = false; // Sirve para saber si el codigo ya esta guardado

            // Recorre los codigos que ya fueron guardados
            for (int i = 0; i < cantidadRegistros; i++)
            {
                // Si el codigo ya existe en el arreglo
                if (codigosVendidos[i] == codigoProducto)
                {
                    cantidadesVendidas[i] = cantidadesVendidas[i] + cantidadComprada; // Suma cantidades
                    codigoEncontrado = true; // Indica que ya estaba guardado
                }
            }

            // Si el codigo no estaba guardado
            if (codigoEncontrado == false)
            {
                codigosVendidos[cantidadRegistros] = codigoProducto;       // Guarda el nuevo codigo
                cantidadesVendidas[cantidadRegistros] = cantidadComprada;  // Guarda su cantidad
                cantidadRegistros++; // Aumenta la cantidad de registros
            }
        }
    }
    else // Si no se pudo abrir VENTAS.txt
    {
        cout << "Error: No se pudo abrir el archivo de ventas " << nombreArchivoTexto << endl;
        return; // Sale de la funcion
    }

    archivoTexto.close(); // Cierra VENTAS.txt

    cout << fixed << setprecision(2); // Muestra numeros decimales con 2 cifras

    cout << "PROCESAR VENTAS Y LISTAR RESULTADOS" << endl; // Titulo
    cout << "===================================" << endl;          // Linea decorativa
    cout << endl; // Salto de linea

    // Imprime los encabezados de la tabla
    cout << left << setw(10) << "CODIGO"
         << setw(25) << "NOMBRE PRODUCTO"
         << setw(15) << "CANT. INICIAL"
         << setw(10) << "PRECIO"
         << setw(15) << "CANT. VENDIDA"
         << setw(12) << "TOTAL Bs." 
         << "ESTADO" << endl;

    // Recorre todos los productos vendidos que se guardaron en los arreglos
    for (int i = 0; i < cantidadRegistros; i++)
    {
        // Abre PRODUCTOS.BIN para leer y modificar
        archivoBinario.open(nombreArchivoBinario, ios::binary | ios::in | ios::out);

        if (archivoBinario.good()) // Verifica si PRODUCTOS.BIN se abrio correctamente
        {
            structProducto producto;          // Variable para leer cada producto
            bool productoEncontrado = false;  // Sirve para saber si el producto fue encontrado

            // Lee producto por producto desde PRODUCTOS.BIN
            while (archivoBinario.read((char*)&producto, sizeof(structProducto)))
            {
                // Compara el codigo del producto con el codigo vendido
                if (producto.codigo == codigosVendidos[i])
                {
                    productoEncontrado = true; // Indica que el producto existe

                    int cantidadInicialAntes = producto.cantidadInicial; // Guarda el stock antes de restar
                    int cantidadVendida = cantidadesVendidas[i];         // Guarda la cantidad vendida
                    double totalVenta = cantidadVendida * producto.precioUnitario; // Calcula el total

                    // Imprime los datos del producto vendido
                    cout << left << setw(10) << producto.codigo
                         << setw(25) << producto.nombre
                         << setw(15) << cantidadInicialAntes
                         << setw(10) << producto.precioUnitario
                         << setw(15) << cantidadVendida
                         << setw(12) << totalVenta;

                    // Verifica si hay stock suficiente
                    if (producto.cantidadInicial >= cantidadVendida)
                    {
                        producto.cantidadInicial = producto.cantidadInicial - cantidadVendida; // Resta el stock

                        // Retrocede el puntero de escritura al inicio del producto actual
                        archivoBinario.seekp(-(int)sizeof(structProducto), ios::cur);

                        // Sobrescribe el producto con el stock actualizado
                        archivoBinario.write((char*)&producto, sizeof(structProducto));

                        cout << "Venta realizada"; // Muestra estado
                    }
                    else // Si no hay stock suficiente
                    {
                        cout << "Stock insuficiente"; // Muestra estado
                    }

                    cout << endl; // Salto de linea
                }
            }

            // Si el producto vendido no existe en PRODUCTOS.BIN
            if (productoEncontrado == false)
            {
                cout << left << setw(10) << codigosVendidos[i]
                     << setw(25) << "NO EXISTE"
                     << setw(15) << 0
                     << setw(10) << 0
                     << setw(15) << cantidadesVendidas[i]
                     << setw(12) << 0
                     << "Producto no encontrado" << endl;
            }
        }
        else // Si no se pudo abrir PRODUCTOS.BIN
        {
            cout << "Error: No se pudo abrir el archivo de inventario " << nombreArchivoBinario << endl;
        }

        archivoBinario.close(); // Cierra PRODUCTOS.BIN
    }
}
