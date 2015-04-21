#ifndef CORREPOCOYO_H_
#define CORREPOCOYO_H_

#include <iostream>
#include <cassert>
using namespace std;

/* 
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class CorrePocoyo{

  public:

	/*
	 * Crea una nueva carrera
	 */	
	CorrePocoyo();

	/*
	 * Una vez copiada, ambas CorrePocoyos deben ser independientes, 
	 * es decir, cuando se borre una no debe borrar la otra.
	 */	
	CorrePocoyo(const CorrePocoyo<T>&);
	
	/*
	 * Acordarse de liberar toda la memoria!
	 */	 
	~CorrePocoyo();

	/*
	 * Agrega un nuevo corredor al CorrePocoyo. Lo agregarÃ¡ al final 
	 */
	void nuevoCorredor(const T&);
	
	/*
	 * Agrega un nuevo corredor al CorrePocoyo. El primer T es el corredor a agregar y lo hace delante del segundo
	 *
	 * PRE: Existe el segundo corredor 
	 */
	void nuevoCorredor(const T&, const T&);
	
	/*
	 * Elimina del pocoyo al que se envÃ­a
	 *
	 * PRE: Existe el corredor
	 */
	void seCansa(const T&);
	/*
	 * El corredor pasa al que estÃ¡ adelante 
	 *
	 * PRE: Existe un corredor delante de Ã©l y T es un corredor 
	 */
	void sobrepasar(const T&);
	
	/*
	 * Devuelve el corredor que estÃ¡ siendo filmado.
	 *
	 * PRE: Hay adeptos en la CorrePocoyo.
	 */
	const T& corredorFilmado() const;
	
    /*
	 * Devuelve el prÃ³ximo elemento segÃºn el orden dado.
	 * Pasa a filmar al corredor de atÃ¡s 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxPerdedor();
	    /*
	 * Devuelve el prÃ³ximo elemento segÃºn el orden dado.
	 * Pasa a filmar al corredor de adelante 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxExitoso();
	
	/*
	 * Devuelve al Primero. 
	 *
	 * PRE: Hay elementos 
	 */
	const T& damePrimero() const;	

	/*
	 * Devuelve la posiciÃ³n del elemento pasado por parÃ¡metro. 
	 *
	 * PRE: Existe ese corredor 
	 */
	int damePosicion(const T& ) const;	

	/*
	 * Devuelve el corredor de la posiciÃ³n. 
	 *
	 * PRE: Existe al menos esa cantidad de corredores en la carrera
	 */
	const T& dameCorredorEnPos(int) const;	




	/*
	 * Dice si la CorrePocoyo tiene o no corredores.
	 */
	bool esVacia() const;

	
	/*
	 * Devuelve la cantidad de corredores de la CorrePocoyo.
	 */
	int tamanio() const;	

	/*
	 * Devuelve true si las CorrePocoyos son iguales.
	 */
	bool operator==(const CorrePocoyo<T>&) const;	
	
	/*
	 * Debe mostrar la carrera por el ostream (y retornar el mismo).
	 * CorrePocoyo vacio: []
	 */
	ostream& mostrarCorrePocoyo(ostream&) const;
	
	
  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	CorrePocoyo<T>& operator=(const CorrePocoyo<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementaciÃ³n del nodo.
	 */
	struct Nodo {
		T corredor;
		int posicion;
		Nodo* siguiente;
		Nodo* anterior;

		Nodo (const T& corr): corredor(corr), siguiente(NULL), anterior(NULL){}
	};

	Nodo* primero;
	Nodo* filmado;
	int nCompetidores;


};

