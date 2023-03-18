/*****************************************************************//**
 * \file   Cliente.h
 * \brief  estrutura de dados e assinaturas para clientes
 * 
 * \author Ricardo Salema de Almeida_n26344
 * \date   March 2023
 *********************************************************************/
#pragma once
#pragma warning (disable:4996)
#define S 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Cliente {
	int NIF;
	char nome[S];
	char morada[S];
	float saldo;
	struct Cliente* next;
}Cliente;

typedef struct ClienteFile
{ 
	int NIF;
	char nome[S];
	char morada[S];
	float saldo;

}ClienteFile;

Cliente* CriaCliente(int nif, char* nome, char* morada, float saldo);
bool ExisteCliente(Cliente* h, int nif);
Cliente* InsereCliente(Cliente* h, Cliente* novo);
Cliente* RemoveCliente(Cliente* h, int nif);
Cliente* ProcuraCliente(Cliente* h, int nif);
Cliente* AlteraCliente(Cliente* h,int nif, char* nome, char* morada, float saldo);
void MostraCliente(Cliente* cliente);
void MostraClientes(Cliente* h);
void GravaClientesTexto(Cliente* h, char* nomef);
Cliente* LerClientesTexto(char* nomeFicheiro);
bool GravarClienteBinario(Cliente* h, char* nomef);
Cliente* LerClientesBinario(char* nomef);
