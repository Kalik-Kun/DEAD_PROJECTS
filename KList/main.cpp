#include <iostream>
#include "KList.h"


int main() {
    KList<int> a(10);
    a.KLPushBegin(50);
    a.KLPushBegin(100);
    a.KLPushEnd(4);
    a.KLPushEnd(3);
    a.KLInsertBefore(2, -111);
    a.KLInsertAfter(1, -100);
    a.KLDelete(0);
    a.KLPushEnd(2);
    a.print_elems();
    a.KLDump(KL_DEB_ELEM("hue"));
    return 0;
}
