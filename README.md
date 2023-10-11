# Libzim-GLib

**Partial GObject/C bindings for the libzim.**

This bindings was primarly done to permit [libzim] usage for [WebArchives].

## Dependencies and environnement

See flatpak manifest and adapt your system in consequence.

## Building

```
meson setup build
meson compile -C build
```

## Tests

Enable tests by passing `enable-tests=true` argument during meson configuration.

```
meson setup -Denable-tests=true build
```

**Disclaimer:** tests are not truely unit tests, just try to use the library to
get informations from an archive.
Those are useful to quickly show result of bindings use.

### All tests

```
meson test -C build --test-args=<archive-full-path>
```

**Notice:** don't forget to:
1. give *absolute path* of the archive.
2. *double quote* the path.
3. *escape space character* with backslash.


### Test and print output of a specific test

```
meson test -C build --test-args=<archive-full-path> prog-c -v
```

**Notice:** same requirements as previous notice.

## Memory usage

Use environment variables `ZIM_DIRENTCACHE` and `ZIM_CLUSTERCACHE` to control in
memory cache sizing.
Example: `ZIM_DIRENTCACHE=1 ZIM_CLUSTERCACHE=1` is the minimal size.

## TODO

1. Write true unit tests.
2. Make doc.

## License

GPLv3 or later, see COPYING for more details.

<!-- Links references -->

[libzim]: https://github.com/openzim/libzim
[WebArchives]: https://github.com/birros/web-archives
