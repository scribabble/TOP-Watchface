#include <pebble.h>
#define KEY_LYRICS 0

static Window *s_main_window;

static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;
static GBitmap *s_background_bitmap_dithered;

static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_dayOfWeek_layer;
static TextLayer *s_lyrics_layer;

int dayOfYear = 0;        // needed to choose lyrics

static void chooseLyrics ()
{
    dayOfYear = dayOfYear % 21;    // <--number based on number of lyrics in system    (the last case + 1)
    
    switch (dayOfYear)
    {
        default:
            text_layer_set_text(s_lyrics_layer, "Sometimes to stay alive, you've gotta kill your mind");
            break;
        case 1:
            text_layer_set_text(s_lyrics_layer, "Sometimes quiet is violent");
            break;
        case 2:
            text_layer_set_text(s_lyrics_layer, "But you specialize in dying, You hear me screaming Father");
            break;
        case 3:
            text_layer_set_text(s_lyrics_layer, "Faith is to be awake, and to be awake is for us to think");
            break;
        case 4:
            text_layer_set_text(s_lyrics_layer, "Somebody stole my car radio and now I just sit in silence");
            break;
        case 5:
            text_layer_set_text(s_lyrics_layer, "My lungs will fill and then deflate. They fill with fire, exhale desire.");
            break;
        case 6:
            text_layer_set_text(s_lyrics_layer, "Stay alive");
            break;
        case 7:
            text_layer_set_text(s_lyrics_layer, "We're broken people");
            break;
        case 8:
            text_layer_set_text(s_lyrics_layer, "I'll put you on the map, I'll cure you of disease");
            break;
        case 9:
            text_layer_set_text(s_lyrics_layer, "Some see a pen, I see a harpoon");
            break;
        case 10:
            text_layer_set_text(s_lyrics_layer, "I don't want to be heard. I want to be listened to");
            break;
        case 11:
            text_layer_set_text(s_lyrics_layer, "Power to the local dreamer");
            break;
        case 12:
            text_layer_set_text(s_lyrics_layer, "Peace will win and fear will lose");
            break;
        case 13:
            text_layer_set_text(s_lyrics_layer, "I'm forced to deal with what I feel. There's no distraction to mask what is real.");
            break;
        case 14:
            text_layer_set_text(s_lyrics_layer, "And once again, I will be on a march to the sea");
            break;
        case 15:
            text_layer_set_text(s_lyrics_layer, "The sun will rise and we will try again");
            break;
        case 16:
            text_layer_set_text(s_lyrics_layer, "I'll stay awake, because the dark's not taking prisoners tonight");
            break;
        case 17:
            text_layer_set_text(s_lyrics_layer, "He is waiting, oh so patiently, while we repeat the same routine as we will please comfortability");
            break;
        case 18:
            text_layer_set_text(s_lyrics_layer, "And I'm lying here just crying, so wash me with your water");
            break;
        case 19:
            text_layer_set_text(s_lyrics_layer, "I know my soul's freezing. Hell's hot for good reason");
            break;
        case 20:
            text_layer_set_text(s_lyrics_layer, "You're the judge, oh no, set me free");
            break;
        /*case 21:
            text_layer_set_text(s_lyrics_layer, "I'm a goner. Somebody catch my breath.");
            break;
        case 22:
            text_layer_set_text(s_lyrics_layer, "It ain't the speakers that bump hearts, it's our hearts that make the beat");
            break;
        case 23:
            text_layer_set_text(s_lyrics_layer, "Where we're from, we're no one, Our hometown's in the dark");
            break;
        case 24:
            text_layer_set_text(s_lyrics_layer, "Am I the only one I know, waging my wars behind my face and above my throat?");
            break;
        case 25:
            text_layer_set_text(s_lyrics_layer, "No one looks up anymore, cause you might get a raindrop in your eye");
            break;
        case 26:
            text_layer_set_text(s_lyrics_layer, "I've been thinking too much");
            break;
        case 27:
            text_layer_set_text(s_lyrics_layer, "My name is Blurryface and I care what you think");
            break;
        case 28:
            text_layer_set_text(s_lyrics_layer, "Our brains are sick, but that's okay");
            break;
        case 29:
            text_layer_set_text(s_lyrics_layer, "Domingo en fuego, I think I lost my halo");
            break;
        case 30:
            text_layer_set_text(s_lyrics_layer, "You would do almost anything just to feel free");
            break;*/
    }
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
        
        chooseLyrics();
    }
}


static void main_window_load (Window *window)
{
    bool lyrics = persist_read_bool(KEY_LYRICS);
    
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
    if (lyrics) {  // Show lyrics
        bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
        layer_set_hidden(text_layer_get_layer(s_lyrics_layer), false);
    }
    else {  // Hide lyrics
        bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap); // change back to s_background_bitmap_dithered?
        layer_set_hidden(text_layer_get_layer(s_lyrics_layer), true);
    }
        
    // Load time when window is loaded
    time_t now = time(NULL); 
    tick_handler(localtime(&now),MINUTE_UNIT | DAY_UNIT);
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

static void in_recv_handler(DictionaryIterator *iterator, void *context)
{
  // Get Tuple
  Tuple *t = dict_read_first(iterator);
  if(t)
  {
    switch(t->key)
    {
    case KEY_LYRICS:
      // It's the KEY_LYRICS key
      if(strcmp(t->value->cstring, "on") == 0)
      {
        // Set and save with lyrics on
        bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
        layer_set_hidden(text_layer_get_layer(s_lyrics_layer), false);
        persist_write_bool(KEY_LYRICS, true);
      }
      else if(strcmp(t->value->cstring, "off") == 0)
      {
        // Set and save with lyrics off
        bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);    // change back to s_background_bitmap_dithered?
        layer_set_hidden(text_layer_get_layer(s_lyrics_layer), true);
        persist_write_bool(KEY_LYRICS, false);
      }
      break;
    }
  }
}

static void init()
{
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