#include <pebble.h>
#include "main.h"
#include "lyrics.h"

ClaySettings settings;

static Window *s_main_window;

static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;
static GBitmap *s_background_bitmap_dithered;

static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_dayOfWeek_layer;
static TextLayer *s_lyrics_layer;

int dayOfYear = 0;		// needed to choose lyrics

// Initialize the default settings
static void default_settings()
{
	settings.Lyrics = false;
}

// Read settings from persistent storage
static void load_settings()
{
	default_settings();
	persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

// Save settings to persistent storage
static void save_settings()
{
	persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
	update_display();
}

// Update the display elements
static void update_display()
{
	if (settings.Lyrics) {  // Show lyrics
        bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
        layer_set_hidden(text_layer_get_layer(s_lyrics_layer), false);
    }
    else {  // Hide lyrics
        bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap); // change back to s_background_bitmap_dithered?
        layer_set_hidden(text_layer_get_layer(s_lyrics_layer), true);
    }
}

static void in_recv_handler(DictionaryIterator *iterator, void *context)
{
  	// Get Tuple
  	Tuple *lyrics_t = dict_find(iterator, MESSAGE_KEY_Lyrics);
	if (lyrics_t)
	{
		settings.Lyrics = lyrics_t->value->int32 == 1;	
	}
	
	// Save the new settings to persistent storage
	save_settings();
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) 
{
    if (units_changed & MINUTE_UNIT)
    {
        // Create a long-lived buffer
        static char buffer[] = "00:00";

        // Write the current hours and minutes into the buffer
        if(clock_is_24h_style() == true)    //Use 24h hour format
        {
            strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
        } 
        else     //Use 12 hour format
        {
            strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
            if (buffer[0] == '0')
            {
                buffer [0] = buffer[1];
                buffer [1] = buffer[2];
                buffer [2] = buffer[3];
                buffer [3] = buffer[4];
                buffer [4] = '\0';
            }
        }
        
        // Display this time on the TextLayer
        text_layer_set_text(s_time_layer, buffer);
    }
    
    if (units_changed & DAY_UNIT)
    {
        static char dateBuffer[] = "MM/DD/YY";
        strftime(dateBuffer, sizeof(dateBuffer), "%D", tick_time);
        
        static char dayOfWeekBuffer[] = "Sun";
        strftime(dayOfWeekBuffer, sizeof(dayOfWeekBuffer),"%a",tick_time);
        
        // this selects day of month so lyrics will be the same for a full day
        static char dayOfYearBuffer[] = "000";
        strftime(dayOfYearBuffer,sizeof(dayOfYearBuffer),"%j",tick_time);
        dayOfYear = atoi(dayOfYearBuffer);
    
        // Display this date on the TextLayer
        text_layer_set_text(s_date_layer, dateBuffer);
        text_layer_set_text(s_dayOfWeek_layer, dayOfWeekBuffer);
        
        chooseLyrics(s_lyrics_layer, dayOfYear);
    }
}


static void main_window_load (Window *window)
{
	// TODO: REMOVE THIS
	bool lyrics = true;
	
    s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TOP_LOGO);
    s_background_bitmap_dithered = gbitmap_create_with_resource(RESOURCE_ID_TOP_LOGO_DITHER);
    s_background_layer = PBL_IF_RECT_ELSE(bitmap_layer_create(GRect(0, 0, 144, 168)),bitmap_layer_create(GRect(0, 7, 144, 168)));
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));
    
    s_time_layer = PBL_IF_RECT_ELSE(text_layer_create(GRect(15, 63, 97, 50)),text_layer_create(GRect(15, 70, 97, 50)));
    text_layer_set_text_alignment(s_time_layer, GTextAlignmentLeft);
    text_layer_set_background_color(s_time_layer, GColorClear);
    text_layer_set_text_color(s_time_layer, GColorWhite);
    text_layer_set_font(s_time_layer,fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS));
    layer_add_child(window_get_root_layer(window),text_layer_get_layer(s_time_layer));
    
    s_date_layer = PBL_IF_RECT_ELSE(text_layer_create(GRect(74,150,67,50)),text_layer_create(GRect(114,89,67,50)));
    text_layer_set_text_alignment(s_date_layer, PBL_IF_RECT_ELSE(GTextAlignmentRight,GTextAlignmentLeft));
    text_layer_set_background_color(s_date_layer, GColorClear);
    text_layer_set_text_color(s_date_layer, GColorBlack);
    text_layer_set_font(s_date_layer,fonts_get_system_font(FONT_KEY_GOTHIC_14));
    layer_add_child(window_get_root_layer(window),text_layer_get_layer(s_date_layer));
    
    s_dayOfWeek_layer = PBL_IF_RECT_ELSE(text_layer_create(GRect(74,137,67,50)),text_layer_create(GRect(115,76,67,50)));
    text_layer_set_text_alignment(s_dayOfWeek_layer, PBL_IF_RECT_ELSE(GTextAlignmentRight,GTextAlignmentLeft));
    text_layer_set_background_color(s_dayOfWeek_layer, GColorClear);
    text_layer_set_text_color(s_dayOfWeek_layer, GColorBlack);
    text_layer_set_font(s_dayOfWeek_layer,fonts_get_system_font(FONT_KEY_GOTHIC_14));
    layer_add_child(window_get_root_layer(window),text_layer_get_layer(s_dayOfWeek_layer));

    s_lyrics_layer = PBL_IF_RECT_ELSE(text_layer_create(GRect(10,5,124,60)),text_layer_create(layer_get_bounds(window_get_root_layer(s_main_window))));
    text_layer_set_font(s_lyrics_layer,fonts_get_system_font(FONT_KEY_GOTHIC_14));
    text_layer_set_background_color(s_lyrics_layer, GColorClear);
    text_layer_set_text_alignment(s_lyrics_layer, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window),text_layer_get_layer(s_lyrics_layer));
    text_layer_enable_screen_text_flow_and_paging(s_lyrics_layer, 1);
    /*if (lyrics) {  // Show lyrics
        bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
        layer_set_hidden(text_layer_get_layer(s_lyrics_layer), false);
    }
    else {  // Hide lyrics
        bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap); // change back to s_background_bitmap_dithered?
        layer_set_hidden(text_layer_get_layer(s_lyrics_layer), true);
    }*/
        
    // Load time when window is loaded
    time_t now = time(NULL); 
    tick_handler(localtime(&now),MINUTE_UNIT | DAY_UNIT);
	
	update_display();
}

static void main_window_unload (Window *window)
{
    gbitmap_destroy(s_background_bitmap);
    gbitmap_destroy(s_background_bitmap_dithered);
    bitmap_layer_destroy(s_background_layer);
    
    text_layer_destroy (s_time_layer);
    text_layer_destroy (s_date_layer);
    text_layer_destroy (s_dayOfWeek_layer);
    text_layer_destroy (s_lyrics_layer);
}

static void init()
{
	load_settings();
	
    s_main_window = window_create();
    
    window_set_window_handlers(s_main_window, (WindowHandlers) 
    {
        .load = main_window_load,
        .unload = main_window_unload
    });
    
    app_message_register_inbox_received((AppMessageInboxReceived) in_recv_handler);
    app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
    
    window_stack_push(s_main_window, true);
    
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit()
{
    window_destroy(s_main_window);
}
    
int main (void)
{
    init();
    app_event_loop();
    deinit();
}