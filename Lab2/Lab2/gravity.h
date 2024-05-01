#pragma once

typedef int coord[12];
typedef void (*DragFunctionType)(coord& data, float g);

extern "C" __declspec(dllimport) void drag(coord & data, float g);