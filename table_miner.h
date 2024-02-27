#ifndef INC_TABLES_METHOD_H_
#define INC_TABLES_METHOD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define _Bool bool

/**
 * MAX_EVENTS_NUM - максимальное количество уникальных событий системы
 */
#define MAX_EVENTS_NUM 15

/**
 * инициализация таблиц
 */
void init_event_table(uint16_t eventsNum);

/**
 * добавление события (event_num - номер события, time - временная метка)
 */
void add_event_to_tables(uint16_t event_num, uint32_t time);

/**
 * вывод итогового Digraph
 */
void print_gigraph();

/**
 * добавление перехода некорректного по времени (from - из, to - в, time - значение времени перехода)
 */
void add_bad_time_to_table(uint16_t from, uint16_t to, uint32_t time);

/**
 * table_events - таблица корректных по времени переходов
 */
extern uint16_t table_events[MAX_EVENTS_NUM][MAX_EVENTS_NUM];

/**
 * table_bad_events - таблица не корректных по времени переходов
 */
extern uint16_t table_bad_events[MAX_EVENTS_NUM][MAX_EVENTS_NUM];

/**
 * table_time_bad_events - таблица максимально допустимого времени переходов между событиями
 */
extern uint32_t table_time_bad_events[MAX_EVENTS_NUM][MAX_EVENTS_NUM];

/**
 * e_prev_place - предыдущее событие
 */
extern uint16_t e_prev_place;

/**
 * first_e_was - первое событие уже было?
 */
extern _Bool first_e_was;

/**
 * time_before_e - время предыдущего события
 */
extern uint32_t time_before_e;

#endif /* INC_TABLES_METHOD_H_ */
