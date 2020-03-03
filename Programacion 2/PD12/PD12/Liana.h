#pragma once

using namespace System::Drawing;

class CLiana
{
public:
	int x, y, w, h, r1, r2, xcentral, ycentral, angulo, dang;
	CLiana();
	~CLiana();
	void transformar();
	void mover(int pxcentral, int pycentral);
	void dibujar(Graphics^gr);
	bool colision(int px, int py, int pw, int ph);

private:

};

CLiana::CLiana()
{
	xcentral = 350;
	ycentral = 0;
	r1 = 150;
	r2 = 150;
	angulo = 70;
	x = 0; y = 0; w = 40; h = 40;
	dang = 10;
}

CLiana::~CLiana()
{
}

void CLiana::transformar() {
	float angrad = (angulo * 3.141516) / 180;
	x = xcentral + r1*1.5*System::Math::Cos(angrad);
	y = ycentral + r2*1.5*System::Math::Sin(angrad);
}

void CLiana::mover(int pxcentral, int pycentral) {


	if (angulo > 120 || angulo<60) dang *= -1;
	angulo += dang;
	if (System::Math::Abs(angulo)>360)
		angulo = 0;
	xcentral = pxcentral;
	ycentral = pycentral;
	transformar();
	//dibujar(gr);
}
void CLiana::dibujar(Graphics^gr) {
	mover(350, 0);
	gr->DrawLine(Pens::Brown, x, y, xcentral, ycentral);
	gr->FillEllipse(Brushes::Brown, x - w / 2, y - h / 2, w, h);
}

bool CLiana::colision(int px, int py, int pw, int ph)
{
	if (px >x - w / 2 + w ||
		py >y - h / 2 + h ||
		x - w / 2>px + pw ||
		y - h / 2>py + ph)
		return false;
	else
		return true;
}