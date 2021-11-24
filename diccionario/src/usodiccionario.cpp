#include <iostream>
#include "../include/diccionario.h"

/*Operator<<. Obsérvese el uso de 2 tipos diferentes de iteradores. Uno sobre
listas de listas y otro sobre listas
*/
ostream &operator<<(ostream &os, const Diccionario<string, string> &D)
{

	list<data<string, string> >::const_iterator it;

	for (it = D.begin(); it != D.end(); ++it)
	{

		list<string>::const_iterator it_s;

		os << endl
		   << (*it).clave << endl
		   << " informacion asociada:" << endl;
		for (it_s = (*it).info_asoci.begin(); it_s != (*it).info_asoci.end(); ++it_s)
		{
			os << (*it_s) << endl;
		}
		os << "**************************************" << endl;
	}

	return os;
}

/*Operator >>. El formato de la entrada es:
     numero de claves en la primera linea
     clave-iésima retorno de carro
     numero de informaciones asociadas en la siguiente linea
     y en cada linea obviamente la informacion asociada
*/

istream &operator>>(istream &is, Diccionario<string, string> &D)
{
	int np;
	is >> np;
	is.ignore(); //quitamos \n
	Diccionario<string, string> Daux;
	for (int i = 0; i < np; i++)
	{
		string clave;

		getline(is, clave);

		int ns;
		is >> ns;
		is.ignore(); //quitamos \n
		list<string> laux;
		for (int j = 0; j < ns; j++)
		{
			string s;
			getline(is, s);

			// cout<<"Significado leido "<<s<<endl;
			laux.insert(laux.end(), s);
		}
		Daux.Insertar(clave, laux);
	}
	D = Daux;
	return is;
}

/*Recorre la lista de información asociada a una clave y la imprime*/
void EscribeSigni(const list<string> &l)
{
	list<string>::const_iterator it_s;

	for (it_s = l.begin(); it_s != l.end(); ++it_s)
	{
		cout << *it_s << endl;
	}
}

/*Lee un diccioario e imprime datos asociados a una clave.
Hay un fichero ejemplo de prueba: data.txt.Para lanzar el programa con ese fichero se escribe:
                  ./usodiccionario < data.txt
*/
int main()
{
	
	Diccionario<string, string> D3;

	cin>>D3;

	cout << " Pasamos al cout " << endl;
	cout<<D3;

	string a;
    cout<<"Introduce una palabra: "<<endl;
    cin>>a;

    list<string>l=D3.getInfo_Asoc(a);

    if (l.size()>0)
          EscribeSigni(l);


	Diccionario<string, string> D;
	Diccionario<string, string> D2;

	string definiciones[5] = {"Def 1", "Def 2", "Def 3", "Def 4", "Def 5"};
	list<string> defList(definiciones, definiciones + sizeof(definiciones) / sizeof(string));
	D.Insertar("A", defList);
	D.Insertar("B", defList);
	D.Insertar("C", defList);
	D.Insertar("D", defList);
	D.Insertar("E", defList);
	D.Insertar("F", defList);

	D2.Insertar("G", defList);
	D2.Insertar("H", defList);
	D2.Insertar("I", defList);
	D2.Insertar("J", defList);
	D2.Insertar("K", defList);
	string definiciones2[5] = {"Def 1", "Def 2", "Def 8", "Def 9", "Def 10"};
	list<string> defList2(definiciones2, definiciones2 + sizeof(definiciones2) / sizeof(string));
	D2.Insertar("F", defList2);

	Diccionario<string, string>::iterator iterador;

	for (iterador = D.begin(); iterador != D.end(); ++iterador)
	{
		cout << (*iterador).clave << endl;
		list<string> l = D.getInfo_Asoc((*iterador).clave);

		if (l.size() > 0)
			EscribeSigni(l);
	}

	cout << "***************** DELETE ELEMENT BY KEY ************" << endl;

	D.deleteElementByKey("A");

	for(iterador = D.begin(); iterador != D.end(); ++iterador){
		cout << (*iterador).clave << endl;
		list<string>l=D.getInfo_Asoc((*iterador).clave);

		if (l.size()>0)
			EscribeSigni(l);
	}


	cout << "***************** GET RANGE KETS ************" << endl;

	Diccionario<string, string> aux = D.getRangeKeys("B", "E");

	for (iterador = aux.begin(); iterador != aux.end(); ++iterador)
	{
		cout << (*iterador).clave << endl;
		list<string> l = aux.getInfo_Asoc((*iterador).clave);

		if (l.size() > 0)
			EscribeSigni(l);
	}

	cout << "**************** DIFERENCIA DICCIONARIOS ************" << endl;

	Diccionario<string, string> difference = D.diferenciaDiccionario(aux);

	for (iterador = difference.begin(); iterador != difference.end(); ++iterador)
	{
		cout << (*iterador).clave << endl;
		list<string> l = difference.getInfo_Asoc((*iterador).clave);

		if (l.size() > 0)
			EscribeSigni(l);
	}

	cout << "**************** UNION DICCIONARIOS ************" << endl;

	Diccionario<string, string> unionDeDiccionarios = D.unionDiccionarios(D2);

	for (iterador = unionDeDiccionarios.begin(); iterador != unionDeDiccionarios.end(); ++iterador)
	{
		cout << (*iterador).clave << endl;
		list<string> l = unionDeDiccionarios.getInfo_Asoc((*iterador).clave);

		if (l.size() > 0)
			EscribeSigni(l);
	}
}
