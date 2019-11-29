#include "BinaryNode.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    double value1, value2;
    cin >> value1 >> value2;

    Node node1 = Node(value1) + Node(value2);
    cout << node1.rep() << " = " << node1.caculate() << endl;

    Node node2 = Node(value1) - Node(value2);
    cout << node2.rep() << " = " << node2.caculate() << endl;

    Node node3 = Node(value1) * Node(value2);
    cout << node3.rep() << " = " << node3.caculate() << endl;

    Node node4 = Node(value1) / Node(value2);
    cout << node4.rep() << " = " << node4.caculate() << endl;

    return 0;
}