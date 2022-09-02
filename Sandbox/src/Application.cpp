#include <iostream>

namespace Cazel {
__declspec(dllimport) void Setup();
}

int main() {
  Cazel::Setup();
  std::cin.get();
}

