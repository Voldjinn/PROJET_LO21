﻿#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H

#include <QDateTime>
#include "duree.h"
#include "evenement.h"
#include "exception.h"
#include "projet.h"

#include <exception>
#include <QMessageBox>

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLabel>
#include <QSpinBox>
#include <QSpinBox>
#include <QDate>
#include <QTime>


/*! \class Programmation
* \brief entree de l'emploi du temps, referencie un evenement
*/
class Programmation{
	friend class ProgrammationManager;
private:
    static int currentId;  //<!id de la prochaine programmation>
    int id;    //<!id de la programmation>
    QDate dateChoisie;    //<!date de la programmation>
    QTime horaireChoisi;    //<!horaire de la programmation>
    Duree duree;          //<!duree de la programmation>
    Evenement * evt;      //<!evenement relatif a la programmation (Tache ou Activite)>

    Programmation(Evenement * event, const QDate & dateChoisie, const QTime& horaireChoisi, Duree dur = Duree(0));
	Programmation operator=(Programmation & other);
	Programmation(Programmation & other);

public:
    const QDate& getDateChoisie() const {return dateChoisie; }   //<!renvoit la date choisie>
    const QTime& getHoraireChoisi() const {return horaireChoisi; }  //<!renvoit l''interlocuteur'horaire choisi>
    const Duree& getDuree()const { return duree; }     //<!renvoit la duree choisie>

    void setDateChoisie(QDate d) { dateChoisie = d; }   //<!modifie la date>
    void setHoraireChoisi(QTime t) { horaireChoisi = t; }   //<!modifie l'horaire>
    void setDuree(Duree d);         //<!modifie la duree>

    int getId()const {return id;}    //<!renvoit l'id de la programmation>
    Evenement * getEvent() { return evt; }    //<!renvoit l'interlocuteur'evenement relatif>
    const QTime getHoraireFin () const;    //<!renvoit l'horaire de fin de la programmation>

    ~Programmation();  //<!destructeur, ne supprimme pas evenement relatif, a part si il s'agit d'une Activite>



    bool operator>(const Programmation & other) const; //<!compare les dates et horaires choisis (renvoit true si other est apres this)>
    bool operator<(const Programmation & other) const;   //<!compare les dates et horaires choisis>
};




/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////               gere toutes les programmations                    /////////////////////////////
//////////         permet de regrouper toutes les programmations            /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class ProgrammationManager
* \brief regroupe toutes les programmations, l'emploi du temps est créé grace a elle
*/
class ProgrammationManager{
	friend class CreationProgrammationPreemptee;
private:
    std::vector<Programmation*> programmations;  //<!liste des programmations>
    static ProgrammationManager * instance;  //<!signleton, on ne considere qu'un emploi du temps>


    ProgrammationManager(){}   //<!private, l'appel se fait par getinstance()>
    ~ProgrammationManager();   //<!private, la suppression se fait par libereInstance()>
	/*!
	*  \brief cherche une programmation
	*  \param id : id de la programmation recherchée
	*/
    Programmation* trouverProgrammation(int id) const;
	/*!
	*  \brief cherche une programmation
	*  \param id : id de la programmation recherchée
	*/
	Programmation* trouverDerniereProgrammation(Evenement * evt) const;
	Programmation* createProgPreemptee(Evenement * event, QDate date, QTime horaire);
	void addItem(Programmation* t);


public:
    static ProgrammationManager& getInstance();
	static void libererInstance();
	bool creneaulibre(const QDate& da, const QTime& h, const Duree& du);

    void creerProgrammation(Evenement * event, QDate dateChoisie, QTime horaireChoisi, Duree d = 0);

	Programmation& getProgrammation(int id);
	Programmation& getDerniereProgrammation(Evenement * evt);

	
	const std::vector<Programmation*> & getProgrammations() const {return programmations; }
	std::vector<Programmation*> getSemaine(QDate & date) const;
	
	void supprimerProgrammationsEvt(const QString p);
	void supprimerProgrammation(int id);	
};

////////////////////////////////////////////////////////////////////////////////////////////////
///////////           lorsque l'on cree une programmation                    ///////////////////
///////////			 d'une tache preemptee on doit avoir la duree voulue     ///////////////////
///////////			  cette fenetre permet de l'avoir                        ///////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


class CreationProgrammationPreemptee : public QWidget {
	friend class ProgrammationManager;
	Q_OBJECT
private:
	QGridLayout *lay;
	QPushButton *valider;
	QLabel *text, *text1, *textR;
	QSpinBox *heure, *minute, *tempsR;
	Evenement * event;
	QDate _date;
    QTime _horaire;

    CreationProgrammationPreemptee(Evenement * e, QDate date, QTime horaire, Duree dur = 0, QWidget * parent = 0);
	~CreationProgrammationPreemptee();

	private slots :
	void save();
};



#endif