template<class T>
ostream& operator<<(ostream& out, const CorrePocoyo<T>& a) {
	return a.mostrarCorrePocoyo(out);
}


	
	template<class T>
	CorrePocoyo<T>::CorrePocoyo(){
		this->nCompetidores = 0;
		this->primero = NULL;
		this->filmado = NULL;
	}

	/*
	 * Una vez copiada, ambas CorrePocoyos deben ser independientes, 
	 * es decir, cuando se borre una no debe borrar la otra.
	 */	
	template<class T>
	CorrePocoyo<T>::CorrePocoyo(const CorrePocoyo<T>& cp){
		if (cp.tamanio () == 0){
			this->primero = NULL;
			this->filmado = NULL;
			nCompetidores = 0;
		}else{
			this->nCompetidores = cp.tamanio();
			this->primero = new Nodo(cp.damePrimero());
			Nodo* p = this->primero;
			int i;
			if (cp.damePosicion(cp.corredorFilmado()) == 1){
					this->filmado = this->primero;
				}
			for (i=2; i <= nCompetidores; i++){

				p->anterior = new Nodo(cp.dameCorredorEnPos(i));
				p->anterior->siguiente = p;

				//me fijo si es el filmado.
				if (i==cp.damePosicion(cp.corredorFilmado()) ){
					this->filmado = p->anterior;
				}

				p = p->anterior;
			}
			p->anterior = this->primero;
			this->primero->siguiente = p;
		}
	}
	
	/*
	 * Acordarse de liberar toda la memoria!
	 */	 
	template<class T>
	CorrePocoyo<T>::~CorrePocoyo(){
		int i;
		Nodo* p = this->primero;
		for (i=1; i<nCompetidores; i++)
		{
			p = p->siguiente;
			delete p->anterior;
		}
		delete p;
	}

	// Tomamos como siguiente del primero, al ultimo.
	template<class T>
	void CorrePocoyo<T>::nuevoCorredor(const T& t){

		if (nCompetidores == 0)
		{
			this->primero = new Nodo(t);
			this->primero->siguiente = this->primero;
			this->primero->anterior = this->primero;
			this->primero->posicion = 1;
			this->filmado = this->primero;
			
		}
		else
		{
			Nodo* nuevoC = new Nodo(t);
			nuevoC->posicion = nCompetidores + 1;
			primero->siguiente->anterior = nuevoC;
			nuevoC->siguiente = primero->siguiente;
			primero->siguiente = nuevoC;
			nuevoC->anterior = primero;
						
			nuevoC = NULL;
		}
		nCompetidores ++;
	}
	
	template<class T>
	void CorrePocoyo<T>::nuevoCorredor(const T& nuevo, const T& corredor){
		nCompetidores++;

		//Creo punteros a nodos necesarios.
		Nodo* corr = this->primero;
		//EncontrarNodo
		bool encuentroNodo = (corr->corredor == corredor);
		while (!encuentroNodo)
		{
				corr = corr->anterior;
				if (corr->corredor == corredor)
				{
					encuentroNodo = true;
				}
				
		}
		Nodo* nue = new Nodo(nuevo);
		
		//Relaciones de corredores: corr <-> nue <-> corr->sig.
		nue->siguiente = corr->siguiente;
		corr->siguiente->anterior = nue;
		corr->siguiente = nue;
		nue->anterior = corr;

		//Posicion del nuevo corredor.
		nue->posicion = corr->posicion;

		//Corrijo posiciones.
		Nodo* n = corr;
		int i;
		for (i = corr->posicion+1; i <= nCompetidores; i++)
		{
			n->posicion = n->posicion +1;
			n = n->anterior;	
		}

		//Si estaba primero, lo cambio.
		if (corr->corredor == this->primero->corredor)
		{
			this->primero = nue;
		}
	}


