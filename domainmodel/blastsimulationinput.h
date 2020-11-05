#ifndef BLASTSIMULATIONINPUT_H
#define BLASTSIMULATIONINPUT_H

#include <qstring.h>



class BlastSimulationInput
{
public:
    BlastSimulationInput();

private:
    QString blastholecsv;
    QString deckinputcsv;
    QString materialcsv;
    QString rockcsv;
    QString dxffile;
};

#endif // BLASTSIMULATIONINPUT_H
