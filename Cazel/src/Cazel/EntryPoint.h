#pragma once

#ifdef CZ_PLATFORM_WINDOWS

#include "Application.h"

int main(int argc, char** argv) {
  // allocate it on Heap
  auto app = Cazel::CreateApplication();

  app->Run();

  delete app;
}

#endif