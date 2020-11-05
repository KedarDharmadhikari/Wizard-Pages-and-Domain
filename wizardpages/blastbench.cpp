#include "blastbench.h"
#include "domainmodel/BlastGraphicsRectItem.h"
#include "domainmodel/blastbenchcustomtablemodel.h"
#include <QDebug>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsView>
#include <QTableView>
#include <QFrame>
#include <QPushButton>
#include <QGraphicsItem>
#include <QMenu>
BlastBench::BlastBench(Simulation *currentSimulation,QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Blast Bench Edit"));
    simulationref = currentSimulation;
    dxf = new QCheckBox("DXF");
    openpitmetal= new QCheckBox("OpenPit Metal");
    openpitcoal = new QCheckBox("OpenPit Coal");

    QHBoxLayout* layouthor = new QHBoxLayout();
    layouthor->addWidget(dxf);
    layouthor->addWidget(openpitmetal);
    layouthor->addWidget(openpitcoal);


    North = new QLabel("N");
    topgrpahicsview = new View();
    line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    toegrpahicsview = new View();

    QVBoxLayout* viewlayoutver = new QVBoxLayout();
    viewlayoutver->addWidget(North);
    viewlayoutver->addWidget(topgrpahicsview);
    viewlayoutver->addWidget(line);
    viewlayoutver->addWidget(toegrpahicsview);

    QHBoxLayout* viewlayoutHor = new QHBoxLayout();
    viewlayoutHor->addItem(viewlayoutver);

    QVBoxLayout* tablelayoutver = new QVBoxLayout();
    tableview = new QTableView();

    tablelayoutver->addWidget(tableview);

    clearwallitemsbutton = new QPushButton("Clear Wall Items");
    Edges = new QCheckBox ("Show Only Edges");

    QHBoxLayout* buttonlayouthor = new QHBoxLayout();
    buttonlayouthor->addWidget(Edges);
    buttonlayouthor->addWidget(clearwallitemsbutton);

    tablelayoutver->addItem(buttonlayouthor);

    viewlayoutHor->addItem(tablelayoutver);

    QVBoxLayout* mainlayoutver = new QVBoxLayout();
    mainlayoutver->addItem(layouthor);
    mainlayoutver->addItem(viewlayoutHor);
    setLayout(mainlayoutver);


}

