#ifndef _DICCIONARIO_H
#define _DICCIONARIO_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

/*Tipo elemento que define el diccionario. T es el tipo de dato asociado a una clave que
no se repite (DNI p.ej.) y list<U> es una lista de datos (string p.ej) asociados a la clave
de tipo T. El diccionario está ordenado de menor a mayor clave.
*/
template <class T, class U>
struct data
{
	T clave;
	list<U> info_asoci;
};

/*Comparador de datos. Ordena 2 registros de acuerdo a la clave de tipo T. Puede usarse como
 un funtor.
 */
template <class T, class U>
bool operator<(const data<T, U> &d1, const data<T, U> &d2)
{
	if (d1.clave < d2.clave)
		return true;
	return false;
}

/*Un diccionario es una lista de datos de los definidos anteriormente. Cuidado porque se
manejan listas de listas. Se añaden 2 funciones privadas que hacen más facil la implementación
de algunos operadores o funciones de la parte pública. Copiar copia un diccioario en
otro y borrar elimina todos los elementos de un diccionario. La implementación de copiar
puede hacerse usando iteradores o directamente usando la función assign.
*/
template <class T, class U>
class Diccionario
{

private:
	list<data<T, U> > datos;

	void Copiar(const Diccionario<T, U> &D)
	{
		/*typename list<data<T,U> >::const_iterator it_d;
			   typename list<data<T,U> >::iterator it=this->datos.begin();*/

		datos.assign(D.datos.begin(), D.datos.end());
		/*for (it_d=D.datos.begin(); it_d!=D.datos.end();++it_d,++it){
				     this->datos.insert(it,*it_d);

			   }*/
	}

	void Borrar()
	{

		this->datos.erase(datos.begin(), datos.end());
	}

	bool findDefinition(const U &s, const T &key)
	{
		typename list<U>::iterator it;
		list<U> data = getInfo_Asoc(key);
		for (it = data.begin(); it != data.end(); ++it)
		{
			if ((*it) == s)
			{
				return true;
			}
		}
		return false;
	}

public:
	/* Constructor por defecto*/
	Diccionario() : datos(list<data<T, U> >()) {}

	/* Constructor de copias*/
	Diccionario(const Diccionario &D)
	{
		Copiar(D);
	}

	/* Desstructor*/
	~Diccionario() {}

	/* Operador de asignación*/
	Diccionario<T, U> &operator=(const Diccionario<T, U> &D)
	{
		if (this != &D)
		{
			Borrar();
			Copiar(D);
		}
		return *this;
	}

	/* Busca la clave p en el diccionario. Si está devuelve un iterador a
		dónde está clave. Si no está, devuelve end() y deja el iterador de salida
		apuntando al sitio dónde debería estar la clave
		*/
	bool Esta_Clave(const T &p, typename list<data<T, U> >::iterator &it_out)
	{

		if (datos.size() > 0)
		{

			typename list<data<T, U> >::iterator it;

			for (it = datos.begin(); it != datos.end(); ++it)
			{
				if ((*it).clave == p)
				{
					it_out = it;
					return true;
				}
				else if ((*it).clave > p)
				{
					it_out = it;
					return false;
				}
			}

			it_out = it;
			return false;
		}
		else
		{
			it_out = datos.end();
			return false;
		}
	}

	/* Inserta un nuevo registro en el diccionario. Lo hace a través de la clave
		 e inserta la lista con toda la información asociada a esa clave. Si el
		 diccionario no estuviera ordenado habría que usar la función sort()
		 */
	void Insertar(const T &clave, const list<U> &info)
	{

		typename list<data<T, U> >::iterator it;

		if (!Esta_Clave(clave, it))
		{
			data<T, U> p;
			p.clave = clave;
			p.info_asoci = info;

			datos.insert(it, p);
		}
	}

	/*Añade una nueva informacion asocida a una clave que está en el diccionario.
		 la nueva información se inserta al final de la lista de información.
                  Si no esta la clave la inserta y añade la informacion asociada.
		 */
	void AddSignificado_Palabra(const U &s, const T &p)
	{
		typename list<data<T, U> >::iterator it;

		if (!Esta_Clave(p, it))
		{
			Insertar(p, list<U>());
		}

		//Insertamos el siginificado al final
		(*it).info_asoci.insert((*it).info_asoci.end(), s);
	}

	/* Devuelve la información (una lista) asociada a una clave p. Podrían
		 haberse definido operator[] como
		 data<T,U> & operator[](int pos){ return datos.at(pos);}
		 const data<T,U> & operator[](int pos)const { return datos.at(pos);}
		  */
	list<U> getInfo_Asoc(const T &p)
	{
		typename list<data<T, U> >::iterator it;

		if (!Esta_Clave(p, it))
		{
			return list<U>();
		}
		else
		{
			return (*it).info_asoci;
		}
	}

