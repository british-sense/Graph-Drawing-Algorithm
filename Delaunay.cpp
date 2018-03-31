#include <iostream>
#include <cmath>
#include <cfloat>
#include <map>
#include <set>

struct Point{  
    
    double x;  
    double y;  
 
    bool operator==(const Point &p) const{  
      return (x == p.x && y == p.y);  
    }  

    bool operator<(const Point &p) const{  
      return x != p.x ? x < p.x : y < p.y;  
    }  
};

struct Circle{
    Point center;
    double radius;
};

class Triangle{

    public:  
    const Point *p1, *p2, *p3;  // 頂点座標  

    private:  
    // 最小の頂点を返す     
    inline const Point *MinPoint() const{  
        return *p1 < *p2 && *p1 < *p3 ? p1 : *p2 < *p3 ? p2 : p3;  
    }  

    // 中央の頂点を返す  
    inline const Point *MidPoint() const{  
        return *p1 < *p2 && *p2 < *p3 || *p3 < *p2 && *p2 < *p1 ? p2 : 
               *p2 < *p3 && *p3 < *p1 || *p1 < *p3 && *p3 < *p2 ? p3 : p1;  
    }  

    // 最大の頂点を返す  
    inline const Point *MaxPoint() const{  
        return *p2 < *p1 && *p3 < *p1 ? p1 : *p3 < *p2 ? p2 : p3;  
    }  

    public:
    // 等価性の判定  
    bool operator==(const Triangle &t) const{  
        return *p1 == *t.p1 && *p2 == *t.p2 && *p3 == *t.p3 || 
               *p1 == *t.p2 && *p2 == *t.p3 && *p3 == *t.p1 || 
               *p1 == *t.p3 && *p2 == *t.p1 && *p3 == *t.p2 || 
               *p1 == *t.p3 && *p2 == *t.p2 && *p3 == *t.p1 || 
               *p1 == *t.p2 && *p2 == *t.p1 && *p3 == *t.p3 || 
               *p1 == *t.p1 && *p2 == *t.p3 && *p3 == *t.p2;  
    }  
 
    // 大小判定
    bool operator<(const Triangle &t) const{  
        return !(*MinPoint() == *t.MinPoint()) ? *MinPoint() < *t.MinPoint() :  
               !(*MidPoint() == *t.MidPoint()) ? *MidPoint() < *t.MidPoint() :  
               *MaxPoint() < *t.MaxPoint();  
    }  

    // 他の三角形と共通の点を持つかどうか
    bool CommonPoint(const Triangle &t) const{  
        return *p1 == *t.p1 || *p1 == *t.p2 || *p1 == *t.p3 ||  
               *p2 == *t.p1 || *p2 == *t.p2 || *p2 == *t.p3 ||  
               *p3 == *t.p1 || *p3 == *t.p2 || *p3 == *t.p3;  
    }
};

class Delaunay{

    // 型定義
    typedef const std::set<Point> ConstPointSet;  
    typedef ConstPointSet::const_iterator ConstPointIter;
    typedef std::set<Triangle> TriangleSet;
    typedef std::set<Triangle>::iterator TriangleIter;
    typedef std::map<Triangle, bool> TriangleMap;

    private:
    // 重複判定 <三角形, 重複しているかどうか>
    static inline void OverlapJudge(TriangleMap *pjudge, Triangle &tri){
        TriangleMap::iterator itr = pjudge->find(tri);  
        if(itr != pjudge->end() && itr->second){  
            pjudge->erase(itr);  
            pjudge->insert(TriangleMap::value_type(tri, false));  
        }else{  
            pjudge->insert(TriangleMap::value_type(tri, true));  
        }
    };

    static void DelaunayTriangle(ConstPointSet &pointset, TriangleSet *ptriset){
        
        // 全ての点を内包する三角形を作る
        Point max, min;
        max.x = -DBL_MAX, max.y = -DBL_MAX; 
        min.x = DBL_MAX, min.y = DBL_MAX; 
        
        for(ConstPointIter itr = pointset.begin(); itr != pointset.end(); itr++){
            Point pt;
            pt.x = itr->x; pt.y = itr->y;
            if(max.x < pt.x) max.x = pt.x; if(max.y < pt.y) max.y = pt.y;
            if(min.x > pt.x) min.x = pt.x; if(min.y > pt.y) min.y = pt.y;
        }

        Point center;
        center.x  = (max.x - min.x) * 0.5;
        center.y  = (max.y - min.y) * 0.5;

        Point diff;
        diff.x = max.x - center.x;
        diff.y = max.y - center.y;  
        double radius = sqrt(diff.x * diff.x + diff.y * diff.y) + 1.0;  
  
        Triangle EncloseTriangle;
        Point *p1 = new Point;  // メモリ確保（314行目で解放）  
        p1->x = center.x - sqrt(3.0) * radius;  
        p1->y = center.y - radius;  
  
        Point *p2 = new Point;  // メモリ確保（315行目で解放）  
        p2->x = center.x + sqrt(3.0) * radius;  
        p2->y = center.y - radius;  
  
        Point *p3 = new Point;  // メモリ確保（316行目で解放）  
        p3->x = center.x;  
        p3->y = center.y + 2.0 * radius;  
  
        EncloseTriangle.p1 = p1;  
        EncloseTriangle.p2 = p2;  
        EncloseTriangle.p3 = p3;

        ptriset->insert(EncloseTriangle);

        // 点を順番に探索していく
        for(ConstPointIter pitr = pointset.begin(); pitr != pointset.end(); pitr++){  
        const Point *p = &*pitr;  
  
        // 追加候補の三角形を保持する一時マップ  
        TriangleMap tmptriangle;

            // 三角形のセットからひとつずつ要素を取り出し,
            // 三角形の外接円の内部に含まれるかどうかを判定する
            for(TriangleIter titr = ptriset->begin(); titr != ptriset->end(); ){

                Triangle t = *titr;
                Circle c;

                double m = 2.0 * ((t.p2->x - t.p1->x) * (t.p3->y - t.p1->y) - (t.p2->y - t.p1->y) * (t.p3->x - t.p1->x));    
                double x = ((t.p3->y - t.p1->y) * (t.p2->x * t.p2->x - t.p1->x * t.p1->x + t.p2->y * t.p2->y - t.p1->y * t.p1->y) + (t.p1->y - t.p2->y) * (t.p3->x * t.p3->x - t.p1->x * t.p1->x + t.p3->y * t.p3->y - t.p1->y * t.p1->y)) / m;  
                double y = ((t.p1->x - t.p3->x) * (t.p2->x * t.p2->x - t.p1->x * t.p1->x + t.p2->y * t.p2->y - t.p1->y * t.p1->y) + (t.p2->x - t.p1->x) * (t.p3->x * t.p3->x - t.p1->x * t.p1->x + t.p3->y * t.p3->y - t.p1->y * t.p1->y)) / m;

                c.center.x = x;
                c.center.y = y;

                diff.x = t.p1->x - x; 
                diff.y = t.p1->y - y;
                radius = sqrt(diff.x * diff.x + diff.y * diff.y);

                c.radius = radius; 
            }
        }
    };
};

int main(){

    return 0;
}