void BlastBench::initializePage()
{
    initalizeWidget();

    setBlastHoles(simulationref->getblastholes());
    double minx,miny,minz,maxx,maxy,maxz;
    getMinAndMax(minx,miny,minz,maxx,maxy,maxz);

    qDebug() << minx << miny << minz << maxx << maxy << maxz ;

}
void BlastBench::addBlastWalls(QList<BlastHole *> northWall, QList<BlastHole *> eastWall, QList<BlastHole *> southWall, QList<BlastHole *> westWall)
{
    m_selectedBlastHoleEastWallPath = QPainterPath();
    m_selectedBlastHoleWestWallPath = QPainterPath();
    m_selectedBlastHoleNorthWallPath = QPainterPath();
    m_selectedBlastHoleSouthWallPath = QPainterPath();


    m_selectedBlastHoleEastWallPathToe = QPainterPath();
    m_selectedBlastHoleWestWallPathToe = QPainterPath();
    m_selectedBlastHoleNorthWallPathToe = QPainterPath();
    m_selectedBlastHoleSouthWallPathToe = QPainterPath();

    m_selectedBlastHoleEastWall.clear();
    m_selectedBlastHoleWestWall.clear();
    m_selectedBlastHoleNorthWall.clear();
    m_selectedBlastHoleSouthWall.clear();


    m_selectedBlastHoleEastWall =eastWall;
    m_selectedBlastHoleWestWall =westWall;
    m_selectedBlastHoleNorthWall =northWall;
    m_selectedBlastHoleSouthWall =southWall;

     foreach (auto curItem, northWall)
     {
        QString holeId = curItem->holeID();
        m_strUserSelectedItem = holeId;
        if (m_blastGraphicsItem.contains(holeId.toInt())) {
            m_currentSelectedItem = m_blastGraphicsItem[holeId.toInt()];
        }
        slotAddSelectedItemToNortBlastWall();
        qDebug() << "NORTH" <<curItem->collarEast_x() << curItem->collarNorth_y() << curItem->offsetCollarEast_x() << curItem->offsetCollarNorth_y();

        m_paintterpathNorth[holeId.toInt()] = QPointF(curItem->collarEast_x()+ curItem->offsetCollarEast_x(), curItem->collarNorth_y()+curItem->offsetCollarNorth_y());
        m_paintterpathNorthToe[holeId.toInt()] = QPointF(curItem->toeEast_x()+ curItem->offsetToeEast_x(), curItem->toeNorth_y()+curItem->offsetToeNorth_y());
    }
    foreach (auto curItem, eastWall)
    {
        QString holeId = curItem->holeID();
        m_strUserSelectedItem = holeId;
        if (m_blastGraphicsItem.contains(holeId.toInt())) {
            m_currentSelectedItem = m_blastGraphicsItem[holeId.toInt()];
        }

        slotAddSelectedItemToEastBlastWall();

        qDebug() << "EAST" <<curItem->collarEast_x() << curItem->collarNorth_y() << curItem->offsetCollarEast_x() << curItem->offsetCollarNorth_y();

        m_paintterpathEast[holeId.toInt()] = QPointF(curItem->collarEast_x()+ curItem->offsetCollarEast_x(), curItem->collarNorth_y()+curItem->offsetCollarNorth_y());
        m_paintterpathEastToe[holeId.toInt()] = QPointF(curItem->toeEast_x()+ curItem->offsetToeEast_x(), curItem->toeNorth_y()+curItem->offsetToeNorth_y());

//        dataHole->updatePosition();

    }
    foreach (auto curItem, southWall) {
        QString holeId = curItem->holeID();
        m_strUserSelectedItem = holeId;
        if (m_blastGraphicsItem.contains(holeId.toInt())) {
            m_currentSelectedItem = m_blastGraphicsItem[holeId.toInt()];
        }
        slotAddSelectedItemToSouthBlastWall();

        qDebug() << "SOUTH" <<curItem->collarEast_x() << curItem->collarNorth_y() << curItem->offsetCollarEast_x() << curItem->offsetCollarNorth_y();


        m_paintterpathSouth[holeId.toInt()] = QPointF(curItem->collarEast_x()+ curItem->offsetCollarEast_x(), curItem->collarNorth_y()+curItem->offsetCollarNorth_y());
        m_paintterpathSouthToe[holeId.toInt()] = QPointF(curItem->toeEast_x()+ curItem->offsetToeEast_x(), curItem->toeNorth_y()+curItem->offsetToeNorth_y());

//        dataHole->updatePosition();


    }
    foreach (auto curItem, westWall) {
        QString holeId = curItem->holeID();
        m_strUserSelectedItem = holeId;
        if (m_blastGraphicsItem.contains(holeId.toInt())) {
            m_currentSelectedItem = m_blastGraphicsItem[holeId.toInt()];
        }
        slotAddSelectedItemToWestBlastWall();
        BlastGraphicsRectItem *dataHole =m_blastGraphicsItem.value(holeId.toInt());

        qDebug() << "WEST" <<curItem->collarEast_x() << curItem->collarNorth_y() << curItem->offsetCollarEast_x() << curItem->offsetCollarNorth_y();


        m_paintterpathWest[holeId.toInt()] = QPointF(curItem->collarEast_x()+ curItem->offsetCollarEast_x(), curItem->collarNorth_y()+curItem->offsetCollarNorth_y());
        m_paintterpathWestToe[holeId.toInt()] = QPointF(curItem->toeEast_x()+ curItem->offsetToeEast_x(), curItem->toeNorth_y()+curItem->offsetToeNorth_y());

//        dataHole->updatePosition();


    }

    createpainterpath();

    topgraphicsscene->update();
    toegraphicsscene->update();

}
void BlastBench::createpainterpath()
{
    m_selectedItemsPath = QPainterPath();

    m_selectedBlastHoleEastWallPath = QPainterPath();
    m_selectedBlastHoleWestWallPath = QPainterPath();
    m_selectedBlastHoleNorthWallPath = QPainterPath();
    m_selectedBlastHoleSouthWallPath = QPainterPath();

    m_selectedItemsPathToe = QPainterPath();
    m_selectedBlastHoleEastWallPathToe = QPainterPath();
    m_selectedBlastHoleWestWallPathToe = QPainterPath();
    m_selectedBlastHoleNorthWallPathToe = QPainterPath();
    m_selectedBlastHoleSouthWallPathToe = QPainterPath();

    qDebug() << __FUNCTION__<< "****START****";

    for (int nCOunt = 0; nCOunt <m_blastEdge.count(); ++nCOunt)
    {

        QPointF dataHole =m_paintterpath.value(m_blastEdge.at(nCOunt));
        QPointF dataHoleToe =m_paintterpathToe.value(m_blastEdge.at(nCOunt));


        qDebug() << m_blastEdge.at(nCOunt);

        if(nCOunt == 0)
        {
            m_selectedItemsPath.moveTo(dataHole.x(),dataHole.y());
            m_selectedItemsPathToe.moveTo(dataHoleToe.x(),dataHoleToe.y());


        }else
        {
            m_selectedItemsPath.lineTo(dataHole.x(),dataHole.y());
            m_selectedItemsPathToe.lineTo(dataHoleToe.x(),dataHoleToe.y());

        }
    }

    for (int nCOunt = 0; nCOunt <m_selectedBlastHoleEastWall.count(); ++nCOunt)
    {

        BlastHole *dataHole1 =m_selectedBlastHoleEastWall.at(nCOunt);
        QPointF dataHole =m_paintterpathEast.value(dataHole1->holeID().toInt());
        QPointF dataHoleToe =m_paintterpathEastToe.value(dataHole1->holeID().toInt());

        if(nCOunt == 0)
        {
            m_selectedBlastHoleEastWallPath.moveTo(dataHole.x(),dataHole.y());
            m_selectedBlastHoleEastWallPathToe.moveTo(dataHoleToe.x(),dataHoleToe.y());


        }else
        {
            m_selectedBlastHoleEastWallPath.lineTo(dataHole.x(),dataHole.y());
            m_selectedBlastHoleEastWallPathToe.lineTo(dataHoleToe.x(),dataHoleToe.y());

        }
    }

    for (int nCOunt = 0; nCOunt <m_selectedBlastHoleWestWall.count(); ++nCOunt)
    {

        BlastHole *dataHole1 =m_selectedBlastHoleWestWall.at(nCOunt);
        QPointF dataHole =m_paintterpathWest.value(dataHole1->holeID().toInt());
        QPointF dataHoleToe =m_paintterpathWestToe.value(dataHole1->holeID().toInt());


        if(nCOunt == 0)
        {
            m_selectedBlastHoleWestWallPath.moveTo(dataHole.x(),dataHole.y());
            m_selectedBlastHoleWestWallPathToe.moveTo(dataHoleToe.x(),dataHoleToe.y());


        }else
        {
            m_selectedBlastHoleWestWallPath.lineTo(dataHole.x(),dataHole.y());
            m_selectedBlastHoleWestWallPathToe.lineTo(dataHoleToe.x(),dataHoleToe.y());

        }
    }

    for (int nCOunt = 0; nCOunt <m_selectedBlastHoleNorthWall.count(); ++nCOunt)
    {

        BlastHole *dataHole1 =m_selectedBlastHoleNorthWall.at(nCOunt);
        QPointF dataHole =m_paintterpathNorth.value(dataHole1->holeID().toInt());
        QPointF dataHoleToe =m_paintterpathNorthToe.value(dataHole1->holeID().toInt());


        if(nCOunt == 0)
        {
            m_selectedBlastHoleNorthWallPath.moveTo(dataHole.x(),dataHole.y());
            m_selectedBlastHoleNorthWallPathToe.moveTo(dataHoleToe.x(),dataHoleToe.y());


        }else
        {
            m_selectedBlastHoleNorthWallPath.lineTo(dataHole.x(),dataHole.y());
            m_selectedBlastHoleNorthWallPathToe.lineTo(dataHole.x(),dataHole.y());

        }
    }

    for (int nCOunt = 0; nCOunt <m_selectedBlastHoleSouthWall.count(); ++nCOunt)
    {

        BlastHole *dataHole1 =m_selectedBlastHoleSouthWall.at(nCOunt);
        QPointF dataHole =m_paintterpathSouth.value(dataHole1->holeID().toInt());
        QPointF dataHoleToe =m_paintterpathSouthToe.value(dataHole1->holeID().toInt());


        if(nCOunt == 0)
        {
            m_selectedBlastHoleSouthWallPath.moveTo(dataHole.x(),dataHole.y());
            m_selectedBlastHoleSouthWallPathToe.moveTo(dataHoleToe.x(),dataHoleToe.y());


        }else
        {
            m_selectedBlastHoleSouthWallPath.lineTo(dataHole.x(),dataHole.y());
            m_selectedBlastHoleSouthWallPathToe.lineTo(dataHoleToe.x(),dataHoleToe.y());

        }
    }

    qDebug() << __FUNCTION__<< "****END****";

    pItem->setPath(m_selectedItemsPath);
    pItem->update();

    pItemEastBlastWall->setPath(m_selectedBlastHoleEastWallPath);
    pItemEastBlastWall->setPen(QColor(Qt::darkRed));
    pItemEastBlastWall->update();

    pItemWestBlastWall->setPath(m_selectedBlastHoleWestWallPath);
    pItemWestBlastWall->setPen(QColor(Qt::darkRed));
    pItemWestBlastWall->update();

    pItemNorthBlastWall->setPath(m_selectedBlastHoleNorthWallPath);
    pItemNorthBlastWall->setPen(QColor(Qt::darkGreen));
    pItemNorthBlastWall->update();

    pItemSouthBlastWall->setPath(m_selectedBlastHoleSouthWallPath);
    pItemSouthBlastWall->setPen(QColor(Qt::darkGreen));
    pItemSouthBlastWall->update();


    pItemToe->setPath(m_selectedItemsPathToe);
    pItemToe->update();

    pItemEastBlastWallToe->setPath(m_selectedBlastHoleEastWallPathToe);
    pItemEastBlastWallToe->setPen(QColor(Qt::darkRed));
    pItemEastBlastWallToe->update();

    pItemWestBlastWallToe->setPath(m_selectedBlastHoleWestWallPathToe);
    pItemWestBlastWallToe->setPen(QColor(Qt::darkRed));
    pItemWestBlastWallToe->update();

    pItemNorthBlastWallToe->setPath(m_selectedBlastHoleNorthWallPathToe);
    pItemNorthBlastWallToe->setPen(QColor(Qt::darkGreen));
    pItemNorthBlastWallToe->update();

    pItemSouthBlastWallToe->setPath(m_selectedBlastHoleSouthWallPathToe);
    pItemSouthBlastWallToe->setPen(QColor(Qt::darkGreen));
    pItemSouthBlastWallToe->update();


    topgraphicsscene->update();
    toegraphicsscene->update();

}
void BlastBench::modifySceneRect(double minX, double maxX, double minY, double maxY)
{
    double width = (maxX - minX) + 200;
    double height = (maxY - minY) + 200;
    topgraphicsscene->setSceneRect((minX-100), (minY-100), width, height);
    toegraphicsscene->setSceneRect((minX-100), (minY-100), width, height);
}
void BlastBench::setBlastHoles(const QList<BlastHole *> &blastHoles)
{
    m_blastHoles = blastHoles;
    for(int i=0; i<m_blastHoles.count(); ++i)
    {
        m_mapBlastHoleData.insert(m_blastHoles.at(i)->holeID().toInt(),m_blastHoles.at(i));
        BlastGraphicsRectItem* item = new BlastGraphicsRectItem(m_blastHoles.at(i));
        BlastGraphicsRectItem* itemToe = new BlastGraphicsRectItem(m_blastHoles.at(i));

        connect(item,SIGNAL(sigClickedHoleId(QString)),this,SLOT(slotSelectedItem(QString)));
        connect(itemToe,SIGNAL(sigClickedHoleId(QString)),this,SLOT(slotSelectedItem(QString)));

        item->setAcceptHoverEvents(true);
        itemToe->setAcceptHoverEvents(true);

        //        m_blastGraphicsItem.append(item);
        m_blastGraphicsItem.insert(m_blastHoles.at(i)->holeID().toInt(),item);
        m_blastGraphicsItemToe.insert(m_blastHoles.at(i)->holeID().toInt(),itemToe);

        topgraphicsscene->addItem(item);
        toegraphicsscene->addItem(itemToe);

    }
    m_Model->setBlastHoleMap(m_mapBlastHoleData);
}

