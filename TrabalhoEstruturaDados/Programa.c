#include "Cliente.h"
#include "Gestor.h"
#include "Meios.h"


void main() 
{
	Meios* b = CriaMeio(bicicleta, 1234, 100, 25, false, "porto");
	//Meios* t = CriaMeio(trotinete, 1235, 150, 25, false, "cascais");
	//Meios* m = CriaMeio(metro, 1123, 20, 25, false, "lisboa");
	//Meios* r = CriaMeio(metro, 0004, 20, 25, false, "lisboa");
	Meios* k = CriaMeio(bicicleta, 9876, 75, 40, false, "ovar");
	Gestor* novog = CriaGestor("Joao", 1256);
	Gestor* novog2 = CriaGestor("Maria", 1456);
	Gestor* hg = NULL;
	Cliente* c = CriaCliente(123456789, "Maria", "Avenida da Régua", 25);
	Cliente* c2 = CriaCliente(987654321, "Jose", "Benfica", 36);
	Cliente* hc = NULL;
	hc = InsereCliente(hc, c2);
	hc = InsereCliente(hc, c);
	GravaClientesTexto(hc, "Clientes.txt");
	LerClientesTexto("Clientes.txt");
	bool y = GravarClienteBinario(hc, "Clientes.bin");
	hc = LerClientesBinario("Clientes.bin");
	hg = InsereGestor(hg, novog2);
	hg = InsereGestor(hg, novog);
	bool x = GravarGestorBinario(hg, "Gestor.bin");
	hg = LerGestorBinario("Gestor.bin");
	Meios* h = NULL;
	h=InsereMeio(h, b);
	h = InsereMeio(h, k);
	//h=InsereMeio(h, m);
	//h=InsereMeio(h, t);
	//h = InsereMeio(h, r);
	//MostraMeios(h);
	//Aluguer(b, 1234);
	bool z = GravarMeioBinario(h, "Meios.bin");
	h = LerMeioBinario("Meios.bin");
	//MostraMeios(h);
	//bool aux = ExisteMeio(h, 1123);
	//h=RemoveMeio(h, 4);
	//AlteraMeio(h, bicicleta, 1235, 30, 40, "lisboa");
    //Meios* laux=MesmoGeo(h,"lisboa");
	//Meios* laux2 = OrdenarPorAutonomia(h);
	//MostraMeios(laux2);*/

}
