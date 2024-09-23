#include "table_miner.h"

uint16_t** table_events;
uint16_t** table_bad_events;
uint32_t** table_time_bad_events;
uint16_t table_events_num;
uint16_t e_prev_place;
_Bool first_e_was;
uint32_t time_before_e;

uint8_t init_event_table(uint16_t eventsNum) {
    table_events = (uint16_t**)calloc(eventsNum, sizeof (uint16_t*));
    if (table_events == NULL) {
        return 1;
    }

    table_bad_events = (uint16_t**)calloc(eventsNum, sizeof (uint16_t*));
    if (table_bad_events == NULL) {
        return 1;
    }

    table_time_bad_events = (uint32_t**)calloc(eventsNum, sizeof (uint32_t*));
    if (table_time_bad_events == NULL) {
        return 1;
    }

    for (uint16_t i = 0; i < eventsNum; i++) {
        table_events[i] = (uint16_t*)calloc(eventsNum, sizeof (uint16_t));
        if (table_events[i] == NULL) {
            return 1;
        }
    }

    for (uint16_t i = 0; i < eventsNum; i++) {
        table_bad_events[i] = (uint16_t*)calloc(eventsNum, sizeof (uint16_t));
        if (table_bad_events[i] == NULL) {
            return 1;
        }
    }

    for (uint16_t i = 0; i < eventsNum; i++) {
        table_time_bad_events[i] = (uint32_t*)calloc(eventsNum, sizeof (uint32_t));
        if (table_time_bad_events[i] == NULL) {
            return 1;
        }
    }

    table_events_num = eventsNum;
    first_e_was = 0;
    e_prev_place = 0;
    return 0;
}

void add_limit(uint16_t from, uint16_t to, uint32_t time) {
    table_time_bad_events[from][to] = time;
}

void add_event(uint16_t event_num, uint32_t time) {
    if (first_e_was == 0) {
        first_e_was = 1;
    } else {
        int32_t check_time = table_time_bad_events[e_prev_place][event_num];
        if (check_time != 0) {
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

void print_gigraph() {
    printf("Digraph {\r\n");
    printf("node [shape = box];");

    for (uint8_t i = 0; i < table_events_num; i++) {
        printf("%d;", i);
    }
    printf("\r\n");

    for (uint16_t i = 0; i < table_events_num; i++) {
        for (uint16_t j = 0; j < table_events_num; j++) {
            if (table_events[i][j] != 0)
                printf("%d->%d [label=\"%d\",len=1.00];\r\n", i, j, table_events[i][j]);
        }
    }

    for (uint8_t i = 0; i < table_events_num; i++) {
        for (uint8_t j = 0; j < table_events_num; j++) {
            if (table_bad_events[i][j] != 0) {
                 printf("%d->%d [label=\"%d\",len=1.00,color=\"red\"];\r\n", i, j, table_bad_events[i][j]);
            }
        }
    }

    printf("}\r\n");
}
