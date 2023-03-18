/*****************************************************************//**
 * \file   Meios.h
 * \brief  estruturas de dados e assinaturas para Meios
 * 
 * \author Ricardo Salema de Almeida_n26344
 * \date   March 2023
 *********************************************************************/
#pragma once
#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define S 100

typedef enum TipoDeTransporte{
	trotinete,
	bicicleta,
	metro,
}tipo;
typedef struct MeiosDeMobilidadeElétrica {
	tipo tipo;
	int codigo;
	int carga;
	float custo;
	bool alugado;
	char posGeo[S];
	struct Meios* next;
}Meios;
typedef struct MeiosFile {
	tipo tipo;
	int codigo;
	int carga;
	float custo;
	bool alugado;
	char posGeo[S];
}MeiosFile;
Meios* CriaMeio(tipo tipo,int cod, int carga, float custo,bool alugado, char* pos);
bool ExisteMeio(Meios* h, int cod);
Meios* InsereMeio(Meios* h, Meios* novo);
Meios* RemoveMeio(Meios* h, int cod);
Meios* ProcuraMeio(Meios* h, int cod);
Meios* AlteraMeio(Meios* h, tipo tipo, int cod, int carga, float custo, char* posGeo);
Meios* Aluguer(Meios* h, int cod);
void MostraMeio(Meios* meio);
void MostraMeios(Meios* h);
Meios* AuxiliarCarga(Meios* h, Meios* novo);
Meios* OrdenarPorAutonomia(Meios* h);
Meios* MesmoGeo(Meios* h, char* posgeo);
bool GravarMeioBinario(Meios* h, char* nomef);
Meios* LerMeioBinario(char* nomef);


