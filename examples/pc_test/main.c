#include <stdio.h>

#include <table_miner.h>

void testFunc()
{
    _Bool next2 = true;
    _Bool next4 = true;
    _Bool next6 = true;
    _Bool bad_time_f3_to6 = true;
    uint32_t current_time = 0;

    add_limit(3, 6, 2);

    add_event(0, current_time++);

    for (uint8_t i = 0; i < 100; i++) {
        add_event(1, current_time++);
        if (next2) {
            add_event(2, current_time++);
            if (next4) {
                add_event(4, current_time++);
            } else {
                add_event(5, current_time++);
            }
            next4 = !next4;
        } else {
            add_event(3, current_time++);
            if (next6) {
                if (bad_time_f3_to6) {
                    current_time++;
                    add_event(6, current_time++);
                } else {
                    add_event(6, current_time++);
                }
                bad_time_f3_to6 = !bad_time_f3_to6;
            }
            next6 = !next6;
        }
        next2 = !next2;
        add_event(7, current_time++);
    }

    add_event(8, current_time++);
}

int main()
{
    if (init_event_table(10) != 0) {
        printf("init event table ERROR (memory calloc problem)!\n");
    }

    printf("Start!\n");
    testFunc();
    print_gigraph();
    printf("End!\n");
    return 0;
}
