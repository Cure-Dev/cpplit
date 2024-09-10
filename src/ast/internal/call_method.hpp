#pragma once

#include <string>
#include "model/fm.hpp"

model_object* call_method(model_object* obj, std::wstring name, std::vector<model_object*> arglist = {});