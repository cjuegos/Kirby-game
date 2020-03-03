#pragma once
#include "CKisame.h"
#include "CVecEnemigo.h"
#define NFRAMES 5
class CJuego
{
private:
	CKisame* objKisame;
	CVecEnemigo* objVecEnemigo;
	int Contador;
	int Contador2;
	int Contador3;
	int Puntaje;
	int nivel;
	int Indice;
	int final;
	int v;
	int RX; int RD;
	int D;
	int vidas;
public:
CJuego();
	CJuego(int X, int Y);
	~CJuego();
	void Dibujar(Graphics^ g, Bitmap^ imgKisame, Bitmap^ imgEnemigo, Bitmap^ imgFondo, Bitmap^ imgFondo2, Bitmap^ imgFondo3, Bitmap^ imgFondo4
	,Bitmap^ imgpeach, Bitmap^ imgpeach2);
	void Set_Movimiento(TypeMovimiento TipoMovimiento);
	void Mover_Principal(Keys Tecla);
	void Mover_Enemigo(int AnchoF, int LargoF);
	void fondo(Graphics^g, Bitmap^ imgFondo);
	void menu(Graphics^g, Bitmap^ imgItachi, Bitmap^ imgFondo);
	void Win(Graphics^g, Bitmap^ imgFondo, Bitmap^ imgFondo2);
	int Get_final();
	int Get_nivel();
	int Get_vidas();
	void fin(Graphics^g, Bitmap^imgFondo8);
};
CJuego::CJuego(){
}
CJuego::CJuego(int X, int Y)
{
	objKisame = new CKisame(X, Y);
	objVecEnemigo = new CVecEnemigo();
	Contador = 0;
	Contador2 = 0;
	Contador3 = 0;
	Puntaje = 0;
	nivel =1;
	Indice = 0;
	objKisame->Get_Z();

	vidas=objKisame->Get_NroVidas();
}

CJuego::~CJuego() {}

void CJuego::Dibujar(Graphics^ g, Bitmap^ imgKisame, Bitmap^ imgEnemigo, Bitmap^ imgFondo, Bitmap^ imgFondo2, Bitmap^ imgFondo3, Bitmap^ imgFondo4
, Bitmap^ imgpeach, Bitmap^ imgpeach2)
{
	Random^ r = gcnew Random((int)DateTime::Now.Ticks);
	RX=r->Next(300,760);
	RD = r->Next(1, 3);
if(nivel==1)
{
	// DIBUJAR EL FONDO
	Rectangle OrigenF = Rectangle(0, 0, imgFondo->Width, imgFondo->Height);
	Rectangle DestinoF = Rectangle(0, 0,
		(int)g->VisibleClipBounds.Width, (int)g->VisibleClipBounds.Height);
	g->DrawImage(imgFondo, DestinoF, OrigenF, GraphicsUnit::Pixel);
}
if (nivel == 2)
{
     // DIBUJAR EL FONDO 2
     Rectangle OrigenF2 = Rectangle(0, 0, imgFondo2->Width, imgFondo2->Height);
	 Rectangle DestinoF2 = Rectangle(0, 0,
	 (int)g->VisibleClipBounds.Width, (int)g->VisibleClipBounds.Height);
	 g->DrawImage(imgFondo2, DestinoF2, OrigenF2, GraphicsUnit::Pixel);
}
if (nivel == 3)
{
	// DIBUJAR EL FONDO 2
	Rectangle OrigenF3 = Rectangle(0, 0, imgFondo3->Width, imgFondo3->Height);
	Rectangle DestinoF3 = Rectangle(0, 0,
		(int)g->VisibleClipBounds.Width, (int)g->VisibleClipBounds.Height);
	g->DrawImage(imgFondo3, DestinoF3, OrigenF3, GraphicsUnit::Pixel);
}
if (nivel == 4)
{
	// DIBUJAR EL FONDO 2
	Rectangle OrigenF4 = Rectangle(0, 0, imgFondo4->Width, imgFondo4->Height);
	Rectangle DestinoF4 = Rectangle(0, 0,
		(int)g->VisibleClipBounds.Width, (int)g->VisibleClipBounds.Height);
	g->DrawImage(imgFondo4, DestinoF4, OrigenF4, GraphicsUnit::Pixel);

	// DIBUJAR A ITACHI
	int AnchoI = imgpeach->Width / NFRAMES;
	int LargoI = imgpeach->Height;
	Rectangle Origen = Rectangle(AnchoI * Indice, 0, AnchoI, LargoI);
	Rectangle Destino = Rectangle(800, 260, 30, 40);
	g->DrawImage(imgpeach, Destino, Origen, GraphicsUnit::Pixel);

	if (Indice == NFRAMES - 1)
		Indice = 0;
	else
		Indice++;

}
	objVecEnemigo->Dibujar(g, imgEnemigo);
	objKisame->Dibujar(g, imgKisame,imgpeach2);
	if (objKisame->nivel() != nivel)
	{
		objVecEnemigo->EliminarTodos();
	}
	nivel = objKisame->nivel();
	g->DrawString("Puntaje: " + Puntaje.ToString() +
		"                                 # de Vidas: " + objKisame->Get_NroVidas().ToString() +
		"                               Nivel de Vida: " + objKisame->Get_NivelVida().ToString(),
		gcnew Font("AR DELANEY", 12), Brushes::White,
		100, 100);

		final=objKisame->Get_Z();
}

