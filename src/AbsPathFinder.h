#ifndef ABSPATHFINDER_H
#define ABSPATHFINDER_H

#include <QVector>
#include <QDebug>
#include <QMultiMap>
#include <QRectF>

struct SmartPoint
{

    int         id;
    int         parent;
    int         distance;
    QPointF     point;

    SmartPoint(QPointF value=QPointF(), int parent=-1, int distance=0, int id=0)
        :   id(id), parent(parent), distance(distance), point(value)
    {

    }

};

class AbsPathFinder
{

    typedef QVector<QPointF>                        Points;
    typedef Points::iterator                        PointsItr;
    typedef QList<SmartPoint>                       SmartPoints;
    typedef SmartPoints::iterator                   SmartPointsItr;
    typedef QMultiMap<float,SmartPoint>             SmartPointsWeighted;
    typedef SmartPointsWeighted::iterator           SmartPointsWeightedItr;

    public:
        static Points             pathFindAStar(QPointF begin, QPointF end, Points avaliable, Points blocked, int step, bool diagonal=false)
        {

            SmartPointsWeighted         unexplored;
            SmartPointsWeightedItr      unexploredItr;
            SmartPoints                 explored;
            Points                      neighbours;
            PointsItr                   neighboursItr;
            SmartPoint                  pointCurrent;
            int                         g;
            int                         h;

            if (begin!=end && !blocked.contains(begin) && !blocked.contains(end))
            {
                unexplored.insert(0,SmartPoint(end));
                blocked.push_back(end);

                do
                {
                    pointCurrent = unexplored.begin().value();
                    pointCurrent.id = explored.size();
                    explored.push_back(pointCurrent);
                    if (pointCurrent.point != begin)
                    {
                        unexplored.erase(unexplored.begin());
                        neighbours = AbsPathFinder::getPointNeighbours(pointCurrent.point,avaliable,blocked,step,diagonal);
                        for (neighboursItr=neighbours.begin() ; neighboursItr!=neighbours.end() ; ++neighboursItr)
                        {
                            g = pointCurrent.distance + step;
                            h = (begin-(*neighboursItr)).manhattanLength();
                            unexplored.insert(g+h,SmartPoint(*neighboursItr,pointCurrent.id,g));
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
        static Points             getRectPerimeterPoints(QRectF rect, int step)
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
        static Points             getRectInnerPoints(QRectF rect, int step)
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
        static Points             getPointNeighbours(QPointF point, Points avaliable, Points blocked, int step, bool diagonal=false)
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
                if (!blocked.contains(*pointsItr) && avaliable.contains(*pointsItr))
                    neighboursAvaliable.push_back(*pointsItr);

            return neighboursAvaliable;

        }
        static Points             pathUnwind(SmartPoints points)
        {
            Points path;
            SmartPoint point;

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
};


#endif // ABSPATHFINDER_H
