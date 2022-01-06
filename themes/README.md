These are example Xresource themes for the [dusk](https://github.com/bakkeby/dusk) window manager.

You may want to consider placing these under `~/.config/dusk/` (or a more familiar location) and
adding something like this to your `~/.Xresources` file:

```
#include ".config/dusk/dusk.xresources.nord_theme.txt"
!#include ".config/dusk/dusk.xresources.fjord_theme.txt"
!#include ".config/dusk/dusk.xresources.gruvbox_theme.txt"
!#include ".config/dusk/dusk.xresources.dracula_theme.txt"
!#include ".config/dusk/dusk.xresources.dwm_theme.txt"
!#include ".config/dusk/dusk.xresources.one_dark_theme.txt"
```

This way you can quickly change between them as and when needed by commenting and uncommenting.

The resources can then be applied and updated using the following command:

```sh
xrdb ~/.Xresources && duskc run_command xrdb
```

Also refer to the [Xresources](https://github.com/bakkeby/dusk/wiki/Xresources) wiki page.
