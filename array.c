#include "Chaos.h"
#include <stdlib.h>


// Array operations

// list array.merge(list l1, list l2)

char *merge_params_name[] = {
    "l1",
    "l2"
};
unsigned merge_params_type[] = {
    K_LIST,
    K_LIST
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

    kaos.returnList(K_ANY);
    return 0;
}

// num array.length(list l)

char *length_params_name[] = {
    "l"
};
unsigned length_params_type[] = {
    K_LIST
};
unsigned short length_params_length = (unsigned short) sizeof(length_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_length()
{
    unsigned long list_length = kaos.getListLength(length_params_name[0]);
    kaos.returnVariableInt((long long) list_length);
    return 0;
}

// list array.insert(list l, any x, num i)

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
unsigned short insert_params_length = (unsigned short) sizeof(insert_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_insert()
{
    kaos.startBuildingList();
    unsigned long length_i = kaos.getListLength(insert_params_name[0]);
    char *value = NULL;
    for (unsigned long i = 0; i < length_i; i++) {
        if (i == kaos.getVariableInt(insert_params_name[2])) {
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

int KAOS_EXPORT KaosRegister(struct Kaos _kaos)
{
    kaos = _kaos;
    kaos.defineFunction("merge", K_LIST, merge_params_name, merge_params_type, merge_params_length);
    kaos.defineFunction("length", K_NUMBER, length_params_name, length_params_type, length_params_length);
    kaos.defineFunction("insert", K_LIST, insert_params_name, insert_params_type, insert_params_length);
    kaos.defineFunction("reverse", K_LIST, reverse_params_name, reverse_params_type, reverse_params_length);

    return 0;
}
