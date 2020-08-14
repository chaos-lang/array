#include <stdlib.h>
#include <string.h>

#include "Chaos.h"


// Array Operations

// list array.merge(list l1, list l2)

char *merge_params_name[] = {
    "l1",
    "l2"
};
unsigned merge_params_type[] = {
    K_LIST,
    K_LIST
};
unsigned merge_params_secondary_type[] = {
    K_ANY,
    K_ANY
};
unsigned short merge_params_length = (unsigned short) sizeof(merge_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_merge()
{
    enum Type list1_type = kaos.getListType(merge_params_name[0]);
    enum Type list2_type = kaos.getListType(merge_params_name[1]);
    if (list1_type != K_ANY && list2_type != K_ANY && list1_type != list2_type)
        kaos.raiseError("List types are incompatible for merging!");

    kaos.startBuildingList();
    unsigned long length_i = kaos.getListLength(merge_params_name[0]);
    for (unsigned long i = 0; i < length_i; i++) {
        kaos.copyListElement(merge_params_name[0], i);
    }
    unsigned long length_j = kaos.getListLength(merge_params_name[1]);
    for (unsigned long j = 0; j < length_j; j++) {
        kaos.copyListElement(merge_params_name[1], j);
    }

    kaos.returnList(list1_type);
    return 0;
}

// list array.insert(list l, any x, num i = -1)

char *insert_params_name[] = {
    "l",
    "x",
    "i"
};
unsigned insert_params_type[] = {
    K_LIST,
    K_ANY,
    K_NUMBER
};
unsigned insert_params_secondary_type[] = {
    K_ANY,
    K_ANY,
    K_ANY
};
unsigned short insert_params_length = (unsigned short) sizeof(insert_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_insert()
{
    kaos.startBuildingList();
    unsigned long length_i = kaos.getListLength(insert_params_name[0]);
    long long index = kaos.getVariableInt(insert_params_name[2]);
    if (index < 0)
        index = length_i + index + 1;
    char *value = NULL;
    for (unsigned long i = 0; i <= length_i; i++) {
        if (i == index) {
            enum ValueType value_type = kaos.getValueType(insert_params_name[1]);
            switch (value_type)
            {
                case V_BOOL:
                    kaos.createVariableBool(NULL, kaos.getVariableBool(insert_params_name[1]));
                    break;
                case V_INT:
                    kaos.createVariableInt(NULL, kaos.getVariableInt(insert_params_name[1]));
                    break;
                case V_FLOAT:
                    kaos.createVariableFloat(NULL, kaos.getVariableFloat(insert_params_name[1]));
                    break;
                case V_STRING:
                    value = kaos.getVariableString(insert_params_name[1]);
                    kaos.createVariableString(NULL, value);
                    free(value);
                    break;
                default:
                    break;
            }
        }
        if (i != length_i)
            kaos.copyListElement(insert_params_name[0], i);
    }

    kaos.returnList(K_ANY);
    return 0;
}

// list array.reverse(list l)

char *reverse_params_name[] = {
    "l"
};
unsigned reverse_params_type[] = {
    K_LIST
};
unsigned reverse_params_secondary_type[] = {
    K_ANY
};
unsigned short reverse_params_length = (unsigned short) sizeof(reverse_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_reverse()
{
    kaos.startBuildingList();
    unsigned long length_i = kaos.getListLength(reverse_params_name[0]);
    for (long i = (long) (length_i - 1); i >= 0; i--) {
        kaos.copyListElement(reverse_params_name[0], i);
    }

    kaos.returnList(K_ANY);
    return 0;
}

// list array.chunk(list l, num x)

char *chunk_params_name[] = {
    "l",
    "x"
};
unsigned chunk_params_type[] = {
    K_LIST,
    K_NUMBER
};
unsigned chunk_params_secondary_type[] = {
    K_ANY,
    K_ANY
};
unsigned short chunk_params_length = (unsigned short) sizeof(chunk_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_chunk()
{
    unsigned long list_length = kaos.getListLength(chunk_params_name[0]);
    if (list_length == 0)
        kaos.raiseError("Empty lists cannot be chunked");

    enum Type list_type = kaos.getListType(chunk_params_name[0]);
    unsigned long x = kaos.getVariableInt(chunk_params_name[1]);

    kaos.startBuildingList();
    kaos.startBuildingList();

    for (unsigned long i = 0; i < list_length; i++) {
        if (i != 0 && (i % x) == 0) {
            kaos.finishList(list_type);
            kaos.startBuildingList();
        }
        kaos.copyListElement(chunk_params_name[0], i);
    }

    kaos.finishList(list_type);
    kaos.returnList(list_type);
    return 0;
}


// Searching & Replacing

// num list array.search(list haystack, any needle)

char *search_params_name[] = {
    "haystack",
    "needle"
};
unsigned search_params_type[] = {
    K_LIST,
    K_ANY
};
unsigned search_params_secondary_type[] = {
    K_ANY,
    K_ANY
};
unsigned short search_params_length = (unsigned short) sizeof(search_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_search()
{
    unsigned long list_length = kaos.getListLength(search_params_name[0]);

    kaos.startBuildingList();

    for (unsigned long i = 0; i < list_length; i++) {
        enum ValueType value_type = kaos.getListElementValueType(search_params_name[0], i);

        bool x_b, y_b;
        long long x_i, y_i;
        long double x_f, y_f;
        char *x_s, *y_s;

        switch (value_type)
        {
            case V_BOOL:
                x_b = kaos.getVariableBool(search_params_name[1]);
                y_b = kaos.getListElementBool(search_params_name[0], i);
                if (x_b == y_b) {
                    kaos.createVariableInt(NULL, i);
                }
                break;
            case V_INT:
                x_i = kaos.getVariableInt(search_params_name[1]);
                y_i = kaos.getListElementInt(search_params_name[0], i);
                if (x_i == y_i) {
                    kaos.createVariableInt(NULL, i);
                }
                break;
            case V_FLOAT:
                x_f = kaos.getVariableFloat(search_params_name[1]);
                y_f = kaos.getListElementFloat(search_params_name[0], i);
                if (x_f == y_f) {
                    kaos.createVariableInt(NULL, i);
                }
                break;
            case V_STRING:
                x_s = kaos.getVariableString(search_params_name[1]);
                y_s = kaos.getListElementString(search_params_name[0], i);
                if (strcmp(x_s, y_s) == 0) {
                    kaos.createVariableInt(NULL, i);
                }
                free(x_s);
                free(y_s);
                break;
            default:
                break;
        }
    }

    kaos.returnList(K_NUMBER);
    return 0;
}

// list array.replace(list haystack, any needle, any replacement)

char *replace_params_name[] = {
    "haystack",
    "needle",
    "replacement"
};
unsigned replace_params_type[] = {
    K_LIST,
    K_ANY,
    K_ANY
};
unsigned replace_params_secondary_type[] = {
    K_ANY,
    K_ANY,
    K_ANY
};
unsigned short replace_params_length = (unsigned short) sizeof(replace_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_replace()
{
    unsigned long list_length = kaos.getListLength(replace_params_name[0]);
    enum Type list_type = kaos.getListType(replace_params_name[0]);

    kaos.startBuildingList();

    for (unsigned long i = 0; i < list_length; i++) {
        enum ValueType value_type = kaos.getListElementValueType(replace_params_name[0], i);

        bool x_b, y_b;
        long long x_i, y_i;
        long double x_f, y_f;
        char *x_s, *y_s;
        char *replacement;

        switch (value_type)
        {
            case V_BOOL:
                x_b = kaos.getVariableBool(replace_params_name[1]);
                y_b = kaos.getListElementBool(replace_params_name[0], i);
                if (x_b == y_b) {
                    kaos.createVariableBool(NULL, kaos.getVariableBool(replace_params_name[2]));
                } else {
                    kaos.createVariableBool(NULL, y_b);
                }
                break;
            case V_INT:
                x_i = kaos.getVariableInt(replace_params_name[1]);
                y_i = kaos.getListElementInt(replace_params_name[0], i);
                if (x_i == y_i) {
                    kaos.createVariableInt(NULL, kaos.getVariableInt(replace_params_name[2]));
                } else {
                    kaos.createVariableInt(NULL, y_i);
                }
                break;
            case V_FLOAT:
                x_f = kaos.getVariableFloat(replace_params_name[1]);
                y_f = kaos.getListElementFloat(replace_params_name[0], i);
                if (x_f == y_f) {
                    kaos.createVariableFloat(NULL, kaos.getVariableFloat(replace_params_name[2]));
                } else {
                    kaos.createVariableFloat(NULL, y_f);
                }
                break;
            case V_STRING:
                x_s = kaos.getVariableString(replace_params_name[1]);
                y_s = kaos.getListElementString(replace_params_name[0], i);
                if (strcmp(x_s, y_s) == 0) {
                    replacement = kaos.getVariableString(replace_params_name[2]);
                    kaos.createVariableString(NULL, replacement);
                    free(replacement);
                } else {
                    kaos.createVariableString(NULL, y_s);
                }
                free(x_s);
                free(y_s);
                break;
            default:
                break;
        }
    }

    kaos.returnList(list_type);
    return 0;
}


// Information Functions

// num array.length(list l)

char *length_params_name[] = {
    "l"
};
unsigned length_params_type[] = {
    K_LIST
};
unsigned length_params_secondary_type[] = {
    K_ANY
};
unsigned short length_params_length = (unsigned short) sizeof(length_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_length()
{
    unsigned long list_length = kaos.getListLength(length_params_name[0]);
    kaos.returnVariableInt((long long) list_length);
    return 0;
}

int KAOS_EXPORT KaosRegister(struct Kaos _kaos)
{
    kaos = _kaos;

    struct KaosValue insert_optional_index;
    insert_optional_index.f = -1.0;
    struct KaosValue insert_optional_params[] = {
        insert_optional_index
    };

    // Array Operations
    kaos.defineFunction("merge", K_LIST, K_ANY, merge_params_name, merge_params_type, merge_params_secondary_type, merge_params_length, NULL, 0);
    kaos.defineFunction("insert", K_LIST, K_ANY, insert_params_name, insert_params_type, insert_params_secondary_type, insert_params_length, insert_optional_params, 1);
    kaos.defineFunction("reverse", K_LIST, K_ANY, reverse_params_name, reverse_params_type, reverse_params_secondary_type, reverse_params_length, NULL, 0);
    kaos.defineFunction("chunk", K_LIST, K_ANY, chunk_params_name, chunk_params_type, chunk_params_secondary_type, chunk_params_length, NULL, 0);

    // Searching & Replacing
    kaos.defineFunction("search", K_LIST, K_NUMBER, search_params_name, search_params_type, search_params_secondary_type, search_params_length, NULL, 0);
    kaos.defineFunction("replace", K_LIST, K_ANY, replace_params_name, replace_params_type, replace_params_secondary_type, replace_params_length, NULL, 0);

    // Information Functions
    kaos.defineFunction("length", K_NUMBER, K_ANY, length_params_name, length_params_type, length_params_secondary_type, length_params_length, NULL, 0);

    return 0;
}
