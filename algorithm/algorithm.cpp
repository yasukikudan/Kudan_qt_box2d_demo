#include "algorithm.h"

//-------------------------------------------------
int Algorithm::SignFunction(int num)
{
    //符号関数
    //入力が＋の場合１ −の場合−１ ゼロの場合ゼロを返す.
    if(num>0){
        return 1;
    }else if(num<0){
        return -1;
    }else{
        return 0;
    }
}

//-------------------------------------------------
int Algorithm::AbsoluteIncrement(int num)
{
    //絶対値をインクリメントする関数
    const int tmp=SignFunction(num);
    num=num-tmp;
    return num;
}

//-------------------------------------------------
int Algorithm::AbsoluteDecrement(int num)
{
    //絶対値をデクリメントする関数
    const int tmp=SignFunction(num);
    num=num-tmp;
    return num;
}
//-------------------------------------------------
vertex Algorithm::DirectionConvert(const int direction)
{
    auto convertDirection=[](const int direction){
        //0下1左2右3上4左上5右上6左下7右下
        //vertex vert(0,0);
        const int f=1;
        vertex vert;
        switch (direction){
        case 0:
            //0下
            vert=vertex(0,-f);
            break;
        case 1:
            //1左
            vert=vertex(f,0);
            break;
        case 2:
            //2右
            vert=vertex(-f,0);
            break;
        case 3:
            //3上
            vert=vertex(0,f);
            break;
        case 4:
            //4左上
            vert=vertex(f,-f);
            break;
        case 5:
            //5右上
            vert=vertex(f,f);
            break;
        case 6:
            //6左下
            vert=vertex(-f,-f);
            break;
        case 7:
            //7右下
            vert=vertex(-f,f);
            break;
        default:
            vert=vertex(0,-f);
            break;
        }
        return vert;
    };
    return convertDirection(direction);
}


//-------------------------------------------------
bool Algorithm::SegmentIntersection(Vector vect1, Vector vect2)
{
    //線分交差判定関数
    const int x1=vect1.vs.vx,x2=vect1.vt.vx;
    const int y1=vect1.vs.vy,y2=vect1.vt.vy;

    const int x3=vect2.vs.vx,x4=vect2.vt.vx;
    const int y3=vect2.vs.vy,y4=vect2.vt.vy;

    return SegmentIntersection(x1,y1,x2,y2,x3,y3,x4,y4);
}

/*
bool Kudan_Algorithm::SegmentIntersection(point x1, point y1, point x2, point y2, point x3, point y3, point x4, point y4)
{

    const int tc=((x1-x2)*(y3-y1))+((y1-y2)*(x1-x3));
    const int td=((x1-x2)*(y4-y1))+((y1-y2)*(x1-x4));

    if(tc*td<0){
        const int tc2=((x3-x4)*(y1-y3))+((y3-y4)*(x3-x1));
        const int td2=((x3-x4)*(y2-y3))+((y3-y4)*(x3-x2));
        if(tc2*td2<0){
            return true;
        }
    }
    return false;
}*/

//-------------------------------------------------
bool Algorithm::SegmentIntersection(point x1, point y1, point x2, point y2, point x3, point y3, point x4, point y4)
{

    //const int x1=vect1.vs.vx,x2=vect1.vt.vx;
    //const int y1=vect1.vs.vy,y2=vect1.vt.vy;

    //const int x3=vect2.vs.vx,x4=vect2.vt.vx;
    //const int y3=vect2.vs.vy,y4=vect2.vt.vy;
     //線分交差判定関数
    const int x2_x1=x2-x1;
    const int y2_y1=y2-y1;

    const int x4_x3=x4-x3;
    const int y4_y3=y4-y3;

    const int x4_x1=x4-x1;
    const int y4_y1=y4-y1;
    const int delta=(x2-x1)*(y4-y3)-(y2-y1)*(x4-x3);
    if(delta==0){
        //deltaがゼロなら交差しない　ゼロ除算チェック
        return false;
    }
    const int ksi=((y4_y3)*(x4_x1))-((x4_x3)*(y4_y1));
    //const double ramda=static_cast<double>(ksi)/static_cast<double>(delta);
    if((ksi*delta)<0){
        return false;
    }
    if(abs(ksi)>abs(delta)){
        return false;
    }
   /* if(!Kudan_Algorithm::RengedValue(ramda,1.0,0.0)){
        return false;
    }*/

    const int eta=(x2-x1)*(y4-y1)-(y2-y1)*(x4-x1);
    //const double mu=static_cast<double>(eta)/static_cast<double>(delta);
    if((eta*delta)<0){
        return false;
    }
    if(abs(eta)>abs(delta)){
        return false;
    }
    /*
    if(!Kudan_Algorithm::RengedValue(mu,1.0,0.0)){
        return false;
    }*/
    return true;
}

