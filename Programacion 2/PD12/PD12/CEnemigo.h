#pragma once
#include "CMovimiento.h"
#include <vector>
#include <stdio.h>

using namespace std;
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

enum TypeMovimientoEnemigo { Mover, Ataque1, Ataque2, Muerte };

class CEnemigo
{
private:
	int X, Y;
	vector<CMovimiento *>* arrMovimiento;
	int Direccion, Indice;
	TypeMovimientoEnemigo TipoMovimiento;
	bool Estado;
public:
	CEnemigo(int X, int Y, int Direccion);
	~CEnemigo();
	void Set_Movimiento(TypeMovimientoEnemigo TipoMovimiento);
	void Dibujar(Graphics^ g, Bitmap^ imgEnemigo);
	void Mover(int AnchoF, int LargoF);
	void Set_Estado(bool Estado);
	int Get_X();
	int Get_Y();
	int Get_Ancho();
	int Get_Largo();
	bool Get_Estado();
	bool HayColision(int pX, int pY);
	bool HayColision(int pX, int pY, int pAncho, int pLargo);
};


CEnemigo::CEnemigo(int X, int Y, int Direccion)
{
	this->X = X;
	this->Y = Y;
	this->Indice = 0;
	this->Direccion = Direccion;
	this->arrMovimiento = new vector<CMovimiento *>();
	Set_Movimiento(TypeMovimientoEnemigo::Mover);
	this->Estado = true;
}

CEnemigo::~CEnemigo(){}

void CEnemigo::Dibujar(Graphics^ g, Bitmap^ imgEnemigo)
{


	Rectangle Origen = Rectangle(arrMovimiento->at(Indice)->Get_X(),
		arrMovimiento->at(Indice)->Get_Y(),
		arrMovimiento->at(Indice)->Get_Ancho(),
		arrMovimiento->at(Indice)->Get_Largo());
	Rectangle Destino = Rectangle(X,
		Y - arrMovimiento->at(Indice)->Get_Largo(),
		Direccion*60,
		60);

	g->DrawImage(imgEnemigo, Destino, Origen, GraphicsUnit::Pixel);

	if (Indice == arrMovimiento->size() - 1)
	{
		if (TipoMovimiento != TypeMovimientoEnemigo::Mover)
			Set_Movimiento(TypeMovimientoEnemigo::Mover);

		Indice = 0;
	}
	else
		Indice++;
}

void CEnemigo::Set_Movimiento(TypeMovimientoEnemigo TipoMovimiento)
{
	this->TipoMovimiento = TipoMovimiento;
	char* Archivo = new char[100];

	switch (TipoMovimiento)
	{
	case TypeMovimientoEnemigo::Mover: strcpy(Archivo, "MOVER_ENEMIGO.txt"); break;
	case TypeMovimientoEnemigo::Ataque1: strcpy(Archivo, "ATAQUE1_ENEMIGO.txt"); break;
	case TypeMovimientoEnemigo::Ataque2: strcpy(Archivo, "ATAQUE2_ENEMIGO.txt"); break;
	case TypeMovimientoEnemigo::Muerte:  strcpy(Archivo, "MUERTE.txt"); break;
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

void CEnemigo::Mover(int AnchoF, int LargoF)
{
	if (X + arrMovimiento->at(Indice)->Get_dX() < 0 ||
		X + arrMovimiento->at(Indice)->Get_dX() +
		arrMovimiento->at(Indice)->Get_Ancho() > AnchoF)
	{
		Direccion *= -1;
	}
	
	X += (Direccion * arrMovimiento->at(Indice)->Get_dX());
	Y += (arrMovimiento->at(Indice)->Get_dY());
}

void CEnemigo::Set_Estado(bool Estado)
{
	this->Estado = Estado;
	if(Estado==false)
	{
		Set_Movimiento(TypeMovimientoEnemigo::Muerte);
	}
}

int CEnemigo::Get_X()
{
	return this->X;
}

int CEnemigo::Get_Y()
{
	return Y - arrMovimiento->at(Indice)->Get_Largo();
}

int CEnemigo::Get_Ancho()
{
	return arrMovimiento->at(Indice)->Get_Ancho();
}

int CEnemigo::Get_Largo()
{
	return arrMovimiento->at(Indice)->Get_Largo();
}

bool CEnemigo::Get_Estado()
{
	return this->Estado;
}

bool CEnemigo::HayColision(int pX, int pY)
{
	return pX >= X && pX <= X + Get_Ancho() &&
		   pY >= Get_Y() && pY <= Get_Y() + Get_Largo();
}

bool CEnemigo::HayColision(int pX, int pY, int pAncho, int pLargo)
{
	return HayColision(pX, pY) ||
		HayColision(pX + pAncho, pY) ||
		HayColision(pX, pY + pLargo) ||
		HayColision(pX + pAncho, pY + pLargo);
}