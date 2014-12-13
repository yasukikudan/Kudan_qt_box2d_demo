#include "dataclass.h"
#include "algorithm/algorithm.h"

std::array<int,4> CollisionFactor::CollisionShape(cint mapx, cint mapy, cint mapw, cint maph, cbool wallflag, std::array<bool,4> floorflags) const
{
    //始点を計算する関数
    auto calcp=[](cbool wallflag,cbool floorflag,cint wfact,cint ffact){
        int shift;
        if(floorflag==true){
            //高所に接している場合
            shift=-ffact;
        }else if(wallflag==true){
           //自身が壁である場合
            shift=-wfact;

        }else{
            //いずれでも無い場合
            shift=0;
        }
        return shift;
    };
    //幅を計算する関数
    auto calcw=[](cbool wallflag,cbool floorflag,cint wfact,cint ffact,cint shift){
        int out;
        if(floorflag==true){
            //高所に接している場合
            out=+ffact;
        }else if(wallflag==true){
           //自身が壁である場合
            out=+wfact;
        }else{
            //いずれでも無い場合
            out=0;
        }
        out=out-shift;
        return out;
    };
    //壁の場合y方向には距離を開けない
    cbool wallflagy=false;
    cint shiftx=calcp(wallflag,floorflags[1],WallFactor(),WallFactor());
    cint shifty=calcp(wallflagy,floorflags[0],WallFactor(),WallFactor());
    cint w=calcw(wallflag,floorflags[2],WallFactor(),WallFactor(),shiftx)+mapw;
    cint h=calcw(wallflagy,floorflags[3],WallFactor(),WallFactor(),shifty)+maph;
    std::array<int,4> out{mapx+shiftx,mapy+shifty,w,h};
    return out;
}

ClockCounter::ClockCounter()
{
    time=Algorithm::rdtsc();
}

quint64 ClockCounter::Time()
{
    quint64 tmp=Algorithm::rdtsc();
    auto timer=tmp-time;
    qDebug() << "time" <<  timer;
    time=Algorithm::rdtsc();;
    return timer;
}

quint64 ClockCounter::Time(QString text)
{
    quint64 tmp=Algorithm::rdtsc();
    auto timer=tmp-time;
    qDebug() << text <<  timer;
    time=Algorithm::rdtsc();;
    return timer;
}
