#pragma once

#include <string>
#include "model/fm.hpp"

semantic_object* call_method(semantic_object* obj, std::wstring name, std::vector<semantic_object*> arglist = {});