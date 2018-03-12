#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Grafika.h"
#include <QDebug>
#include "QtClass.h"

class Grafika : public QMainWindow
{
	Q_OBJECT

public:
	Grafika(QWidget *parent = Q_NULLPTR);
public slots:
	void on_kocka_clicked();
	void on_sfera_clicked();
	void on_vymaz_clicked();
	void on_rovnobezna_clicked();
	void on_stredova_clicked();
	void on_tetha_sliderMoved(int);
	void on_fi_sliderMoved(int);
	void on_rovnobezky_sliderMoved(int);
	void on_poludniky_sliderMoved(int);
	void on_distancia_sliderMoved(int);
	void on_uloz_clicked();
	void transformacia_rovnobezna(int tetha, int fi);
	void transformacia_stredova(int tetha, int fi, double distancia);
	void on_zmenaSfera_clicked();
private:
	int typ_telesa=3;
	Ui::GrafikaClass ui;
	QtClass widgetNaKreslenie;
};
