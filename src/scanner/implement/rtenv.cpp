#include "input_device.hpp"
#include "language.hpp"

thread_local input_device* device = nullptr;
thread_local language lang;