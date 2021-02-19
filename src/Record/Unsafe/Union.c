#include <purescript.h>

PURS_FFI_FUNC_UNCURRIED_2(Record_Unsafe_Union_unsafeUnionFn, _r1, _r2) {
	const purs_record_t *r1 = purs_any_force_record(_r1);
	const purs_record_t *r2 = purs_any_force_record(_r2);
	purs_any_t ret = purs_any_record(purs_record_merge(r1, r2));
	PURS_RC_RELEASE(r2);
	PURS_RC_RELEASE(r1);
	return ret;
}