//-------------------------------------------------
bool Algorithm::SegmentLeftPoint(Vector vect1, vertex vert)
{
    //線分の左側に点があるかどうか判定
    const int vx2_vx1=vect1.vt.vx-vect1.vs.vx;
    const int yp_vy1=vert.vy-vect1.vs.vy;

    const int xp_vx1=vert.vx-vect1.vs.vx;
    const int vy2_vy1=vect1.vt.vy-vect1.vs.vy;
    const int result=(vx2_vx1*yp_vy1)-(xp_vx1*vy2_vy1);
    if(result>=0){
        //点は線分の方向の左に位置する
        return true;
    }
    return false;
}

//-------------------------------------------------
bool Algorithm::SegmentLeftPoint(point x1, point y1, point x2, point y2, point xp, point yp)
{

    const int vx2_vx1=x2-x1;
    const int yp_vy1=yp-y1;

    const int xp_vx1=xp-x1;
    const int vy2_vy1=y2-y1;
    const int result=(vx2_vx1*yp_vy1)-(xp_vx1*vy2_vy1);
    if(result>=0){
        //点は線分の方向の左に位置する
        return true;
    }
    return false;
}

//-------------------------------------------------
Vector Algorithm::VectorResize(Vector vect, const double fact)
{
    double dx=vect.vt.vx-vect.vs.vx;
    double dy=vect.vt.vy-vect.vs.vy;
    dx=dx*fact;
    dy=dy*fact;
    Vector out;
    out.vs=vect.vs;
    out.vt.vx=vect.vs.vx+dx;
    out.vt.vy=vect.vs.vy+dy;
    return out;
}

//-------------------------------------------------
Vector Algorithm::VectorResize(Vector vect, const int longvert)
{
    double longelem;
    int dx=vect.vt.vx-vect.vs.vx;
    int dy=vect.vt.vy-vect.vs.vy;
    if(dx>dy){
        longelem=dx;
    }else{
        longelem=dy;
    }
    double fact=longvert;
    fact=fact/longelem;
}

//-------------------------------------------------
vertex Algorithm::VectorResize(double dx,double dy, const double fact)
{
    dx=dx*fact;
    dy=dy*fact;
    vertex out;
    out.vx=dx;
    out.vy=dy;
    return out;
}

//-------------------------------------------------
int Algorithm::BigLitle(const int num1,const int num2)
{
    int anum1=abs(num1),anum2=abs(num2);
    if(anum1>anum2){
        return anum1;
    }else{
        return anum2;
    }
}

//-------------------------------------------------
int Algorithm::SignLitleBig(const int num1, const int num2)
{
    int anum1=abs(num1),anum2=abs(num2);
    if(anum1<anum2){
        return num1;
    }else{
        return num2;
    }
}

//-------------------------------------------------
bool Algorithm::RengedValue(double num, double max, double min)
{
    if(num<=max){
        if(num>=min){
            return true;
        }
    }
    return false;
}

//-------------------------------------------------
bool Algorithm::RengedValue(cint num,cint max,cint min)
{
    if(num<=max){
        if(num>=min){
            return true;
        }
    }
    return false;
}


//-------------------------------------------------
bool Algorithm::RengedValue2D(cint x, cint maxx, cint minx, cint y, cint maxy, cint miny)
{
    if(RengedValue(x,maxx,minx)){
        if(RengedValue(y,maxy,miny)){
            return true;
        }
    }
    return false;
}

