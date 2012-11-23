#ifndef ABSPATHFINDER_H
#define ABSPATHFINDER_H

#include <QVector>
#include <QDebug>
#include <QMultiMap>

struct SmartPoint
{

    int id;
    int parent;
    int distance;
    QPointF value;

    SmartPoint()
    {

    }

    SmartPoint(int id, int parent, int distance, QPointF value)
        :   id(id), parent(parent), distance(distance), value(value)
    {

    }

};

class AbsPathFinder
{

    typedef QVector<QPointF>                         Points;
    typedef Points::iterator                        PointsItr;
    typedef QList<SmartPoint>                       SmartPoints;
    typedef SmartPoints::iterator                   SmartPointsItr;
    typedef QMultiMap<float,SmartPoint>             SmartPointsWeighted;
    typedef SmartPointsWeighted::iterator           SmartPointsWeightedItr;

    public:
        static Points             pathFindAStar(QPointF begin, QPointF end, Points blocked, int step, bool diagonal=false)
        {

            SmartPointsWeighted         unexplored;
            SmartPoints                 explored;
            Points                      neighbours;
            PointsItr                   neighboursItr;
            SmartPoint                  pointCurrent;
            int                         g;
            int                         h;

            if (begin!=end && !blocked.contains(begin) && !blocked.contains(end))
            {
                unexplored.insert(0,SmartPoint(0,-1,0,end));
                blocked.push_back(end);

                do
                {
                    pointCurrent = unexplored.begin().value();
                    pointCurrent.id = explored.size();
                    explored.push_back(pointCurrent);
                    if (pointCurrent.value != begin)
                    {
                        unexplored.erase(unexplored.begin());
                        neighbours = AbsPathFinder::getPointNeighbours(pointCurrent.value,blocked,step,diagonal);
                        for (neighboursItr=neighbours.begin() ; neighboursItr!=neighbours.end() ; ++neighboursItr)
                        {
                            g = pointCurrent.distance + step;
                            h = (begin-(*neighboursItr)).manhattanLength();
                            unexplored.insert(g+h,SmartPoint(0,pointCurrent.id,g,*neighboursItr));
                            blocked.push_back(*neighboursItr);
                        }
                    }
                    else
                        return AbsPathFinder::pathUnwind(explored);
                }
                while(!unexplored.isEmpty());
            }

            return Points();

        }
        static Points             getRectPoints(QRectF rect, int step)
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
        static Points             getSegmentPoints(QPointF begin, QPointF end, int step)
        {

            Points points;
            QPointF delta;

            begin.x() == end.x() ? delta = QPointF(0,step) : delta = QPointF(step,0);

            while (begin != end)
            {

                points.push_back(begin);
                begin += delta;

            }

            points.push_back(end);

            return points;

        }

    private:
        static Points             getPointNeighbours(QPointF point, Points blocked, int step, bool diagonal=false)
        {

            Points neighboursAll, neighboursOpened;
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
                if (!blocked.contains(*pointsItr))
                    neighboursOpened.push_back(*pointsItr);

            return neighboursOpened;

        }
        static float              getPointManhattanLength(QPointF point, QPointF destination)
        {

            return (destination - point).manhattanLength();

        }
        static Points             pathUnwind(SmartPoints points)
        {
            Points path;
            SmartPoint point;

            while (points.size() > 0)
            {

                point = points.last();
                path.push_back(point.value);

                if(point.parent >= 0)
                    while (points.last().id != point.parent)
                        points.pop_back();
                else
                    break;
            }

            return path;

        }
};


#endif // ABSPATHFINDER_H
