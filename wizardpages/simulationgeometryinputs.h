#ifndef SIMULATIONGEOMETRYINPUTS_H
#define SIMULATIONGEOMETRYINPUTS_H

#include <qlabel.h>
#include <qlineedit.h>
#include <qwizard.h>
#include <QSpinBox>
#include <qgroupbox.h>
#include <QDebug>
#include <QDir>

#include <domainmodel/simulation.h>
#include "simulationmasters/simulationmasterdetails.h"

class SimulationGeometryInputs : public QWizardPage
{
    Q_OBJECT

public:
    SimulationGeometryInputs(Simulation *currentSimulation,QWidget *parent = 0);
    void initializePage();
    bool validatePage();

private:
    QLabel *blastHoleInputLabel;
    QLabel *blastDeckInputLabel;
    QLabel *blastMaterialLabel;
    QLabel *blastRockInputLabel;
    QLabel *blastSurfaceLabel;

    QLineEdit *blastHoleInputLineEdit;
    QLineEdit *blastDeckInputLineEdit;
    QLineEdit *blastMaterialLineEdit;
    QLineEdit *blastRockInputLineEdit;
    QLineEdit *blastSurfaceLineEdit;

    QPushButton *blastHoleInputbrowseButton;
    QPushButton *blastDeckInputbrowseButton;
    QPushButton *blastMaterialbrowseButton;
    QPushButton *blastRockInputbrowseButton;
    QPushButton *blastSurfacebrowseButton;

    QLabel *blastHoleDiameterLabel;
    QLabel *blockSize;
    QDoubleSpinBox *blastHoleDiameterSpinBox;
    QDoubleSpinBox *blockSizeSpinBox;

    QString inputspath = QDir::currentPath();
    QPushButton *createButton(const QString &text, const char *member);
    QString createFolderStructure(QString foldername);
    Simulation *simulationref;


      QGroupBox *groupBox;
private:
      void readblastholecsvfile(QString& filename);

private slots:
    void fileBrowse();


};

#endif // SIMULATIONGEOMETRYINPUTS_H
