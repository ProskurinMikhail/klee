#include "klee/Solver/SolverUtil.h"

namespace klee {

const char *pv_to_str(PartialValidity pv) {
  switch (pv) {
  case PValidity::MustBeTrue:
    return "MustBeTrue";
  case PValidity::MustBeFalse:
    return "MustBeFalse";
  case PValidity::MayBeTrue:
    return "MayBeTrue";
  case PValidity::MayBeFalse:
    return "MayBeFalse";
  case PValidity::TrueOrFalse:
    return "TrueOrFalse";
  case PValidity::None:
    return "None";
  }
}

Validity fromPartial(PartialValidity pv) {
  switch (pv) {
  case PValidity::MustBeTrue:
    return Validity::True;
  case PValidity::MustBeFalse:
    return Validity::False;
  case PValidity::TrueOrFalse:
    return Validity::Unknown;
  default:
    assert(0 && "PV not convertible to Validity");
  }
}

PartialValidity toPartial(Validity v) {
  switch (v) {
  case Validity::True:
    return PValidity::MustBeTrue;
  case Validity::False:
    return PValidity::MustBeFalse;
  case Validity::Unknown:
    return PValidity::TrueOrFalse;
  }
}

PartialValidity negatePartialValidity(PartialValidity pv) {
  switch (pv) {
  default:
    assert(0 && "invalid partial validity");
  case PValidity::MustBeTrue:
    return PValidity::MustBeFalse;
  case PValidity::MustBeFalse:
    return PValidity::MustBeTrue;
  case PValidity::MayBeTrue:
    return PValidity::MayBeFalse;
  case PValidity::MayBeFalse:
    return PValidity::MayBeTrue;
  case PValidity::TrueOrFalse:
    return PValidity::TrueOrFalse;
  }
}

PartialValidity pValidityEvaluation(ref<SolverResponse> queryRes, ref<SolverResponse> negativeQueryRes) {
  PartialValidity result;
   if (isa<ValidResponse>(queryRes) &&
        isa<InvalidResponse>(negativeQueryRes)) {
      result = PValidity::MustBeTrue;
    } else if (isa<InvalidResponse>(queryRes) &&
               isa<ValidResponse>(negativeQueryRes)) {
      result = PValidity::MustBeFalse;
    } else if (isa<InvalidResponse>(queryRes) &&
               isa<InvalidResponse>(negativeQueryRes)) {
      result = PValidity::TrueOrFalse;
    } else if (isa<InvalidResponse>(queryRes) &&
               isa<UnknownResponse>(negativeQueryRes)) {
      result = PValidity::MayBeFalse;
    } else if (isa<UnknownResponse>(queryRes) &&
               isa<InvalidResponse>(negativeQueryRes)) {
      result = PValidity::MayBeTrue;
    } else if (isa<UnknownResponse>(queryRes) &&
               isa<UnknownResponse>(negativeQueryRes)) {
      result = PValidity::None;
    } else {
      assert(0 && "unreachable");
    }
    return result;
}

}; // namespace klee
