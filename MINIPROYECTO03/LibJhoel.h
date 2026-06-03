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

