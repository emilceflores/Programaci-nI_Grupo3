#include <iostream>
#include <fstream>

using namespace std;

struct Producto
{
    int codigo;
    char nombre[30];
    float precio;
};

void ModificarProducto(string NombreArchivo)
{
    Producto producto;
    fstream archivo;
    int codigoBuscado;

    // Variable para indicar si se encontró el producto
    bool encontrado = false;

    system("cls");

    cout << "Ingrese el codigo del producto a modificar: ";
    cin >> codigoBuscado;

    // Abrir el archivo en modo lectura y escritura binaria
    archivo.open(NombreArchivo, ios::in | ios::out | ios::binary);

    // Verificar si el archivo se abrió correctamente
    if (archivo.good())
    {
        // Leer los registros del archivo y buscar el producto
        while (archivo.read((char*)&producto, sizeof(Producto)) && !encontrado)
        {
            if (codigoBuscado == producto.codigo)
            {
                cout << "\nPRODUCTO ENCONTRADO: " << producto.nombre << endl;
                cout << "-----------------------------------" << endl;
                cout << "\tCodigo: " << producto.codigo << endl;
                cout << "\tPrecio: " << producto.precio << endl;
                cout << "-----------------------------------" << endl;

                encontrado = true;

                // Regresar al inicio del registro encontrado
                archivo.seekp(-sizeof(Producto), ios::cur);

                // Ingresar los nuevos datos
                cin.ignore();

                cout << "Ingrese el nuevo nombre: ";
                cin.getline(producto.nombre, 30);

                cout << "Ingrese el nuevo precio: ";
                cin >> producto.precio;

                // Guardar los cambios en el archivo
                archivo.write((char*)&producto, sizeof(Producto));

                cout << "\nProducto modificado correctamente." << endl;
            }
        }

        if (!encontrado)
        {
            cout << "Producto no encontrado." << endl;
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }

    system("pause");

    // Cerrar el archivo
    archivo.close();
}