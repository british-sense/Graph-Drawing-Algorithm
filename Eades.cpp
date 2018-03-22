#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct Point{
    double x;
    double y;

    void add(Point v1, Point v2){
        x = v1.x + v2.x;
        y = v1.y + v2.y;
    };
};

struct Node{

    int id;
    Point rectangle;
    Point velocity;
    Point force;

    void Eular(double dt, Point force){
        rectangle.x += dt * velocity.x;
        rectangle.y += dt * velocity.y;
        velocity.x += dt * force.x;
        velocity.y += dt * force.y;
    };

    void SpringForce(Node another){
        
        double k = 0.1;
        double l = 60.0;
        double dx = rectangle.x - another.rectangle.x;
        double dy = rectangle.y - another.rectangle.y;
        double d2 = dx * dx + dy + dy;
        
        if(d2 < 0.001){
            force.x = (double)rand() / RAND_MAX - 0.5;
            force.y = (double)rand() / RAND_MAX - 0.5;
            return;
        }

        double d = sqrt(d2);
        double cos = dx / d;
        double sin = dy / d;
        double dl = d - l;

        force.x = -k * dl * cos;
        force.y = -k * dl * sin;
    };

    void FrictionalForce(Node another){
        double m = 0.3;
        force.x = -m * velocity.x;
        force.y = -m * velocity.y;
    }

    void Move(vector<Node> &other){

        int i;
        for(i = 0; i < other.size(); i++){
            SpringForce(other[i]);
            FrictionalForce(other[i]);
        }
    }
};

int main(){

    int i, j, k;
    vector<Node> data(6);

    // 初期化
    for(i = 0; i < data.size(); i++){
        data[i].id = i;
    }

    // バネモデル実行
    for(i = 0; i < 6; i++){
        for(j = 0; j < 6; j++){
            if(i != j){
                data[i].SpringForce(data[j]);
                data[i].Eular(0.01, data[j].force);             
            }
        }
    }

    // 出力
    for(i = 0; i < 6; i++){
        cout << i << " " << data[i].rectangle.x << " " << data[i].rectangle.y << endl;
    }

    return 0;
}