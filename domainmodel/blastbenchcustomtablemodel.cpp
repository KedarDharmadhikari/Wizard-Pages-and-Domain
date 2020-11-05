#include "blastbenchcustomtablemodel.h"
#include "domainmodel/blasthole.h"

#include <QtCore/QVector>
#include <QtCore/QRandomGenerator>
#include <QtCore/QRect>
#include <QtGui/QColor>

BlastBenchCustomTableModel::BlastBenchCustomTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 7;
    m_rowCount = 0;

}

int BlastBenchCustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_mapData.count();
}

int BlastBenchCustomTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant BlastBenchCustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    QVariant varHeader;
    if(orientation ==Qt::Horizontal) {
        switch (role) {
        case Qt::DisplayRole: {
            switch (section) {
            case 0:
                varHeader = "Hole Id";
                break;
            case 1:
                varHeader = "X Cor";
                break;
            case 2:
                varHeader = "Y Cor";
                break;
            case 3:
                varHeader = "Collar X";
                break;
            case 4:
                varHeader = "Collar Y";
                break;
            case 5:
                varHeader = "Toe X";
                break;
            case 6:
                varHeader = "Toe Y";
                break;

            default:
                break;
            }
        }
            break;

        default:
            break;
        }
    }
    else {
        varHeader = section + 1;
    }

    return varHeader;
}

QVariant BlastBenchCustomTableModel::data(const QModelIndex &index, int role) const
{
    QVariant data;
    int column = index.column();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        BlastHole *ptheData=lstData.at(index.row());

        switch (column) {
        case 0:
            data= ptheData->holeID().toInt();
            break;
        case 1:
            data= ptheData->collarEast_x();

            break;
        case 2:
            data= ptheData->collarNorth_y();

            break;
        case 3:
            data= ptheData->offsetCollarEast_x();
            break;
        case 4:
            data= ptheData->offsetCollarNorth_y();
            break;
        case 5:
            data= ptheData->offsetToeEast_x();
            break;
        case 6:
            data=  ptheData->offsetToeNorth_y();
            break;
        default:
            break;
        }
        return data;


    }

    return QVariant();
}

bool BlastBenchCustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //    if (index.isValid() && role == Qt::EditRole)
    //    {
    ////        m_mapData.values().at(index.row())->replace(index.column(), value.toDouble());
    //        lstData[index.row()]->replace(index.column(), value.toDouble());
    //        emit dataChanged(index, index);
    //        return true;
    //    }
    //    return false;

    bool result=false;
    if (role != Qt::EditRole)
        return false;

    if (index.isValid()) {

        switch (index.column()) {
        case 0:
            //                lstData[index.row()]->set(value.toInt());
            break;
        case 1:
            //  lstData[index.row()]->setCollarEast_x(value.toDouble());

            break;
        case 2:
            //   lstData[index.row()]->setCollarNorth_y(value.toDouble());

            break;
        case 3:
            lstData[index.row()]->setOffsetCollarEast_x(value.toDouble());
            result=true;

            break;
        case 4:
            lstData[index.row()]->setOffsetCollarNorth_y(value.toDouble());
            result=true;

            break;
        case 5:
            lstData[index.row()]->setOffsetToeEast_x(value.toDouble());
            result=true;

            break;
        case 6:
            lstData[index.row()]->setOffsetToeNorth_y(value.toDouble());
            result=true;

            break;

        default:
            break;
        }

    }


    if (result)
    {
        emit sigDataChanged(index);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    }

    return false;
}

Qt::ItemFlags BlastBenchCustomTableModel::flags(const QModelIndex &index) const
{
    if(index.column() ==  0 || index.column() ==  1 || index.column() ==  2)
    {
        return QAbstractItemModel::flags(index);
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void BlastBenchCustomTableModel::setBlastHoleMap(QMap<int, BlastHole*>  &i_mapData)
{
    beginResetModel();
    m_mapData = i_mapData;
    lstData=m_mapData.values();
    endResetModel();
}

void BlastBenchCustomTableModel::selectRow(QString i_strHoleId)
{


}
