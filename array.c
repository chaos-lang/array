#include "Chaos.h"


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

int KAOS_EXPORT KaosRegister(struct Kaos _kaos)
{
    kaos = _kaos;
    kaos.defineFunction("merge", K_LIST, merge_params_name, merge_params_type, merge_params_length);

    return 0;
}
