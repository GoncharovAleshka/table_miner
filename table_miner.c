#include "micropm/table_miner.h"

uint16_t table_events[MAX_EVENTS_NUM][MAX_EVENTS_NUM];
uint16_t table_bad_events[MAX_EVENTS_NUM][MAX_EVENTS_NUM];
uint32_t table_time_bad_events[MAX_EVENTS_NUM][MAX_EVENTS_NUM];
uint16_t e_prev_place;
_Bool first_e_was;
uint32_t time_before_e;

void init_event_table(uint16_t eventsNum) {
    for (uint8_t i = 0; i < eventsNum; i++) {
        for (uint8_t j = 0; j < eventsNum; j++) {
            table_events[i][j] = 0;
            table_bad_events[i][j] = 0;
            table_time_bad_events[i][j] = UINT32_MAX;
        }
    }

    first_e_was = 0;
    e_prev_place = 0;
}

void add_bad_time_to_table(uint16_t from, uint16_t to, uint32_t time) {
    table_time_bad_events[from][to] = time;
}

void add_event_to_tables(uint16_t event_num, uint32_t time) {
    if (first_e_was == 0) {
        first_e_was = 1;
    } else {
        int32_t check_time = table_time_bad_events[e_prev_place][event_num];
        if (check_time != UINT32_MAX) {
            if ((time - time_before_e) >= check_time) {
                table_bad_events[e_prev_place][event_num]++;
            } else {
                table_events[e_prev_place][event_num]++;
            }
        } else {
            table_events[e_prev_place][event_num]++;
        }
    }
    time_before_e = time;
    e_prev_place = event_num;
}

void print_tables_gigraph() {
    printf("Digraph {\r\n");
    printf("node [shape = box];");

    for (uint8_t i = 0; i < MAX_EVENTS_NUM; i++) {
        printf("%d;", i + 1);
    }
    printf("\r\n");

    for (uint16_t i = 0; i < MAX_EVENTS_NUM; i++) {
        for (uint16_t j = 0; j < MAX_EVENTS_NUM; j++) {
            if (table_events[i][j] != 0)
                printf("%d->%d [label=\"%d\",len=1.00];\r\n", i + 1, j + 1, table_events[i][j]);
        }
    }
    printf("}\r\n");

    printf("BAD:\r\n");
    for (uint8_t i = 0; i < MAX_EVENTS_NUM; i++) {
            for (uint8_t j = 0; j < MAX_EVENTS_NUM; j++) {
                if (table_bad_events[i][j] != 0) {
                    printf("%d->%d [label=\"%d\",len=1.00,color=\"red\"];\r\n", i + 1, j + 1, table_bad_events[i][j]);
                }
            }
    }
    printf("BAD end\r\n");
}
