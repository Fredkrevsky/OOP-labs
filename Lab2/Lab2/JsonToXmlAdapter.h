#pragma once
#include <nlohmann/json.hpp>
#include "tinyxml2.h"
#include <fstream>

using namespace tinyxml2;
using json = nlohmann::json;

typedef void (*ConvertFunc)(const std::string&, const std::string&);

static void convert(const std::string& jsonPath, const std::string& xmlPath);

