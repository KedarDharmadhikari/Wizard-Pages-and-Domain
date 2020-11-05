#include "modelparameters.h"
#include <QDebug>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QFrame>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QTableView>
#include <QLineEdit>

ModelParameters::ModelParameters(Simulation *currentSimulation,QWidget *parent): QWizardPage(parent)
{
    localref = currentSimulation;
    setTitle("Model Parameters");
    QVBoxLayout* mainlayout = new QVBoxLayout();
    QGridLayout* gridlayout = new QGridLayout();
    cubelabel = new QLabel("Cuboid Scale Factor (fraction)");
    cubespinbox = new QDoubleSpinBox();
    gridlayout->addWidget(cubelabel,0,0);
    gridlayout->addWidget(cubespinbox,0,1);
    gridlayout->setVerticalSpacing(5);

    frictionlabel = new QLabel("Friction");
    frictionspinbox = new QDoubleSpinBox();
    gridlayout->addWidget(frictionlabel,1,0);
    gridlayout->addWidget(frictionspinbox,1,1);

    restitutionlabel = new QLabel("Restitution");
    restitutionspinbox = new QDoubleSpinBox();
    gridlayout->addWidget(restitutionlabel,2,0);
    gridlayout->addWidget(restitutionspinbox,2,1);

    timestepdecklabel = new QLabel("Time step during decks firing (ms)");
    timestepdeckspinbox = new QDoubleSpinBox();
    gridlayout->addWidget(timestepdecklabel,3,0);
    gridlayout->addWidget(timestepdeckspinbox,3,1);

    timestepdeckafterfiredlabel = new QLabel("Time step after all decks fired (ms)");
    timestepdeckafterfiredspinbox = new QDoubleSpinBox();
    gridlayout->addWidget(timestepdeckafterfiredlabel,4,0);
    gridlayout->addWidget(timestepdeckafterfiredspinbox,4,1);

    verticallabel = new QLabel("Vertical Enhancement Factor");
    verticalspinbox = new QDoubleSpinBox();
    gridlayout->addWidget(verticallabel,5,0);
    gridlayout->addWidget(verticalspinbox,5,1);

    Displacementlabel = new QLabel("Dispalcement needed to break(m)");
    Displacementspinbox = new QDoubleSpinBox();
    gridlayout->addWidget(Displacementlabel,6,0);
    gridlayout->addWidget(Displacementspinbox,6,1);

    cubeexpansionlabel = new QLabel("Cube Expand Per Unit Time (%)");
    cubeexpansionspinbox = new QDoubleSpinBox();
    gridlayout->addWidget(cubeexpansionlabel,7,0);
    gridlayout->addWidget(cubeexpansionspinbox,7,1);

    expansionlabel = new QLabel("Expansion Factor Based on Displacement (%)");
    expansionspinbox = new QDoubleSpinBox();
    gridlayout->addWidget(expansionlabel,8,0);
    gridlayout->addWidget(expansionspinbox,8,1);

    cubeexpansionlabel = new QLabel("Cube Expand Maximum limit (%)");
    cubeexpansionspinbox = new QDoubleSpinBox();
    gridlayout->addWidget(cubeexpansionlabel,9,0);
    gridlayout->addWidget(cubeexpansionspinbox,9,1);

    exittimelabel = new QLabel("Exit Time (Sec) ");
    exittimespinbox = new QDoubleSpinBox();
    gridlayout->addWidget(exittimelabel,10,0);
    gridlayout->addWidget(exittimespinbox,10,1);

    QHBoxLayout* damplayouthor = new QHBoxLayout();
    dampinglabel = new QLabel("Damping");
    damplayouthor->addWidget(dampinglabel);
    damplayouthor->addSpacing(20);
    for(int i=0;i<6;++i)
    {
        QDoubleSpinBox* ptr = new QDoubleSpinBox();
        ptr->setMaximumWidth(62);
        dampingvec.push_back(ptr);
        damplayouthor->addWidget(ptr);
        damplayouthor->addSpacing(5);
        ptr = nullptr;
    }
    velocitycheckbox = new QCheckBox("Add Velocity After Break");
    startprocessingbutton = new QPushButton("Start Pre-Processing");
    startprocessingbutton->setMaximumWidth(120);
    mainlayout->addItem(gridlayout);
    mainlayout->addItem(damplayouthor);
    mainlayout->addWidget(velocitycheckbox);
    mainlayout->addWidget(startprocessingbutton);
    setLayout(mainlayout);
}
void ModelParameters::initializePage()
{
    qDebug() << "SimulationKickStart::initializePage";
}

bool ModelParameters::validatePage()
{
    return true;
}
