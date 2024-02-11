These are example Xresource themes for the [dusk](https://github.com/bakkeby/dusk) window manager.

You may want to consider placing these under `~/.config/dusk/` (or a more familiar location) and
adding something like this to your `~/.Xresources` file:

```
#include "~/.config/dusk/themes/dark/dread.res"
#include "~/.config/dusk/themes/template.txt"
```

The `.res` files contain pre-processor definitions for the colours used (essentially giving them
names) and these are then applied in the template file when generating resource properties.

The `defaults.txt` file helps cascading some of the higher level colours down to the lower level
ones. For example if `TITLE_NORM_BG_COLOR` is not defined in the resource file then it will be set
to whatever `BASE_BACKGROUND` is set to. Likewise if `SCRATCH_NORM_BG_COLOR` is not defined then it
will be set to whatever `TITLE_NORM_BG_COLOR` is set to. This file is used by `template.txt` to make
sure that all definitions exist before they are used.

The `template.txt` file prepares resources for dusk, dmenu, sxiv, slock as well as others. Feel free
to remove the ones you do not need.

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
