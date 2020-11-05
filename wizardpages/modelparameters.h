#ifndef MODELPARAMETERS_H
#define MODELPARAMETERS_H

#include <QWizardPage>
#include <domainmodel/simulation.h>
#include <vector>
class QLabel;
class QDoubleSpinBox;
class QPushButton;
class QComboBox;
class QGroupBox;
class QTableView;
class QHBoxLayout;
class QLineEdit;
class QCheckBox;


class ModelParameters : public QWizardPage
{
    Q_OBJECT
private:
    QLabel* cuboidlabel;
    QDoubleSpinBox* cuboidspinbox;
    QLabel* frictionlabel;
    QDoubleSpinBox*  frictionspinbox;
    QLabel* restitutionlabel;
    QDoubleSpinBox*  restitutionspinbox;
    QLabel* timestepdecklabel;
    QDoubleSpinBox*  timestepdeckspinbox;
    QLabel* timestepdeckafterfiredlabel;
    QDoubleSpinBox*  timestepdeckafterfiredspinbox;
    QLabel* verticallabel;
    QDoubleSpinBox*  verticalspinbox;
    QLabel* Displacementlabel;
    QDoubleSpinBox*  Displacementspinbox;
    QLabel* cubelabel;
    QDoubleSpinBox*  cubespinbox;
    QLabel* expansionlabel;
    QDoubleSpinBox*  expansionspinbox;
    QLabel* cubeexpansionlabel;
    QDoubleSpinBox*  cubeexpansionspinbox;
    QLabel* exittimelabel;
    QDoubleSpinBox*  exittimespinbox;
    QLabel* dampinglabel;
    std::vector<QDoubleSpinBox*> dampingvec;
    QCheckBox* velocitycheckbox;
    QPushButton* startprocessingbutton;
public:
    ModelParameters(Simulation *currentSimulation,QWidget *parent = 0);
    Simulation *localref;
    void initializePage();
    bool validatePage();

};

#endif // MODELPARAMETERS_H
