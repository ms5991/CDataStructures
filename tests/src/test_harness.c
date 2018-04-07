#include "test_list.h"
#include <stdlib.h>
#include <time.h>

void init_test_harness(){
	srand(time(NULL));   
}

int main(){

	init_test_harness();

	test_all_list_scenarios();

	return 0;
}