void BlastBench::showDialogItem()
{
    clearwallitemsbutton->show();
}

QList<BlastHole *> BlastBench::getSelectedBlastHoleWestWall() const
{
    return m_selectedBlastHoleWestWall;
}

QList<BlastHole *> BlastBench::getSelectedBlastHoleSouthWall() const
{
    return m_selectedBlastHoleSouthWall;
}

QList<BlastHole *> BlastBench::getSelectedBlastHoleEastWall() const
{
    return m_selectedBlastHoleEastWall;
}

QList<BlastHole *> BlastBench::getSelectedBlastHoleNorthWall() const
{
    return m_selectedBlastHoleNorthWall;
}

void BlastBench::clearModel()
{
    m_blastHoles.clear();
    m_selectedEdgeHoleList.clear();

    m_cubeSize = 1;

    QMap<int, BlastHole*>  empty_mapData;
    m_Model->setBlastHoleMap(empty_mapData);
    m_mapBlastHoleData.clear();
    m_blastGraphicsItem.clear();
    m_blastGraphicsItemToe.clear();

    m_bSelectHoles =false;

    m_paintterpath.clear();
    m_paintterpathToe.clear();

    m_strUserSelectedItem = QString();
    m_blastEdge.clear();

    m_paintterpathEast.clear();
    m_paintterpathWest.clear();
    m_paintterpathNorth.clear();
    m_paintterpathSouth.clear();

    m_paintterpathEastToe.clear();
    m_paintterpathWestToe.clear();
    m_paintterpathNorthToe.clear();
    m_paintterpathSouthToe.clear();

    m_currentSelectedItem = nullptr;

    m_selectedBlastHoleEastWall.clear();
    m_selectedBlastHoleWestWall.clear();
    m_selectedBlastHoleNorthWall.clear();
    m_selectedBlastHoleSouthWall.clear();

    m_selectedItemsPath = QPainterPath();
    m_selectedBlastHoleEastWallPath = QPainterPath();
    m_selectedBlastHoleWestWallPath = QPainterPath();
    m_selectedBlastHoleNorthWallPath = QPainterPath();
    m_selectedBlastHoleSouthWallPath = QPainterPath();

    m_selectedItemsPathToe = QPainterPath();
    m_selectedBlastHoleEastWallPathToe = QPainterPath();
    m_selectedBlastHoleWestWallPathToe = QPainterPath();
    m_selectedBlastHoleNorthWallPathToe = QPainterPath();
    m_selectedBlastHoleSouthWallPathToe = QPainterPath();

}

