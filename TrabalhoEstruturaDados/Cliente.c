/*****************************************************************//**
 * \file   Cliente.c
 * \brief  
 * 
 * \author Ricardo Salema de Almeida_n26344
 * \date   March 2023
 *********************************************************************/
#include "Cliente.h"
#define _CRT_SECURE_NO_WARNINGS
/**
 * \brief cria��o de um cliente
 * 
 * \param nif
 * \param nome
 * \param morada
 * \param saldo
 * \return o cliente criado
 */
Cliente* CriaCliente(int nif, char* nome, char* morada, float saldo)
{
	Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));
	if (novoCliente == NULL) return NULL;
	novoCliente->NIF = nif;
	strcpy(novoCliente->nome, nome);
	strcpy(novoCliente->morada, morada);
	novoCliente->saldo = saldo;
	novoCliente->next = NULL;
	return novoCliente;
}
/**
 * \brief fun��o auxiliar para verificar se um cliente j� existe na lista
 * 
 * \param h
 * \param nif
 * \return true se o cliente j� existir e false se n�o
 */
bool ExisteCliente(Cliente* h, int nif) 
{
	if (h == NULL) return false;
	Cliente* aux = h;
	while (aux != NULL) 
	{
		if (aux->NIF == nif)
			return true;
		aux = aux->next;

	}
	return false;

}
/**
 * \brief Insere um cliente novo, de forma ordenada pelo NIF, numa lista verificando tamb�m se a o cliente j� existe usando a fun��o ExisteCliente()
 * 
 * \param h
 * \param novo
 * \return lista atualizada
 */
Cliente* InsereCliente(Cliente* h, Cliente* novo) 
{
	if (novo == NULL) return h; //se o novo tiver NULL retorna a cabe�a da lista
	if (ExisteCliente(h, novo->NIF)) return h;
	if (h == NULL) 
	{
		h=novo;
	}
	else
	{
		Cliente* aux = h;
		Cliente* ant = NULL;
		while (aux!=NULL && aux->NIF<novo->NIF) 
		{
			ant = aux;
			aux = aux -> next;
		}
		if (ant == NULL)
		{
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
 * \brief usa a fun��o auxiliar procura cliente para encontrar o cliente, usando o NIF, e depois remove o cliente 
 * 
 * \param h
 * \param nif
 * \return a lista atualizada sem o cliente removido
 */
Cliente* RemoveCliente(Cliente* h, int nif)
{
	Cliente* aux = ProcuraCliente(h, nif);

	if (aux == NULL) {
		// O cliente com o NIF especificado n�o existe na lista
		return h;
	}

	if (h == aux) {
		// O cliente a ser removido � o primeiro da lista
		h = h->next;
		free(aux);
	}
	else {
		// O cliente a ser removido n�o � o primeiro da lista
		Cliente* ant = h;
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
 * \brief fun��o auxiliar para procurar cliente usando o NIF
 * 
 * \param h
 * \param nif
 * \return o cliente que procuramos ou NULL se n�o encontrar o nif
 */
Cliente* ProcuraCliente(Cliente* h, int nif) 
{
	if (h == NULL)return NULL;
	else
	{
		Cliente* aux = h;
		while (aux != NULL) 
		{
			if (aux->NIF == nif)
			{
				return(aux);
			}
			aux = aux->next;

		}
		return NULL;
	}

}
/**
 * \brief usa a fun��o auxiliar ProcuraCliente para encontrar o cliente cujos dados se desejam alterar, sendo o NIF inalter�vel
 * 
 * \param h
 * \param nif
 * \param nome
 * \param morada
 * \param saldo
 * \return lista atualizada
 */
Cliente* AlteraCliente(Cliente* h, int nif,  char* nome, char* morada, float saldo)
{
	Cliente* aux = ProcuraCliente(h, nif);
	if(aux!=NULL)
	{
		strcpy(aux->nome,nome);
		strcpy(aux->morada, morada);
		aux->saldo = saldo;
	}

	return h;

}
/**
 * \brief fun��o para mostrar um �nico cliente
 * 
 * \param cliente
 */
void MostraCliente(Cliente* cliente)
{
	printf("NIF: %09d\n", cliente->NIF);
	printf("Nome: %s\n", cliente->nome);
	printf("Morada: %s\n", cliente->morada);
	printf("Saldo: %lf\n", cliente->saldo);

}
/**
 * \brief usando a fun��o MostraCliente, usamos um ciclo para mostrar a lista inteira
 * 
 * \param h
 */
void MostraClientes(Cliente* h)
{
	Cliente* aux = h;
	while(aux!=NULL)
	{
		MostraCliente(aux);
		aux = aux->next;
	
	}

}
/*void GravaClientesTexto(Cliente* h, char* nomef)
{
	FILE* fp;
	Cliente* aux = h;
	ClienteFile auxFile;

	fp = fopen(nomef, "w");

	while (aux!=NULL)
	{
		auxFile.NIF = aux->NIF;
		strcpy(auxFile.nome, aux->nome);
		strcpy(auxFile.morada, aux->morada);
		auxFile.saldo = aux->saldo;
		
		fprintf(fp, "%d;%s;%s;%lf\n", auxFile.NIF, auxFile.nome, auxFile.morada, auxFile.saldo);
		aux = aux->next;
	}

	fclose(fp);
}
Cliente* LerClientesTexto(char* nomeFicheiro)
{
	FILE* fp;
	Cliente* h = NULL;
	Cliente* aux;
	ClienteFile auxFile;

	fp = fopen(nomeFicheiro, "r");

	while (fscanf(fp, "%d;%[^;];%[^;];%lf\n", &auxFile.NIF, auxFile.nome, auxFile.morada, &auxFile.saldo) != EOF) {
		aux = CriaCliente(auxFile.NIF, auxFile.nome, auxFile.morada, auxFile.saldo);
		h = InsereCliente(h, aux);
	}

	fclose(fp);
	return h;
}*/



/**
 * \brief fun��o para guardar a lista de clientes num ficheiro bin�rio
 * 
 * \param h
 *
 */
bool GravarClienteBinario(Cliente* h, char* nomef) 
{
	FILE* fp;
	if (h == NULL)return false;
	if((fp=fopen( nomef, "wb"))==NULL) return false;
	Cliente* aux = h;
	ClienteFile auxFile;
	while (aux) 
	{
		auxFile.NIF = aux->NIF;
		strcpy(auxFile.nome, aux->nome);
		strcpy(auxFile.morada, aux->morada);
		auxFile.saldo = aux->saldo;
		fwrite(&auxFile, sizeof(ClienteFile), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;

}
/**
 * brief fun��o para ler um ficheiro bin�rio com uma lista de clientes
 * 
 * 
 */
Cliente* LerClientesBinario(char* nomef) {
	FILE* fp;
	Cliente* h = NULL;
	Cliente* aux;

	if ((fp = fopen("Clientes.bin", "rb")) == NULL) return NULL;
	ClienteFile auxFile;
	while (fread(&auxFile, sizeof(ClienteFile), 1, fp)) {
		aux = CriaCliente(auxFile.NIF, auxFile.nome, auxFile.morada, auxFile.saldo);
		h = InsereCliente(h, aux);
	}
	fclose(fp);
	return h;
}
