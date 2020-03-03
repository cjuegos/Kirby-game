#pragma once

#include "CMovimiento.h"
#include "CVecPoder.h"
#include <vector>
#include <stdio.h>

using namespace std;
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

enum TypeMovimiento { Estatico, Caminar, Saltar, Golpe1, Golpe2, Nadar, Nadar2, Estaticoagua, caminaraguaI, caminaraguaD};

class CKisame
{
private:
	int X, Y, Z;
	int X2, Y2;
	vector<CMovimiento *>* arrMovimiento;
	int Direccion, Indice, Direccion2;
	TypeMovimiento TipoMovimiento;
	CVecPoder* objVecPoder;/*
	CVecEnemigo* objVecEnemigo;*/
	int NroVidas;
	int NivelVida;
	int Nivel;
	bool salto;

public:
	CKisame(int X, int Y);
	~CKisame();

	void Dibujar(Graphics^ g, Bitmap^ imgKisame, Bitmap^ imgpeach);
	void Set_Movimiento(TypeMovimiento TipoMovimiento);
	void Mover(Keys Tecla);
	void Mover_Poder(int AnchoF, int LargoF);
	CVecPoder* Get_VecPoder();
	int Get_X();
	int Get_Y();
	int Get_Z();
	int Get_Ancho();
	int Get_Largo();
	void Set_NroVidas(int NroVidas);
	void Set_NivelVida(int NivelVida);
	int Get_NroVidas();
	int Get_NivelVida();
	int nivel();
};

CKisame::CKisame(int X, int Y)
{
	this->X = X;
	this->Y = Y;
	this->Indice = 0;
	this->Direccion = 1; // HACIA LA DERECHA
	this->arrMovimiento = new vector<CMovimiento *>();
	Set_Movimiento(TypeMovimiento::Estatico);
	objVecPoder = new CVecPoder();
	/*objVecEnemigo=new CVecEnemigo();*/
	this->NivelVida = 100;
	this->NroVidas = 3;
	Nivel = 1;
	salto = false;
	Z = 0;
}

CKisame::~CKisame(){}

void CKisame::Dibujar(Graphics^ g, Bitmap^ imgKisame, Bitmap^ imgpeach)
{
    
	Rectangle Origen = Rectangle(arrMovimiento->at(Indice)->Get_X(),
		arrMovimiento->at(Indice)->Get_Y(),
		arrMovimiento->at(Indice)->Get_Ancho(),
		arrMovimiento->at(Indice)->Get_Largo());
	Rectangle Destino = Rectangle(X, Y - arrMovimiento->at(Indice)->Get_Largo(),
		Direccion*arrMovimiento->at(Indice)->Get_Ancho(),
		arrMovimiento->at(Indice)->Get_Largo());

	g->DrawImage(imgKisame, Destino, Origen, GraphicsUnit::Pixel);
	
	X += (Direccion * arrMovimiento->at(Indice)->Get_dX());
	Y += ( arrMovimiento->at(Indice)->Get_dY());

	if(X>(int)g->VisibleClipBounds.Width-20){
	Nivel++;
	if (Nivel == 2)
		Y = 100;
	if(Nivel!=2)
	Y=300;
    X=50;
	/*objVecEnemigo->EliminarTodos();*/
}

	if(X>800 && Nivel == 4)


	Z=1;

	if (Indice == arrMovimiento->size() - 1)
	{
		if (TipoMovimiento != TypeMovimiento::Estatico)
			Set_Movimiento(TypeMovimiento::Estatico);
		if(Nivel==2)
			Set_Movimiento(TypeMovimiento::Estaticoagua);
		Indice = 0;
	}
	else
		Indice++;

	// DIBUJAR LOS PODERES
	objVecPoder->Dibujar(g, imgpeach);
}

void CKisame::Mover_Poder(int AnchoF, int LargoF)
{
	objVecPoder->Mover(AnchoF, LargoF);
	objVecPoder->Eliminar(); // ELIMINAR TODOS LOS QUE TENGAN ESTADO FALSE
}

