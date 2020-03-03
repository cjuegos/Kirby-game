#pragma once
#include "CEnemigo.h"

class CVecEnemigo
{
private:
	vector<CEnemigo*>* arrEnemigo;
public:
	CVecEnemigo();
	~CVecEnemigo();
	void Agregar(int X, int Y, int Direccion);
	void Dibujar(Graphics^ g, Bitmap^ imgEnemigo);
	void Mover(int AnchoF, int LargoF);
	void Eliminar();
	int HayColision(CVecPoder* objVecPoder);
	int HayColision(CKisame* objKisame);
	void EliminarTodos();
};

CVecEnemigo::CVecEnemigo()
{
	arrEnemigo = new vector<CEnemigo *>();
}

CVecEnemigo::~CVecEnemigo(){}

void CVecEnemigo::Agregar(int X, int Y, int Direccion)
{
	CEnemigo* objEnemigo = new CEnemigo(X, Y, Direccion);
	arrEnemigo->push_back(objEnemigo);
}

void CVecEnemigo::Dibujar(Graphics^ g, Bitmap^ imgEnemigo)
{
	for (int i = 0; i < arrEnemigo->size(); i++)
		arrEnemigo->at(i)->Dibujar(g, imgEnemigo);
}

void CVecEnemigo::Mover(int AnchoF, int LargoF)
{
	for (int i = 0; i < arrEnemigo->size(); i++)
		arrEnemigo->at(i)->Mover(AnchoF, LargoF);
}

void CVecEnemigo::Eliminar()
{
	vector<CEnemigo *>* Aux = new vector<CEnemigo *>();

	for (int i = 0; i < arrEnemigo->size(); i++)
		if (arrEnemigo->at(i)->Get_Estado())
			Aux->push_back(arrEnemigo->at(i));

	arrEnemigo = Aux;
}

int CVecEnemigo::HayColision(CVecPoder* objVecPoder)
{
	int Puntaje = 0;

	for (int i = 0; i < arrEnemigo->size(); i++)
		Puntaje += objVecPoder->HayColision(arrEnemigo->at(i));

	return Puntaje;
}

int CVecEnemigo::HayColision(CKisame* objKisame)
{
	int Puntaje = 0;

	for (int i = 0; i < arrEnemigo->size(); i++)
		if (arrEnemigo->at(i)->HayColision(objKisame->Get_X(), 
			objKisame->Get_Y(), objKisame->Get_Ancho(), 
			objKisame->Get_Largo()))
		{
			Puntaje -= 50;
			objKisame->Set_NivelVida(objKisame->Get_NivelVida() - 20);
			arrEnemigo->at(i)->Set_Estado(false);
			if (objKisame->Get_NivelVida() <= 0)
			{
				objKisame->Set_NivelVida(100);
				objKisame->Set_NroVidas(objKisame->Get_NroVidas() - 1);
			}
		}

	return Puntaje;
}
void CVecEnemigo::EliminarTodos()
{
arrEnemigo->clear();

}