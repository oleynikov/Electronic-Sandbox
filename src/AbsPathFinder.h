#ifndef ABSPATHFINDER_H
#define ABSPATHFINDER_H

#include <QVector>
#include <QDebug>
#include <QMultiMap>
#include <QRectF>

struct SPoint
{

    int         id;
    int         parent;
    int         distance;
    QPointF     point;

    SPoint(QPointF value=QPointF(), int parent=-1, int distance=0, int id=0)
        :   id(id), parent(parent), distance(distance), point(value)
    {

    }

};

enum Algorithm
{

    ALGORITHM_ASTAR

};

typedef QVector<QPointF>                Points;
typedef Points::iterator                PointsItr;
typedef QList<SPoint>                   SPoints;
typedef SPoints::iterator               SPointsItr;
typedef QMultiMap<float,SPoint>         SPointsWeighted;
typedef SPointsWeighted::iterator       SPointsWeightedItr;

class AbsPathFinder
{

    public:
        static Points                   pathFindAStar(QPointF pBegin, QPointF pEnd, Points pOpen, Points pClosed, int pStep, bool pDiagonal=false, Algorithm=ALGORITHM_ASTAR)
        {

            if (
                    pBegin!=pEnd
                        &&
                    !pClosed.contains(pBegin)
                        &&
                    !pClosed.contains(pEnd)
                        &&
                    (
                        pOpen.empty()
                            ||
                        (
                            pOpen.contains(pBegin)
                                &&
                            pOpen.contains(pEnd)
                        )
                    )
                )
            {
                SPointsWeighted pUnexplored;
                SPoints pExplored;
                pUnexplored.insert(0,SPoint(pEnd));
                pClosed.push_back(pEnd);
                do
                {
                    SPoint pointCurrent = pUnexplored.begin().value();
                    pointCurrent.id = pExplored.size();
                    pExplored.push_back(pointCurrent);
                    pClosed.push_back(pointCurrent.point);
                    if (pointCurrent.point != pBegin)
                    {
                        pUnexplored.erase(pUnexplored.begin());
                        Points neighbours = AbsPathFinder::getNeighbourPoints(pointCurrent.point,pOpen,pClosed,pStep,pDiagonal);
                        for (PointsItr neighboursItr=neighbours.begin() ; neighboursItr!=neighbours.end() ; ++neighboursItr)
                        {
                            int g = pointCurrent.distance + pStep;
                            int h = (pBegin-(*neighboursItr)).manhattanLength();
                            SPoint pNeighbour(*neighboursItr,pointCurrent.id,g);
                            SPointsWeightedItr pUnexploredNew = AbsPathFinder::sPointWeightedFind(pUnexplored,pNeighbour);
                            if (pUnexploredNew != pUnexplored.end())
                            {
                                pUnexplored.erase(pUnexploredNew);
                            }
                            pUnexplored.insert(g+h,pNeighbour);
                        }
                    }
                    else
                    {
                        return AbsPathFinder::pathUnwind(pExplored);
                    }
                }
                while(!pUnexplored.isEmpty());
            }
            return Points();
        }
        static Points                   getRectPerimeterPoints(QRectF rect, int step)
        {

            Points points;
            QPointF tl,tr,br,bl;

            tl = rect.topLeft();
            tr = rect.topRight();
            br = rect.bottomRight();
            bl = rect.bottomLeft();

            points += AbsPathFinder::getSegmentPoints(tl,tr,step);
            points += AbsPathFinder::getSegmentPoints(tr,br,step);
            points += AbsPathFinder::getSegmentPoints(bl,br,step);
            points += AbsPathFinder::getSegmentPoints(tl,bl,step);

            return points;

        }
        static Points                   getRectInnerPoints(QRectF rect, int step)
        {

            Points points;
            QPointF begin;
            QPointF end;

            int pointLinesCount = rect.height() / step;

            for (int i=0 ; i<pointLinesCount ; ++i)
            {

                begin = QPointF(rect.topLeft().x(),rect.topLeft().y()+i*step);
                end = QPointF(rect.topRight().x(),rect.topRight().y()+i*step);
                points += AbsPathFinder::getSegmentPoints(begin,end,step);

            }

            return points;

        }
        static Points                   getSegmentPoints(QPointF begin, QPointF end, int step)
        {

            Points points;
            QPointF delta;

            begin.x() == end.x() ? delta = QPointF(0,step) : delta = QPointF(step,0);

            while (begin.x() <= end.x() && begin.y() <= end.y())
            {

                points.push_back(begin);
                begin += delta;

            }

            points.push_back(end);

            return points;

        }

    private:
        static Points                   getNeighbourPoints(QPointF point, Points avaliable, Points blocked, int step, bool diagonal=false)
        {

            Points neighboursAll, neighboursAvaliable;
            PointsItr pointsItr;

            neighboursAll.push_back(point + QPointF(0,step));
            neighboursAll.push_back(point + QPointF(step,0));
            neighboursAll.push_back(point - QPointF(0,step));
            neighboursAll.push_back(point - QPointF(step,0));

            if(diagonal)
            {

                neighboursAll.push_back(point + QPointF(step,step));
                neighboursAll.push_back(point + QPointF(step,-step));
                neighboursAll.push_back(point - QPointF(step,step));
                neighboursAll.push_back(point - QPointF(step,-step));

            }

            for (pointsItr=neighboursAll.begin() ; pointsItr!=neighboursAll.end() ; ++pointsItr)
            {

                if  (
                        !blocked.contains(*pointsItr)
                            &&
                        (
                            avaliable.empty()
                                ||
                            avaliable.contains(*pointsItr)
                        )
                    )

                {

                    neighboursAvaliable.push_back(*pointsItr);

                }
            }

            return neighboursAvaliable;

        }
        static Points                   pathUnwind(SPoints points)
        {
            Points path;
            SPoint point;

            while (points.size() > 0)
            {

                point = points.last();
                path.push_back(point.point);

                if(point.parent >= 0)
                    while (points.last().id != point.parent)
                        points.pop_back();
                else
                    break;
            }

            return path;

        }
        static SPointsWeightedItr       sPointWeightedFind(SPointsWeighted points, SPoint point)
        {

            for (SPointsWeightedItr itr=points.begin() ; itr!=points.end() ; ++itr)
            {

                if (itr.value().point == point.point)
                {

                    return itr;

                }

            }

            return points.end();

        }
};

#endif // ABSPATHFINDER_H