void BlastBench::slotSelectedItem(QString i_strSelectedItem)
{
    BlastGraphicsRectItem* curItem = dynamic_cast<BlastGraphicsRectItem*>(sender());
    if (curItem) {
        m_currentSelectedItem = curItem;
        qDebug() << m_currentSelectedItem->getBlastHole()->holeID();
    }


    m_strUserSelectedItem = i_strSelectedItem;

    if(i_strSelectedItem.length()>0)
    {
        QMenu *menu = new QMenu(topgrpahicsview);
        QMenu* submenuAdd = menu->addMenu( "Add" );
        QMenu* submenuRemove = menu->addMenu( "Remove" );

//        if(m_paintterpath.keys().contains(i_strSelectedItem.toInt()))
//        {
//            submenuRemove->addAction(QString("Remove Item From Blast Edge"), this, SLOT(slotRemoveSelectedItemMouseAction()));

//        }else
//        {
//            submenuAdd->addAction(QString("Add Item to Blast Edge"), this, SLOT(slotSelectedItemMouseAction()));
//        }

        bool bState=false;
        for ( BlastHole *data : m_selectedBlastHoleEastWall)
        {

            if(data->holeID() == i_strSelectedItem)
            {
                bState=true;
                break;
            }

        }

        if(bState)
        {
            submenuRemove->addAction(QString("Remove Item From East Blast Wall"), this, SLOT(slotRemoveSelectedItemFromEastBlastWall()));
        }else
        {
            submenuAdd->addAction(QString("Add Item to East Blast Wall"), this,  SLOT(slotAddSelectedItemToEastBlastWall()));
        }

        bState =false;

        for ( BlastHole *data : m_selectedBlastHoleWestWall)
        {

            if(data->holeID() == i_strSelectedItem)
            {
                bState=true;
                break;
            }

        }

        if(bState)
        {
            submenuRemove->addAction(QString("Remove Item From West Blast Wall"), this, SLOT(slotRemoveSelectedItemFromWestBlastWall()));

        }else
        {
            submenuAdd->addAction(QString("Add Item to West Blast Wall"), this,  SLOT(slotAddSelectedItemToWestBlastWall()));
        }
        bState =false;

        for ( BlastHole *data : m_selectedBlastHoleNorthWall)
        {

            if(data->holeID() == i_strSelectedItem)
            {
                bState=true;
                break;
            }

        }

        if(bState)
        {
            submenuRemove->addAction(QString("Remove Item From North Blast Wall"), this, SLOT(slotRemoveSelectedItemFromNortBlastWall()));

        }else
        {
            submenuAdd->addAction(QString("Add Item to North Blast Wall"), this, SLOT(slotAddSelectedItemToNortBlastWall()));
        }

        bState =false;

        for ( BlastHole *data : m_selectedBlastHoleSouthWall)
        {

            if(data->holeID() == i_strSelectedItem)
            {
                bState=true;
                break;
            }

        }

        if(bState)
        {
            submenuRemove->addAction(QString("Remove Item From South Blast Wall"), this, SLOT(slotRemoveSelectedItemFromSouthBlastWall()));

        }else
        {
            submenuAdd->addAction(QString("Add Item to South Blast Wall"), this, SLOT(slotAddSelectedItemToSouthBlastWall()));
        }

        if(m_paintterpath.keys().count()>1)
        {

            menu->addAction(QString("Blast Edge Selection Finish"), this, SLOT(sloFinishBlastEdgeSelection()));
        }

        menu->exec(QCursor::pos());
    }
}