//-------------------------------------------------
int Algorithm::DimensionConvert(cint d1, cint d2, cint row)
{
    int out=d1*row;
    out+=d2;
    return out;
}

//-------------------------------------------------
bool Algorithm::isFull(QVector<int> &in)
{
    cint count=in.count();
    if(count==0){
        return true;
    }
    if(count==1){
        return true;
    }
    cint num=in[0];
    for(int i=1;i<count;i++){
        if(num!=in[i]){
            return false;
        }
    }

    return true;
}

//-------------------------------------------------
int Algorithm::mode(QVector<int> &in)
{
    //最頻値
    const int count=in.count();
    if(count>0){
        qSort(in);
        QVector<QPair<int,int>> info;
        QPair<int,int> tmp;
        tmp.first=1;
        tmp.second=in[0];
        info.append(tmp);
        int pc=0;
        for(int i=1;i<count;i++){
            const int c2=info.count();
            if(info[c2-1].second==in[i]){
                info[c2-1].first++;
            }else{
                QPair<int,int> tmp2;
                tmp2.first=1;
                tmp2.second=in[i];
                info.append(tmp2);
            }
        }
        //逆順でソート
        qSort(info.begin(),info.end(),qGreater<QPair<int,int>>());
        return info[0].second;

    }else{
        return 0;
    }
}

//-------------------------------------------------
int Algorithm::mean(cint num, cint num2, cint hint)
{
    cint sum=num+num2;
    cint me=sum/2;
    //もし余りがある場合
    if(sum%2!=0){
        //平均と平均に１を足した数とヒントとの差を取って、近い方を返す
        cint dis=abs(hint-(me));
        cint dis2=abs(hint-(me+1));
        if(dis2>dis){
            return me;
        }else{
            return me+1;
        }
    }else{
        return me;
    }
}

//-------------------------------------------------
bool Algorithm::LineSegmentIntersectionPoint(Vector vect1, Vector vect2, vertex &result)
{
    //線分の交点を計算
    const int x1=vect1.vs.vx,x2=vect1.vt.vx;
    const int y1=vect1.vs.vy,y2=vect1.vt.vy;

    const int x3=vect2.vs.vx,x4=vect2.vt.vx;
    const int y3=vect2.vs.vy,y4=vect2.vt.vy;

    const int x2_x1=x2-x1;
    const int y2_y1=y2-y1;

    const int x4_x3=x4-x3;
    const int y4_y3=y4-y3;

    const int x4_x1=x4-x1;
    const int y4_y1=y4-y1;
    const int ksi=((y4_y3)*(x4_x1))-((x4_x3)*(y4_y1));
    //const int eta=(x2-x1)*(y4-y1)-(y2-y1)*(x4-x1);
    //const double delta=((y4_y3)*(x2_x1))-((x4_x3)*(y2_y1));
    const int delta=(x2-x1)*(y4-y3)-(y2-y1)*(x4-x3);
    if(delta==0){
        //deltaがゼロなら交差しない　ゼロ除算チェック
        return false;
    }
    const double ramda=static_cast<double>(ksi)/static_cast<double>(delta);
    //ramdaが1以上でも計算する 交点は線分を延長した直線上のどこか
    const double verx=x1+(ramda*(x2_x1));
    const double very=y1+(ramda*(y2_y1));
    result.vx=round(verx);
    result.vy=round(very);
    return true;
}

