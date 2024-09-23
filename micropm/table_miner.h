#ifndef INC_TABLES_METHOD_H_
#define INC_TABLES_METHOD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define _Bool bool

/**
 * инициализация таблиц
 */
uint8_t init_event_table(uint16_t eventsNum);

/**
 * добавление события (event_num - номер события, time - временная метка события)
 */
void add_event(uint16_t event_num, uint32_t time);

/**
 * вывод итогового Digraph
 */
void print_gigraph();

/**
 * добавление перехода некорректного по времени (from - из, to - в, time - значение времени перехода)
 */
void add_limit(uint16_t from, uint16_t to, uint32_t time);

/**
 * table_events - таблица корректных по времени переходов
 */
extern uint16_t** table_events;

/**
 * table_bad_events - таблица не корректных по времени переходов
 */
extern uint16_t** table_bad_events;

/**
 * table_time_bad_events - таблица максимально допустимого времени переходов между событиями
 */
extern uint32_t** table_time_bad_events;

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

/**
 * table_events_num - количество событий для которых производтся фиксация и сохранение в модели
 */
extern uint16_t table_events_num;

#endif
