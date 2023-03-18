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
 * \brief função para criar um gestor
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
 * \brief função para determinar se um gestor já existe
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
 * \brief Insere um gestor novo, de forma ordenada pelo ID, numa lista verificando também se a o gestor já existe usando a função ExisteGestor()
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
 * \brief Função auxiliar que procura um gestor através do ID do mesmo
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
 * \brief usando a função ProcuraCliente() procura o cliente a remover da lista através do ID do mesmo
 * 
 * \param h
 * \param ID
 * \return 
 */
Gestor* RemoveGestor(Gestor* h, int ID)
{
	Gestor* aux = ProcuraGestor(h, ID);

	if (aux == NULL) {
		// O gestor com o ID especificado não existe na lista
		return h;
	}

	if (h == aux) {
		// O gestor a ser removido é o primeiro da lista
		h = h->next;
		free(aux);
	}
	else {
		// O gestor a ser removido não é o primeiro da lista
		Gestor* ant = h;
		while (ant->next != aux) {
			ant = ant->next;
		}
		ant->next = aux->next;
		free(aux);
	}

	// Retorna um apontador para o início da lista atualizada
	return h;

}
/**
 * \brief usando a função ProcuraGestor() procura o gestor cujos dados são para alterar
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
 * \brief função para mostrar um unico gestor
 * 
 * \param gestor
 */
void MostraGestor(Gestor* gestor) 
{
	printf("Nome: %s", gestor->nome);
	printf("ID: %04d", gestor->ID);

}
/**
 * \brief utilizando a função anterior mostra os gestores todos de uma lista
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
 * \brief Função para armazenar os dados de uma lista em binário
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
 * \brief lê os dados de um ficheiro binário de gestores
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

