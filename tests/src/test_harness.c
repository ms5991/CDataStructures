#include "test_list.h"
#include "test_stack.h"
#include <stdlib.h>
#include <time.h>

void init_test_harness(){
    srand(time(NULL));
}

int main(){

    init_test_harness();

    test_all_list_scenarios();
    test_all_stack_scenarios();

    return 0;
}
