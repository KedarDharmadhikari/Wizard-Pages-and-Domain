#include "simulationgeometryinputs.h"

#include <qfiledialog.h>
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <qstringlistmodel.h>

SimulationGeometryInputs::SimulationGeometryInputs(Simulation *currentSimulation,QWidget *parent)
    : QWizardPage(parent)
{

    simulationref = currentSimulation;
    //! [8]
    setTitle(tr("Blast simulation geometry"));
    setSubTitle(tr("Specify the blast geomtry files i.e. blast holes, decks, rock and blast material with optional dxf."));
//    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo1.png"));


    //Blast Hole input csv file control
    blastHoleInputLabel = new QLabel(tr("Blaset &Holes:"));
    blastHoleInputLineEdit = new QLineEdit;
    blastHoleInputLineEdit->setReadOnly(true);
    blastHoleInputLabel->setBuddy(blastHoleInputLineEdit);
    blastHoleInputbrowseButton = createButton(tr("..."),SLOT(fileBrowse()));


    //Blast Deck input csv file control
    blastDeckInputLabel = new QLabel(tr("Blast &Deck:"));
    blastDeckInputLineEdit = new QLineEdit;
    blastDeckInputLineEdit->setReadOnly(true);
    blastDeckInputLabel->setBuddy(blastDeckInputLineEdit);
    blastDeckInputbrowseButton = createButton(tr("..."),SLOT(fileBrowse()));

    //Blast material csv file control
    blastMaterialLabel = new QLabel(tr("Blast &Material:"));
    blastMaterialLineEdit = new QLineEdit;
    blastMaterialLineEdit->setReadOnly(true);
    blastMaterialLabel->setBuddy(blastMaterialLineEdit);
    blastMaterialbrowseButton = createButton(tr("..."),SLOT(fileBrowse()));

    //Blast material csv file control
    blastRockInputLabel = new QLabel(tr("Blast &Rock:"));
    blastRockInputLineEdit = new QLineEdit;
    blastRockInputLineEdit->setReadOnly(true);
    blastRockInputLabel->setBuddy(blastRockInputLineEdit);
    blastRockInputbrowseButton = createButton(tr("..."),SLOT(fileBrowse()));

    //Blast material csv file control
    blastSurfaceLabel = new QLabel(tr("Blast D&XF Surface:"));
    blastSurfaceLineEdit = new QLineEdit;
    blastSurfaceLineEdit->setReadOnly(true);
    blastSurfaceLabel->setBuddy(blastSurfaceLineEdit);
    blastSurfacebrowseButton = createButton(tr("..."),SLOT(fileBrowse()));

    //! [10]
    groupBox = new QGroupBox(tr("Blast bench parameters"));
    groupBox->setAlignment(Qt::AlignRight);
    //! [9]

//    qobjectCtorRadioButton = new QRadioButton(tr("&QObject-style constructor"));
//    qwidgetCtorRadioButton = new QRadioButton(tr("Q&Widget-style constructor"));
//    defaultCtorRadioButton = new QRadioButton(tr("&Default constructor"));
//    copyCtorCheckBox = new QCheckBox(tr("&Generate copy constructor and "
//                                        "operator="));

//    defaultCtorRadioButton->setChecked(true);

//    connect(defaultCtorRadioButton, SIGNAL(toggled(bool)),
//            copyCtorCheckBox, SLOT(setEnabled(bool)));

    //! [11] //! [12]
    registerField("blastHoleInput*", blastHoleInputLineEdit);
    registerField("blastDeckInput*", blastDeckInputLineEdit);
    registerField("blastMaterial*", blastMaterialLineEdit);
    registerField("blastRockInput*", blastRockInputLineEdit);


    QGridLayout *groupBoxLayout = new QGridLayout;
    blastHoleDiameterLabel = new QLabel(tr("Blast hole diameter"));
    blastHoleDiameterSpinBox = new QDoubleSpinBox;
    blastHoleDiameterSpinBox->setRange(0.01,10);
    blastHoleDiameterSpinBox->setValue(0.25);
    blastHoleDiameterSpinBox->setSingleStep(0.01);


    blockSize = new QLabel(tr("Block Size"));
    blockSizeSpinBox =new QDoubleSpinBox;
    blockSizeSpinBox->setRange(0.01,10);
    blockSizeSpinBox->setValue(3.00);
    blockSizeSpinBox->setSingleStep(0.10);

    groupBoxLayout->addWidget(blastHoleDiameterLabel,0,0);
    groupBoxLayout->addWidget(blastHoleDiameterSpinBox,0,1);
    groupBoxLayout->addWidget(blockSize,0,2);
    groupBoxLayout->addWidget(blockSizeSpinBox,0,3);
    groupBox->setLayout(groupBoxLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(blastHoleInputLabel, 0, 0);
    layout->addWidget(blastHoleInputLineEdit, 0, 1);
    layout->addWidget(blastHoleInputbrowseButton, 0, 2);

    layout->addWidget(blastDeckInputLabel, 1, 0);
    layout->addWidget(blastDeckInputLineEdit, 1, 1);
    layout->addWidget(blastDeckInputbrowseButton, 1, 2);

    layout->addWidget(blastMaterialLabel, 2, 0);
    layout->addWidget(blastMaterialLineEdit, 2, 1);
    layout->addWidget(blastMaterialbrowseButton, 2, 2);

    layout->addWidget(blastRockInputLabel, 3, 0);
    layout->addWidget(blastRockInputLineEdit, 3, 1);
    layout->addWidget(blastRockInputbrowseButton, 3, 2);

    layout->addWidget(blastSurfaceLabel, 4, 0);
    layout->addWidget(blastSurfaceLineEdit, 4, 1);
    layout->addWidget(blastSurfacebrowseButton, 4, 2);

//    layout->addWidget(qobjectMacroCheckBox, 4, 0, 1, 3);
    layout->addWidget(groupBox, 5, 0, 1, 3);
    setLayout(layout);
    //! [13]
}

void SimulationGeometryInputs::initializePage(){
    qDebug() << "SimulationKickStart::initializePage";

//    QStringListModel *model = new QStringListModel();
//    model->setStringList(SimulationMasterDetails::getMines());

//    mineLineEdit->setModel(model);
}

bool SimulationGeometryInputs::validatePage()
{
        //project base directory
    simulationref->setBaseDir(createFolderStructure(QDir::currentPath()+QDir::separator()+simulationref->getMine()+"__"+simulationref->getMinepit()+"__"+simulationref->getProject()));

    //project base directory
    createFolderStructure(simulationref->getBaseDir()+QDir::separator()+"inputfiles");

    //Project simulation folder underneath
    simulationref->setSimulationDir(createFolderStructure(simulationref->getBaseDir()+QDir::separator()+simulationref->getSimulation()));

    /* copy all the inputs provided into the project folder */
    QString filename;
    QFile::copy(field("blastHoleInput").toString(), simulationref->getBaseDir()+QDir::separator()+"inputfiles"+QDir::separator()+"blastholes.csv");
    QFile::copy(field("blastDeckInput").toString(), simulationref->getBaseDir()+QDir::separator()+"inputfiles"+QDir::separator()+"blastdecks.csv");
    QFile::copy(field("blastMaterial").toString(), simulationref->getBaseDir()+QDir::separator()+"inputfiles"+QDir::separator()+"blastmaterial.csv");
    QFile::copy(field("blastRockInput").toString(), simulationref->getBaseDir()+QDir::separator()+"inputfiles"+QDir::separator()+"rocks.csv");
    QFile::copy(blastSurfaceLineEdit->text(), simulationref->getBaseDir()+QDir::separator()+"inputfiles"+QDir::separator()+"surface.dxf");

    filename = simulationref->getBaseDir()+QDir::separator()+"inputfiles"+QDir::separator()+"blastholes.csv";
    qDebug() << filename;
    readblastholecsvfile(filename);
    qDebug() << "SimulationGeometryInputs" << simulationref->getMine() << " " << simulationref->getMinepit();
    return true;
}

QString SimulationGeometryInputs::createFolderStructure(QString foldername)
{
    QDir *dirtocreate = new QDir(foldername);

    if(!dirtocreate->exists())
        dirtocreate->mkdir(foldername);

    return dirtocreate->path();
}

QPushButton *SimulationGeometryInputs::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    button->setMaximumWidth(32);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}



