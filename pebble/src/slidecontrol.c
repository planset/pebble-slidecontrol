#include <pebble.h>

static Window *window;
static TextLayer *text_layer;
static ActionBarLayer *action_bar;

static GBitmap *action_icon_previous;
static GBitmap *action_icon_next;

static void send_cmd(int control) {
  Tuplet value = TupletInteger(0, control);

  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  if (iter == NULL) {
    return;
  }

  dict_write_tuplet(iter, &value);
  dict_write_end(iter);

  app_message_outbox_send();
}

static void accel_tap_handler(AccelAxisType axis, int32_t direction) {
  text_layer_set_text(text_layer, "Next");
  send_cmd(1);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Next");
  send_cmd(1);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Back");
  send_cmd(0);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Next");
  send_cmd(1);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  accel_tap_service_subscribe(accel_tap_handler);

  // action bar
  action_bar = action_bar_layer_create();
  action_bar_layer_add_to_window(action_bar, window);
  action_bar_layer_set_click_config_provider(action_bar,
                                             click_config_provider);
  action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, action_icon_previous);
  action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, action_icon_next);

}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  action_icon_previous = gbitmap_create_with_resource(
          RESOURCE_ID_IMAGE_ACTION_ICON_PREVIOUS);
  action_icon_next = gbitmap_create_with_resource(
          RESOURCE_ID_IMAGE_ACTION_ICON_NEXT);

  window = window_create();
  app_message_open(64, 64);
  //window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
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
