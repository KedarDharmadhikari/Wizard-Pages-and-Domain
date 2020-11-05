#include "BlastGraphicsRectItem.h"
#include "blasthole.h"
#include <QPen>
#include <QBrush>

BlastGraphicsRectItem::BlastGraphicsRectItem(BlastHole* hole)
    : m_blastHole(hole)
{
    this->setPen(QPen(QBrush(QColor(Qt::black)),1));
    setPos(m_blastHole->collarEast_x()/*- m_blastHole->offsetCollarEast_x()*/, m_blastHole->collarNorth_y() /*-m_blastHole->offsetCollarNorth_y()*/);
    setRect(0,0,2,2);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);

    m_modifiedRectItem =new QGraphicsRectItem(this);
    m_modifiedRectItem->setVisible(false);
    m_modifiedRectItem->setRect(0,0,2,2);
    m_modifiedRectItem->setPen(QPen(QBrush(QColor(Qt::yellow)),1));


    m_modifiedRectItemToe =new QGraphicsRectItem(this);
    m_modifiedRectItemToe->setVisible(false);
    m_modifiedRectItemToe->setRect(0,0,2,2);
    m_modifiedRectItemToe->setPen(QPen(QBrush(QColor(Qt::red)),1));

    m_griBackground = new QGraphicsRectItem();
    m_griBackground->setVisible(false);
    setParent();
}
void BlastGraphicsRectItem::setParent()
{
    m_griBackground->setParentItem(this);
}
void BlastGraphicsRectItem::updateToePosition()
{
    m_modifiedRectItemToe->setPos(m_blastHole->offsetToeEast_x(), m_blastHole->offsetToeNorth_y());
    m_modifiedRectItemToe->setVisible(true);

    if(lineToe !=nullptr)
    {
        delete lineToe;
        lineToe=nullptr;
    }
    if(lineToe ==nullptr)
    {
        lineToe = new  QGraphicsLineItem(this);
    }

    lineToe->setVisible(false);
    lineToe->setPen(QPen(QBrush(QColor(Qt::magenta)),1));
    lineToe->setPos(0,0);

    lineToe->setLine(QLineF((QPointF(0,0)),QPointF(m_blastHole->offsetToeEast_x(),m_blastHole->offsetToeNorth_y())));

    if( m_blastHole->offsetToeEast_x() == 0.0 && m_blastHole->offsetToeNorth_y() == 0.0 )
    {
        lineToe->setVisible(false);
    }else
    {
        lineToe->setVisible(true);
    }

    update();
}


void BlastGraphicsRectItem::updatePosition()
{
    m_modifiedRectItem->setPos(m_blastHole->offsetCollarEast_x(),m_blastHole->offsetCollarNorth_y());
    m_modifiedRectItem->setVisible(true);

    if(line !=nullptr)
    {
        delete line;
        line=nullptr;
    }
    if(line ==nullptr)
    {
        line = new  QGraphicsLineItem(this);
    }

    line->setVisible(false);
    line->setPen(QPen(QBrush(QColor(Qt::magenta)),1));
    line->setPos(0,0);

    line->setLine(QLineF((QPointF(0,0)),QPointF(m_blastHole->offsetCollarEast_x(),m_blastHole->offsetCollarNorth_y())));

    if( m_blastHole->offsetCollarEast_x() == 0.0 && m_blastHole->offsetCollarNorth_y() == 0.0 )
    {
        line->setVisible(false);
    }else
    {
        line->setVisible(true);
    }

    update();
}

BlastHole* BlastGraphicsRectItem::getBlastHole()
{
    return m_blastHole;
}

void BlastGraphicsRectItem::updateSelectedItemPosition()
{
    setSelected(true);
    update();

}

void BlastGraphicsRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    setToolTip(QString("Hole id-%1\nx->%2\ny->%3").arg(m_blastHole->holeID()).arg(m_blastHole->collarEast_x()).arg(m_blastHole->collarNorth_y()));
}

void BlastGraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigClickedHoleId(m_blastHole->holeID());
}

void BlastGraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(isSelected())
    {
        m_griBackground->setRect(0,0,2,2);
        m_griBackground->setZValue(99);
        m_griBackground->setPen(QPen(QBrush(QColor(Qt::gray)),1));
        m_griBackground->setVisible(true);

    }else
    {
        m_griBackground->setRect(0,0,2,2);
        m_griBackground->setZValue(0);
        m_griBackground->setPen(QPen(QBrush(QColor(Qt::black)),1));
        m_griBackground->setVisible(false);
        QGraphicsRectItem::paint(painter,option, widget);
    }
    //qDebug() <<__FUNCTION__;
}




