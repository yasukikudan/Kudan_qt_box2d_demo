#ifndef DATACLASS_H
#define DATACLASS_H
#include <QVector>
#include <memory>
#include <array>
#include <cstdio>
#include <QDebug>
#include <iostream>
#include <QString>
#include <QMutex>
//#include <QSqlQuery>


typedef const int cint;

class vertex
{
public:
    constexpr vertex():vx(0),vy(0){;}
    constexpr vertex(int x,int y):vx(x),vy(y){;}
    int vx;
    int vy;
    constexpr int isX() const {return vx;}
    constexpr int isY() const {return vy;}
    void mul(const int m){vx=vx*m;vy=vy*m;}
    void div(const int d){vx=vx/d;vy=vy/d;}
    QString info() const
    {
        return QString("x=%1 y=%2").arg(isX()).arg(isY());
    }
    friend QDebug& operator << (QDebug& os,const vertex& p)
    {
        os << p.info();
       return os;
    }
};

class Vector
{
public:
    constexpr  Vector(){;}
    constexpr  Vector(vertex s,vertex t):vs(s),vt(t){;}
    constexpr  Vector(int sx,int sy,int tx,int ty):vs(vertex(sx,sy)),vt(vertex(tx,ty)){;}//{vs.vx=sx;vs.vy=sy;vt.vx=tx;vt.vy=ty;}
    QString info() const
    {
        QString tmp=QString("vs x=%1 y=%2 vt x=%3 y=%4 dx=%5 dy=%6")
                .arg(vs.vx).arg(vs.vy).arg(vt.vx).arg(vt.vy).arg(vt.vx-vs.vx).arg(vt.vy-vs.vy);
        return tmp;
    }
    friend QDebug& operator << (QDebug& os,const Vector& p){
        os << p.info();
        return os;
    }
    vertex vs;
    vertex vt;
};

class VectorShape;

//衝突補正情報
class CollisionFactor
{
    typedef const int cint;
    typedef const bool cbool;
public:
    CollisionFactor(){WallFact=0;}
    CollisionFactor(const int wallfact){WallFact=wallfact;}
    //矩形のサイズを返す関数
    std::array<int,4> CollisionShape(cint mapx, cint mapy,cint mapw,cint maph,cbool wallflag, std::array<bool,4> floorflags) const;
    int WallFactor() const {return WallFact;}
private:
    //壁と衝突する際に左右に開ける空白
    int WallFact;
    int FloorFactX;
    int FloorFactY;
};

class ClockCounter
{
    //クロック周波数基準のカウンタ
public:
    ClockCounter();
    quint64 Time();
    quint64 Time(QString text);
private:
    quint64 time;//=Algorithm::rdtsc();
};

//トレース可能なbool
class SmartBool{
public:
    SmartBool():flag(true){;}
    SmartBool(bool setflag):flag(setflag){;}
    bool chack(){return flag;}
    void set(){flag=true;}
    void reset(){flag=false;}
private:
    bool flag;
};


//排他アクセス権クラス RAII
template <typename T>
class  ExclusiveController
{
public:
    ExclusiveController( std::shared_ptr<T> r,std::shared_ptr<QMutex> m)
        :res(r),mutex(m)
    {
        mutex->lock();
    }
    ~ExclusiveController()
    {
        mutex->unlock();
    }
    std::shared_ptr<T> Res() {return res;}
private:
    std::shared_ptr<T> res;
    std::shared_ptr<QMutex> mutex;
};

//リソースへの排他アクセス
template <typename T>
class  ExclusiveControl
{
public:
    ExclusiveControl():mutex(std::make_shared<QMutex>(QMutex::Recursive)){;}
    ExclusiveControl(std::shared_ptr<T> query):mutex(std::make_shared<QMutex>(QMutex::Recursive)),qy(query){;}
    std::shared_ptr<T> lock()
    {
        mutex->lock();
        return qy;
    }
    void unlock(){
        mutex->unlock();
    }
    ExclusiveController<T> autolock(){
        ExclusiveController<T> contl(qy,mutex);
        return contl;
    }

private:
    std::shared_ptr<QMutex> mutex;
    std::shared_ptr<T> qy;
};

//範囲ｆｏｒ用の  添字イテレータ intを返す
class CountIterator
{
public:
    constexpr CountIterator(int set):index(set){;}
   //デリファレンス
    int operator *() const
    {
        const int out=index;
       //index++;
        return out;
    }
    //非一致判定
    bool operator !=(CountIterator set) const{
        if(index!=set.Index()){
            return true;
        }else{
            return false;
        }
    }
    //インクリメント
    void operator ++()
    {
        index++;
    }
    //比較用関数
    int Index() const {
        return index;
    }
private:
    int index;
};

//範囲ｆｏｒ用のカウンタ
class SmartCountor
{
public:
    constexpr SmartCountor(int size):index(0),countSize(size){;}
    constexpr SmartCountor(int pos,int length):index(pos),countSize(pos+length){}
    constexpr CountIterator begin() const {return CountIterator(index);}
    constexpr CountIterator end() const {return CountIterator(countSize);}
private:
    int index;
    int countSize;
};

//指定された係数を元に座標を変換
class RangeConvert
{
public:
    constexpr RangeConvert():force(0){;}
    constexpr RangeConvert(double setforce):force(setforce){;}
    constexpr float  mulForce(double num) const {return force*num;}
    constexpr float  divForce(double num) const {return num/force;}
private:
    double force;
};



namespace kudan_tool {
//弱参照を生成するクラス
template <class T>
class ReferenceAssembler{
public:
    //コンストラクタ weak_ptrのポインタをnullptrで初期化
    ReferenceAssembler():assemble(nullptr){;}
    //weak_ptrの登録
    void setWeak(std::weak_ptr<T> &setweak){
        assemble=&setweak;
    }
    //ポインタの代入操作
    void operator =(std::shared_ptr<T> set){
        set_ptr=set;
        //ポインタが設定されていれば 代入
        if(assemble!=nullptr){
            std::weak_ptr<T> tmp_weak=set;
            assemble->operator =(tmp_weak);
        }
    }
    std::shared_ptr<T> Shared(){return set_ptr;}
private:
    //weak_ptrのポインタ
    std::weak_ptr<T> *assemble;
    //make_sharedの返り値を受け取るポインタ
    std::shared_ptr<T> set_ptr;
};

//弱参照を生成後 クラスのshared_ptrを返す
template <class Tp,typename... Ts>
std::shared_ptr<Tp> make_RefAsm(Ts... args)
{

    ReferenceAssembler<Tp> refasm;
    refasm=std::make_shared<Tp>(refasm,args...);
    return refasm.Shared();
}

}


#endif // DATACLASS_H