void BlastBench::slotDataChanged( QModelIndex topLeft)
{
    //qDebug()<< topLeft.row()<< topLeft.column();

    double val=m_Model->index(topLeft.row(),topLeft.column()).data(Qt::DisplayRole).toDouble();
    // qDebug()<< topLeft.row()<< topLeft.column() << "val" << val;
    int holeid=m_Model->index(topLeft.row(),0).data(Qt::DisplayRole).toInt();
    BlastGraphicsRectItem *dataHole =m_blastGraphicsItem.value(holeid);
    BlastGraphicsRectItem *dataHoleToe =m_blastGraphicsItemToe.value(holeid);

    qDebug() <<__FUNCTION__ << m_paintterpath.value(holeid).x() << dataHole->getBlastHole()->offsetToeEast_x() <<   m_paintterpath.value(holeid).y()<< dataHole->getBlastHole()->offsetToeNorth_y();

    switch (topLeft.column()) {
        case 1:
        {
           dataHole->getBlastHole()->setCollarEast_x(val);
           dataHoleToe->getBlastHole()->setCollarEast_x(val);

           if(m_paintterpath.contains(holeid))
           {
               m_paintterpath[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x(), val);

           }
            if(m_paintterpathEast.contains(holeid))
            {
                m_paintterpathEast[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x(), val);
                m_paintterpathEastToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x(), val);


            }

            if(m_paintterpathWest.contains(holeid))
            {
                m_paintterpathWest[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x(), val);
                m_paintterpathWestToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x(), val);

            }

            if(m_paintterpathNorth.contains(holeid))
            {
                m_paintterpathNorth[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x(), val);
                m_paintterpathNorthToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x(), val);


            }


            if(m_paintterpathSouth.contains(holeid))
            {
                m_paintterpathSouth[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x(), val);
                m_paintterpathSouthToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x(), val);

            }



        }
            break;
        case 2:
        {
            dataHole->getBlastHole()->setCollarNorth_y(val);
            dataHoleToe->getBlastHole()->setCollarNorth_y(val);

            if(m_paintterpath.contains(holeid))
            {
                m_paintterpath[holeid] = QPointF(val,dataHole->getBlastHole()->collarNorth_y());

            }
             if(m_paintterpathEast.contains(holeid))
             {
                 m_paintterpathEast[holeid] = QPointF(val,dataHole->getBlastHole()->collarNorth_y());
                 m_paintterpathEastToe[holeid] = QPointF(val,dataHole->getBlastHole()->toeNorth_y());


             }

             if(m_paintterpathWest.contains(holeid))
             {
                 m_paintterpathWest[holeid] = QPointF(val,dataHole->getBlastHole()->collarNorth_y());
                 m_paintterpathWestToe[holeid] = QPointF(val,dataHole->getBlastHole()->toeNorth_y());


             }

             if(m_paintterpathNorth.contains(holeid))
             {
                 m_paintterpathNorth[holeid] = QPointF(val,dataHole->getBlastHole()->collarNorth_y());
                 m_paintterpathNorthToe[holeid] = QPointF(val,dataHole->getBlastHole()->toeNorth_y());

             }


             if(m_paintterpathSouth.contains(holeid))
             {
                 m_paintterpathSouth[holeid] = QPointF(val,dataHole->getBlastHole()->collarNorth_y());
                 m_paintterpathSouthToe[holeid] = QPointF(val,dataHole->getBlastHole()->toeNorth_y());


             }


        }
            break;
        case 3:
        {
            dataHole->getBlastHole()->setOffsetCollarEast_x(val);


            if(m_paintterpath.contains(holeid))
            {
                m_paintterpath[holeid] =QPointF(dataHole->getBlastHole()->collarEast_x()+ dataHole->getBlastHole()->offsetCollarEast_x(), dataHole->getBlastHole()->collarNorth_y()+dataHole->getBlastHole()->offsetCollarNorth_y());

            }
             if(m_paintterpathEast.contains(holeid))
             {
                 m_paintterpathEast[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x()+ dataHole->getBlastHole()->offsetCollarEast_x(), dataHole->getBlastHole()->collarNorth_y()+dataHole->getBlastHole()->offsetCollarNorth_y());

             }

             if(m_paintterpathWest.contains(holeid))
             {
                 m_paintterpathWest[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x()+ dataHole->getBlastHole()->offsetCollarEast_x(), dataHole->getBlastHole()->collarNorth_y()+dataHole->getBlastHole()->offsetCollarNorth_y());

             }

             if(m_paintterpathNorth.contains(holeid))
             {
                 m_paintterpathNorth[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x()+ dataHole->getBlastHole()->offsetCollarEast_x(), dataHole->getBlastHole()->collarNorth_y()+dataHole->getBlastHole()->offsetCollarNorth_y());

             }


             if(m_paintterpathSouth.contains(holeid))
             {
                 m_paintterpathSouth[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x()+ dataHole->getBlastHole()->offsetCollarEast_x(), dataHole->getBlastHole()->collarNorth_y()+dataHole->getBlastHole()->offsetCollarNorth_y());

             }

             dataHole->updatePosition();

        }
            break;
        case 4:
        {
            dataHole->getBlastHole()->setOffsetCollarNorth_y(val);



            if(m_paintterpath.contains(holeid))
            {
                m_paintterpath[holeid] =QPointF(dataHole->getBlastHole()->collarEast_x()+ dataHole->getBlastHole()->offsetCollarEast_x(), dataHole->getBlastHole()->collarNorth_y()+dataHole->getBlastHole()->offsetCollarNorth_y());

            }
             if(m_paintterpathEast.contains(holeid))
             {
                 m_paintterpathEast[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x()+ dataHole->getBlastHole()->offsetCollarEast_x(), dataHole->getBlastHole()->collarNorth_y()+dataHole->getBlastHole()->offsetCollarNorth_y());

             }

             if(m_paintterpathWest.contains(holeid))
             {
                 m_paintterpathWest[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x()+ dataHole->getBlastHole()->offsetCollarEast_x(), dataHole->getBlastHole()->collarNorth_y()+dataHole->getBlastHole()->offsetCollarNorth_y());

             }

             if(m_paintterpathNorth.contains(holeid))
             {
                 m_paintterpathNorth[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x()+ dataHole->getBlastHole()->offsetCollarEast_x(), dataHole->getBlastHole()->collarNorth_y()+dataHole->getBlastHole()->offsetCollarNorth_y());

             }


             if(m_paintterpathSouth.contains(holeid))
             {
                 m_paintterpathSouth[holeid] = QPointF(dataHole->getBlastHole()->collarEast_x()+ dataHole->getBlastHole()->offsetCollarEast_x(), dataHole->getBlastHole()->collarNorth_y()+dataHole->getBlastHole()->offsetCollarNorth_y());

             }


             dataHole->updatePosition();

        }
            break;
        case 5:
         {
            dataHoleToe->getBlastHole()->setOffsetToeEast_x(val);

            if(m_paintterpathToe.contains(holeid))
            {
                m_paintterpathToe[holeid] =QPointF(dataHole->getBlastHole()->toeEast_x()+ dataHole->getBlastHole()->offsetToeEast_x(), dataHole->getBlastHole()->toeNorth_y()+dataHole->getBlastHole()->offsetToeNorth_y());

            }
             if(m_paintterpathEastToe.contains(holeid))
             {
                 m_paintterpathEastToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x()+ dataHole->getBlastHole()->offsetToeEast_x(), dataHole->getBlastHole()->toeNorth_y()+dataHole->getBlastHole()->offsetToeNorth_y());

             }

             if(m_paintterpathWestToe.contains(holeid))
             {
                 m_paintterpathWestToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x()+ dataHole->getBlastHole()->offsetToeEast_x(), dataHole->getBlastHole()->toeNorth_y()+dataHole->getBlastHole()->offsetToeNorth_y());

             }

             if(m_paintterpathNorthToe.contains(holeid))
             {
                 m_paintterpathNorthToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x()+ dataHole->getBlastHole()->offsetToeEast_x(), dataHole->getBlastHole()->toeNorth_y()+dataHole->getBlastHole()->offsetToeNorth_y());

             }


             if(m_paintterpathSouthToe.contains(holeid))
             {
                 m_paintterpathSouthToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x()+ dataHole->getBlastHole()->offsetToeEast_x(), dataHole->getBlastHole()->toeNorth_y()+dataHole->getBlastHole()->offsetToeNorth_y());

             }

            dataHoleToe->updateToePosition();

         }
            break;
        case 6:
        {
            dataHoleToe->getBlastHole()->setOffsetToeNorth_y(val);


            if(m_paintterpathToe.contains(holeid))
            {
                m_paintterpathToe[holeid] =QPointF(dataHole->getBlastHole()->toeEast_x()+ dataHole->getBlastHole()->offsetToeEast_x(), dataHole->getBlastHole()->toeNorth_y()+dataHole->getBlastHole()->offsetToeNorth_y());

            }
             if(m_paintterpathEastToe.contains(holeid))
             {
                 m_paintterpathEastToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x()+ dataHole->getBlastHole()->offsetToeEast_x(), dataHole->getBlastHole()->toeNorth_y()+dataHole->getBlastHole()->offsetToeNorth_y());

             }

             if(m_paintterpathWestToe.contains(holeid))
             {
                 m_paintterpathWestToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x()+ dataHole->getBlastHole()->offsetToeEast_x(), dataHole->getBlastHole()->toeNorth_y()+dataHole->getBlastHole()->offsetToeNorth_y());

             }

             if(m_paintterpathNorthToe.contains(holeid))
             {
                 m_paintterpathNorthToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x()+ dataHole->getBlastHole()->offsetToeEast_x(), dataHole->getBlastHole()->toeNorth_y()+dataHole->getBlastHole()->offsetToeNorth_y());

             }


             if(m_paintterpathSouthToe.contains(holeid))
             {
                 m_paintterpathSouthToe[holeid] = QPointF(dataHole->getBlastHole()->toeEast_x()+ dataHole->getBlastHole()->offsetToeEast_x(), dataHole->getBlastHole()->toeNorth_y()+dataHole->getBlastHole()->offsetToeNorth_y());

             }

            dataHoleToe->updateToePosition();

        }
        break;
        default:
            break;
        }


    //    qDebug() <<__FUNCTION__ << dataHole->getBlastHole()->collarEast_x()<<  dataHole->getBlastHole()->collarNorth_y() ;
    //    qDebug() <<__FUNCTION__ << dataHole->getBlastHole()->collarEast_x()+dataHole->getBlastHole()->offsetToeEast_x() <<  dataHole->getBlastHole()->collarNorth_y()+dataHole->getBlastHole()->offsetToeNorth_y();
    //    qDebug() <<__FUNCTION__ << m_paintterpath.value(holeid).x() << dataHole->getBlastHole()->offsetToeEast_x() <<   m_paintterpath.value(holeid).y()<< dataHole->getBlastHole()->offsetToeNorth_y();

    topgraphicsscene->update();
    toegraphicsscene->update();

    createpainterpath();
}

