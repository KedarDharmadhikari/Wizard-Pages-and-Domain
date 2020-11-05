#ifndef BLASTBENCH_H
#define BLASTBENCH_H
#include <simulationmasters/simulationmasterdetails.h>
#include <domainmodel/simulation.h>
#include<QWizard>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QQueue>
#include <QModelIndex>

class QCheckBox;
class QLabel;
class QGraphicsView;
class QTableView;
class QFrame;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class BlastGraphicsRectItem;
class BlastBenchCustomTableModel;
class QGraphicsPathItem;

class View : public QGraphicsView
{
    Q_OBJECT

public:

    explicit View(QWidget *parent = nullptr) : QGraphicsView(parent)
    {
        //setDragMode(QGraphicsView::ScrollHandDrag);
    }

protected Q_SLOTS:

    void wheelEvent(QWheelEvent *event)
    {
        if(event->delta() > 0)
            scale(1.25, 1.25);
        else
            scale(0.8, 0.8);
    }

    void keyPressEvent(QKeyEvent *event)
    {
        if(event->key() == Qt::Key_Left)
            rotate(1);
        else if(event->key() == Qt::Key_Right)
            rotate(-1);
    }
};

class BlastBench : public QWizardPage
{
    Q_OBJECT
public:
    BlastBench(Simulation *currentSimulation,QWidget *parent = 0);
    void addBlastWalls(QList<BlastHole *> northWall, QList<BlastHole *> eastWall, QList<BlastHole *> southWall, QList<BlastHole *> westWall);
    void modifySceneRect(double minX, double maxX, double minY, double maxY);

    void setBlastHoles(const QList<BlastHole *> &blastHoles);
    void showDialogItem();

    QList<BlastHole *> getSelectedBlastHoleNorthWall() const;
    QList<BlastHole *> getSelectedBlastHoleEastWall() const;
    QList<BlastHole *> getSelectedBlastHoleSouthWall() const;
    QList<BlastHole *> getSelectedBlastHoleWestWall() const;
    QList<BlastHole *> getBlastHoles() const;
    void getMinAndMax(double &minX, double &minY, double &minZ, double &maxX, double &maxY, double &maxZ);
    void clearModel();
public slots:
    void slotSelectedItem(QString i_strSelectedItem);
    void slotDataChanged( QModelIndex topLeft );
    void slotRemoveSelectedItemFromEastBlastWall();
    void slotRemoveSelectedItemFromWestBlastWall();
    void slotRemoveSelectedItemFromNortBlastWall();
    void slotRemoveSelectedItemFromSouthBlastWall();

    void slotAddSelectedItemToEastBlastWall();
    void slotAddSelectedItemToWestBlastWall();
    void slotAddSelectedItemToNortBlastWall();
    void slotAddSelectedItemToSouthBlastWall();
    void on_m_pbClearWallItems_clicked();
    void on_m_pbApply_clicked();
signals:
    void sigPainterPath(QPainterPath);
    void sigBlastHoleList(QList<BlastHole*> );
    void sigBlastWallsEastWestNorthSouth(QList<BlastHole*> ,QList<BlastHole*>,QList<BlastHole*>,QList<BlastHole*>);
private slots:
    void on_checkBox_clicked(bool checked);
private:
    void initalizeWidget();
    void createBlastGraphicsItem();
    QList<BlastHole *> getUniqueListOfSelectedHoles();
    void createpainterpath();

protected:
    void initializePage();
private:
    QCheckBox* dxf;
    QCheckBox* openpitmetal;
    QCheckBox* openpitcoal;
    QCheckBox* Edges;
    QLabel* North;
    View* topgrpahicsview;
    View* toegrpahicsview;
    QTableView* tableview;
    QFrame* line;
    QPushButton* clearwallitemsbutton;
    Simulation *simulationref;
    QList<BlastHole*> m_blastHoles;
    QList<BlastHole*> m_selectedEdgeHoleList;

    double m_cubeSize = 1;
    QGraphicsScene* topgraphicsscene;
    QGraphicsScene* toegraphicsscene;
    BlastBenchCustomTableModel* m_Model;
    QMap<int, BlastHole*>  m_mapBlastHoleData;
    QMap<int, BlastGraphicsRectItem*>  m_blastGraphicsItem;
    QMap<int, BlastGraphicsRectItem*>  m_blastGraphicsItemToe;

    bool m_bSelectHoles =false;

    QHash<int, QPointF>  m_paintterpath;
    QHash<int, QPointF>  m_paintterpathToe;

    QString m_strUserSelectedItem;
    QQueue<int> m_blastEdge;

    QHash<int, QPointF>  m_paintterpathEast;
    QHash<int, QPointF>  m_paintterpathWest;
    QHash<int, QPointF>  m_paintterpathNorth;
    QHash<int, QPointF>  m_paintterpathSouth;

    QHash<int, QPointF>  m_paintterpathEastToe;
    QHash<int, QPointF>  m_paintterpathWestToe;
    QHash<int, QPointF>  m_paintterpathNorthToe;
    QHash<int, QPointF>  m_paintterpathSouthToe;

    QGraphicsPathItem* pItem ;
    QGraphicsPathItem* pItemEastBlastWall ;
    QGraphicsPathItem* pItemWestBlastWall ;
    QGraphicsPathItem* pItemNorthBlastWall ;
    QGraphicsPathItem* pItemSouthBlastWall ;

    QGraphicsPathItem* pItemToe ;
    QGraphicsPathItem* pItemEastBlastWallToe ;
    QGraphicsPathItem* pItemWestBlastWallToe ;
    QGraphicsPathItem* pItemNorthBlastWallToe ;
    QGraphicsPathItem* pItemSouthBlastWallToe ;

    BlastGraphicsRectItem* m_currentSelectedItem;

    QList<BlastHole*> m_selectedBlastHoleEastWall;
    QList<BlastHole*> m_selectedBlastHoleWestWall;
    QList<BlastHole*> m_selectedBlastHoleNorthWall;
    QList<BlastHole*> m_selectedBlastHoleSouthWall;

    QPainterPath m_selectedItemsPath;
    QPainterPath m_selectedBlastHoleEastWallPath;
    QPainterPath m_selectedBlastHoleWestWallPath;
    QPainterPath m_selectedBlastHoleNorthWallPath;
    QPainterPath m_selectedBlastHoleSouthWallPath;

    QPainterPath m_selectedItemsPathToe;
    QPainterPath m_selectedBlastHoleEastWallPathToe;
    QPainterPath m_selectedBlastHoleWestWallPathToe;
    QPainterPath m_selectedBlastHoleNorthWallPathToe;
    QPainterPath m_selectedBlastHoleSouthWallPathToe;
};


#endif // BLASTBENCH_H
