// Runtime Environment Variables

#pragma once

#include "input_device.hpp"
#include "language.hpp"

static thread_local input_device* device;
thread_local static language lang;