void BlastBench::slotRemoveSelectedItemFromEastBlastWall()
{

    int i_strItem=m_strUserSelectedItem.toInt();
    m_paintterpathEast.remove(i_strItem);
    m_selectedBlastHoleEastWall.removeOne(m_currentSelectedItem->getBlastHole());
    createpainterpath();

}

void BlastBench::slotRemoveSelectedItemFromWestBlastWall()
{
    int i_strItem=m_strUserSelectedItem.toInt();
    m_paintterpathWest.remove(i_strItem);
    m_selectedBlastHoleWestWall.removeOne(m_currentSelectedItem->getBlastHole());
    createpainterpath();

}

void BlastBench::slotRemoveSelectedItemFromNortBlastWall()
{

    int i_strItem=m_strUserSelectedItem.toInt();
    m_paintterpathNorth.remove(i_strItem);
    m_selectedBlastHoleNorthWall.removeOne(m_currentSelectedItem->getBlastHole());
    createpainterpath();

}

void BlastBench::slotRemoveSelectedItemFromSouthBlastWall()
{
    int i_strItem=m_strUserSelectedItem.toInt();
    m_paintterpathSouth.remove(i_strItem);
    m_selectedBlastHoleSouthWall.removeOne(m_currentSelectedItem->getBlastHole());
    createpainterpath();
}
void BlastBench::slotAddSelectedItemToEastBlastWall()
{
    QString i_strSelectedItem=m_strUserSelectedItem;

    for (int nRowCOunt = 0; nRowCOunt < m_Model->rowCount(); ++nRowCOunt)
    {

        QString strHoleId= m_Model->index(nRowCOunt,0).data(Qt::DisplayRole).toString();

        if(strHoleId == i_strSelectedItem)
        {
            tableview->selectRow(nRowCOunt);

            BlastGraphicsRectItem *dataHole =m_blastGraphicsItem.value(strHoleId.toInt());
            BlastGraphicsRectItem *dataHoleToe =m_blastGraphicsItemToe.value(strHoleId.toInt());


            m_paintterpathEast.insert(i_strSelectedItem.toInt(),QPointF(dataHole->getBlastHole()->collarEast_x(),dataHole->getBlastHole()->collarNorth_y()));
            m_paintterpathEastToe.insert(i_strSelectedItem.toInt(),QPointF(dataHoleToe->getBlastHole()->toeEast_x(),dataHoleToe->getBlastHole()->toeNorth_y()));

            if (!m_selectedBlastHoleEastWall.contains(m_currentSelectedItem->getBlastHole()))
                m_selectedBlastHoleEastWall.append(m_currentSelectedItem->getBlastHole());
            dataHole->updateSelectedItemPosition();
            dataHoleToe->updateSelectedItemPosition();


            break;
        }

    }

    createpainterpath();
}

void BlastBench::slotAddSelectedItemToWestBlastWall()
{
    QString i_strSelectedItem=m_strUserSelectedItem;

    for (int nRowCOunt = 0; nRowCOunt < m_Model->rowCount(); ++nRowCOunt)
    {

        QString strHoleId= m_Model->index(nRowCOunt,0).data(Qt::DisplayRole).toString();

        if(strHoleId == i_strSelectedItem)
        {
            tableview->selectRow(nRowCOunt);

            BlastGraphicsRectItem *dataHole =m_blastGraphicsItem.value(strHoleId.toInt());
            BlastGraphicsRectItem *dataHoleToe =m_blastGraphicsItemToe.value(strHoleId.toInt());

            m_paintterpathWest.insert(i_strSelectedItem.toInt(),QPointF(dataHole->getBlastHole()->collarEast_x(),dataHole->getBlastHole()->collarNorth_y()));
            m_paintterpathWestToe.insert(i_strSelectedItem.toInt(),QPointF(dataHoleToe->getBlastHole()->toeEast_x(),dataHoleToe->getBlastHole()->toeNorth_y()));

            if (!m_selectedBlastHoleWestWall.contains(m_currentSelectedItem->getBlastHole()))
                m_selectedBlastHoleWestWall.append(m_currentSelectedItem->getBlastHole());

            dataHole->updateSelectedItemPosition();
            dataHoleToe->updateSelectedItemPosition();

            break;
        }

    }
    createpainterpath();

}

