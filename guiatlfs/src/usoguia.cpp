#include "../include/guiatlf.h"
#include <fstream>
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Dime el nombre del fichero con la guia" << endl;
        return 0;
    }
    ifstream f(argv[1]);
    if (!f)
    {
        cout << "No puedo abrir el fichero " << argv[1] << endl;
        return 0;
    }

    Guia_Tlf g;

    f >> g;
    cout << "La guia insertada " << g << endl;
    cin.clear();
    cout << "Dime un nombre sobre el que quieres obtener el telefono" << endl;
    string n;
    while (getline(cin, n))
    {
        cout << "Buscando " << n << "...." << endl;
        string tlf = g.gettelefono(n);
        if (tlf == "")
        {
            cout << "No existe ese nombre en la guia" << endl;
        }
        else
            cout << "El telefono es " << tlf << endl;
        cout << "[Pulse CTRL+D para finalizar] Dime un nombre sobre el que quieres obtener el telefono" << endl;
    }

    cout << "Listando la guia con iteradores:" << endl;
    Guia_Tlf::iterator it;
    for (it = g.begin(); it != g.end(); ++it)
        cout << (*it) << endl;

    cout << "******** GUIA CON TODOS LOS NOMBRES QUE EMPIEZAN POR LA MISMA LETRA " << endl;

    Guia_Tlf guiaMismaLetra = g.tlfByFirstLetter('C');
    for (it = guiaMismaLetra.begin(); it != guiaMismaLetra.end(); ++it)
        cout << (*it) << endl;

    cout << "******** GUIA LOS TELEFONOS ENTRE DOS NOMBRES " << endl;

    Guia_Tlf guiaRango = g.getTlfByRange("Fernando Gonzalez Pro", "Simon Bolivar Carrion");
    for (it = guiaRango.begin(); it != guiaRango.end(); ++it)
        cout << (*it) << endl;

    cout << "******** MODIFICAR NUMERO DE SIMON BOLIVAR " << endl;

    g.modifyTlfByname("Simon Bolivar Carrion", "111111112"); //No se modifica si hay alguien que tenga ese numero
    for (it = g.begin(); it != g.end(); ++it)
        cout << (*it) << endl;

    cout << "******** INTERSECCION DE GUIAS  " << endl;

    ifstream f2(argv[2]);
    if (!f2)
    {
        cout << "No puedo abrir el fichero " << argv[2] << endl;
        return 0;
    }

    Guia_Tlf g2;

    f2 >> g2;
    cin.clear();

    Guia_Tlf interseccion = g.interseccion(g2); // No sale Simon porque hemos cambiado su numero antes
    for (it = interseccion.begin(); it != interseccion.end(); ++it)
        cout << (*it) << endl;
}
