#include <purescript.h>

PURS_FFI_FUNC_UNCURRIED_2(Record_Unsafe_Union_unsafeUnionFn, _r1, _r2, {
	const purs_record_t * r1 = purs_any_get_record(_r1);
	const purs_record_t * r2 = purs_any_get_record(_r2);
	return purs_any_record_new(purs_record_merge(r2, r1));
});
