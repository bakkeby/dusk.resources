
These are additional helper tools that can be used standalone or as part of status scripts.

By default some scripts expect that the content of the tools directory is placed under `~/bin/`.

## pulse

This directory contains a few pulse audio scripts to adjust volume, toggle mute, etc. that also
trigger status updates for the volume status script.

## relabel.sh

A minor example script that changes the window class of the active window. This can be used for
demo purposes changing the labels used in the bar when the
[WorkspaceLabels](https://github.com/bakkeby/dusk/wiki/WorkspaceLabels) functionality is enabled.

## change_kblayout.sh

An example script demonstrating how to:
   - show language options to the user using a context menu
   - setting the X keyboard mapping to the given choice
   - updating status 9 on the bar to the user's choice

The script can be set up to trigger on mouse clicks, refer to the
[kblayout](https://github.com/bakkeby/dusk.resources/blob/master/scripts/statusbar/kblayout) and
[kblayout_click](https://github.com/bakkeby/dusk.resources/blob/master/scripts/statusbar/kblayout_click)
statusbar scripts.

## theme_menu.sh `<theme dir>`

An example script which:
   - looks for .res files in the theme directory (defaults to ~/.config/dusk/themes)
   - presents the base name of the files as options via dmenu
   - passes the selected file as an argument to xrdb_reload.sh

Uses `XDG_CONFIG_HOME`/dusk/themes for the default theme directory if set.

Optionally the theme directory can be passed in as an argument (e.g. when setting up a keyboard
shortcut).

The script as-is depends on [this bespoke version of dmenu](https://github.com/bakkeby/dmenu).
If using a stock dmenu then most of the command line arguments will need to be removed.

## xrdb_reload.sh `<theme file>`

This is a script which will:
   - if a given theme file is provided, will update the \~/.Xresources file to include the given
     theme file
   - run `xrdb ~/.Xresources` to reload the X resources
   - then run commands to trigger programs to pick up the updated resources

The latter has certain dependencies, e.g.
   - st depends on being modified with the [xresources-with-reload-signal](https://st.suckless.org/patches/xresources-with-reload-signal/) patch
   - dunst (commented out) depends on being patched with xresources support

Also note that many programs like dmenu, sxiv, nsxiv, xmenu do not support live reload of x
resources.

For the first bit add the following to be added to your \~/.Xresources file:

```c
#include "/path/to/themes/dark/dread.res"
#include "/path/to/themes/template.txt"
```

The script will replace the very first #include line that contains `/themes/` and ends with
`.res"`. Note that the replacement logic only works with GNU sed.

See the [themes](https://github.com/bakkeby/dusk.resources/tree/master/themes) section for more
details on how this works.
