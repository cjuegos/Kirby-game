#pragma once
#define NFRAMES 3
#include "CEnemigo.h"

using namespace System::Drawing;

class CPoder
{
private:
	int X, Y;
	int Ancho, Largo;
	int dX, dY;
	bool Estado;
	int Direccion;
	int Indice;
public:
	CPoder(int X, int Y, int Ancho, int Largo, int dX, int dY);
	~CPoder();
	void Dibujar(Graphics^ g, Bitmap^ imgpeach2);
	void MoverD(int AnchoF, int LargoF);
	void Set_Estado(bool Estado);
	bool Get_Estado();
	bool HayColision(int pX, int pY);
	bool HayColision(CEnemigo* objEnemigo);
};

CPoder::CPoder(int X, int Y, int Ancho, int Largo, int dX, int dY)
{
	this->X = X;
	this->Y = Y;
	this->Ancho = Ancho;
	this->Largo = Largo;
	this->dX = dX;
	this->dY = dY;
	this->Direccion = Direccion;
	this->Estado = true;
	Indice = 0;
}

CPoder::~CPoder(){}

void CPoder::Dibujar(Graphics^ g, Bitmap^ imgpeach2)
{
	
	int AnchoI = imgpeach2->Width / NFRAMES;
	int LargoI = imgpeach2->Height;
	Rectangle Origen = Rectangle(AnchoI * Indice, 0, AnchoI, LargoI);
	Rectangle Destino = Rectangle(X, Y-10, 25, 25);
	g->DrawImage(imgpeach2, Destino, Origen, GraphicsUnit::Pixel);

	if (Indice == NFRAMES - 1)
		Indice = 0;
	else
		Indice++;
}

void CPoder::MoverD(int AnchoF, int LargoF)
{

	if (X + dX < 0 || X + Ancho + dX > AnchoF)
		Estado = false;

	X += dX;
	Y += dY;
}

void CPoder::Set_Estado(bool Estado)
{
	this->Estado = Estado;
}

bool CPoder::Get_Estado()
{
	return this->Estado;
}

bool CPoder::HayColision(int pX, int pY)
{
	return pX >= X && pX <= X + Ancho &&
		   pY >= Y && pY <= Y + Largo;
}

bool CPoder::HayColision(CEnemigo* objEnemigo)
{
	if (HayColision(objEnemigo->Get_X(), objEnemigo->Get_Y()) ||HayColision(objEnemigo->Get_X()-50, objEnemigo->Get_Y()) ||
		HayColision(objEnemigo->Get_X(), objEnemigo->Get_Y()) ||
		HayColision(objEnemigo->Get_X(),
			objEnemigo->Get_Y()) ||
		objEnemigo->HayColision(X, Y, Ancho, Largo))
	{
		objEnemigo->Set_Movimiento(TypeMovimientoEnemigo::Muerte);
		objEnemigo->Set_Estado(false);
		this->Estado = false;
		return true;
	}
	return false;
}