void BlastBench::slotAddSelectedItemToNortBlastWall()
{

    QString i_strSelectedItem=m_strUserSelectedItem;

    for (int nRowCOunt = 0; nRowCOunt < m_Model->rowCount(); ++nRowCOunt)
    {

        QString strHoleId= m_Model->index(nRowCOunt,0).data(Qt::DisplayRole).toString();

        if(strHoleId == i_strSelectedItem)
        {
            tableview->selectRow(nRowCOunt);

            BlastGraphicsRectItem *dataHole =m_blastGraphicsItem.value(strHoleId.toInt());
            BlastGraphicsRectItem *dataHoleToe =m_blastGraphicsItemToe.value(strHoleId.toInt());


            m_paintterpathNorth.insert(i_strSelectedItem.toInt(),QPointF(dataHole->getBlastHole()->collarEast_x(),dataHole->getBlastHole()->collarNorth_y()));
            m_paintterpathNorthToe.insert(i_strSelectedItem.toInt(),QPointF(dataHoleToe->getBlastHole()->toeEast_x(),dataHoleToe->getBlastHole()->toeNorth_y()));

            if (!m_selectedBlastHoleNorthWall.contains(m_currentSelectedItem->getBlastHole()))
                m_selectedBlastHoleNorthWall.append(m_currentSelectedItem->getBlastHole());
            dataHole->updateSelectedItemPosition();
            dataHoleToe->updateSelectedItemPosition();


            break;
        }

    }
    createpainterpath();
}

void BlastBench::slotAddSelectedItemToSouthBlastWall()
{
    QString i_strSelectedItem=m_strUserSelectedItem;

    for (int nRowCOunt = 0; nRowCOunt < m_Model->rowCount(); ++nRowCOunt)
    {
        tableview->selectRow(nRowCOunt);

        QString strHoleId= m_Model->index(nRowCOunt,0).data(Qt::DisplayRole).toString();

        if(strHoleId == i_strSelectedItem)
        {
            BlastGraphicsRectItem *dataHole =m_blastGraphicsItem.value(strHoleId.toInt());
            BlastGraphicsRectItem *dataHoleToe =m_blastGraphicsItemToe.value(strHoleId.toInt());
            m_paintterpathSouth.insert(i_strSelectedItem.toInt(),QPointF(dataHole->getBlastHole()->collarEast_x(),dataHole->getBlastHole()->collarNorth_y()));
            m_paintterpathSouthToe.insert(i_strSelectedItem.toInt(),QPointF(dataHoleToe->getBlastHole()->toeEast_x(),dataHoleToe->getBlastHole()->toeNorth_y()));
            if (!m_selectedBlastHoleSouthWall.contains(m_currentSelectedItem->getBlastHole()))
                m_selectedBlastHoleSouthWall.append(m_currentSelectedItem->getBlastHole());

            dataHole->updateSelectedItemPosition();
            dataHoleToe->updateSelectedItemPosition();

            break;
        }

    }

    createpainterpath();

}
void BlastBench::on_m_pbClearWallItems_clicked()
{
    m_selectedBlastHoleEastWall.clear();
    m_selectedBlastHoleWestWall.clear();
    m_selectedBlastHoleNorthWall.clear();
    m_selectedBlastHoleSouthWall.clear();

    m_selectedBlastHoleEastWallPath = QPainterPath();
    m_selectedBlastHoleWestWallPath = QPainterPath();
    m_selectedBlastHoleNorthWallPath = QPainterPath();
    m_selectedBlastHoleSouthWallPath = QPainterPath();

    m_selectedBlastHoleEastWallPathToe = QPainterPath();
    m_selectedBlastHoleWestWallPathToe = QPainterPath();
    m_selectedBlastHoleNorthWallPathToe = QPainterPath();
    m_selectedBlastHoleSouthWallPathToe = QPainterPath();


    m_paintterpathEast.clear();
    m_paintterpathWest.clear();
    m_paintterpathNorth.clear();
    m_paintterpathSouth.clear();


    m_paintterpathEastToe.clear();
    m_paintterpathWestToe.clear();
    m_paintterpathNorthToe.clear();
    m_paintterpathSouthToe.clear();

    topgraphicsscene->update();
    toegraphicsscene->update();
}

void BlastBench::on_m_pbApply_clicked()
{
    emit sigPainterPath(m_selectedItemsPath);
    m_selectedEdgeHoleList.clear();
    m_selectedEdgeHoleList.append(m_selectedBlastHoleNorthWall);
    if (m_selectedBlastHoleEastWall.count() && m_selectedEdgeHoleList.contains(m_selectedBlastHoleEastWall.at(0)))
        m_selectedEdgeHoleList.removeOne(m_selectedBlastHoleEastWall.at(0));
    m_selectedEdgeHoleList.append(m_selectedBlastHoleEastWall);

    if (m_selectedBlastHoleSouthWall.count() && m_selectedEdgeHoleList.contains(m_selectedBlastHoleSouthWall.at(0)))
        m_selectedEdgeHoleList.removeOne(m_selectedBlastHoleSouthWall.at(0));
    m_selectedEdgeHoleList.append(m_selectedBlastHoleSouthWall);

    if (m_selectedBlastHoleWestWall.count() && m_selectedEdgeHoleList.contains(m_selectedBlastHoleWestWall.at(0)))
        m_selectedEdgeHoleList.removeOne(m_selectedBlastHoleWestWall.at(0));
    m_selectedEdgeHoleList.append(m_selectedBlastHoleWestWall);

    emit sigBlastWallsEastWestNorthSouth(m_selectedBlastHoleEastWall,
    m_selectedBlastHoleWestWall,
    m_selectedBlastHoleNorthWall,
    m_selectedBlastHoleSouthWall);

    emit sigBlastHoleList(m_selectedEdgeHoleList);

    qDebug() << "total holes selected are " << m_selectedEdgeHoleList.count();
    qDebug() << "total holes east  wall  are " << m_selectedBlastHoleEastWall.count();
    qDebug() << "total holes west wall are " << m_selectedBlastHoleWestWall.count();
    qDebug() << "total holes north wall are " << m_selectedBlastHoleNorthWall.count();
    qDebug() << "total holes south wall are " << m_selectedBlastHoleSouthWall.count();

    this->close();
}

void BlastBench::on_checkBox_clicked(bool checked)
{
    // if checked only show the edges

    if (checked) {
        QList<BlastHole*> allHoles = getUniqueListOfSelectedHoles();
        QStringList selectedHolesList;
        for(int i=0; i<allHoles.count(); ++i)
        {
            selectedHolesList << allHoles.at(i)->holeID();
        }
        for (int nRowCOunt = 0; nRowCOunt < m_Model->rowCount(); ++nRowCOunt)
        {
            QString strHoleId= m_Model->index(nRowCOunt,0).data(Qt::DisplayRole).toString();
            if (!selectedHolesList.contains(strHoleId)) {
                tableview->hideRow(nRowCOunt);
            } else
                tableview->showRow(nRowCOunt);
        }


    } else {
        for (int nRowCOunt = 0; nRowCOunt < m_Model->rowCount(); ++nRowCOunt)
        {
            tableview->showRow(nRowCOunt);
        }
    }
}

