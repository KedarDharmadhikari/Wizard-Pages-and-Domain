#include "simulation.h"

Simulation::Simulation()
{

}

QString Simulation::getMine() const
{
    return mine;
}

void Simulation::setMine(const QString &value)
{
    mine = value;
}

QString Simulation::getMinepit() const
{
    return minepit;
}

void Simulation::setMinepit(const QString &value)
{
    minepit = value;
}

QString Simulation::getProject() const
{
    return project;
}

void Simulation::setProject(const QString &value)
{
    project = value;
}

QString Simulation::getSimulation() const
{
    return simulation;
}

void Simulation::setSimulation(const QString &value)
{
    simulation = value;
}

QString Simulation::getBaseDir() const
{
    return baseDir;
}

void Simulation::setBaseDir(const QString &value)
{
    baseDir = value;
}

QString Simulation::getSimulationDir() const
{
    return simulationDir;
}

void Simulation::setSimulationDir(const QString &value)
{
    simulationDir = value;
}

void Simulation::setblastholes(const QList<BlastHole*> &blastholeslist)
{
   blastHolesList.clear();
   blastHolesList = blastholeslist;
}

QList<BlastHole*> Simulation::getblastholes()
{
    return blastHolesList;
}
