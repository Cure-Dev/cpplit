// Runtime Environment Variables

#pragma once

#include "input_device.hpp"
#include "language.hpp"

extern thread_local input_device* device;
thread_local static language lang;