void BlastBench::initalizeWidget()
{
    topgraphicsscene = new QGraphicsScene(topgrpahicsview);
    topgrpahicsview->scale(1, -1);
    toegraphicsscene = new QGraphicsScene(toegrpahicsview);
    toegrpahicsview->scale(1, -1);
    m_selectedItemsPath = QPainterPath();
    //connect(topgraphicsscene,SIGNAL(sigMousePressEvent(QPointF)),this,SLOT(slotMousePressEvent(QPointF)));
    topgrpahicsview->setScene(topgraphicsscene);
    topgrpahicsview->setMouseTracking(true);
    toegrpahicsview->setScene(toegraphicsscene);
    toegrpahicsview->setMouseTracking(true);

    m_Model = new BlastBenchCustomTableModel(this);

    connect(m_Model,SIGNAL(sigDataChanged( QModelIndex )),
            this,SLOT(slotDataChanged( QModelIndex )));
    //having 100 margins all the sides

    tableview->setSortingEnabled(true);
    tableview->sortByColumn(0,Qt::AscendingOrder);

    tableview->setSelectionMode(QTableView::MultiSelection);
    tableview->setSelectionBehavior(QTableView::SelectRows);

    tableview->sortByColumn(0,Qt::AscendingOrder);
    m_Model->setBlastHoleMap(m_mapBlastHoleData);
    tableview->setModel(m_Model);

    pItem  = new QGraphicsPathItem();
    topgraphicsscene->addItem(pItem);


    pItemEastBlastWall  = new QGraphicsPathItem();
    topgraphicsscene->addItem(pItemEastBlastWall);

    pItemWestBlastWall  = new QGraphicsPathItem();
    topgraphicsscene->addItem(pItemWestBlastWall);

    pItemNorthBlastWall  = new QGraphicsPathItem();
    topgraphicsscene->addItem(pItemNorthBlastWall);

    pItemSouthBlastWall  = new QGraphicsPathItem();
    topgraphicsscene->addItem(pItemSouthBlastWall);


    pItemToe  = new QGraphicsPathItem();
    toegraphicsscene->addItem(pItemToe);


    pItemEastBlastWallToe  = new QGraphicsPathItem();
    toegraphicsscene->addItem(pItemEastBlastWallToe);

    pItemWestBlastWallToe  = new QGraphicsPathItem();
    toegraphicsscene->addItem(pItemWestBlastWallToe);

    pItemNorthBlastWallToe  = new QGraphicsPathItem();
    toegraphicsscene->addItem(pItemNorthBlastWallToe);

    pItemSouthBlastWallToe  = new QGraphicsPathItem();
    toegraphicsscene->addItem(pItemSouthBlastWallToe);

    topgrpahicsview->fitInView(topgrpahicsview->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
    //toe
    toegrpahicsview->fitInView(toegrpahicsview->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}

QList<BlastHole *> BlastBench::getUniqueListOfSelectedHoles()
{
    QList<BlastHole *> all;
    all.append(m_selectedBlastHoleNorthWall);
    for(int i=0; i<m_selectedBlastHoleEastWall.count(); i++) {
        BlastHole* cur = m_selectedBlastHoleEastWall.at(i);
        if (!all.contains(cur)) {
            all.append(cur);
        }
    }

    for(int i=0; i<m_selectedBlastHoleWestWall.count(); i++) {
        BlastHole* cur = m_selectedBlastHoleWestWall.at(i);
        if (!all.contains(cur)) {
            all.append(cur);
        }
    }
    for(int i=0; i<m_selectedBlastHoleSouthWall.count(); i++) {
        BlastHole* cur = m_selectedBlastHoleSouthWall.at(i);
        if (!all.contains(cur)) {
            all.append(cur);
        }
    }

    return all;
}

void BlastBench::getMinAndMax(double &minX, double &minY, double &minZ, double &maxX, double &maxY, double &maxZ)
{
    minX = std::numeric_limits<double>::max();
    minY = std::numeric_limits<double>::max();
    minZ = std::numeric_limits<double>::max();
    maxX = std::numeric_limits<double>::min();
    maxY = std::numeric_limits<double>::min();
    maxZ = std::numeric_limits<double>::min();

    for(int i=0; i<m_blastHoles.count(); ++i) {
        BlastHole* curItem = m_blastHoles.at(i);
        if (curItem->collarEast_x() < minX || curItem->toeEast_x() < minX || minX == std::numeric_limits<double>::max())
            minX = curItem->collarEast_x() < curItem->toeEast_x() ? curItem->collarEast_x() : curItem->toeEast_x();

        if (curItem->collarNorth_y() < minY || curItem->toeNorth_y() < minY || minY == std::numeric_limits<double>::max())
            minY = curItem->collarNorth_y() < curItem->toeNorth_y() ? curItem->collarNorth_y() : curItem->toeNorth_y();

        if (curItem->collarLevel_z() < minZ || curItem->toeLevel_z() < minZ || minZ == std::numeric_limits<double>::max())
            minZ = curItem->collarLevel_z() < curItem->toeLevel_z() ? curItem->collarLevel_z() : curItem->toeLevel_z();

        if (curItem->collarEast_x() > maxX || curItem->toeEast_x() > maxX || maxX == std::numeric_limits<double>::min())
            maxX = curItem->collarEast_x() > curItem->toeEast_x() ? curItem->collarEast_x() : curItem->toeEast_x();

        if (curItem->collarNorth_y() > maxY || curItem->toeNorth_y() > maxY || maxY == std::numeric_limits<double>::min())
            maxY = curItem->collarNorth_y() > curItem->toeNorth_y() ? curItem->collarNorth_y() : curItem->toeNorth_y();

        if (curItem->collarLevel_z() > minZ || curItem->toeLevel_z() > maxZ || maxZ == std::numeric_limits<double>::min())
            maxZ = curItem->collarLevel_z() > curItem->toeLevel_z() ? curItem->collarLevel_z() : curItem->toeLevel_z();
    }

    qDebug() << "minx "<<minX<<" minY "<<minY<<" minz "<<minZ<<" maxX "<<maxX<<" maxY "<<maxY<<" maxZ "<<maxZ ;
}

