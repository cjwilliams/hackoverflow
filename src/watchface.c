#include <pebble.h>
#include "watchface.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_hackoverflow;
static BitmapLayer *image_layer;
static TextLayer *time_layer;
static GColor *palette;
static char *time_text;

static int MAX_TIME_SIZE = 6;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, true);
  
  s_res_image_hackoverflow = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_HACKOVERFLOW);
  palette = gbitmap_get_palette(s_res_image_hackoverflow);
  palette[0] = GColorVividCerulean;
  palette[1] = GColorFashionMagenta;
  
  // image_layer
  image_layer = bitmap_layer_create(GRect(0, 20, 144, 144));
  bitmap_layer_set_bitmap(image_layer, s_res_image_hackoverflow);
  bitmap_layer_set_background_color(image_layer, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)image_layer);
  
  // allocate memory for time_text
  time_text = malloc(MAX_TIME_SIZE);
  
  // time_layer
  time_layer = text_layer_create(GRect(0, 0, 144, 20));
  text_layer_set_background_color(time_layer, GColorBlack);
  text_layer_set_text_color(time_layer, GColorWhite);
  text_layer_set_text(time_layer, time_text);
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)time_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(image_layer);
  text_layer_destroy(time_layer);
  free(time_text);
  gbitmap_destroy(s_res_image_hackoverflow);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void change_logo_color(void) {
  palette[1] = GColorFromRGB(rand()/255, rand()/255, rand()/255);
}

void update_time(struct tm* time) {
  strftime(time_text, MAX_TIME_SIZE, "%H:%M", time);
  text_layer_set_text(time_layer, time_text);
}

void show_watchface(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_watchface(void) {
  window_stack_remove(s_window, true);
}
