#ifndef SIMULATION_H
#define SIMULATION_H

#include "blasthole.h"
#include "blastsimulationinput.h"
#include "deck.h"

#include <qstring.h>



class Simulation
{
public:
    Simulation();

    QString getMine() const;

    void setMine(const QString &value);

    QString getMinepit() const;

    void setMinepit(const QString &value);

    QString getProject() const;

    void setProject(const QString &value);

    QString getSimulation() const;

    void setSimulation(const QString &value);

    QString getBaseDir() const;

    void setBaseDir(const QString &value);

    QString getSimulationDir() const;

    void setSimulationDir(const QString &value);

    void setblastholes(const QList<BlastHole*>& blastholeslist);
    QList<BlastHole *> getblastholes();
private:
    QString mine; //mine name
    QString minepit; //mine pit
    QString project; //project
    QString simulation; //simulation name
    QString baseDir;
    QString simulationDir;
    BlastSimulationInput simuinputs;

    //We will use only project as the basis and multiple simulations underneath
    //mine and pit are virtual entities for logical organization purpose only
    QString basepath; //the base simulation path ... usually project directory

    //entire blast holes list ... the processed blastholes with collar and toe 3D
    QList<BlastHole*> blastHolesList;
    //Entire deck list items  ... the processed deckscsv files
    QList<Deck> *deckitems;

    //All input file references. Let us copy the files to input folder in simulation
    //BlastInputSouces *bis;

    //The convex hull based on exterior holes
    QList<BlastHole> *blastBenchConfinemnet;

    //the extended boundary of blast bench based on toe and collar burdens
    QList<BlastHole> *blastBenchExtendedConfinemnet;



};

#endif // SIMULATION_H
