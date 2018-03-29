#include <iostream>
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
    inline const Point *minpoint() const{  
        return *p1 < *p2 && *p1 < *p3 ? p1 : *p2 < *p3 ? p2 : p3;  
    }  

    // 中央の頂点を返す  
    inline const Point *midpoint() const{  
        return *p1 < *p2 && *p2 < *p3 || *p3 < *p2 && *p2 < *p1 ? p2 : 
               *p2 < *p3 && *p3 < *p1 || *p1 < *p3 && *p3 < *p2 ? p3 : p1;  
    }  

    // 最大の頂点を返す  
    inline const Point *maxpoint() const{  
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
        return !(*minpoint() == *t.minpoint()) ? *minpoint() < *t.minpoint() :  
               !(*midpoint() == *t.midpoint()) ? *midpoint() < *t.midpoint() :  
               *maxpoint() < *t.maxpoint();  
    }  

    // 他の三角形と共通の点を持つかどうか
    bool commonpoint(const Triangle &t) const{  
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
    static inline void overlapjudge(TriangleMap *pjudge, Triangle &tri){
        TriangleMap::iterator itr = pjudge->find(tri);  
        if(itr != pjudge->end() && itr->second){  
            pjudge->erase(itr);  
            pjudge->insert(TriangleMap::value_type(tri, false));  
        }else{  
            pjudge->insert(TriangleMap::value_type(tri, true));  
        }
    };
}

int main(){

    return 0;
}