/*****************************************************************//**
 * \file   Meios.c
 * \brief  
 * 
 * \author Ricardo Salema de Almeida_n26344
 * \date   March 2023
 *********************************************************************/


#include "Meios.h"
#define _CRT_SECURE_NO_WARNINGS

/**
 * \brief cria��o de um Meio
 * 
 * \param tipo
 * \param cod
 * \param carga
 * \param custo
 * \param pos
 * \return 
 */
Meios* CriaMeio(tipo tipo, int cod, int carga, float custo, bool alugado, char* pos) 
{
	Meios* novoMeio = (Meios*)malloc(sizeof(Meios));
	if (novoMeio == NULL) return NULL;
	novoMeio->tipo = tipo;
	novoMeio->codigo = cod;
	novoMeio->carga = carga;
	novoMeio->custo = custo;
	novoMeio->alugado = alugado;
	strcpy(novoMeio->posGeo, pos);
	novoMeio->next = NULL;

	return novoMeio;

}
/**
 * \brief Fun��o auxiliar que serve para ver se um meio j� existe numa lista
 * 
 * \param h
 * \param cod
 * \return 
 */
bool ExisteMeio(Meios* h, int cod) {
	if (h == NULL)return false;
	Meios* aux = h;
	while (aux != NULL) 
	{
		if (aux->codigo == cod)
			return true;
		aux = aux -> next;
	}
	return false;
}

/**
 * \brief fun��o que serve para inserir ordenadamente pelo c�digo um meio novo a uma lista e que usa o ExisteMeio() para verificar se o Meio j� est� na lista
 * 
 * \param h
 * \param novo
 * \return 
 */
Meios* InsereMeio(Meios* h, Meios* novo)
{
	if (novo == NULL) return h;
	if (ExisteMeio(h, novo->codigo)) return h;
	if (h == NULL)
		h = novo;
	else
	{
		Meios* aux = h;
		Meios* ant = NULL;

		while (aux != NULL && aux->codigo < novo->codigo)
		{
			ant = aux;
			aux = aux->next;

		}
		if (ant == NULL) {
			novo->next = h;
			h = novo;
		}
		else
		{
			ant->next = novo;
			novo->next = aux;

		}


	}
	return h;
 
}
/**
 * \brief fun��o auxiliar que serve para procurar um meio, pelo seu c�digo, numa lista
 * 
 * \param h
 * \param cod
 * \return 
 */
Meios* ProcuraMeio(Meios* h, int cod)
{
	if (h == NULL) return NULL;
	else
	{
		Meios* aux = h;
		while (aux != NULL)
		{
			if (aux->codigo == cod)
			{
				return(aux);
			}
			aux = aux->next;

		}
		return NULL;
	}
}
/**
 * \brief fun��o que remove um meio de uma lista atrav�s da fun��o ProcuraMeio() que usa o seu c�digo
 * 
 * \param h
 * \param cod
 * \return 
 */
Meios* RemoveMeio(Meios* h, int cod)
{
	Meios* aux = ProcuraMeio(h, cod);

	if (aux == NULL) {
		// O gestor com o ID especificado n�o existe na lista
		return h;
	}

	if (aux == h) {
		// O gestor a ser removido � o primeiro da lista
		h = h->next;
		free(aux);
		return h;
		
	}
	else {
		// O gestor a ser removido n�o � o primeiro da lista
		Meios* ant = h;
		while (ant->next != aux) {
			ant = ant->next;
		}
		ant->next = aux->next;
		free(aux);
	}

	

	// Retorna um apontador para o in�cio da lista atualizada
	return h;

}
/**
 * \brief fun��o que serve para alterar dados de um meio usando a fun��o ProcuraMeio()
 * 
 * \param h
 * \param tipo
 * \param cod
 * \param carga
 * \param custo
 * \param posGeo
 * \return 
 */
Meios* AlteraMeio(Meios* h, tipo tipo, int cod, int carga, float custo, char* posGeo)
{
	Meios* aux = ProcuraMeio(h, cod);
	if (aux != NULL)
	{
		aux->tipo = tipo;
		aux->carga = carga;
		aux->custo = custo;
		strcpy(aux->posGeo, posGeo);
	}
	return h;
}
/**
 * \brief fun��o que regista o aluguer de um meio
 * 
 * \param h
 * \param cod
 * \return 
 */
Meios* Aluguer(Meios* h, int cod) 
{
	Meios* aux = ProcuraMeio(h, cod);
	if (aux == NULL)return h;
	else 
	{
		if (aux->alugado == true)
			return h;
		else
		{
			aux->alugado = true;
			return h;
		}

	}
}
/**
 * \brief fun��o que serve para mostrar um meio
 * 
 * \param meio
 */