void CKisame::Set_Movimiento(TypeMovimiento TipoMovimiento)
{
	this->TipoMovimiento = TipoMovimiento;
	char* Archivo = new char[100];

	switch (TipoMovimiento)
	{
	case TypeMovimiento::Estatico: strcpy(Archivo, "ESTATICO.txt");salto = false; break;
	case TypeMovimiento::Caminar: strcpy(Archivo, "CAMINAR.txt"); break;
	case TypeMovimiento::Saltar: strcpy(Archivo, "SALTAR.txt"); break;
	case TypeMovimiento::Golpe1: strcpy(Archivo, "GOLPE1.txt"); break;
	case TypeMovimiento::Golpe2: strcpy(Archivo, "GOLPE2.txt"); break;
	case TypeMovimiento::Nadar: strcpy(Archivo, "NADAR.txt"); break;
	case TypeMovimiento::Nadar2: strcpy(Archivo, "NADAR2.txt"); break;
	case TypeMovimiento::Estaticoagua: strcpy(Archivo, "ESTATICOAGUA.txt"); break;
	case TypeMovimiento::caminaraguaI: strcpy(Archivo, "CAMINARAGUAI.txt"); break;
	case TypeMovimiento::caminaraguaD: strcpy(Archivo, "CAMINARAGUAD.txt"); break;
	}

	int NroMovimientos, X, Y, Ancho, Largo, dX, dY;
	freopen(Archivo, "r", stdin);
	scanf("%d", &NroMovimientos);
	arrMovimiento->clear();
	
	for (int i = 0; i < NroMovimientos; i++)
	{
		scanf("%d %d %d %d %d %d", &X, &Y, &Ancho, &Largo, &dX, &dY);
		arrMovimiento->push_back(new CMovimiento(X, Y, Ancho, Largo, dX, dY));
	}


}

void CKisame::Mover(Keys Tecla)
{
	switch (Tecla)
	{
		case Keys::Left: 
			if (Nivel == 2)
			{
				Indice = 0;
				Direccion = -1;
				Set_Movimiento(TypeMovimiento::caminaraguaI);
			}
			else {
				Indice = 0;
				Direccion = -1;
				Set_Movimiento(TypeMovimiento::Caminar);
			}
		break;

		case Keys::Right:
			if (Nivel == 2)
			{
				Indice = 0;
				Direccion = 1;
				Set_Movimiento(TypeMovimiento::caminaraguaD);
		}
		else{
				Indice = 0;
				Direccion = 1;
				Set_Movimiento(TypeMovimiento::Caminar);
				}
		break;

		case Keys::Space: 
		if(Nivel==2){
			Indice = 0;
			Set_Movimiento(TypeMovimiento::Nadar);
		}
		else
		{
				if (!salto) {
				salto = true;
				Indice = 0;
				Set_Movimiento(TypeMovimiento::Saltar);
			}
		}
		break;

		case Keys::Z: 
			Indice = 0;
			if(Direccion!=1){X2=X-90;}
			else{X2=X;}
			Set_Movimiento(TypeMovimiento::Golpe1); 
			objVecPoder->Agregar(X2 + arrMovimiento->at(Indice)->Get_Ancho(),
				Y - arrMovimiento->at(Indice)->Get_Largo()/2, 10, 10, 5*Direccion, 0);
		break;
		case Keys::X: 
			Indice = 0;
			if(Direccion!=1) {X2= X-90;}
			else { X2 = X; }
			Set_Movimiento(TypeMovimiento::Golpe2); 
			objVecPoder->Agregar(X2 + arrMovimiento->at(Indice)->Get_Ancho(),
				Y - arrMovimiento->at(Indice)->Get_Largo() / 2, 10, 10, 5*Direccion, 0);
		break;
		case Keys::Down:
			if (Nivel == 2)
			{
				//Direccion2 = -1;
				Indice = 0;
				Set_Movimiento(TypeMovimiento::Nadar2);
			}
		break;
	}
}

CVecPoder* CKisame::Get_VecPoder()
{
	return this->objVecPoder;
}

int CKisame::Get_X()
{
	return this->X;
}

int CKisame::Get_Z()
{
	return this->Z;
}

int CKisame::Get_Y()
{
	return this->Y - arrMovimiento->at(Indice)->Get_Largo();
}

int CKisame::Get_Ancho()
{
	return arrMovimiento->at(Indice)->Get_Ancho();
}

int CKisame::Get_Largo()
{
	return arrMovimiento->at(Indice)->Get_Largo();
}

void CKisame::Set_NroVidas(int NroVidas)
{
	this->NroVidas = NroVidas;
}

void CKisame::Set_NivelVida(int NivelVida)
{
	this->NivelVida = NivelVida;
}

int CKisame::Get_NroVidas()
{
	return this->NroVidas;
}

int CKisame::Get_NivelVida()
{
	return this->NivelVida;
}
int  CKisame::nivel(){
return Nivel;
}