#include <vector>
#include <string>
#include <iostream>


typedef Node struct {
  std::string prefix
  std::vector<Node*> Nodes
  };

int CompareStrings(std::string a, std::string b)
{
  std::string cmp;
  if (a.length() < b.length()) {
    cmp = a;
  } else {
    cmp = b;
  }

 
  int idx = 0;
  for (;idx<cmp.length();++idx) {
    if (a[idx] != b[idx]) {
      break;
    }
    std::cout << idx;
  }

  return idx;
}

int main() {
  std::cout << CompareStrings("Helllooooo", "Hell");
}


