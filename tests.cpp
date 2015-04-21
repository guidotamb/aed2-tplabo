// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include "mini_test.h"
#include "correpocoyo.h"


template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
 }


/*
 * Crea una carrera de int vacia y no agrega elementos
 */
void check_crear_carrera_vacia() {
    CorrePocoyo<int> carrera;

    ASSERT_EQ(carrera.esVacia(), true);

    ASSERT_EQ(carrera.tamanio(), 0);
}

/*
 * Agrega 3 elementos y verifica que esten agregados segun lo pedido
 */
void check_agregar_corredores() {
    CorrePocoyo<int> carrera;

    carrera.nuevoCorredor(14);
    carrera.nuevoCorredor(3,14);
    carrera.nuevoCorredor(15);

    ASSERT(!carrera.esVacia());

    ASSERT_EQ(to_s(carrera), "[3, 14, 15]");

    ASSERT_EQ(carrera.tamanio(), 3);
}

/*
 * Agrega corredores y verifica que esten agregados donde corresponde
 */
void check_agregar_corredores2() {
    CorrePocoyo<int> carrera;
    carrera.nuevoCorredor(10);
    carrera.nuevoCorredor(22);
    carrera.nuevoCorredor(27);
    carrera.nuevoCorredor(20,22);

    ASSERT_EQ(to_s(carrera), "[10, 20, 22, 27]");
}


/*
 * Se copia una carrera y verifica que sus atributos sean iguales.
 * OJO! Este test puede pasar aun si implementan mal el constructor
 * por copia y tambien implementan mal el operator== y el metodo
 * dameCorredorEnPos, tengan mucho cuidado con esto
 */

void check_copiar_carrera() {
    CorrePocoyo<int> carrera;
    carrera.nuevoCorredor(10);
    carrera.nuevoCorredor(22);
    carrera.nuevoCorredor(27);
    carrera.nuevoCorredor(20,22);

    CorrePocoyo<int> copia(carrera);

    ASSERT_EQ((carrera==copia),true);

    for(int i=1;i<=carrera.tamanio();i++)
        ASSERT_EQ(carrera.dameCorredorEnPos(i),copia.dameCorredorEnPos(i));
    

    ASSERT_EQ(carrera.corredorFilmado(),copia.corredorFilmado());

}

/*
 * Verifica que se canse el corredor correcto.
 */

void check_se_cansa() {
    CorrePocoyo<int> carrera;
    carrera.nuevoCorredor(10);
    carrera.nuevoCorredor(22);
    carrera.nuevoCorredor(27);
    carrera.nuevoCorredor(20,22);

    carrera.seCansa(20);

    ASSERT_EQ(to_s(carrera), "[10, 22, 27]");

    carrera.seCansa(10);

    ASSERT_EQ(to_s(carrera), "[22, 27]");

    carrera.seCansa(27);

    ASSERT_EQ(to_s(carrera), "[22]");

    carrera.seCansa(22);

    ASSERT_EQ(to_s(carrera), "[]");
}

/*
 * Verifica que el sobrepaso sea correcto
 */

void check_sobrepasar() {
    CorrePocoyo<int> carrera;
    carrera.nuevoCorredor(10);
    carrera.nuevoCorredor(22);
    carrera.nuevoCorredor(27);
    carrera.nuevoCorredor(20,22);

    carrera.sobrepasar(22);

    ASSERT_EQ(to_s(carrera), "[10, 22, 20, 27]");

    carrera.sobrepasar(22);

    ASSERT_EQ(to_s(carrera), "[22, 10, 20, 27]");

    carrera.sobrepasar(27);

    ASSERT_EQ(to_s(carrera), "[22, 10, 27, 20]");
}

/*
 * Verifica que se filme al corredor correcto
 */

void check_corredor_filmado() {
    CorrePocoyo<int> carrera;
    carrera.nuevoCorredor(10);

    ASSERT_EQ(carrera.corredorFilmado(), 10);

    carrera.nuevoCorredor(22);
    carrera.nuevoCorredor(27);
    carrera.nuevoCorredor(20,22);

    carrera.filmarProxPerdedor();

    ASSERT_EQ(carrera.corredorFilmado(),20);

    carrera.sobrepasar(22);

    ASSERT_EQ(carrera.corredorFilmado(),20);

    carrera.filmarProxExitoso();

    ASSERT_EQ(carrera.corredorFilmado(),22);
}

/*
 * Verifica que el primero sea el que tiene que ser el primero
 */

void check_primero() {
    CorrePocoyo<int> carrera;
    carrera.nuevoCorredor(1);

    ASSERT_EQ(carrera.damePrimero(),1);

    carrera.nuevoCorredor(2,1);

    ASSERT_EQ(carrera.damePrimero(),2);

    carrera.nuevoCorredor(3,1);

    ASSERT_EQ(carrera.damePrimero(),2);

    carrera.seCansa(2);

    ASSERT_EQ(carrera.damePrimero(),3);
}

/*
 * Verifica que los corredores esten en la posicion correcta
 */

void check_posicion() {
    CorrePocoyo<int> carrera;
    carrera.nuevoCorredor(1);
    carrera.nuevoCorredor(2);
    carrera.nuevoCorredor(3);
    carrera.nuevoCorredor(5);
    carrera.nuevoCorredor(8);
   
    ASSERT_EQ(carrera.damePosicion(1),1);
    ASSERT_EQ(carrera.damePosicion(3),3);
    ASSERT_EQ(carrera.damePosicion(8),5);
    ASSERT_EQ(carrera.dameCorredorEnPos(1),1);
    ASSERT_EQ(carrera.dameCorredorEnPos(3),3);
    ASSERT_EQ(carrera.dameCorredorEnPos(5),8);

    carrera.seCansa(8);
    ASSERT_EQ(carrera.damePosicion(5),4);
    ASSERT_EQ(carrera.dameCorredorEnPos(4),5);
}

int main() {
    RUN_TEST(check_crear_carrera_vacia);
    RUN_TEST(check_agregar_corredores);
    RUN_TEST(check_agregar_corredores2);
    RUN_TEST(check_copiar_carrera);
    RUN_TEST(check_se_cansa);
    RUN_TEST(check_sobrepasar);
    RUN_TEST(check_corredor_filmado);
    RUN_TEST(check_primero);
    RUN_TEST(check_posicion);
    return 0;
}