/*DAME NODO NO SIRVE
	template<class T>
	CorrePocoyo::Nodo CorrePocoyo<T>::dameNodo(const T& t){
		for (i=0, i<this->nCompetidores, i++)
		{
			Nodo* n = this->primero;
				if (n->corredor = t)
				{
					return n;
				}
				n = n->siguiente;
		}
	}
	*/
	/*
	 * Elimina del pocoyo al que se envÃ­a
	 *
	 * PRE: Existe el corredor
	 */
	template<class T>
	void CorrePocoyo<T>::seCansa(const T& t){

		Nodo* corredor = this->primero;
		//EncontrarNodo
		bool encuentroNodo = (corredor->corredor == t);
		while (!encuentroNodo)
		{
			corredor = corredor->anterior;
			if (corredor->corredor == t)
			{
				encuentroNodo = true;
			}
		}
		//Si el corredor era el primero, le asigno primero al segundo.
		if (corredor->corredor == this->primero->corredor)
		{
			this->primero = this->primero->anterior;
		}

		if (nCompetidores > 0)
		{
			corredor->anterior->siguiente = corredor->siguiente;
			corredor->siguiente->anterior = corredor->anterior;

			//Corrijo posiciones.
			Nodo* n = corredor->anterior;
			nCompetidores--;
			//Si no es el ultimo
			if (n->corredor != this->primero->corredor)
			{
				n->posicion = n->posicion -1;
				int i;
				for (i = n->posicion; i <= nCompetidores; i++)
				{
					n->posicion = n->posicion -1;
					n = n->anterior;
				}
			}
			delete corredor;
		}else{
			delete corredor;
		}
	}
	
	template<class T>
	void CorrePocoyo<T>::sobrepasar(const T& t){
		// n- <-> sig <-> n -> sig+
		Nodo* n = this->primero;
		//EncontrarNodo
		bool encuentroNodo = (n->corredor == t);
		while (!encuentroNodo)
		{
			n = n->anterior;
			if (n->corredor == t)
			{
				encuentroNodo = true;
			}
				
		}
		Nodo* sig = n->siguiente;

		//Si era el primero, lo cambio.

		if (sig->corredor == this->primero->corredor)
		{
			this->primero = this->primero->anterior;
		}
		//Ya tengo el que avanza (n) y el que retrocede (sig) en la carrera.
		

		//Cambio relaciones.
		sig->siguiente->anterior = n;
		n->siguiente = sig->siguiente;
		n->anterior->siguiente = sig;
		sig->anterior = n->anterior;
		n->anterior = sig;
		sig->siguiente = n;

		//Cambio posiciones.
		n->posicion = n->posicion -1;
		sig->posicion = sig->posicion +1;
	
		
		//Si el corredor era el primero, le asigno primero al segundo.
		
		// Más facil cambiar solo el corredor?
	}
	
	template<class T>
	const T& CorrePocoyo<T>::corredorFilmado() const{
		return this->filmado->corredor;
	}
	
    /*
	 * Devuelve el prÃ³ximo elemento segÃºn el orden dado.
	 * Pasa a filmar al corredor de atÃ¡s 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	template<class T>
	void CorrePocoyo<T>::filmarProxPerdedor(){
		this->filmado = this->filmado->anterior;
	}
	 
	template<class T>
	void CorrePocoyo<T>::filmarProxExitoso(){
		this->filmado = this->filmado->siguiente;
	}
	
	/*
	 * Devuelve al Primero. 
	 *
	 * PRE: Hay elementos 
	 */
	template<class T>
	const T& CorrePocoyo<T>::damePrimero() const{
		return this->primero->corredor;
	}	

	/*
	 * Devuelve la posiciÃ³n del elemento pasado por parÃ¡metro. 
	 *
	 * PRE: Existe ese corredor 
	 */
	template<class T>
	int CorrePocoyo<T>::damePosicion(const T& t) const{
		Nodo* n = this->primero;
		bool encuentroNodo = (n->corredor == t);
		while (!encuentroNodo)
		{
			n = n->anterior;
			if (n->corredor == t)
			{
				encuentroNodo = true;
				
			}
		}
		return n->posicion;
	}	

	/*
	 * Devuelve el corredor de la posiciÃ³n. 
	 *
	 * PRE: Existe al menos esa cantidad de corredores en la carrera
	 */
	template<class T>
	const T& CorrePocoyo<T>::dameCorredorEnPos(int pos) const{
		Nodo* p = this->primero;
		int i;
		for (i = 2; i <= pos; i++)
		{
			p = p->anterior;
		}
		return p->corredor;
	}	

	/*
	 * Dice si la CorrePocoyo tiene o no corredores.
	 */
	template<class T>
	bool CorrePocoyo<T>::esVacia() const{
		return (this->nCompetidores == 0);
	}

	
	/*
	 * Devuelve la cantidad de corredores de la CorrePocoyo.
	 */
	template<class T>
	int CorrePocoyo<T>::tamanio() const{
		return this->nCompetidores;

	}	

	/*
	 * Devuelve true si las CorrePocoyos son iguales.
	 */
	template<class T>
	bool CorrePocoyo<T>::operator==(const CorrePocoyo<T>& cp) const{

		if (this->nCompetidores != cp.tamanio() && this->primero->corredor != cp.damePrimero() && this->filmado->corredor != cp.corredorFilmado())
		{
			return false;
		}else{
			int i;
			Nodo* n = this->primero;
			bool iguales = (n->corredor == cp.damePrimero());
			for (i=2; i<=this->nCompetidores; i++)
			{
				n = n->anterior;
				//mismo corredor y posicion?
				iguales = iguales && n->corredor == cp.dameCorredorEnPos(i);

				//Avanzo ambos.
				//cp.filmarProxExitoso();
				
			}
			return iguales;
		}
	}	
	
	/*
	 * Debe mostrar la carrera por el ostream (y retornar el mismo).
	 * CorrePocoyo vacio: []
	 */
	template<class T>
	ostream& CorrePocoyo<T>::mostrarCorrePocoyo(ostream& cout) const{
		int i;
		Nodo* n = this->primero;
		if(this->nCompetidores == 0){cout << "[]";}
		for(i=1; i<=nCompetidores; i++)
		{	
			bool esPrimero = (n->corredor == this->primero->corredor);
			bool esUltimo = (n->anterior->corredor == this->primero->corredor);

			if (esPrimero)
			{
				cout << "[" << n->corredor;
			}else {
				cout << ", " << n->corredor ;
			}
			if(esUltimo){
				cout << "]";
			}
			n = n->anterior;
		}
	}


#endif //CORREPOCOYO_H_

