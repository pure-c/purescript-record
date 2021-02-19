#include <purescript.h>

PURS_FFI_FUNC_2(Record_ST_freeze, _record, _) {
	const purs_record_t *record = purs_any_unsafe_get_record(_record);
	return purs_any_record(purs_record_copy_shallow(record));
}

PURS_FFI_FUNC_2(Record_ST_thaw, _record, _) {
	const purs_record_t *record = purs_any_force_record(_record);
	purs_any_t ret = purs_any_record(purs_record_copy_shallow(record));
	PURS_RC_RELEASE(record);
	return ret;
}

PURS_FFI_FUNC_3(Record_ST_unsafePeek, _key, _record, _) {
	const purs_str_t *key = purs_any_force_string(_key);
	const purs_record_t *record = purs_any_unsafe_get_record(_record);
	purs_any_t *hit = purs_record_find_by_key(record, key->data);
	assert(hit != NULL);
	PURS_ANY_RETAIN(*hit);
	PURS_RC_RELEASE(key);
	return *hit;
}

PURS_FFI_FUNC_4(Record_ST_unsafePoke, _key, value, _record, _) {
	const purs_str_t *key = purs_any_force_string(_key);
	purs_record_t *record = (purs_record_t*)purs_any_unsafe_get_record(_record);
	purs_record_add_mut(record, key->data, value);
	PURS_RC_RELEASE(key);
	return purs_any_null;
}

PURS_FFI_FUNC_4(Record_ST_unsafeModify, _key, f, _record, _) {
	const purs_str_t *key = purs_any_force_string(_key);
	purs_record_t *record = (purs_record_t*)purs_any_unsafe_get_record(_record);
	purs_any_t *hit = purs_record_find_by_key(record, key->data);
	assert(hit != NULL);
	purs_any_t tmp1 = purs_any_app(f, *hit);
	purs_record_add_mut(record, key->data, tmp1);
	PURS_ANY_RELEASE(tmp1);
	PURS_RC_RELEASE(key);
	return purs_any_null;
}
