#include <iostream>
#include "map"
#include "unordered_map"
#include "vector"
using namespace std;

int main() {
    unordered_map<int, int> map;
//    cout << map[0] << endl;
    cout << map.count(0) << endl;
//    cout << map.find(0)->first << endl;
    return 0;
}
