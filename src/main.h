#pragma once
#include <pebble.h>

#define SETTINGS_KEY 1

typedef struct ClaySettings {
	bool Lyrics;
} __attribute__((__packed__)) ClaySettings;

static void default_settings();
static void load_settings();
static void save_settings();
static void update_display();
static void tick_handler(struct tm *tick_time, TimeUnits units_changed);
static void main_window_load (Window *window);
static void main_window_unload (Window *window);
static void in_recv_handler(DictionaryIterator *iterator, void *context);
static void init();
static void deinit();
static void init();