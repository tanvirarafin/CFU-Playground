// Copyright 2021 The CFU-Playground Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include "menu.h"
#include "perf.h"

unsigned CFU_start_counts[NUM_PERF_COUNTERS];

// Counter Tests
static int counter_num = 0;

static void do_perf_set_0(void)
{
    counter_num = 0;
    printf("-curr perf counter %d: %u\n", counter_num, get_counter(counter_num));
}

static void do_perf_set_1(void)
{
    counter_num = 1;
    printf("-curr perf counter %d: %u\n", counter_num, get_counter(counter_num));
}

static void do_perf_enable(void)
{
    printf("enable perf counter %d\n", counter_num);
    set_counter_enable(counter_num, 1);
}

static void do_perf_pause(void)
{
    printf("pause perf counter %d\n", counter_num);
    set_counter_enable(counter_num, 0);
}

static void do_perf_zero(void)
{
    printf("zero perf counter %d and mcycle\n", counter_num);
    set_mcycle(0);
    set_counter_enable(counter_num, 0);
    set_counter(counter_num, 0);
}

static void do_perf_show(void)
{
    printf("Counters:\n");
    printf("  0:      %8d\n", get_counter(0));
    printf("  1:      %8d\n", get_counter(1));
    printf("  mcycle: %8d\n", get_counter(1));
}

static struct Menu MENU = {
    "Performance Counter Tests",
    "perf counter",
    {
        MENU_ITEM('0', "switch to perf counter 0 and show value", do_perf_set_0),
        MENU_ITEM('1', "switch to perf counter 1 and show value", do_perf_set_1),
        MENU_ITEM('e', "Enable current perf counter", do_perf_enable),
        MENU_ITEM('p', "Pause current perf counter", do_perf_pause),
        MENU_ITEM('z', "Zero current perf counter and mcycle", do_perf_zero),
        MENU_ITEM('s', "Show perf counters and mcycle values", do_perf_show),
        MENU_END,
    },
};

void do_performance_counter_tests()
{
    menu_run(&MENU);
}
