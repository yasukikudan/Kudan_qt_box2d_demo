#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <QtAlgorithms>
#include <QVector>
#include <QPair>
#include <QHash>
#include "algorithm/dataclass.h"
#include <QPolygonF>
#include <Box2D/Box2D.h>

namespace Algorithm{
//-------------------------------------------------
typedef const int point;
typedef const int cint;
//-------------------------------------------------
//符号関数
int SignFunction(int num);
//-------------------------------------------------
//絶対インクリメント関数
int AbsoluteIncrement(int num);
int AbsoluteDecrement(int num);
//-------------------------------------------------
//線分交差判定
bool SegmentIntersection(Vector vect1, Vector vect2);
bool SegmentIntersection(point x1,point y1,point x2,point y2,point x3,point y3,point x4,point y4);
//-------------------------------------------------
//線分と点の位置関係を調べる関数
bool SegmentLeftPoint(Vector vect1,vertex vert);
bool SegmentLeftPoint(point x1,point y1,point x2,point y2,point xp,point yp);
//-------------------------------------------------
//ベクトルのサイズを変更する関数
Vector VectorResize(Vector vect, const double fact);
Vector VectorResize(Vector vect, const int longvert);
vertex VectorResize(double dx,double dy,const double fact);
//大小比較関数
//-------------------------------------------------
int BigLitle(const int num1, const int num2);
//-------------------------------------------------
//絶対値大小比較関数
int SignLitleBig(const int num1, const int num2);
//-------------------------------------------------
//引数の範囲を調べる
bool RengedValue(double num,double max,double min);
bool RengedValue(cint num, cint max,cint min);
bool RengedValue2D(cint x,cint maxx,cint minx,cint y,cint maxy,cint miny);
//-------------------------------------------------
//線分交差点導出関数
bool SegmentIntersectionPoint(Vector vect1, Vector vect2,vertex &result);
//-------------------------------------------------
//線分直線交差点導出関数
bool LineSegmentIntersectionPoint(Vector vect1, Vector vect2,vertex &result);
//-------------------------------------------------
//二次元変数一次元化関数
int DimensionConvert(cint d1,cint d2,cint row);
//-------------------------------------------------
//最頻値算出関数
int mode(QVector<int> &in);
//-------------------------------------------------
//2値平均
int mean(cint num,cint num2,cint hint);
//-------------------------------------------------
//FULL判定
bool isFull(QVector<int> &in);
//-------------------------------------------------
//除算 床関数
int DivisionFloor(cint num,cint range);
//-------------------------------------------------
//第一引数に一番近い数を返す
int near(cint num,QVector<int> array);
//-------------------------------------------------
//第一引数と符号が異なる数を配列から排除する ０は常に排除しない
QVector<int> SameSigns(cint num,QVector<int> array);
//-------------------------------------------------
//乗算 関数
int Multiplication(cint num,cint fact);
int Division(cint num,cint fact);
//-------------------------------------------------
//二点間距離
int CollisionDistance(const int p1x,const int p1y,const int p2x,const int p2y);
//最大値、最小値
//class arrayMaxMinResult{public:int max,min;};
//arrayMaxMinResult arrayMaxMin(int &max,int &min,QVector<int> array);
//-------------------------------------------------
//クロックタイムカウント
unsigned long long rdtsc();
//-------------------------------------------------
//二点間距離算出
int DistancePoints(point x1,point y1,point x2,point y2);
//-------------------------------------------------
//キャラクターの方角を移動差分に変換
vertex DirectionConvert(const int direction);
//-------------------------------------------------

/*
//Qtのポリゴンをbox2dの頂点配列に変換
QVector<b2Vec2> ConvertB2Vec2(QPolygonF &poly,RangeConvert &r){
    QVector<b2Vec2> vect(poly.count());
    for(const int i:SmartCountor(poly.count())){
        vect[i].x=r.divForce(poly[i].x());
        vect[i].y=r.divForce(poly[i].y());
    }
    return vect;
}
*/
//-------------------------------------------------
//QVectorのデイープコピー
template <typename T>
QVector<T> VectorDeepCopy(QVector<T> in)
{
    const int size=in.count();
    QVector<T> out(size);
    for(const int i:SmartCountor(size)){
        out[i]=in[i];
    }

    return out;
}
//-------------------------------------------------
/*!
  重複削除
*/
template <typename T>
QVector<T> VectorDeduplication(QVector<T> in)
{
    if(in.count()>0){
        qSort(in);
        const int size=in.size();
        QVector<T> out;
        out.reserve(size);
        //検索開始位置
        const int pos=1;
        //最初の要素の参照を取得
        T &chack=in[0];
        //一番最初の要素を登録
        out.append(in[0]);
        for(const int i:SmartCountor(pos,size-pos)){
            if(chack==in[i]){
               //一致するなら何もしない
            }else{
                //要素を更新
                chack=in[i];
                //配列に登録
                out.append(in[i]);
            }
        }
    return out;
    }else{
        return in;
    }
}


}



#endif // ALGORITHM_H
