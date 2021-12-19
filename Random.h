//
// Created by Vishweshwar Ramanakumar on 4/19/21.
//

#ifndef PROJECT3_RANDOM_H
#define PROJECT3_RANDOM_H
#include <random>
using namespace std;


class Random {

public:
    static mt19937 random;
    static int Int(int min, int max);
    static float Float(float min, float max);

};


#endif //PROJECT3_RANDOM_H
