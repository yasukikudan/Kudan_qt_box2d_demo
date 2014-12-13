#ifndef LABYRINTHFACTORY_H
#define LABYRINTHFACTORY_H

#include <memory>
#include <vector>
#include <QList>
#include <random>
#include <QDebug>


struct LabyrinthCell{
    int cellnum;
    bool top=true;
    bool bottom=true;
    bool left=true;
    bool right=true;
};

template <class T>
bool rangeChacky(const int x,const T& v){
    return (x>=0&&x<v.size())?(true):(false);
}

class LabyrinthData{
    int cellx;
    int celly;
public:
    QVector<LabyrinthCell> cells2d;
    int isX() const {return cellx;}
    int isY() const {return celly;}
    LabyrinthData(const int x,const int y):cellx(x),celly(y){
        cells2d.resize(x*y);
        const int len=cells2d.size();
        //番号を振る
        QList<int> indexsm;
        for(int i=0;i<len;i++){
            cells2d[i].cellnum=i;
            indexsm.append(i);
        }
        std::random_device seed_gen;
        std::mt19937 randgen(seed_gen());
        std::uniform_int_distribution<int> d(0,3);

        auto genLabyrinthcycle=[&](){
            //QList<int> indexs=indexsm;

            std::uniform_int_distribution<int> dist(0,len-1);
            for(int i=0;;i++){
                //乱数生成
                const int lindex=dist(randgen);
                //壊す壁を生成
                const int n=d(randgen);
                if(n==0){
                    //上方向のマスのインデックスを計算
                    const int topindex=lindex-x;
                    //範囲検査
                    if(rangeChacky(topindex,cells2d)){
                        if(cells2d[topindex].cellnum!=cells2d[lindex].cellnum){
                            cells2d[topindex].bottom=false;
                            cells2d[lindex].top=false;
                            if(update(cells2d[topindex].cellnum,cells2d[lindex].cellnum)){
                                return;
                            }
                        }
                    }
                }else if(n==1){
                    //左方向のマスのインデックスを計算
                    const int leftindex=lindex-1;
                    if(lindex%x!=0){
                        if(cells2d[leftindex].cellnum!=cells2d[lindex].cellnum){
                            cells2d[leftindex].right=false;
                            cells2d[lindex].left=false;
                            if(update(cells2d[leftindex].cellnum,cells2d[lindex].cellnum)){
                                return ;
                            }
                        }
                    }
                }else if(n==2){
                    const int rightindex=lindex+1;
                    if(rightindex%x!=0){
                        if(cells2d[rightindex].cellnum!=cells2d[lindex].cellnum){

                            cells2d[rightindex].left=false;
                            cells2d[lindex].right=false;
                            if(update(cells2d[rightindex].cellnum,cells2d[lindex].cellnum)){
                                return;
                            }
                        }
                    }

                }else if(n==3){
                    //下方向のマスのインデックスを計算
                    const int bottomindex=lindex+x;
                    //範囲検査
                    if(rangeChacky(bottomindex,cells2d)){
                        if(cells2d[bottomindex].cellnum!=cells2d[lindex].cellnum){
                            cells2d[bottomindex].top=false;
                            cells2d[lindex].bottom=false;
                            if(update(cells2d[bottomindex].cellnum,cells2d[lindex].cellnum)){
                                return;
                            }
                        }
                    }
                }
                if(i%1000==0){
                    if(end()){
                        return;
                    }
                }
            }

        };

        genLabyrinthcycle();
    }

    bool end(){
        const int old=cells2d[0].cellnum;
        const int len=cells2d.size();
        bool endflag=true;
        for(int i=0;i<len;i++){
            if(cells2d[i].cellnum!=old){
                endflag=false;
            }
        }
        return endflag;
    }

    bool update(const int old,const int now){
        const int len=cells2d.size();
        bool endflag=true;
        for(int i=0;i<len;i++){
            if(cells2d[i].cellnum==old){
                cells2d[i].cellnum=now;
                endflag=false;
            }
        }
        return endflag;
    }
};


class LabyrinthFactory
{
public:
    static LabyrinthData create(const int x,const int y){
        LabyrinthData out(x,y);
        return out;

    }
private:
    LabyrinthFactory();
};

#endif // LABYRINTHFACTORY_H
