#include <pebble.h>

static Window *window;

static TextLayer *tl_currency;
static TextLayer *tl_exchange_rate;
static TextLayer *tl_ask;
static TextLayer *tl_bid;

static TextLayer *tl_ask_label;
static TextLayer *tl_bid_label;

static ActionBarLayer *abl_action;

static GBitmap *gb_arrow_up;
static GBitmap *gb_arrow_down;
static GBitmap *gb_arrow_reload;

static BitmapLayer *bl_logo;

static void previous_currency(ClickRecognizerRef recognizer, void *context)
{

}

static void next_currency(ClickRecognizerRef recognizer, void *context)
{

}

static void refresh_currency(ClickRecognizerRef recognizer, void *context)
{

}

static void abl_click_config_provider(void *context)
{
    window_single_click_subscribe(BUTTON_ID_UP,     (ClickHandler)previous_currency);
    window_single_click_subscribe(BUTTON_ID_DOWN,   (ClickHandler)next_currency);
    window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler)refresh_currency);
}

static void action_bar_setup(Window *window)
{
  abl_action = action_bar_layer_create();
  action_bar_layer_add_to_window(abl_action, window);
  action_bar_layer_set_click_config_provider(abl_action, abl_click_config_provider);

  gb_arrow_up = gbitmap_create_with_resource(RESOURCE_ID_ARROW_UP);
  gb_arrow_down = gbitmap_create_with_resource(RESOURCE_ID_ARROW_DOWN);
  gb_arrow_reload = gbitmap_create_with_resource(RESOURCE_ID_ARROW_RELOAD);

  action_bar_layer_set_icon(abl_action, BUTTON_ID_UP, gb_arrow_up);
  action_bar_layer_set_icon(abl_action, BUTTON_ID_DOWN, gb_arrow_down);
  action_bar_layer_set_icon(abl_action, BUTTON_ID_SELECT, gb_arrow_reload);
}

static void action_bar_teardown(void)
{
  action_bar_layer_destroy(abl_action);
  gbitmap_destroy(gb_arrow_up);
  gbitmap_destroy(gb_arrow_down);
  gbitmap_destroy(gb_arrow_reload);
}

static void text_layer_setup(Window *window, Layer *window_layer)
{
    GRect gr_currency       = GRect(0, 21, 124, 84);
    GRect gr_exchange_rate  = GRect(0, 58, 124, 84);

    GRect gr_ask            = GRect(62, 103, 60, 84);
    GRect gr_bid            = GRect(62, 120, 60, 84);

    GRect gr_ask_label      = GRect(0, 103, 60, 84);
    GRect gr_bid_label      = GRect(0, 120, 60, 84);


    GFont bitham_42_bold = fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD);
    GFont bitham_42_light = fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT);
    GFont gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
    GFont gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);

    tl_currency = text_layer_create(gr_currency);
    text_layer_set_font(tl_currency, bitham_42_bold);
    text_layer_set_background_color(tl_currency, GColorClear);
    text_layer_set_text_alignment(tl_currency, GTextAlignmentCenter);

    tl_exchange_rate = text_layer_create(gr_exchange_rate);
    text_layer_set_font(tl_exchange_rate, bitham_42_light);
    text_layer_set_background_color(tl_exchange_rate, GColorClear);
    text_layer_set_text_alignment(tl_exchange_rate, GTextAlignmentCenter);

    tl_ask = text_layer_create(gr_ask);
    text_layer_set_font(tl_ask, gothic_24);
    text_layer_set_background_color(tl_ask, GColorClear);
    text_layer_set_text_alignment(tl_ask, GTextAlignmentLeft);

    tl_ask_label = text_layer_create(gr_ask_label);
    text_layer_set_font(tl_ask_label, gothic_24_bold);
    text_layer_set_background_color(tl_ask_label, GColorClear);
    text_layer_set_text_alignment(tl_ask_label, GTextAlignmentRight);

    tl_bid = text_layer_create(gr_bid);
    text_layer_set_font(tl_bid, gothic_24);
    text_layer_set_background_color(tl_bid, GColorClear);
    text_layer_set_text_alignment(tl_bid, GTextAlignmentLeft);

    tl_bid_label = text_layer_create(gr_bid_label);
    text_layer_set_font(tl_bid_label, gothic_24_bold);
    text_layer_set_background_color(tl_bid_label, GColorClear);
    text_layer_set_text_alignment(tl_bid_label, GTextAlignmentRight);

    text_layer_set_text(tl_currency, "CAD");
    text_layer_set_text(tl_exchange_rate, "0.801");
    text_layer_set_text(tl_ask, "0.759");
    text_layer_set_text(tl_bid, "0.805");
    
    text_layer_set_text(tl_ask_label, "Ask : ");
    text_layer_set_text(tl_bid_label, "Bid : ");

    layer_add_child(window_layer, text_layer_get_layer(tl_currency));
    layer_add_child(window_layer, text_layer_get_layer(tl_exchange_rate));
    layer_add_child(window_layer, text_layer_get_layer(tl_ask));
    layer_add_child(window_layer, text_layer_get_layer(tl_bid));

    layer_add_child(window_layer, text_layer_get_layer(tl_ask_label));
    layer_add_child(window_layer, text_layer_get_layer(tl_bid_label));
}

static void text_layer_teardown(void)
{
    text_layer_destroy(tl_currency);
    text_layer_destroy(tl_exchange_rate);
    text_layer_destroy(tl_bid);
    text_layer_destroy(tl_ask);
    text_layer_destroy(tl_bid_label);
    text_layer_destroy(tl_ask_label);
}



static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  //GRect bounds = layer_get_bounds(window_layer);
  GRect logo_offset = GRect(4, 4, 119, 119);

  bl_logo = bitmap_layer_create(logo_offset);
  //bitmap_layer_set_alignment(bl_logo, GAlignTopLeft);
  bitmap_layer_set_bitmap(bl_logo, gbitmap_create_with_resource(RESOURCE_ID_LOGO));

  layer_add_child(window_layer, bitmap_layer_get_layer(bl_logo));

  action_bar_setup(window);
  text_layer_setup(window, window_layer);
}

static void window_unload(Window *window) {
  text_layer_teardown();
  action_bar_teardown();
  bitmap_layer_destroy(bl_logo);
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers)
  {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
