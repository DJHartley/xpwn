#ifndef PLIST_H
#define PLIST_H

#include <abstractfile.h>

enum DictTypes {
	DictionaryType = 1,
	ArrayType,
	StringType,
	DataType,
	IntegerType,
	BoolType
};

typedef struct DictValue {
	int type;
	char* key;
	struct DictValue* next;
	struct DictValue* prev;
} DictValue;

typedef struct StringValue {
	DictValue dValue;
	char* value;
} StringValue;

typedef struct DataValue {
	DictValue dValue;
	int len;
	char* value;
} DataValue;

typedef struct IntegerValue {
	DictValue dValue;
	int value;
} IntegerValue;

typedef struct BoolValue {
	DictValue dValue;
	char value;
} BoolValue;

typedef struct ArrayValue {
	DictValue dValue;
	int size;
	DictValue** values;
} ArrayValue;

typedef struct Dictionary {
	DictValue dValue;
	DictValue* values;
} Dictionary;

typedef struct Tag {
	char* name;
	char* xml;
} Tag;

#ifdef __cplusplus
extern "C" {
#endif
	void array_new(ArrayValue* myself, char* xml);
	void dictionary_new(Dictionary* myself, char* xml);
	Dictionary* dictionary_newFromAbstractFile(AbstractFile* file);
	void array_free(ArrayValue* myself);
	void dictionary_free(Dictionary* myself);
	char* array_to_xml(ArrayValue* myself, int tabsCount);
	char* dictionary_to_xml(Dictionary* myself, int tabsCount);
	Dictionary* root_from_file(char* xml);
	char* root_to_xml(Dictionary* root);
	DictValue* dictionary_get_key(Dictionary* myself, const char* key);
	void array_add_string(ArrayValue* array, char* str);
	void dictionary_remove_key(Dictionary* dict, char* key);
	void dictionary_add_string(Dictionary* dict, const char* key, const char* value);
	void dictionary_add_data(Dictionary* dict, const char* key, const char* value);
	void dictionary_add_bool(Dictionary* dict, const char* key, int value);
	void dictionary_add_integer(Dictionary* dict, const char* key, int value);
	void dictionary_add_value(Dictionary* dict, const char* key, DictValue* value);
#ifdef __cplusplus
}
#endif

#endif

