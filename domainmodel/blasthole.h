#ifndef BLASTHOLE_H
#define BLASTHOLE_H
#include <QObject>

class BlastHole
{
public:
    BlastHole(QString holeId, double cex, double cny, double clz, double tex, double tny, double tlz, double dimension);

    QString holeID() const;

    double collarEast_x() ;
    void setCollarEast_x(double collarEast_x);

    double collarNorth_y() ;
    void setCollarNorth_y(double collarNorth_y);

    double collarLevel_z() ;
    void setCollarLevel_z(double collarLevel_z);

    double toeEast_x() ;
    void setToeEast_x(double toeEast_x);

    double toeNorth_y() ;
    void setToeNorth_y(double toeNorth_y);

    double toeLevel_z() ;
    void setToeLevel_z(double toeLevel_z);

    double dimension() ;
    void setDimension(double dimension);

    void setMultiplier(int multiplier);

    double offsetCollarEast_x() ;
    void setOffsetCollarEast_x(double offsetCollarEast_x);

    double offsetCollarNorth_y() ;
    void setOffsetCollarNorth_y(double offsetCollarNorth_y);

    double offsetToeEast_x() ;
    void setOffsetToeEast_x(double offsetToeEast_x);

    double offsetToeNorth_y() ;
    void setOffsetToeNorth_y(double offsetToeNorth_y);

private:
    QString m_holeID;
    double m_collarEast_x;
    double m_collarNorth_y;
    double m_collarLevel_z;
    double m_toeEast_x;
    double m_toeNorth_y;
    double m_toeLevel_z;
    double m_dimension;

    double m_offsetCollarEast_x=0.0;
    double m_offsetCollarNorth_y=0.0;

    double m_offsetToeEast_x=0.0;
    double m_offsetToeNorth_y=0.0;

    int m_multiplier = 1;
};


//Hole ID,Collar East (m),Collar North (m),Collar Level (m),Toe East (m),Toe North (m),Toe Level (m)
//1,-89.5616,3.995211,0,-89.5616,6.904686,-16.5005

#endif // BLASTHOLE_H
