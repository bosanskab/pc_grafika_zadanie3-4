#include "QtClass.h"

QtClass::QtClass(QWidget *parent)
	: QWidget(parent){

}

QtClass::~QtClass()
{
}

void QtClass::newImage(int x, int y)
{
	obrazok = new QImage(x, y, QImage::Format_RGB32);
	obrazok->fill(Qt::white);
	this->setMinimumSize(obrazok->size()); 
	update(); 
}


void QtClass::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect area = event->rect(); 
	painter.drawImage(area, *obrazok, area);
}

void QtClass::kresli_body() {
	QPainter painter(obrazok);
	painter.setPen(QPen(Qt::black, 3));
	vymaz_platno();

	for (int i = 0; i < newPoint.size(); i++) {
		painter.drawPoint(newPoint[i].x() + 200, newPoint[i].y() + 200);
	}

	update();
}

void QtClass::kresli_spoje(int hodnota) {
	QPainter painter(obrazok);
	painter.setPen(QPen(Qt::black, 1));
	if (hodnota==0) {
		for (int i = 0; i < pocty_spojov.size(); i++) {
			painter.drawLine(newPoint[indexy_bodov[i].x()].x() + 200, newPoint[indexy_bodov[i].x()].y() + 200, newPoint[indexy_bodov[i].y()].x() + 200, newPoint[indexy_bodov[i].y()].y() + 200);
		}
	}

	else if (hodnota == 1) {

		for (int i =0; i < indexy_bodov.size(); i++) {
			painter.drawLine(newPoint[indexy_bodov[i].x()].x() + 200, newPoint[indexy_bodov[i].x()].y() + 200, newPoint[indexy_bodov[i].y()].x() + 200, newPoint[indexy_bodov[i].y()].y() + 200);
			painter.drawLine(newPoint[indexy_bodov[i].x()].x() + 200, newPoint[indexy_bodov[i].x()].y() + 200, newPoint[indexy_bodov[i].z()].x() + 200, newPoint[indexy_bodov[i].z()].y() + 200);
			painter.drawLine(newPoint[indexy_bodov[i].z()].x() + 200, newPoint[indexy_bodov[i].z()].y() + 200, newPoint[indexy_bodov[i].y()].x() + 200, newPoint[indexy_bodov[i].y()].y() + 200);
		}
	}
	update();
}

void QtClass::vymaz_platno(){
	newImage(469, 449);
}

void QtClass::vymaz() {
	Point.clear();
	newPoint.clear();
	indexy_bodov.clear();
	spoje_sfera.clear();
	pocty_spojov.clear();
}

void QtClass::nacitanie_dat_kocka(){
	QVector3D p;
	QVector3D spoj;
	QString fileName = "cube.vtk";
	QFile file(fileName);
	teleso = 0;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		int n = 0,i=0;
		QTextStream stream(&file);
		QString line;
		QStringList list;

		do {
			line = stream.readLine();
			n++;
		} while (n != 4);

		n = 0;
		line = stream.readLine();
		list = line.split(' ');
		
		pocetPointov = list.at(1).toInt();
		typ = list.at(2);
		if (typ=="int") {
			do {
				line = stream.readLine();
				list = line.split(' ');
				p.setX(list.at(0).toInt());
				p.setY(list.at(1).toInt());
				p.setZ(list.at(2).toInt());
				Point.push_back(p);
				i++;
			} while (i != pocetPointov);
		}
		else if (typ == "double") {
			do {
				line = stream.readLine();
				list = line.split(' ');
				p.setX(list.at(0).toDouble());
				p.setY(list.at(1).toDouble());
				p.setZ(list.at(2).toDouble());
				Point.push_back(p);
				i++;
			} while (i != pocetPointov);
		}
		else if (typ == "float") {
			do {
				line = stream.readLine();
				list = line.split(' ');
				p.setX(list.at(0).toFloat());
				p.setY(list.at(1).toFloat());
				p.setZ(list.at(2).toFloat());
				Point.push_back(p);
				i++;
			} while (i != pocetPointov);
		}
		
		line = stream.readLine();
		list = line.split(' ');
		
		pocetS= list.at(1).toInt();
		i = 0;
		do {
			line = stream.readLine();
			list = line.split(' ');
			pocty_spojov.push_back(list.at(0).toInt());
			spoj.setX(list.at(1).toInt());
			spoj.setY(list.at(2).toInt());
			indexy_bodov.push_back(spoj);
			i++;
		} while (i != pocetS);

		file.close();
	}
	else {
		qDebug() << "Unable to open";
	}

}
	
