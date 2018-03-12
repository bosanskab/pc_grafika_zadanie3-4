#pragma once

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QtWidgets>

class QtClass : public QWidget
{
	Q_OBJECT

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	QImage *obrazok;
	QString typ;
	int	pocetPointov;
	int teleso;
	QVector<QVector3D> Point;
	QVector<QVector3D> newPoint;
	int pocetS;
	QVector<int> pocty_spojov;
	QVector<QVector3D> indexy_bodov;
	QVector<QVector3D> spoje_sfera;
	QVector3D Eye;
	QVector3D normala;
	QVector3D osX;
	QVector3D osY;
public:
	QtClass(QWidget *parent = Q_NULLPTR);
	~QtClass();
	void newImage(int x, int y);
	void kresli_body();
	void kresli_spoje(int hodnota);
	void vymaz();
	void vymaz_platno();
	void nacitanie_dat_kocka();
	void nacitanie_dat_sfera();
	void sustava(int tetha, int pi);
	void transformacia_rovnobezna();
	void transformacia_distancia(int d);
	void transformacia_sfera(int pocet_rovnobezky, int pocet_poludniky);
	void spoje(int pocet_rovnobezky, int pocet_poludniky);
	void ulozenie();

};