//Slot to trigger file browser control to choose the CSV and dxf files
void SimulationGeometryInputs::fileBrowse()
{

    QPushButton * senderButton = qobject_cast<QPushButton *>(this->sender());
    QString fname;


    if(senderButton == blastSurfacebrowseButton)
        fname = QFileDialog::getOpenFileName(this,tr("Select DXF"), inputspath, tr("DXF Files (*.dxf)"));
    else
        fname = QFileDialog::getOpenFileName(this,tr("Select CSV"), inputspath, tr("CSV Files (*.csv)"));

    inputspath = QFileInfo(fname).absoluteDir().path();
    qDebug() << "******" << fname;


    /*********
    Inputs files capture
    Is there a better way to conenct multiple signal events triggered by series of buttons to one slot that can take necessart action on the relevance?
    *********/
    if (!fname.isEmpty()){

        if(senderButton == blastHoleInputbrowseButton)
            blastHoleInputLineEdit->setText(fname);
        else if (senderButton == blastDeckInputbrowseButton)
            blastDeckInputLineEdit->setText(fname);
        else if(senderButton == blastMaterialbrowseButton)
            blastMaterialLineEdit->setText(fname);
        else if(senderButton == blastRockInputbrowseButton)
            blastRockInputLineEdit->setText(fname);
        else if(senderButton == blastSurfacebrowseButton)
            blastSurfaceLineEdit->setText(fname);
    }
}

void SimulationGeometryInputs::readblastholecsvfile(QString& filename)
{
    if( !filename.isNull() )
    {
        qDebug() << __FUNCTION__ << __LINE__;
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)) {
            return;
        }

        QTextStream in(&file);
        QMap <QString, int> headerMap;

        QList<BlastHole*> templist;
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (headerMap.isEmpty()) {
                headerMap["Hole ID"] = fields.indexOf("Hole ID");
                headerMap["Collar East (m)"] = fields.indexOf("Collar East (m)");
                headerMap["Collar North (m)"] = fields.indexOf("Collar North (m)");
                headerMap["Collar Level (m)"] = fields.indexOf("Collar Level (m)");
                headerMap["Toe East (m)"] = fields.indexOf("Toe East (m)");
                headerMap["Toe North (m)"] = fields.indexOf("Toe North (m)");
                headerMap["Toe Level (m)"] = fields.indexOf("Toe Level (m)");
                continue;
            }

            BlastHole* item = new BlastHole(fields.at(headerMap["Hole ID"]),
                    fields.at(headerMap["Collar East (m)"]).toDouble(),
                    fields.at(headerMap["Collar North (m)"]).toDouble(),
                    fields.at(headerMap["Collar Level (m)"]).toDouble(),
                    fields.at(headerMap["Toe East (m)"]).toDouble(),
                    fields.at(headerMap["Toe North (m)"]).toDouble(),
                    fields.at(headerMap["Toe Level (m)"]).toDouble(), 200);

            item->setMultiplier(1);
            templist.push_back(item);
        }
        if(templist.size()>0)
           simulationref->setblastholes(templist);

        file.close();
    }
}
