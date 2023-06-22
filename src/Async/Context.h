#pragma once
#include "System/Context.h"

namespace Async {

extern "C" {

extern int save_context(Context*);
extern void load_context(Context const*);
extern void swap_context(Context* save, Context const* load);

}

}
