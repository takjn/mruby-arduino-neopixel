# mruby-arduino-neopixel
NeoPixel library for mruby-arduino environment.
This library is a wrapper library for [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel).

> Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!

## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    # additional configrations for Arduino API
    conf.cc.flags << " -DGRSAKURA -DARDUINO=100 "
    conf.cc.include_paths << ["../gr_common/lib/", "../gr_common", "../gr_common/core", "../gr_common/lib/SPI", "../gr_common/lib/Wire", "../gr_common/lib/Servo" ]
    conf.cxx.flags = conf.cc.flags.dup
    conf.cxx.include_paths = conf.cc.include_paths.dup
    
    # Arduino API
    conf.gem :github => "takjn/mruby-arduino", :branch => "master"

    # NeoPixel library for mruby-arduino environment.
    conf.gem :github => "takjn/mruby-arduino-neopixel", :branch => "master"

end
```

## example
```mruby
neo_pixel=NeoPixel.new

neo_pixel.begin(6, 8)

neo_pixel.set_brightness(5)

neo_pixel.set_pixel_color(0, 0, 0, 255)
neo_pixel.set_pixel_color(1, 0, 255, 0)
neo_pixel.set_pixel_color(2, 255, 0, 0)

neo_pixel.set_pixel_color(3, 0, 0, 255)
neo_pixel.set_pixel_color(4, 0, 255, 0)
neo_pixel.set_pixel_color(5, 255, 0, 0)

neo_pixel.set_pixel_color(6, 0, 0, 255)
neo_pixel.set_pixel_color(7, 0, 255, 0)

neo_pixel.show
```

## License
[Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel) is released under the GPL License:
- see src/Adafruit_NeoPixel/COPYING

## See also
- [mruby-arduino for Gadget Renesas](https://github.com/takjn/mruby-arduino)
- [mirb for Gadget Renesas](https://github.com/takjn/mirb4gr)