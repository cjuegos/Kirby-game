#pragma once

#include "CPoder.h"
#include <vector>

using namespace std;

class CVecPoder
{
private:
	vector<CPoder *>* arrPoder;
public:
	CVecPoder();
	~CVecPoder();
	void Agregar(int X, int Y, int Ancho, int Largo, int dX, int dY);
	void Dibujar(Graphics^ g, Bitmap^ imgpeach2);
	void Mover(int AnchoF, int LargoF);
	void Eliminar();
	int HayColision(CEnemigo *objEnemigo);
};

CVecPoder::CVecPoder()
{
	arrPoder = new vector<CPoder *>();
}

CVecPoder::~CVecPoder(){}

void CVecPoder::Agregar(int X, int Y, int Ancho, int Largo, int dX, int dY)
{
	CPoder *objPoder = new CPoder(X, Y, Ancho, Largo, dX, dY);
	arrPoder->push_back(objPoder);
}

void CVecPoder::Dibujar(Graphics^ g, Bitmap^ imgpeach2)
{
	for (int i = 0; i < arrPoder->size(); i++)
		arrPoder->at(i)->Dibujar(g, imgpeach2);


}

void CVecPoder::Mover(int AnchoF, int LargoF)
{
	for (int i = 0; i < arrPoder->size(); i++)
		arrPoder->at(i)->MoverD(AnchoF, LargoF);

}
void CVecPoder::Eliminar()
{
	vector<CPoder*>* Aux = new vector<CPoder *>();

	for (int i = 0; i < arrPoder->size(); i++)
		if (arrPoder->at(i)->Get_Estado())
			Aux->push_back(arrPoder->at(i));

	arrPoder = Aux;
}

int CVecPoder::HayColision(CEnemigo *objEnemigo)
{
	int Puntaje = 0;

	for (int i = 0; i < arrPoder->size(); i++)
		if (arrPoder->at(i)->HayColision(objEnemigo))
			Puntaje += 15;

	return Puntaje;
}