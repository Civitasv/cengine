#pragma once

#include "Cazel/Core/Application.h"
#include "Cazel/Core/Log.h"

int main(int argc, char **argv) {
  Cazel::Log::Init();
  CZ_CORE_WARN("TEST Initialized Log!");
  CZ_INFO("Initialized Log: {}!", 0);

  // allocate it on Heap
  auto app = Cazel::CreateApplication();

  app->Run();

  delete app;
}