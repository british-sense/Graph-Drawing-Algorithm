#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <list>

using namespace std;

#define NUM 6

struct Point{
    double x;
    double y;
};

struct Node{

    Point rectangle;
    Point velocity;
    Point force;

    Node(){
        rectangle.x = ((double)rand() / RAND_MAX - 0.5) * 10;
        rectangle.y = ((double)rand() / RAND_MAX - 0.5) * 10;
        velocity.x = 0;
        velocity.y = 0;
        force.x = 0;
        force.y = 0;
    }

    void Eular(double dt){
        rectangle.x += dt * velocity.x;
        rectangle.y += dt * velocity.y;
        velocity.x += dt * force.x;
        velocity.y += dt * force.y;
    };

    void SpringForce(Node another){
        
        double l = 10.0;
        double dx = another.rectangle.x - rectangle.x;
        double dy = another.rectangle.y - rectangle.y;
        double d2 = dx * dx + dy * dy;
        
        if(d2 < 0.001){
            force.x = (double)rand() / RAND_MAX - 0.5;
            force.y = (double)rand() / RAND_MAX - 0.5;
            return;
        }

        double d = sqrt(d2);
        double cos = dx / d;
        double sin = dy / d;
        double dl = d - l;

        force.x = dl * cos;
        force.y = dl * sin;
    };

    void FrictionalForce(Node another){
        double m = 0.3;
        force.x = -m * velocity.x;
        force.y = -m * velocity.y;
    }
};

int main(){

    int i, j, k;
    vector<Node> data(NUM);

    // 力学モデル
    for(k = 0; k < 1000000; k++){

        for(i = 0; i < NUM; i++){

            data[i].force.x = 0;
            data[i].force.y = 0;

            for(j = 0; j < NUM; j++){
                if(i == j) continue;
                data[i].SpringForce(data[j]);
                data[i].FrictionalForce(data[j]);
            }

            data[i].Eular(0.1);
        }

    }

    // 出力
    for(i = 0; i < 6; i++){
        cout << i << " " << data[i].rectangle.x << " " << data[i].rectangle.y << endl;
    }

    return 0;
}