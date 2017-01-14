/*
** mrb_neopixel->c - NeoPixel class
**
** Copyright (c) Jun Takeda 2016
**
** See Copyright Notice in LICENSE
*/
#include <new>

#include <Arduino.h>

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/data.h>
#include <mruby/class.h>

#include <Adafruit_NeoPixel.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

void
mrb_neopixel_free(mrb_state *mrb, void *ptr)
{
  Adafruit_NeoPixel *neopixel = (Adafruit_NeoPixel *)ptr;
  neopixel->~Adafruit_NeoPixel();
  mrb_free(mrb, neopixel);
}

struct mrb_data_type mrb_neopixel_type = {"NeoPixel", mrb_neopixel_free};

mrb_value
mrb_neopixel_initialize(mrb_state *mrb, mrb_value self)
{
  void *p = mrb_malloc(mrb, sizeof(Adafruit_NeoPixel));
  Adafruit_NeoPixel *newNeoPixel = new(p) Adafruit_NeoPixel();
  DATA_PTR(self) = newNeoPixel;
  DATA_TYPE(self) = &mrb_neopixel_type;
  return self;
}

mrb_value
mrb_neopixel_begin(mrb_state *mrb, mrb_value self)
{
  Adafruit_NeoPixel *neopixel = (Adafruit_NeoPixel *)mrb_get_datatype(mrb, self, &mrb_neopixel_type);
  int pin, num_pixels;

  mrb_get_args(mrb, "ii", &pin, &num_pixels);
  neopixel->begin();
  neopixel->setPin(pin);
  neopixel->updateLength(num_pixels);
  neopixel->updateType(NEO_GRB + NEO_KHZ800);
  return mrb_nil_value();
}

mrb_value
mrb_neopixel_set_pixel_color(mrb_state *mrb, mrb_value self)
{
  Adafruit_NeoPixel *neopixel = (Adafruit_NeoPixel *)mrb_get_datatype(mrb, self, &mrb_neopixel_type);
  int n, r, g, b;

  mrb_get_args(mrb, "iiii", &n, &r, &g, &b);
  neopixel->setPixelColor(n, neopixel->Color(r, g, b));

  return mrb_nil_value();
}

mrb_value
mrb_neopixel_show(mrb_state *mrb, mrb_value self)
{
  Adafruit_NeoPixel *neopixel = (Adafruit_NeoPixel *)mrb_get_datatype(mrb, self, &mrb_neopixel_type);
  neopixel->show();
  return mrb_nil_value();
}

mrb_value
mrb_neopixel_clear(mrb_state *mrb, mrb_value self)
{
  Adafruit_NeoPixel *neopixel = (Adafruit_NeoPixel *)mrb_get_datatype(mrb, self, &mrb_neopixel_type);
  neopixel->clear();
  return mrb_nil_value();
}

mrb_value
mrb_neopixel_set_brightness(mrb_state *mrb, mrb_value self)
{
  Adafruit_NeoPixel *neopixel = (Adafruit_NeoPixel *)mrb_get_datatype(mrb, self, &mrb_neopixel_type);
  int b;

  mrb_get_args(mrb, "i", &b);
  neopixel->setBrightness(b);

  return mrb_nil_value();
}


extern "C"
void mrb_mruby_arduino_neopixel_gem_init(mrb_state *mrb)
{

  RClass *neoPixelClass = mrb_define_class(mrb, "NeoPixel", mrb->object_class);
  MRB_SET_INSTANCE_TT(neoPixelClass, MRB_TT_DATA);
  mrb_define_method(mrb, neoPixelClass, "initialize", mrb_neopixel_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, neoPixelClass, "begin", mrb_neopixel_begin, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, neoPixelClass, "set_pixel_color", mrb_neopixel_set_pixel_color, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, neoPixelClass, "begin", mrb_neopixel_begin, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, neoPixelClass, "show", mrb_neopixel_show, MRB_ARGS_NONE());
  mrb_define_method(mrb, neoPixelClass, "clear", mrb_neopixel_clear, MRB_ARGS_NONE());
  mrb_define_method(mrb, neoPixelClass, "set_brightness", mrb_neopixel_set_brightness, MRB_ARGS_REQ(1));

  DONE;
}

extern "C"
void mrb_mruby_arduino_neopixel_gem_final(mrb_state *mrb)
{
}
