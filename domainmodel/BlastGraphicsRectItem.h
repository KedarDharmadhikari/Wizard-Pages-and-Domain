#ifndef BLASTGRAPHICSRECTITEM_H
#define BLASTGRAPHICSRECTITEM_H
#include <QGraphicsRectItem>
#include <QGraphicsScene>
class BlastHole;
class BlastGraphicsRectItem : public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    ~BlastGraphicsRectItem(){};
    BlastGraphicsRectItem(BlastHole* hole);
    void updateSelectedItemPosition();
    BlastHole* getBlastHole();
    void updateToePosition();
    void updatePosition();
    void  setParent();
signals:
    void sigClickedHoleId(QString);
protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    QGraphicsRectItem *m_griBackground;
    BlastHole* m_blastHole;
    QGraphicsRectItem *m_modifiedRectItem;
    QGraphicsRectItem *m_modifiedRectItemToe;
    QGraphicsLineItem *line=nullptr;
    QGraphicsLineItem *lineToe=nullptr;
    bool isP1;
};

#endif // BLASTGRAPHICSRECTITEM_H