//-------------------------------------------------
bool Algorithm::SegmentIntersectionPoint(Vector vect1, Vector vect2,vertex &result)
{
    //線分が交差していることを確認
    //if(Kudan_Algorithm::SegmentIntersection(vect1,vect2)){
        //線分の交点を計算
        const int x1=vect1.vs.vx,x2=vect1.vt.vx;
        const int y1=vect1.vs.vy,y2=vect1.vt.vy;

        const int x3=vect2.vs.vx,x4=vect2.vt.vx;
        const int y3=vect2.vs.vy,y4=vect2.vt.vy;

        const int x2_x1=x2-x1;
        const int y2_y1=y2-y1;

        const int x4_x3=x4-x3;
        const int y4_y3=y4-y3;

        const int x4_x1=x4-x1;
        const int y4_y1=y4-y1;
        const int ksi=((y4_y3)*(x4_x1))-((x4_x3)*(y4_y1));
        const int eta=(x2-x1)*(y4-y1)-(y2-y1)*(x4-x1);
        //const double delta=((y4_y3)*(x2_x1))-((x4_x3)*(y2_y1));
        const int delta=(x2-x1)*(y4-y3)-(y2-y1)*(x4-x3);
        if(delta==0){
            //deltaがゼロなら交差しない　ゼロ除算チェック
            return false;
        }
        const double ramda=static_cast<double>(ksi)/static_cast<double>(delta);
        const double mu=static_cast<double>(eta)/static_cast<double>(delta);

        if(!Algorithm::RengedValue(ramda,1.0,0.0)){
            return false;
        }
        if(!Algorithm::RengedValue(mu,1.0,0.0)){
            return false;
        }
        const double verx=x1+(ramda*(x2_x1));
        const double very=y1+(ramda*(y2_y1));
        result.vx=round(verx);
        result.vy=round(very);
        return true;
   //}else{
      // return false;
  // }
}


//-------------------------------------------------
int Algorithm::near(cint num, QVector<int> array)
{
    //配列の中から一番 近い数を算出
    cint cut=array.count();
    if(cut>1){
        int index=0;
        int out=abs(num-array[index]);
        if(out==0){
            return array[0];
        }
        for(int i=1;i<cut;i++){
            cint tmpdis=abs(num-array[i]);
            if(tmpdis<out){
                out=tmpdis;
                index=i;
                if(out==0){
                    break;
                }
            }
        }
        return array[index];
    }else if(cut==1){
        return array[0];
    }else{
        return num;
    }
}

//-------------------------------------------------
QVector<int> Algorithm::SameSigns(cint num, QVector<int> array)
{
    const int row=array.count();
    QVector<int> out(row);
    //符号が同じなら 追加 違うなら追加しない ０は追加する
    const int antisign=SignFunction(-num);
    int ind=0;
    for(int i=0;i<row;i++){
        const int tsign=SignFunction(array[i]);
        if(tsign!=antisign){
            out[ind]=array[i];
            ind++;
        }
    }
    out.resize(ind);
    return out;
}

//-------------------------------------------------
int Algorithm::Multiplication(cint num, cint fact)
{
    return num*fact;
}

//-------------------------------------------------
int Algorithm::Division(cint num, cint fact)
{
    return num/fact;
}

//-------------------------------------------------
//最大値と最小値を返す関数
//Kudan_Algorithm::arrayMaxMinResult Kudan_Algorithm::arrayMaxMin(int &max, int &min, QVector<int> array)
//{
//
//}

//-------------------------------------------------
//クロックカウント
unsigned long long Algorithm::rdtsc(){
  unsigned int a,b;

  //asm("rdtsc":"=a"(a),"=d"(b));

  //return ((long long)b<<32 | a);

  return 345345436;
}

//-------------------------------------------------
//二点間距離
int Algorithm::DistancePoints(point x1, point y1, point x2, point y2)
{
    double out=pow((x1-x2),2)+pow((y1-y2),2);
    out=sqrt(out);
    return out;
}
//-------------------------------------------------
//ハッシュ計算
/*
template <typename T>
QPair<bool,T> Kudan_Algorithm::HashIndex(const QHash<int,T> &hash, const int key)
{
    //ハッシュ検索
    auto itr=hash.find(key);
    if(itr!=hash.end()){
        //存在するなら値を返す 真を返す
        QPair<bool,T> out;
        out.first=true;
        out.second=*itr;
        return out;
    }else{
        //存在しないなら 偽を返す
        QPair<bool,T> out;
        out.first=false;
        //out.second=*itr;
        return out;
    }
}
*/
//-------------------------------------------------
//床関数 割り算
int Algorithm::DivisionFloor(cint num, cint range)
{
    if(range==0){
        return INT_MAX;
    }
    double numd=static_cast<double>(num),ranged=static_cast<double>(range);
    const double outd=numd/ranged;
    const int out=floor(outd);
    return out;
}











