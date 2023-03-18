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
 * \brief criação de um Meio
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
 * \brief Função auxiliar que serve para ver se um meio já existe numa lista
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
 * \brief função que serve para inserir ordenadamente pelo código um meio novo a uma lista e que usa o ExisteMeio() para verificar se o Meio já está na lista
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
 * \brief função auxiliar que serve para procurar um meio, pelo seu código, numa lista
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
 * \brief função que remove um meio de uma lista através da função ProcuraMeio() que usa o seu código
 * 
 * \param h
 * \param cod
 * \return 
 */
Meios* RemoveMeio(Meios* h, int cod)
{
	Meios* aux = ProcuraMeio(h, cod);

	if (aux == NULL) {
		// O gestor com o ID especificado não existe na lista
		return h;
	}

	if (aux == h) {
		// O gestor a ser removido é o primeiro da lista
		h = h->next;
		free(aux);
		return h;
		
	}
	else {
		// O gestor a ser removido não é o primeiro da lista
		Meios* ant = h;
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
 * \brief função que serve para alterar dados de um meio usando a função ProcuraMeio()
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
 * \brief função que regista o aluguer de um meio
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
 * \brief função que serve para mostrar um meio
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
 * função que usa a função MostraMeio() para listar os meios de uma lista
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
 * \brief função auxiliar para inserir por ordem da carga da bateria numa lista
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
 * \brief função que usa a CriaMeio e AuxiliarCarga para criar uma lista nova com os membros ordenados por carga
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
 * \brief função que compara as posições para ver se são iguais e se forem cria uma lista nova filtrada só com os meios com a mesma posição
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
 * \brief função para gravar uma lista de meios num ficheiro binário
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
 * \brief função para ler um ficheiro binário com os meios
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

