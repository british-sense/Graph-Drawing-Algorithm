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
    vector<int> negihbor;

    void Eular(double dt, Point force){
        rectangle.x += dt * velocity.x;
        rectangle.y += dt * velocity.y;
        velocity.x += dt * force.x;
        velocity.y += dt * force.y;
    };

    void SpringForce(Node another){
        
        double k = 0.1;
        double l = 60.0;
        double dx = this.rectangle.x - another.rectangle.x;
        double dy = this.rectangle.y - another.rectangle.y;
        double d2 = dx * dx + dy + dy;
        
        if(d2 < 0.001){
            force.x = (double)rand() / RAND_MAX - 0.5;
            force.y = (double)rand() / RAND_MAX - 0.5;
        }

        double d = sqrt(d2);
        double cos = dx / d;
        double sin = dy / d;
        double dl = d - l;

        force.x = -k * dl * cos;
        force.y = -k * dl * sin;
    };

    void ResilienceForce(Node another){

        double g = 500.0;
        dx = this.rectangle.x - anothe.rectangle.x;
        dy = this.rectangle.y - anothe.rectangle.y;
        double d2 = dx * dx + dy + dy;
        
        if(d2 < 0.001){
            force.x = (double)rand() / RAND_MAX - 0.5;
            force.y = (double)rand() / RAND_MAX - 0.5;
        }

        double d = sqrt(d2);
        double cos = dx / d;
        double sin = dy / d;
        double dl = d - l;

        force.x = g / d2 * cos;
        force.y = g / d2 * sin;
    };

    void FrictionalForce(Node another){
        double m = 0.3;
        force.x = -m * velocity.x;
        force.y = -m * velocity.y;
    }
};

int main(){

    int i;
    vector<Node> data(6);
    data[0].id = 1;
    data[0].neighbor.push_back(2);
    data[0].neighbor.push_back(3);
    data[1].id = 2;
    data[1].neighbor.push_back(1);
    data[2].id = 3;
    data[2].neighbor.push_back(1);
    data[2].neighbor.push_back(4);
    data[2].neighbor.push_back(5);
    data[3].id = 4;
    data[3].neighbor.push_back(3);
    data[4].id = 5;
    data[4].neighbor.push_back(3);
    data[4].neighbor.push_back(6);
    data[5].id = 6;
    data[5].neighbor.push_back(5);

    return 0;
}