void QtClass::nacitanie_dat_sfera() {
	QVector3D p;
	QVector3D spoj;
	QString fileName = "sphere_1.vtk";
	QFile file(fileName);
	teleso =1;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		int n = 0, i = 0;
		QTextStream stream(&file);
		QString line;
		QStringList list;

		do {
			line = stream.readLine();
			n++;
		} while (n != 4);

		n = 0;
		line = stream.readLine();
		list = line.split(' ');

		pocetPointov = list.at(1).toInt();
		typ = list.at(2);
		if (typ == "int") {
			do {
				line = stream.readLine();
				list = line.split(' ');
				p.setX(list.at(0).toInt());
				p.setY(list.at(1).toInt());
				p.setZ(list.at(2).toInt());
				Point.push_back(p);
				i++;
			} while (i != pocetPointov);
		}
		else if (typ == "double") {
			do {

				line = stream.readLine();
				list = line.split(' ');
				p.setX(list.at(0).toDouble()*100);
				p.setY(list.at(1).toDouble()*100);
				p.setZ(list.at(2).toDouble()*100);
				Point.push_back(p);
				i++;
				
			} while (i != pocetPointov);
		}
		else if (typ == "float") {
			do {
				line = stream.readLine();
				list = line.split(' ');
				p.setX(list.at(0).toFloat());
				p.setY(list.at(1).toFloat());
				p.setZ(list.at(2).toFloat());
				Point.push_back(p);
				i++;
			} while (i != pocetPointov);
		}

		line = stream.readLine();

		line = stream.readLine();
		list = line.split(' ');
		pocetS = list.at(1).toInt();

		i = 0;
		do {
			line = stream.readLine();
			list = line.split(' ');
			pocty_spojov.push_back(list.at(0).toInt());
			spoj.setX(list.at(1).toInt());
			spoj.setY(list.at(2).toInt());
			spoj.setZ(list.at(3).toInt());
			indexy_bodov.push_back(spoj);
			i++;
		} while (i != pocetS);

		file.close();
	}
	else {
		qDebug() << "Unable to open";
	}

}


void QtClass::sustava(int tetha1, int fi1) {
	double tetha, fi;

	tetha = tetha1 / 180. * M_PI;
	fi = fi1 / 180. * M_PI;

	normala.setX(qSin(tetha)*qCos(fi));
	normala.setY(qSin(tetha)*qSin(fi));
	normala.setZ(qCos(tetha));

	osX.setX(qSin(tetha + M_PI / 2)*qCos(fi));
	osX.setY(qSin(tetha + M_PI / 2)*qSin(fi));
	osX.setZ(qCos(tetha + M_PI / 2));

	osY.setX(normala.y()*osX.z() - normala.z()*osX.y());
	osY.setY(osX.x()*normala.z() - normala.x()*osX.z());
	osY.setZ(normala.x()*osX.y() - normala.y()*osX.x());
	
}


void QtClass::transformacia_rovnobezna() {
	float x, y, z;
	QVector3D NEW;
	newPoint.clear();

	for (int i = 0; i <pocetPointov; i++) {
		x = Point[i].x()*osX.x() + Point[i].y()*osX.y() + Point[i].z()*osX.z();
		y = Point[i].x()*osY.x() + Point[i].y()*osY.y() + Point[i].z()*osY.z();
		z = Point[i].x()*normala.x() + Point[i].y()*normala.y() + Point[i].z()*normala.z();
		NEW.setX(x);
		NEW.setY(y);
		NEW.setZ(z);
		newPoint.push_back(NEW);
	}
}

void QtClass::transformacia_distancia(int d) {
	float x, y, z;
	QVector3D NEW;
	newPoint.clear();

	for (int i = 0; i < pocetPointov; i++) {
		x = Point[i].x()*osX.x() + Point[i].y()*osX.y() + Point[i].z()*osX.z();
		y = Point[i].x()*osY.x() + Point[i].y()*osY.y() + Point[i].z()*osY.z();
		z = Point[i].x()*normala.x() + Point[i].y()*normala.y() + Point[i].z()*normala.z();

		x = (d * x) / (d - z);
		y = (d * y )/ (d - z);
		z = d;
		NEW.setX(x);
		NEW.setY(y);
		NEW.setZ(z);
		newPoint.push_back(NEW);
	}
}


