/*****************************************************************//**
 * \file   Gestor.h
 * \brief  Estruturas de Dados e assinaturas para Gestores
 * 
 * \author Ricardo Salema de Almeida_n26344
 * \date   March 2023
 *********************************************************************/

#pragma once
#pragma warning (disable:4996)
#include "Meios.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define S 100

typedef struct Gestor {
	char nome[S];
	int ID;
	struct Gestor* next;

}Gestor;

typedef struct GestorFile 
{
	char nome[S];
	int ID;
}GestorFile;
Gestor* CriaGestor(char* nome, int ID);
bool ExisteGestor(Gestor* h, int ID);
Gestor* InsereGestor(Gestor* h, Gestor* novo);
Gestor* RemoveGestor(Gestor* h, int ID);
Gestor* ProcuraGestor(Gestor* h, int ID);
Gestor* AlteraGestor(Gestor* h, int ID, char* nome);
void MostraGestor(Gestor* gestor);
void MostraGestores(Gestor* h);
bool GravarGestorBinario(Gestor* h, char* nomef);
Gestor* LerGestorBinario(char* nomef);
