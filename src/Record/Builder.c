#include <purescript.h>

PURS_FFI_FUNC_1(Record_Builder_copyRecord, _record, {
	const purs_record_t * record = purs_any_get_record(_record);
	return purs_any_record_new(purs_record_copy_shallow(record));
});

PURS_FFI_FUNC_3(Record_Builder_unsafeInsert, _key, value, _record, {
	const purs_record_t * record = purs_any_get_record(_record);
	const void * key  = purs_any_get_string(_key);
	return purs_any_record_new(purs_record_add(record, key, value));
});

PURS_FFI_FUNC_3(Record_Builder_unsafeModify, _key, f, _record, {
	const void * key = purs_any_get_string(_key);
	const purs_record_t * record = purs_any_get_record(_record);
	const purs_record_t * hit = purs_record_find_by_key(record, key);
	assert(hit != NULL);
	return purs_any_record_new(
		purs_record_add_multi_mut((purs_record_t*)record,
					  1,
					  key, purs_any_app(f, hit->value)));
});

PURS_FFI_FUNC_2(Record_Builder_unsafeDelete, _key, _record, {
	const void * key = purs_any_get_string(_key);
	purs_record_t * record = (purs_record_t*) purs_any_get_record(_record);
	purs_record_remove_mut(record, key);
	return _record;
});

PURS_FFI_FUNC_3(Record_Builder_unsafeRename, _keyOld, _keyNew, _record, {
	const void * keyOld = purs_any_get_string(_keyOld);
	const void * keyNew = purs_any_get_string(_keyNew);
	const purs_record_t * record = purs_any_get_record(_record);
	const purs_record_t * hit = purs_record_find_by_key(record, keyOld);
	assert(hit != NULL);
	purs_record_add_multi_mut((purs_record_t*) record, 1, keyNew, hit->value);
	purs_record_remove_mut((purs_record_t*) record, keyOld);
	return _record;
});
