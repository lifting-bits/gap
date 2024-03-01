///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////
// This file is a modified version of cppcoro/test/counted.cpp from the cppcoro
// project. The original file is licenced under the MIT license and the original
// license is included above.
///////////////////////////////////////////////////////////////////////////////

#include "counted.hpp"

int counted::default_construction_count;
int counted::copy_construction_count;
int counted::move_construction_count;
int counted::destruction_count;