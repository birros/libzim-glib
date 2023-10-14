# Libzim-GLib

A partial GObject/C bindings for [libzim], this bindings was created primarily
to be used by [WebArchives].

## Build and install

```shell
$ meson setup build
$ meson compile -C build
$ meson install -C build
```

## Tests

```shell
$ meson setup -Dtests=true build
$ meson test -C build # prog-c -v
```

## Memory usage

Use environment variables `ZIM_DIRENTCACHE` and `ZIM_CLUSTERCACHE` to control
memory cache size.
Example: `ZIM_DIRENTCACHE=1 ZIM_CLUSTERCACHE=1` is the minimum size.

## License

GPLv3 or later, see COPYING for more details.

<!-- Links references -->

[libzim]: https://github.com/openzim/libzim
[WebArchives]: https://github.com/birros/web-archives
