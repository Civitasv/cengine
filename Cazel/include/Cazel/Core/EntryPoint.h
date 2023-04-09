#pragma once

#include "Cazel/Core/Application.h"
#include "Cazel/Core/Log.h"

int main(int argc, char **argv) {
  Cazel::Log::Init();

  // allocate it on Heap
  auto app = Cazel::CreateApplication();

  app->Run();

  delete app;
}