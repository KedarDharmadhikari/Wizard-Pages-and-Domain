#ifndef BLASTBENCHCUSTOMTABLEMODEL_H
#define BLASTBENCHCUSTOMTABLEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>
#include <QMap>
class BlastHole;
class BlastBenchCustomTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BlastBenchCustomTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void setBlastHoleMap(QMap<int, BlastHole *> &i_mapData);

    void selectRow(QString i_strHoleId);

signals:
    void sigDataChanged(QModelIndex topLeft);
private:
    QList<QVector<qreal> * > m_data;
    QHash<QString, QRect> m_mapping;
    int m_columnCount;
    int m_rowCount;
    QMap<int, BlastHole *> m_mapData;
    QList<BlastHole *> lstData;
};

#endif // BLASTBENCHCUSTOMTABLEMODEL_H
