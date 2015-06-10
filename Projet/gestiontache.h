#ifndef GESTIONTACHE_H
#define GESTIONTACHE_H


#include <QApplication>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QDateEdit>
#include <QListWidget>

#include "projet.h"
#include "programmation.h"

class TacheEditeur : public QWidget{
    Q_OBJECT
private:
    QGridLayout* box;
    QLineEdit* titre;
    QSpinBox* heureDebut, *minDebut;
    QSpinBox* heureEffectue, *minEffectue;
    QDateEdit* dispo, *echeance;
    QLabel *label_pre, *label_sousTaches, *label_t, *label_dispo, *label_echeance, *label_duree, *labelDureeEffectue, *labelDureeInitiale, *labelPrerequis;
    QCheckBox* pre;
    QPushButton* annuler, *saveButton;
    QListWidget *sousTaches, *prerequis;
    Tache* tache;

public:
    TacheEditeur(Tache * tacheToEdit, QWidget *parent = 0);
    public slots:
    //void save();
};



class GestionTache : public QWidget{
	Q_OBJECT

    Projet *_proj;
    QVBoxLayout *lay;
    QRadioButton *Preemptive, *Composite, *Unitaire;
    QTreeWidgetItem *p;
    QLabel *Duree1, *Duree3, *Ech1, *Dispo1, *Projet1, *Prerequis1, *Titre1;
    QSpinBox *Duree2, *Duree4;
    QDateEdit *Ech2, *Dispo2;
    std::vector<Tache*> pre;
    QLineEdit *Projet2, *Titre2, *Prerequis2;
    TacheEditeur *editeur;
    QPushButton *Sauvegarder, *Annuler;
	int verif;
    Tache *t;
public:
    GestionTache(Projet & proj);
	~GestionTache();
	public slots:
	void creertache();
	void afficherpreemptive();
	void affichercomposite();
};

class GestionSousTache : public QWidget{
    Q_OBJECT

    Projet &_proj;
    Tache &_tache;
    QVBoxLayout * lay;
	QRadioButton* Preemptive;
	QRadioButton* Composite;
	QRadioButton* Unitaire;
	Tache *t;
	QTreeWidgetItem * p;
	QTreeWidgetItem * tachecomp;
	QLabel * Duree1;
	QSpinBox* Duree2;
	QLabel * Duree3;
	QSpinBox* Duree4;
	QLabel * Ech1;
	QDateEdit* Ech2;
	QLabel* Dispo1;
	QDateEdit* Dispo2;
	std::vector<Tache*> pre;
	QLabel *Projet1;
	QLineEdit * Projet2;
	QLabel *Parent1;
	QLineEdit * Parent2;
	QLabel* Titre1;
	QLineEdit *Titre2;
	QLabel* Prerequis1;
	QLineEdit* Prerequis2;
	TacheEditeur* editeur;
	QPushButton* Sauvegarder;
	QPushButton* Annuler;
	Tache* par;
	int verif;
public:
    GestionSousTache(Projet & proj, Tache & tache);
	~GestionSousTache();
	public slots:
	void creertache();
	void afficherpreemptive();
	void affichercomposite();
};

#endif


