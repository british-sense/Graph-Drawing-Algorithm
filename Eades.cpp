#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <list>

using namespace std;

#define NUM 6

static int elength[NUM][NUM];

struct Point{
    double x;
    double y;
};

struct Node{

    Point rectangle;
    Point velocity;
    Point force;

    void Eular(double dt){
        rectangle.x += dt * velocity.x;
        rectangle.y += dt * velocity.y;
        velocity.x += dt * force.x;
        velocity.y += dt * force.y;
    };

    void CoulombForce(Node another){

        double g = 1;
        double dx = another.rectangle.x - rectangle.x;
        double dy = another.rectangle.y - rectangle.y;
        double d2 = dx * dx + dy * dy;

        if(d2 < 0.001){
            force.x += (double)rand() / RAND_MAX - 0.5;
            force.y += (double)rand() / RAND_MAX - 0.5;
            return;
        }

        double cos = dx / d;
        double sin = dy / d;

        force.x += g / d2 * cos;
        force.y += g / d2 * sin;
    }

    void SpringForce(Node another){
        
        double k = 1;
        double l = 60;
        double dx = another.rectangle.x - rectangle.x;
        double dy = another.rectangle.y - rectangle.y;
        double d2 = dx * dx + dy * dy;
        
        if(d2 < 0.001){
            force.x += (double)rand() / RAND_MAX - 0.5;
            force.y += (double)rand() / RAND_MAX - 0.5;
            return;
        }

        double d = sqrt(d2);
        double cos = dx / d;
        double sin = dy / d;
        double dl = d - l;

        force.x += k * dl * cos;
        force.y += k * dl * sin;
    };

    void FrictionalForce(Node another){
        double m = 0.3;
        force.x += -m * velocity.x;
        force.y += -m * velocity.y;
    }
};

int main(){

    int i, j, k;
    vector<Node> node(NUM);

    // 力学モデル
    for(k = 0; k < 1000; k++){

        for(i = 0; i < NUM; i++){

            node[i].force.x = 0;
            node[i].force.y = 0;

            // 外力
            for(j = 0; j < NUM; j++){
                if(i == j) continue;
                node[i].CoulombForce(node[j])
                node[i].SpringForce(node[j]);
            }

            // 合成
            node[i].Eular(0.1);
        }

    }

    // 出力
    for(i = 0; i < MAX; i++){
        cout << i << " " << node[i].rectangle.x << " " << node[i].rectangle.y << endl;
    }

    return 0;
}