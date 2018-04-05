#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <vector>
#include <random>
#include <list>
#include <stack>

using namespace std;

#define NUM 300

static int elength[NUM][NUM];

struct Point{
    double x;
    double y;
};

struct Node{

    Point rectangle;
    Point velocity;
    Point force;

    Node(){
        rectangle.x = ((double)rand() / RAND_MAX) * 500;
        rectangle.y = ((double)rand() / RAND_MAX) * 500;
        velocity.x = 0;
        velocity.y = 0;
        force.x = 0;
        force.y = 0;
    }

    void CoulombForce(Node another){

        double g = 1;
        double dx = another.rectangle.x - rectangle.x;
        double dy = another.rectangle.y - rectangle.y;
        double d2 = dx * dx + dy * dy;

        if(d2 < 0.001){
            force.x -= (double)rand() / RAND_MAX - 0.5;
            force.y -= (double)rand() / RAND_MAX - 0.5;
            return;
        }

        double d = sqrt(d2);

        double cos = dx / d;
        double sin = dy / d;

        force.x -= (g / d2) * cos;
        force.y -= (g / d2) * sin;
    }

    void SpringForce(Node another, double diff){
        
        double k = 0.1;
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
        double dd = d - diff;

        force.x += k * dd * cos;
        force.y += k * dd * sin;
    };

    void FrictionalForce(){
        double m = 0.3;
        force.x += -m * velocity.x;
        force.y += -m * velocity.y;
    }

     void Eular(double dt){
        rectangle.x += dt * velocity.x;
        rectangle.y += dt * velocity.y;
        velocity.x += dt * force.x;
        velocity.y += dt * force.y;
    };
};

int main(){

    int i, j, k;
    double energy;
    vector<Node> node(NUM);

    for(i = 0; i < NUM; i++){
        for(j = 0; j < NUM; j++){
            elength[i][j] = (int)(((double)rand() / RAND_MAX) * 500);
        }
    }

    // 力学モデル
    do{
        energy = 0;
        for(i = 0; i < NUM; i++){

            node[i].force.x = 0;
            node[i].force.y = 0;

            for(j = 0; j < NUM; j++){
                if(i == j) continue;
                // クーロン力
                node[i].CoulombForce(node[j]);

                // if(繋がっていない) continue;
                // フックの法則
                node[i].SpringForce(node[j], elength[i][j]);

                // 摩擦力
                node[i].FrictionalForce();
            }

            // 力の合成
            node[i].Eular(0.01);

            // 運動エネルギーの合計
            energy += node[i].velocity.x * node[i].velocity.x;
            energy += node[i].velocity.y * node[i].velocity.y;
        }
        // cout << energy << endl;
    }while(energy > NUM);

    // 座標の出力
    for(i = 0; i < NUM; i++){
        cout << i << " " << node[i].rectangle.x << " " << node[i].rectangle.y << endl;
    }
    return 0;
}