void QtClass::transformacia_sfera(int pocet_rovnobezky, int pocet_poludniky) {
	float dr = M_PI / pocet_rovnobezky;
	float dp = 2 * M_PI / pocet_poludniky;
	float x,y, z;
	newPoint.clear();

	newPoint.push_back(QVector3D(0, 0, 100));
	for (int i = 1; i < pocet_rovnobezky; i++) {
		for (int j = 0; j < pocet_poludniky; j++) {
			x = sin(i*dr)*cos(j*dp)*100;
			y = sin(i*dr)*sin(j*dp)*100;
			z = cos(i*dr)*100;
			newPoint.push_back(QVector3D(x, y, z));
		}
	}
	newPoint.push_back(QVector3D(0, 0, -100));
	
}

void QtClass::spoje(int pocet_rovnobezky, int pocet_poludniky) {
	indexy_bodov.clear();
	spoje_sfera.clear();

	for (int i = 1; i <= pocet_poludniky; i++) {
		if (i<pocet_poludniky) {
			spoje_sfera.push_back(QVector3D(0, i, i + 1));
		}
		else {
			spoje_sfera.push_back(QVector3D(0, pocet_poludniky, 1));
		}
	}

	for (int j = 0; j<pocet_rovnobezky - 2; j++) {
		for (int i = j * pocet_poludniky + 1; i < (j + 1)*pocet_poludniky + 1; i = i + 2) {
			spoje_sfera.push_back(QVector3D(i, i + pocet_poludniky, i + 1));
			spoje_sfera.push_back(QVector3D(i + pocet_poludniky + 1, i + 1, i + pocet_poludniky));
			if (i<(j + 1)*pocet_poludniky - 1) {
				spoje_sfera.push_back(QVector3D(i + 2, i + 1, i + pocet_poludniky + 1));
				spoje_sfera.push_back(QVector3D(i + pocet_poludniky + 2, i + 2, i + pocet_poludniky + 1));
			}
			else {
				spoje_sfera.push_back(QVector3D(i - pocet_poludniky + 2, i + 1, i + pocet_poludniky + 1));
				spoje_sfera.push_back(QVector3D(i + 2, i - pocet_poludniky + 2, i + pocet_poludniky + 1));
			}
		}
	}

	for (int i = (pocet_rovnobezky - 2)*pocet_poludniky + 1; i <= pocet_poludniky * (pocet_rovnobezky - 1); i++) {
		if (i == (pocet_rovnobezky - 2)*pocet_poludniky + 1) {
			spoje_sfera.push_back(QVector3D(pocet_poludniky*(pocet_rovnobezky - 1) + 1, i, pocet_poludniky*(pocet_rovnobezky - 1)));
		}
		else {
			spoje_sfera.push_back(QVector3D(pocet_poludniky*(pocet_rovnobezky - 1) + 1, i, i - 1));
		}
	}

	for (int i = 0; i<spoje_sfera.size(); i++) {
		indexy_bodov.push_back(QVector2D(spoje_sfera[i].x(), spoje_sfera[i].y()));
		indexy_bodov.push_back(QVector2D(spoje_sfera[i].x(), spoje_sfera[i].z()));
		indexy_bodov.push_back(QVector2D(spoje_sfera[i].y(), spoje_sfera[i].z()));
	}
	pocetS = spoje_sfera.size();

	kresli_body();
	kresli_spoje(1);
}

void QtClass::ulozenie(){
	QVector3D p;
	QVector3D spoj;
	QString fileName = QFileDialog::getSaveFileName(this, "Save ", "", "Text Files(*.vtk)");
	QFile file(fileName); 


	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		int n = 0, i = 0;
		QTextStream stream(&file);
		QString line;
		QStringList list;

		stream << "# vtk DataFile Version 3.0"<<endl;
		stream << "vtk output" << endl;
		stream << "ASCII" << endl;
		stream << "DATASET POLYDATA" << endl;
		stream << "POINTS "<< newPoint.size() <<" "<<typ << endl;

		for (int i = 0; i < newPoint.size(); i++) {
			stream << newPoint[i].x()/100 << " " << newPoint[i].y()/100 << " " << newPoint[i].z()/100 << endl;
		}
		stream << " "<<endl;

		if (teleso ==1) {
			stream <<"POLYGONS " << pocetS << " " << pocetS * 4 << endl;
			for (int i = 0; i<pocetS; i++) {
				stream << "3 " << indexy_bodov[i].x() << " " << indexy_bodov[i].y() << " " << indexy_bodov[i].z() << endl;
			}
		}

		else if (teleso == 0) {
			stream << "LINES " << pocetS << " " << pocetS * 3 << endl;
			for (int i = 0; i < pocetS;i++) {
				stream << "2 "<< indexy_bodov[i].x() <<" "<< indexy_bodov[i].y() << endl;
			}

		}
		

		file.close();
	
	}
	else {
		qDebug() << "Unable to save";
	}
}