void MostraMeio(Meios* meio)
{
	switch (meio->tipo) {
	case 0:
		printf("Tipo:Bicicleta\n");
		break;
	case 1:
		printf("Tipo:Trotinete\n");
		break;
	case 2:
		printf("Tipo:Metro\n");
	}
	printf("Codigo: %04d\n", meio->codigo);
	printf("Carga Atual: %d\n", meio->carga);
	printf("Custo: %lf\n", meio->custo);
	if (meio->alugado == true)
		printf("Meio: Alugado\n");
	else printf("Meio: Por Alugar\n");
	printf("Posicao: %s\n", meio->posGeo);

}
/**
 * fun��o que usa a fun��o MostraMeio() para listar os meios de uma lista
 * 
 * \param h
 */
void MostraMeios(Meios* h) {
	Meios* aux = h;
	while (aux != NULL) 
	{
		MostraMeio(aux);
		aux = aux->next;
	}
}
/**
 * \brief fun��o auxiliar para inserir por ordem da carga da bateria numa lista
 * 
 * \param h
 * \param carga
 * \return 
 */
Meios* AuxiliarCarga(Meios* h, Meios* novo)
{
	if (novo == NULL) return h;
	if (ExisteMeio(h, novo->codigo)) return h;
	if (h == NULL)
		h = novo;
	else
	{
		Meios* aux = h;
		Meios* ant = NULL;

		while (aux != NULL && aux->carga > novo->carga)
		{
			ant = aux;
			aux = aux->next;

		}
		if (ant == NULL) {
			novo->next = h;
			h = novo;
		}
		else
		{
			ant->next = novo;
			novo->next = aux;

		}


	}
	return h;

}
/**
 * \brief fun��o que usa a CriaMeio e AuxiliarCarga para criar uma lista nova com os membros ordenados por carga
 * 
 * \param h
 * \return 
 */
Meios* OrdenarPorAutonomia(Meios*h)
{
	if (h == NULL)return NULL;
	Meios* aux = h;
	Meios* listaordenada = NULL;
	while (aux != NULL)
	{
		Meios* n = CriaMeio(aux->tipo,aux->codigo,aux->carga,aux->custo,aux->alugado,aux->posGeo);
		listaordenada=AuxiliarCarga(listaordenada, n);

		aux = aux->next;
	}

	return listaordenada;


}

/**
 * \brief fun��o que compara as posi��es para ver se s�o iguais e se forem cria uma lista nova filtrada s� com os meios com a mesma posi��o
 * 
 * \param h
 * \param posgeo
 * \return 
 */
Meios* MesmoGeo(Meios* h, char* posgeo) 
{
	if (h == NULL)return NULL;
	Meios* aux = h;
	Meios* listafiltrada=NULL;
	while (aux != NULL)
	{
		if (!strcmp(aux->posGeo, posgeo))
		{
			Meios* n = CriaMeio(aux->tipo, aux->codigo, aux->carga, aux->custo,aux->alugado, aux->posGeo);
			listafiltrada = InsereMeio(listafiltrada, n);

		}
		aux = aux->next;
	}
	return listafiltrada;
}
/**
 * \brief fun��o para gravar uma lista de meios num ficheiro bin�rio
 * 
 * \param h
 * \return 
 */
bool GravarMeioBinario(Meios* h, char* nomef)
{
	FILE* fp;
	if (h == NULL)return false;
	if ((fp = fopen(nomef, "wb")) == NULL) return false;
	Meios* aux = h;
	MeiosFile auxFile;
	while (aux)
	{
		auxFile.tipo = aux->tipo;
		auxFile.codigo = aux->codigo;
		auxFile.carga = aux->carga;
		auxFile.custo = aux->custo;
		auxFile.alugado = aux->alugado;
		strcpy(auxFile.posGeo, aux->posGeo);
		fwrite(&auxFile, sizeof(MeiosFile), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;

}
/**
 * \brief fun��o para ler um ficheiro bin�rio com os meios
 * 
 * \return 
 */
Meios* LerMeioBinario(char* nomef) {
	FILE* fp;
	Meios* h = NULL;
	Meios* aux;

	if ((fp = fopen(nomef, "rb")) == NULL) return NULL;
	MeiosFile auxFile;
	while (fread(&auxFile, sizeof(MeiosFile), 1, fp)) {
		aux = CriaMeio(auxFile.tipo, auxFile.codigo, auxFile.carga, auxFile.custo, auxFile.alugado, auxFile.posGeo);
		h = InsereMeio(h, aux);
	}
	fclose(fp);
	return h;
}