void CJuego::Set_Movimiento(TypeMovimiento TipoMovimiento)
{
	objKisame->Set_Movimiento(TipoMovimiento);
}

void CJuego::Mover_Enemigo(int AnchoF, int LargoF)
{
if(RD == 1)
D = 1;
if (RD == 2)
D = -1;

if(nivel==1){
	if (Contador == 80)
	{
		objVecEnemigo->Agregar(760, 320, -1);
		Contador = 0;
	}
	else
		Contador++;

	objVecEnemigo->Mover(AnchoF, LargoF);
	objKisame->Mover_Poder(AnchoF, LargoF);
	Puntaje += objVecEnemigo->HayColision(objKisame->Get_VecPoder());
	Puntaje += objVecEnemigo->HayColision(objKisame);
	objVecEnemigo->Eliminar();
}
if (nivel == 2) {
	if (Contador2 == 60)
	{
		objVecEnemigo->Agregar(RX, RX-400, D);
		Contador2 = 0;
	}
	else
		Contador2++;

	objVecEnemigo->Mover(AnchoF, LargoF);
	objKisame->Mover_Poder(AnchoF, LargoF);
	Puntaje += objVecEnemigo->HayColision(objKisame->Get_VecPoder());
	Puntaje += objVecEnemigo->HayColision(objKisame);
	objVecEnemigo->Eliminar();
}
if(nivel==3)
{
	if (Contador3 == 40)
	{
		objVecEnemigo->Agregar(RX, 320, D);
		Contador3 = 0;
	}
	else
		Contador3++;

	objVecEnemigo->Mover(AnchoF, LargoF);
	objKisame->Mover_Poder(AnchoF, LargoF);
	Puntaje += objVecEnemigo->HayColision(objKisame->Get_VecPoder());
	Puntaje += objVecEnemigo->HayColision(objKisame);
	objVecEnemigo->Eliminar();
}
}

void CJuego::Mover_Principal(Keys Tecla)
{
	objKisame->Mover(Tecla);
}

void CJuego::fondo(Graphics^g, Bitmap^ imgFondo) {
	
}

void CJuego::menu(Graphics^g,Bitmap^ imgItachi, Bitmap^ imgFondo) {

	// DIBUJAR EL FONDO
	Rectangle OrigenF = Rectangle(0, 0, imgFondo->Width, imgFondo->Height);
	Rectangle DestinoF = Rectangle(0, 0,
		(int)g->VisibleClipBounds.Width, (int)g->VisibleClipBounds.Height);
	g->DrawImage(imgFondo, DestinoF, OrigenF, GraphicsUnit::Pixel);


	// DIBUJAR A ITACHI
	int AnchoI = imgItachi->Width;
	int LargoI = imgItachi->Height;
	Rectangle Origen = Rectangle(0, 0, AnchoI, LargoI);
	Rectangle Destino = Rectangle(300, 270, 324, 36);
	g->DrawImage(imgItachi, Destino, Origen, GraphicsUnit::Pixel);
}

int CJuego::Get_final()
{
	return this->final;
}

void CJuego::Win(Graphics^g, Bitmap^ imgFondo6, Bitmap^ imgFondo7)
{
	// DIBUJAR EL FONDO
	Rectangle OrigenF6 = Rectangle(0, 0, imgFondo6->Width, imgFondo6->Height);
	Rectangle DestinoF6 = Rectangle(0, 0,
		(int)g->VisibleClipBounds.Width, (int)g->VisibleClipBounds.Height);
	g->DrawImage(imgFondo6, DestinoF6, OrigenF6, GraphicsUnit::Pixel);

}

int CJuego::Get_nivel(){
return this-> nivel;
}
int CJuego::Get_vidas(){
return this->vidas;
}

void CJuego::fin(Graphics^g, Bitmap^imgFondo8)
{
	// DIBUJAR EL FONDO
	Rectangle OrigenF8 = Rectangle(0, 0, imgFondo8->Width, imgFondo8->Height);
	Rectangle DestinoF8 = Rectangle(0, 0,
		(int)g->VisibleClipBounds.Width, (int)g->VisibleClipBounds.Height);
	g->DrawImage(imgFondo8, DestinoF8, OrigenF8, GraphicsUnit::Pixel);
}