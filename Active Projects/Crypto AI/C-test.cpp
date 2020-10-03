#include <iostream>
using namespace std;

#define print(x) cout << x << endl

class Node {
  public:
  string testVariable;
  void test() {
    print("Class created");
    print(testVariable);
  }
};

int main(int argc, char **argv) {
  print("Hello!");
  
  Node n1;
  n1.testVariable = "Test 1";
  n1.test();					//Should print 1
  
  Node n2;
  n2.testVariable = "Test 2";
  n2.test();					//Should print 2
  n1.test();					//Should print 1
  
  n2 = n1;
  n2.test();					//Should print 1
  n2.testVariable = "Test 2";
  n2.test();					//Should print 2
  n1.test();					//

  system("PAUSE");
  return 0;
}