	/*Devuelve el tamaño del diccionario*/
	int size() const
	{
		return datos.size();
	}

	/**
	 * @brief clase para iterar sobre la guia
	 * */

	class iterator
	{
	public:
		typename list<data<T, U> >::iterator it;

		iterator &operator++()
		{
			++it;
			return *this;
		}

		iterator &operator--()
		{
			--it;
			return *this;
		}

		data<T, U> &operator*()
		{
			return *it;
		}
		bool operator==(const iterator &i)
		{
			return i.it == it;
		}

		bool operator!=(const iterator &i)
		{
			return i.it != it;
		}

		friend class Guia_Tlf;
	};

	/**
		     * @brief Inicializa un iterator al comienzo de la guia
		     * */
	iterator begin()
	{
		iterator i;
		i.it = datos.begin();
		return i;
	}

	/**
		     * @brief Inicializa un iterator al final de la guia
		     * */
	iterator end()
	{
		iterator i;
		i.it = datos.end();
		return i;
	}

	typename list<data<T, U> >::const_iterator begin() const
	{
		return datos.begin();
	}
	typename list<data<T, U> >::const_iterator end() const
	{
		return datos.end();
	}

	/**
	 * @brief Element a values by it`s key
	 * 
	 * @param p is the key of the value we want to delete
	 * @post the dictionary will delete the value if exists
	 */
	void deleteElementByKey(const T &p)
	{
		typename list<data<T, U> >::iterator it;

		if (Esta_Clave(p, it))
		{
			datos.erase(it);
		}
	}

	/**
	 * @brief Get the values in a range based on a two keys of the dictionary
	 * 
	 * @param p is the key we will part to find the values (included)
	 * @param t is the key we will finish to find the values (included)
	 * @pre p is ordered before t
	 * @return Diccionario<T, U> the values between p and t
	 */
	Diccionario<T, U> getRangeKeys(const T &p, const T &t)
	{
		typename list<data<T, U> >::iterator it;
		typename list<data<T, U> >::iterator it2;
		if (!Esta_Clave(p, it) || !Esta_Clave(t, it2))
		{
			return Diccionario<T, U>();
		}
		else
		{
			typename list<data<T, U> >::iterator i;
			Diccionario<T, U> aux;
			for (i = it; i != it2; ++i)
			{
				aux.Insertar((*i).clave, (*i).info_asoci);
			}
			aux.Insertar((*it2).clave, (*it2).info_asoci);
			return aux;
		}
	}

	/**
	 * @brief That method does the difference of two dictionaries (quit B values that exist in A)
	 * 
	 * @param g is the other dictionary we want to do the difference
	 * @return Diccionario<T, U> is the result of the difference of this - g (dictionaries)
	 */
	Diccionario<T, U> diferenciaDiccionario(Diccionario &g)
	{
		Diccionario<T, U> aux(*this);
		typename list<data<T, U> >::iterator it;

		typename list<data<T, U> >::iterator dontUse;

		for (it = datos.begin(); it != datos.end(); ++it)
		{
			if ((Esta_Clave((*it).clave, dontUse)) && (g.Esta_Clave((*it).clave, dontUse)))
			{
				aux.deleteElementByKey((*it).clave);
			}
		}
		return aux;
	}

	/**
	 * @brief In this method to do this more efficient first do the difference of the dictionaries and add that values to our return dictionary
	 * and then we do the difference to the other dictionary with the difference first dictionary to get the same values in the other dictionary
	 * and we start to run all the values that are equals comparing all their definitions too to see if they are different or not and if the definition
	 * is different of all the definitions that have the word we add it.
	 * 
	 * @param g is the other dictionary we want to do the union
	 * @return Diccionario<T, U> is the result dictionary of the union of this and the param value
	 */
	Diccionario<T, U> unionDiccionarios(Diccionario &g)
	{
		Diccionario<T, U> aux(*this);
		typename list<data<T, U> >::iterator it;

		Diccionario<T, U> difference = g.diferenciaDiccionario(*this);
		Diccionario<T, U>::iterator iterador;

		for (iterador = difference.begin(); iterador != difference.end(); ++iterador)
		{
			aux.Insertar((*iterador).clave, (*iterador).info_asoci);
		}

		Diccionario<T, U> equals = g.diferenciaDiccionario(difference);
		for (iterador = equals.begin(); iterador != equals.end(); ++iterador)
		{
			if (aux.Esta_Clave((*iterador).clave, it))
			{

				list<U> l2 = equals.getInfo_Asoc((*iterador).clave);
				typename list<U>::iterator it3;

				for (it3 = l2.begin(); it3 != l2.end(); ++it3)
				{
					if (!findDefinition((*it3), (*iterador).clave))
					{
						aux.AddSignificado_Palabra((*it3), (*iterador).clave);
					}
				}
			}
		}

		return aux;
	}
};

#endif
