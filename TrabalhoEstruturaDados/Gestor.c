/*****************************************************************//**
 * \file   Gestor.c
 * \brief  
 * 
 * \author Ricardo Salema de Almeida_n26344
 * \date   March 2023
 *********************************************************************/

#include "Gestor.h"
#define _CRT_SECURE_NO_WARNINGS

/**
 * \brief fun��o para criar um gestor
 * 
 * \param nome
 * \param ID
 * \return 
 */
Gestor* CriaGestor(char* nome, int ID) 
{
	Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));
	if (novoGestor == NULL)return NULL;
	strcpy(novoGestor->nome, nome);
	novoGestor->ID = ID;
	novoGestor->next = NULL;
	return novoGestor;
}
/**
 * \brief fun��o para determinar se um gestor j� existe
 * 
 * \param h
 * \param ID
 * \return 
 */

bool ExisteGestor(Gestor* h, int ID) 
{
	if (h == NULL)return false;
	Gestor* aux = h;
	while (aux != NULL) 
	{
		if (aux->ID == ID) 
			return true;
		aux = aux->next;
    }
	return false;
}
/**
 * \brief Insere um gestor novo, de forma ordenada pelo ID, numa lista verificando tamb�m se a o gestor j� existe usando a fun��o ExisteGestor()
 * 
 * \param h
 * \param novo
 * \return 
 */

Gestor* InsereGestor(Gestor* h, Gestor* novo) 
{
	if (novo == NULL) return h;
	if (ExisteGestor(h, novo->ID)) return h;
	if (h == NULL)
		h = novo;
	else 
	{
		Gestor* aux = h;
		Gestor* ant = NULL;

		while (aux != NULL && aux->ID < novo->ID) 
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
 * \brief Fun��o auxiliar que procura um gestor atrav�s do ID do mesmo
 * 
 * \param h
 * \param ID
 * \return 
 */

Gestor* ProcuraGestor(Gestor* h, int ID) 
{
	if (h == NULL) return NULL;
	else
	{
		Gestor* aux = h;
		while (aux != NULL)
		{
			if (aux->ID == ID)
			{
				return(aux);
			}
			aux = aux->next;

		}
		return NULL;
	}
}
/**
 * \brief usando a fun��o ProcuraCliente() procura o cliente a remover da lista atrav�s do ID do mesmo
 * 
 * \param h
 * \param ID
 * \return 
 */
Gestor* RemoveGestor(Gestor* h, int ID)
{
	Gestor* aux = ProcuraGestor(h, ID);

	if (aux == NULL) {
		// O gestor com o ID especificado n�o existe na lista
		return h;
	}

	if (h == aux) {
		// O gestor a ser removido � o primeiro da lista
		h = h->next;
		free(aux);
	}
	else {
		// O gestor a ser removido n�o � o primeiro da lista
		Gestor* ant = h;
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
 * \brief usando a fun��o ProcuraGestor() procura o gestor cujos dados s�o para alterar
 * 
 * \param h
 * \param nome
 * \param ID
 * \return 
 */
Gestor* AlteraGestor(Gestor* h, char* nome, int ID)
{
	Gestor* aux = ProcuraGestor(h, ID);
	if (aux != NULL)
	{
		strcpy(aux->nome, nome);
	}
	return h;

}
/**
 * \brief fun��o para mostrar um unico gestor
 * 
 * \param gestor
 */
void MostraGestor(Gestor* gestor) 
{
	printf("Nome: %s", gestor->nome);
	printf("ID: %04d", gestor->ID);

}
/**
 * \brief utilizando a fun��o anterior mostra os gestores todos de uma lista
 * 
 * \param h
 */
void MostraGestores(Gestor* h) 
{
	Gestor* aux = h;
	while (aux != NULL) 
	{
		MostraGestor(aux);
		aux = aux->next;

	}

}
/**
 * \brief Fun��o para armazenar os dados de uma lista em bin�rio
 * 
 * \param h
 * 
 */
bool GravarGestorBinario(Gestor* h, char* nomef)
{
	FILE* fp;
	if (h == NULL)return false;
	if ((fp = fopen(nomef, "wb")) == NULL) return false;
	Gestor* aux = h;
	GestorFile auxFile;
	while (aux)
	{
		auxFile.ID = aux->ID;
		strcpy(auxFile.nome, aux->nome);
		fwrite(&auxFile, sizeof(GestorFile), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;

}
/**
 * \brief l� os dados de um ficheiro bin�rio de gestores
 * 
 * 
 */
Gestor* LerGestorBinario(char* nomef) {
	FILE* fp;
	Gestor* h = NULL;
	Gestor* aux;

	if ((fp = fopen(nomef, "rb")) == NULL) return NULL;
	GestorFile auxFile;
	while (fread(&auxFile, sizeof(GestorFile), 1, fp)) {
		aux = CriaGestor(auxFile.nome,auxFile.ID);
		h = InsereGestor(h, aux);
	}
	fclose(fp);
	return h;
}

