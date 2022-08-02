These are example Xresource themes for the [dusk](https://github.com/bakkeby/dusk) window manager.

You may want to consider placing these under `~/.config/dusk/` (or a more familiar location) and
adding something like this to your `~/.Xresources` file:

```
#include "/full/path/to/themes/dark/dread.res"
#include "/full/path/to/themes/template.txt"
```

The `.res` files contain pre-processor definitions for the colours used (essentially giving them
names) and these are then applied in the template file when generating resource properties.

The template prepares resources for dusk, dmenu, sxiv, slock as well as others. Feel free to remove
the ones you do not need.

The first .res entry can also be replaced using a script. Refer to the
[theme_menu.sh](https://github.com/bakkeby/dusk.resources/tree/master/scripts/tools#theme_menush-theme-dir)
and
[xrdb_reload.sh](https://github.com/bakkeby/dusk.resources/tree/master/scripts/tools#xrdb_reloadsh-theme-file)
scripts.

The resources can applied and updated using the following command:

```sh
xrdb ~/.Xresources && duskc run_command xrdb
```

Also refer to the [Xresources](https://github.com/bakkeby/dusk/wiki/Xresources) wiki page.
