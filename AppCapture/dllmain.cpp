// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include "LoopbackCapture.h"

BOOL APIENTRY DllMain(HMODULE hModule,
  DWORD  ul_reason_for_call,
  LPVOID lpReserved
)
{
  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}

void Capture(int timeout)
{
  // Get capture file path
  TCHAR path[MAX_PATH];
  GetCurrentDirectory(MAX_PATH, path);
  _tcscat_s(path, MAX_PATH, L"\\Capture.wav");

  CLoopbackCapture loopbackCapture;
  HRESULT hr = loopbackCapture.StartCaptureAsync(path);
  if (FAILED(hr))
  {
    wil::unique_hlocal_string message;
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, nullptr, hr,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (PWSTR)&message, 0, nullptr);
    std::wcout << L"Failed to start capture\n0x" << std::hex << hr << L": " << message.get() << L"\n";
  }
  else
  {
    std::wcout << L"Capturing 5 seconds of audio." << std::endl;
    Sleep(timeout);

    loopbackCapture.StopCaptureAsync();

    std::wcout << L"Finished.\n";
  }
}
