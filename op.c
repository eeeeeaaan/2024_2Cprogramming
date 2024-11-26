#include <stdio.h>

typedef struct {
    char name[10];
    unsigned id: 20;
    unsigned age: 7;
    unsigned money: 27;
} employee;

int main() {
    employee employees[10] = {{"tom",       10330, 21, 24000000},
                              {"eric",      10333, 23, 28000000},
                              {"jain",      40233, 26, 40000000},
                              {"mary",      30022, 46, 65000000},
                              {"kim",       90032, 25, 38000000},
                              {"lee",       90038, 24, 30000000},
                              {"Test_name", 99999, 65, 100000000}
    };
    for (int i = 0; i < 6; i++) {
        printf("name : %s, ID: %d , Age: %d , Salary: %u \n", employees[i].name, employees[i].id, employees[i].age,
               employees[i].money);
    }

}
