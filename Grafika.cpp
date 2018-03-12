#include "Grafika.h"

Grafika::Grafika(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.scrollArea->setWidget(&this->widgetNaKreslenie);
	ui.scrollArea->setBackgroundRole(QPalette::Dark);

	widgetNaKreslenie.newImage(469, 449);
	ui.uhly->setEnabled(false);
	ui.dist->setEnabled(false);
	ui.rovnobezna->setEnabled(false);
	ui.stredova->setEnabled(false);
	ui.kocka->setEnabled(true);
	ui.sfera->setEnabled(true);
	ui.vymaz->setEnabled(false);
	ui.uloz->setEnabled(false);
	ui.sfera_2->setEnabled(false);
	ui.zmenaSfera->setEnabled(false);
}

void Grafika::on_kocka_clicked() {
	widgetNaKreslenie.nacitanie_dat_kocka();
	typ_telesa = 0;

	ui.uhly->setEnabled(true);
	if(ui.stredova->isChecked())
		ui.dist->setEnabled(true);
	else
		ui.dist->setEnabled(false);
	ui.rovnobezna->setEnabled(true);
	ui.stredova->setEnabled(true);
	ui.kocka->setEnabled(false);
	ui.sfera->setEnabled(false);
	ui.vymaz->setEnabled(true);
	ui.uloz->setEnabled(true);
	ui.sfera_2->setEnabled(false);

	widgetNaKreslenie.sustava(0, 0);
	widgetNaKreslenie.transformacia_rovnobezna();
	widgetNaKreslenie.kresli_body();
	widgetNaKreslenie.kresli_spoje(typ_telesa);


	if (ui.zmenaSfera->isChecked()) {
		ui.rovnobezna->setChecked(true);
		ui.zmenaSfera->setChecked(false);
	}
}


void Grafika::on_sfera_clicked() {
	typ_telesa = 1;

	widgetNaKreslenie.nacitanie_dat_sfera();
	ui.uhly->setEnabled(true);
	if(ui.stredova->isChecked())
		ui.dist->setEnabled(true);
	else ui.dist->setEnabled(false);
	ui.rovnobezna->setEnabled(true);
	ui.stredova->setEnabled(true);
	ui.kocka->setEnabled(false);
	ui.sfera->setEnabled(false);
	ui.vymaz->setEnabled(true);
	ui.uloz->setEnabled(true);
	ui.zmenaSfera->setEnabled(true);

	if (ui.zmenaSfera->isChecked())
		ui.sfera_2->setEnabled(true);
	else ui.sfera_2->setEnabled(false);

	widgetNaKreslenie.sustava(0, 0);
	widgetNaKreslenie.transformacia_rovnobezna();
	widgetNaKreslenie.kresli_body();
	widgetNaKreslenie.kresli_spoje(typ_telesa);
}


void Grafika::on_rovnobezna_clicked() {
	ui.uhly->setEnabled(true);
	ui.dist->setEnabled(false);
	ui.sfera_2->setEnabled(false);
}

void Grafika::on_stredova_clicked() {
	ui.uhly->setEnabled(true);
	ui.dist->setEnabled(true);
	ui.sfera_2->setEnabled(false);
}


void Grafika::on_vymaz_clicked() {
	widgetNaKreslenie.newImage(469, 449);
	widgetNaKreslenie.vymaz_platno();
	widgetNaKreslenie.vymaz();
	ui.uhly->setEnabled(false);
	ui.dist->setEnabled(false);
	ui.rovnobezna->setEnabled(false);
	ui.stredova->setEnabled(false);
	ui.kocka->setEnabled(true);
	ui.sfera->setEnabled(true);
	ui.vymaz->setEnabled(false);
	ui.sfera_2->setEnabled(false);
	ui.zmenaSfera->setEnabled(false);
}

void Grafika::transformacia_rovnobezna(int tetha, int fi) {
	widgetNaKreslenie.sustava(tetha,fi);
	widgetNaKreslenie.transformacia_rovnobezna();
	widgetNaKreslenie.kresli_body();
	widgetNaKreslenie.kresli_spoje(typ_telesa);
}

void Grafika::transformacia_stredova(int tetha, int fi, double distancia) {
	widgetNaKreslenie.sustava(tetha, fi);
	widgetNaKreslenie.transformacia_distancia(distancia);
	widgetNaKreslenie.kresli_body();
	widgetNaKreslenie.kresli_spoje(typ_telesa);
}

void Grafika::on_uloz_clicked() {
	widgetNaKreslenie.ulozenie();
}


void Grafika::on_tetha_sliderMoved(int hodnota){
	QString s = QString::number(hodnota);
	ui.textEdit->setText(s);
	
	if (ui.rovnobezna->isChecked()) {
		transformacia_rovnobezna(ui.tetha->value(), ui.fi->value());
	}
	else if (ui.stredova->isChecked()) {
		transformacia_stredova(ui.tetha->value(), ui.fi->value(), (ui.distancia->value()));
	}
	
	

}

void Grafika::on_fi_sliderMoved(int hodnota){
	QString s = QString::number(hodnota);
	ui.textEdit_2->setText(s);
	if (ui.rovnobezna->isChecked()) {
		transformacia_rovnobezna(ui.tetha->value(), ui.fi->value());
	}
	else if (ui.stredova->isChecked()) {
		transformacia_stredova(ui.tetha->value(), ui.fi->value(), (ui.distancia->value()));
	}
	
	
}

void Grafika::on_distancia_sliderMoved(int hodnota) {
	QString s = QString::number(hodnota);
	ui.textEdit_3->setText(s);
	
	if (ui.stredova->isChecked()) {
		transformacia_stredova(ui.tetha->value(), ui.fi->value(), (ui.distancia->value()));
	}
}


void Grafika::on_rovnobezky_sliderMoved(int hodnota) {
	QString s = QString::number(hodnota);
	ui.textEdit_4->setText(s);

	widgetNaKreslenie.transformacia_sfera(ui.rovnobezky->value(), ui.poludniky->value());
	widgetNaKreslenie.spoje(ui.rovnobezky->value(), ui.poludniky->value());
}

void Grafika::on_poludniky_sliderMoved(int hodnota) {
	QString s = QString::number(hodnota);
	ui.textEdit_5->setText(s);

	

	widgetNaKreslenie.transformacia_sfera(ui.rovnobezky->value(), ui.poludniky->value());
	widgetNaKreslenie.spoje(ui.rovnobezky->value(), ui.poludniky->value());
}

void Grafika::on_zmenaSfera_clicked() {
	ui.sfera_2->setEnabled(true);
	ui.uhly->setEnabled(false);
	ui.dist->setEnabled(false);
}
