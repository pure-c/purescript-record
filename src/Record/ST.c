#include <purescript.h>

PURS_FFI_FUNC_2(Record_ST_freeze, _record, _, {
	const purs_record_t * record = purs_any_get_record(_record);
	return purs_any_record_new(purs_record_copy_shallow(record));
});

PURS_FFI_FUNC_2(Record_ST_thaw, _record, _, {
	const purs_record_t * record = purs_any_get_record(_record);
	return purs_any_record_new(purs_record_copy_shallow(record));
});

PURS_FFI_FUNC_3(Record_ST_unsafePeek, _key, _record, _, {
	const void * key = purs_any_get_string(_key);
	const purs_record_t * record = purs_any_get_record(_record);
	const purs_record_t * hit = purs_record_find_by_key(record, key);
	assert(hit != NULL);
	return hit->value;
});

PURS_FFI_FUNC_4(Record_ST_unsafePoke, _key, value, _record, _, {
	const void * key = purs_any_get_string(_key);
	const purs_record_t * record = purs_any_get_record(_record);
	purs_record_add_multi_mut((purs_record_t*)record,
				  1,
				  key, value);
	return NULL;
});

PURS_FFI_FUNC_4(Record_ST_unsafeModify, _key, f, _record, _, {
	const void * key = purs_any_get_string(_key);
	const purs_record_t * record = purs_any_get_record(_record);
	const purs_record_t * hit = purs_record_find_by_key(record, key);
	assert(hit != NULL);
	purs_record_add_multi_mut((purs_record_t*)record,
				  1,
				  key, purs_any_app(f, hit->value));
	return NULL;
});
