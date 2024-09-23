// See https://aka.ms/new-console-template for more information
using System.Runtime.InteropServices;

[DllImport("AppCapture.dll", CharSet = CharSet.Unicode)]
static extern void Capture(int timeout);

Capture(5000);
