#include <purescript.h>

PURS_FFI_FUNC_1(Record_Builder_copyRecord, _record) {
	const purs_record_t *record = purs_any_force_record(_record);
	purs_any_t ret = purs_any_record(purs_record_copy_shallow(record));
	PURS_RC_RELEASE(record);
	return ret;
}

PURS_FFI_FUNC_3(Record_Builder_unsafeInsert, _key, value, _record) {
	purs_record_t *record = (purs_record_t*) purs_any_force_record(_record);
	const purs_str_t *key  = purs_any_force_string(_key);
	if (record == NULL) {
		PURS_RC_RELEASE(key);
		return purs_any_record(purs_record_new_va(1, key, value));
	}
	purs_record_add_mut(record, key, value);
	PURS_RC_RELEASE(key);
	return _record;
}

PURS_FFI_FUNC_3(Record_Builder_unsafeModify, _key, f, _record) {
	const purs_str_t *key = purs_any_force_string(_key);
	purs_record_t *record = (purs_record_t *) purs_any_force_record(_record);
	const purs_any_t *hit = purs_record_find_by_key(record, key);
	purs_assert(hit != NULL, "missing key");
	purs_any_t tmp1 = purs_any_app(f, *hit);
	purs_record_add_multi_mut(record, 1, key, tmp1);
	PURS_ANY_RELEASE(tmp1);
	PURS_RC_RELEASE(key);
	return _record;
}

PURS_FFI_FUNC_2(Record_Builder_unsafeDelete, _key, _record) {
	const purs_str_t *key = purs_any_force_string(_key);
	purs_record_t *record = (purs_record_t*) purs_any_force_record(_record);
	purs_record_remove_mut(record, key);
	PURS_RC_RELEASE(key);
	return _record;
}

PURS_FFI_FUNC_3(Record_Builder_unsafeRename, _keyOld, _keyNew, _record) {
	const purs_str_t *key_old = purs_any_force_string(_keyOld);
	const purs_str_t *key_new = purs_any_force_string(_keyNew);
	purs_record_t *record = (purs_record_t*)purs_any_force_record(_record);
	const purs_any_t *hit = purs_record_find_by_key(record, key_old);
	assert(hit != NULL);
	purs_record_add_multi_mut((purs_record_t*) record, 1, key_new, *hit);
	purs_record_remove_mut((purs_record_t*) record, key_old);
	PURS_RC_RELEASE(key_old);
	PURS_RC_RELEASE(key_new);
	return _record;
}
