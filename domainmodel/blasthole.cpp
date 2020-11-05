#include "blasthole.h"
#include <QtDebug>

BlastHole::BlastHole(QString holeId, double cex, double cny, double clz, double tex,
                     double tny, double tlz, double dimension)
        : m_holeID(holeId),
          m_collarEast_x(cex),
          m_collarNorth_y(cny),
          m_collarLevel_z(clz),
          m_toeEast_x(tex),
          m_toeNorth_y(tny),
          m_toeLevel_z(tlz),
          m_dimension(dimension)
{}

QString BlastHole::holeID() const
{
    return m_holeID;
}

double BlastHole::collarEast_x()
{
    return m_collarEast_x*m_multiplier;
}

void BlastHole::setCollarEast_x(double collarEast_x)
{
    m_collarEast_x = collarEast_x;
}

double BlastHole::collarNorth_y()
{
    return m_collarNorth_y*m_multiplier;
}

void BlastHole::setCollarNorth_y(double collarNorth_y)
{
    m_collarNorth_y = collarNorth_y;
}

double BlastHole::collarLevel_z()
{
    return m_collarLevel_z*m_multiplier;
}

void BlastHole::setCollarLevel_z(double collarLevel_z)
{
    m_collarLevel_z = collarLevel_z;
}

double BlastHole::toeEast_x()
{
    return m_toeEast_x*m_multiplier;
}

void BlastHole::setToeEast_x(double toeEast_x)
{
    m_toeEast_x = toeEast_x;
}

double BlastHole::toeNorth_y()
{
    return m_toeNorth_y*m_multiplier;
}

void BlastHole::setToeNorth_y(double toeNorth_y)
{
    m_toeNorth_y = toeNorth_y;
}

double BlastHole::toeLevel_z()
{
    return m_toeLevel_z*m_multiplier;
}

void BlastHole::setToeLevel_z(double toeLevel_z)
{
    m_toeLevel_z = toeLevel_z;
}

double BlastHole::dimension()
{
    return m_dimension*m_multiplier;
}

void BlastHole::setDimension(double dimension)
{
    m_dimension = dimension;
}

void BlastHole::setMultiplier(int multiplier)
{
    m_multiplier = multiplier;
}

double BlastHole::offsetCollarEast_x()
{
    return m_offsetCollarEast_x;
}

void BlastHole::setOffsetCollarEast_x(double offsetCollarEast_x)
{
    m_offsetCollarEast_x = offsetCollarEast_x;
    qDebug() << __FUNCTION__ << m_offsetCollarEast_x;
}

double BlastHole::offsetCollarNorth_y()
{
    return m_offsetCollarNorth_y;
}

void BlastHole::setOffsetCollarNorth_y(double offsetCollarNorth_y)
{
    m_offsetCollarNorth_y = offsetCollarNorth_y;
}

double BlastHole::offsetToeEast_x()
{
    return m_offsetToeEast_x;
}

void BlastHole::setOffsetToeEast_x(double offsetToeEast_x)
{
    m_offsetToeEast_x = offsetToeEast_x;
    qDebug() << __FUNCTION__ << m_offsetToeEast_x;
}

double BlastHole::offsetToeNorth_y()
{
    return m_offsetToeNorth_y;
}

void BlastHole::setOffsetToeNorth_y(double offsetToeNorth_y)
{
    m_offsetToeNorth_y = offsetToeNorth_y;
    qDebug() << __FUNCTION__ << m_offsetToeNorth_y;
}
