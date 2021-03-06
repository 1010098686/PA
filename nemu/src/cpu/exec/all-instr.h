#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/xchg.h"
#include "data-mov/movz.h"
#include "data-mov/movs.h"
#include "data-mov/cmovcc.h"
#include "data-mov/crmov.h"

#include "arith/dec.h"
#include "arith/inc.h"
#include "arith/neg.h"
#include "arith/imul.h"
#include "arith/mul.h"
#include "arith/idiv.h"
#include "arith/div.h"
#include "arith/sub.h"
#include "arith/cmp.h"
#include "arith/add.h"
#include "arith/adc.h"
#include "arith/sbb.h"

#include "logic/and.h"
#include "logic/or.h"
#include "logic/not.h"
#include "logic/xor.h"
#include "logic/sar.h"
#include "logic/shl.h"
#include "logic/shr.h"
#include "logic/shrd.h"
#include "logic/test.h"
#include "logic/sal.h"

#include "string/rep.h"
#include "string/stos.h"
#include "string/cmps.h"
#include "string/movsb.h"

#include "control/call.h"
#include "control/push.h"
#include "control/pop.h"
#include "control/jump.h"
#include "control/ret.h"
#include "control/setcc.h"
#include "control/jcc.h"
#include "control/bt.h"

#include "misc/misc.h"

#include "special/special.h"
