/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 5;   /* horiz inner gap between windows */
static const unsigned int gappiv         = 5;   /* vert inner gap between windows */
static const unsigned int gappoh         = 5;   /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 5;   /* vert outer gap between windows and screen edge */
static const unsigned int gappfl         = 5;   /* gap between floating windows (when relevant) */
static const unsigned int smartgaps_fact = 0;   /* smartgaps factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */

static unsigned int attachdefault        = AttachMaster; // AttachMaster, AttachAbove, AttachAside, AttachBelow, AttachBottom

static const int initshowbar             = 1;   /* 0 means no bar */

static const int bar_height              = 0;   /* 0 means derive from font, >= 1 explicit height */
static const int vertpad                 = 0;  /* vertical (outer) padding of bar */
static const int sidepad                 = 0;  /* horizontal (outer) padding of bar */

static const int iconsize                = 16;  /* icon size */
static const int iconspacing             = 5;   /* space between icon and title */

static const float pfact                 = 0.25; /* size of workspace previews relative to monitor size */

static int floatposgrid_x                = 5;   /* float grid columns */
static int floatposgrid_y                = 5;   /* float grid rows */

static const int horizpadbar             = 2;   /* horizontal (inner) padding for statusbar (increases lrpad) */
static const int vertpadbar              = 0;   /* vertical (inner) padding for statusbar (increases bh, overridden by bar_height) */

static const char slopspawnstyle[]       = "-t 0 -c 0.92,0.85,0.69,0.3 -o"; /* do NOT define -f (format) here */
static const char slopresizestyle[]      = "-t 0 -c 0.92,0.85,0.69,0.3"; /* do NOT define -f (format) here */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const char *toggle_float_pos      = "50% 50% 80% 80%"; // default floating position when triggering togglefloating
static const double defaultopacity       = 0;   /* client default opacity, e.g. 0.75. 0 means don't apply opacity */
static const double moveopacity          = 0;   /* client opacity when being moved, 0 means don't apply opacity */
static const double resizeopacity        = 0;   /* client opacity when being resized, 0 means don't apply opacity */
static const double placeopacity         = 0;   /* client opacity when being placed, 0 means don't apply opacity */

/* Indicators: see lib/bar_indicators.h for options */
static int indicators[IndicatorLast] = {
	[IndicatorWsOcc] = INDICATOR_TOP_LEFT_SQUARE,
	[IndicatorFloating] = INDICATOR_TOP_LEFT_SQUARE,
};

/* Custom indicators using status2d markup, e.g. enabled via INDICATOR_CUSTOM_3 */
static char *custom_2d_indicator_1 = "^c#00A523^^r0,h,w,2^"; // green underline
static char *custom_2d_indicator_2 = "^c#55cdfc^^r3,3,4,4^^c#E72608^^r4,4,2,2^"; // blue rectangle
static char *custom_2d_indicator_3 = "^f-10^^c#E72608^𐄛"; // example using a character as an indicator
static char *custom_2d_indicator_4 = "^c#E26F0B^^r0,h,w,1^^r0,0,1,h^^r0,0,w,1^^rw,0,1,h^"; // orange box
static char *custom_2d_indicator_5 = "^c#CB9700^^r0,h,w,1^^r0,0,w,1^"; // top and bottom lines
static char *custom_2d_indicator_6 = "^c#F0A523^^r6,2,1,-4^^r-6,2,1,-4^"; // orange vertical bars

/* The below are only used if the WorkspaceLabels functionality is enabled */
static char *occupied_workspace_label_format = "%s: %s";     /* format of a workspace label */
static char *vacant_workspace_label_format = "%s";           /* format of an empty / vacant workspace */
static int lowercase_workspace_labels = 1;                   /* whether to change workspace labels to lower case */
static int prefer_window_icons_over_workspace_labels = 0;    /* whether to use window icons instead of labels if present */
static int swap_occupied_workspace_label_format_strings = 0; /* 0 gives "icon: label", 1 gives "label: icon" */

/* This determines what happens with pinned workspaces on a monitor when that monitor is removed.
 *   0 - the workspaces becomes unpinned and is moved to another monitor or
 *   1 - the workspace clients are moved to the selected workspace on the first monitor, but
 *       the workspace itself is hidden
 *
 * Non-pinned workspaces are always redistributed among the remaining monitors.
 */
static const int workspaces_per_mon = 1;

/* See util.h for options */
static uint64_t functionality = 0
//	|AutoReduceNmaster // automatically reduce the number of master clients if one is closed
//	|BanishMouseCursor // like xbanish, hides mouse cursor when using the keyboard
//	|BanishMouseCursorToCorner // makes BanishMouseCursor move the cursor to the top right corner of the screen
//	|SmartGaps // enables no or increased gaps if there is only one visible window
//	|SmartGapsMonocle // enforces no gaps in monocle layout
//	|Systray // enables a systray in the bar
//	|SystrayNoAlpha // disables the use of transparency for the systray, enable if you do not use a compositor
//	|Swallow // allows X applications started from the command line to swallow the terminal
//	|SwallowFloating // allow floating windows to swallow the terminal by default
//	|CenteredWindowName // center the window titles on the bar
//	|BarActiveGroupBorderColor // use border color of active group for the bar, otherwise normal scheme is used
//	|BarMasterGroupBorderColor // use border color of master group for the bar, otherwise normal scheme is used
//	|FlexWinBorders // use the SchemeFlex* color schemes, falls back to SchemeTitle* if disabled
//	|SpawnCwd // spawn applications in the currently selected client's working directory
//	|ColorEmoji // enables color emoji support (removes Xft workaround)
//	|Status2DNoAlpha // option to not use alpha when drawing status2d status
//	|BarBorder // draw a border around the bar
//	|BarPadding // add vertical and side padding as per vertpad and sidepad variables above
//	|NoBorders // as per the noborder patch, show no border when only one client in tiled mode
//	|Warp // warp cursor to currently focused window
//	|DecorationHints // omit drawing the window border if the applications asks not to
//	|FocusedOnTop // allows focused window to stay on top of other windows
//	|FocusedOnTopTiled // additional toggle to allow focused tiled clients to show on top of floating windows
//	|FocusFollowMouse // allow window under the mouse cursor to get focus when changing views or killing clients
//	|FocusOnClick // only allow focus change when the user clicks on windows (disables sloppy focus)
//	|FocusOnNetActive // allow windows demanding attention to receive focus automatically
//	|AllowNoModifierButtons // allow some window operations, like move and resize, to work without having to hold down a modifier key
//	|CenterSizeHintsClients // center tiled clients subject to size hints within their tiled area
//	|ResizeHints // respect size hints also when windows are tiled
//	|SnapToWindows // snap to windows when moving floating clients
//	|SnapToGaps // snap to outer gaps when moving floating clients
//	|SortScreens // monitors are numbered from left to right
//	|ViewOnWs // follow a window to the workspace it is being moved to
//	|Xresources // add support for changing colours via Xresources
//	|Debug // enables additional debug output
//	|AltWindowTitles // show alternate window titles, if present
//	|AltWorkspaceIcons // show the workspace name instead of the icons
//	|GreedyMonitor // disables swap of workspaces between monitors
//	|SmartLayoutConvertion // automatically adjust layout based on monitor orientation when moving a workspace from one monitor to another
//	|AutoHideScratchpads // automatically hide open scratchpads when moving to another workspace
//	|RioDrawIncludeBorders // indicates whether the area drawn using slop includes the window borders
//	|RioDrawSpawnAsync // spawn the application alongside rather than after drawing area using slop
//	|RestrictFocusstackToMonitor // restrict focusstack to only operate within the monitor, otherwise focus can drift between monitors
//	|WinTitleIcons // adds application icons to window titles in the bar
//	|StackerIcons // adds a stacker icon hints in window titles
//	|WorkspaceLabels // adds the class of the master client next to the workspace icon
//	|WorkspacePreview // adds preview images when hovering workspace icons in the bar
;

static int flexwintitle_masterweight     = 1; // master weight compared to hidden and floating window titles
static int flexwintitle_stackweight      = 1;  // stack weight compared to hidden and floating window titles
static int flexwintitle_hiddenweight     = 1;  // hidden window title weight
static int flexwintitle_floatweight      = 1;  // floating window title weight, set to 0 to not show floating windows
static int flexwintitle_separator        = 1;  // width of client separator

static const char *fonts[]               = { "monospace:size=10" };
static       char dmenufont[60]          = "monospace:size=10";

static char dmenunormfgcolor[] = "#bbbbbb";
static char dmenunormbgcolor[] = "#222222";
static char dmenuselfgcolor[] = "#eeeeee";
static char dmenuselbgcolor[] = "#005577";
static char dmenubordercolor[] = "#222222";

/* Xresources preferences to load at startup. */
static const ResourcePref resources[] = {
	{ "dmenu.norm.fg.color", STRING, &dmenunormfgcolor },
	{ "dmenu.norm.bg.color", STRING, &dmenunormbgcolor },
	{ "dmenu.sel.fg.color", STRING, &dmenuselfgcolor },
	{ "dmenu.sel.bg.color", STRING, &dmenuselbgcolor },
	{ "dmenu.border.bg.color", STRING, &dmenubordercolor },
	{ "dmenu.font", STRING, &dmenufont },
};

/* Default opacity levels         fg      bg      border */
unsigned int default_alphas[] = { OPAQUE, OPAQUE, OPAQUE };

static char *colors[SchemeLast][4] = {
	/*                       fg         bg         border    */
	[SchemeNorm]         = { "#bbbbbb", "#222222", "#222222" },
	[SchemeTitleNorm]    = { "#bbbbbb", "#222222", "#222222" },
	[SchemeTitleSel]     = { "#eeeeee", "#005577", "#005577" },
	[SchemeScratchNorm]  = { "#bbbbbb", "#222222", "#222222" },
	[SchemeScratchSel]   = { "#eeeeee", "#005577", "#005577" },
	[SchemeHidNorm]      = { "#bbbbbb", "#222222", "#222222" },
	[SchemeHidSel]       = { "#eeeeee", "#005577", "#005577" },
	[SchemeUrg]          = { "#222222", "#bbbbbb", "#bbbbbb" },
	[SchemeMarked]       = { "#222222", "#724559", "#724559" },
	[SchemeWsNorm]       = { "#bbbbbb", "#222222", "#222222" },
	[SchemeWsVisible]    = { "#bbbbbb", "#222222", "#222222" },
	[SchemeWsSel]        = { "#eeeeee", "#005577", "#005577" },
	[SchemeWsOcc]        = { "#bbbbbb", "#222222", "#222222" },
};

/* List of programs to start automatically during startup only. Note that these will not be
 * executed again when doing a restart. */
static const char *const autostart[] = {
//	"st", NULL,
	NULL /* terminate */
};

/* List of programs to start automatically during a restart only. These should usually be short
 * scripts that perform specific operations, e.g. changing a wallpaper. */
static const char *const autorestart[] = {
	NULL /* terminate */
};

/* There are two options when it comes to per-client rules:
 *  - a traditional struct table or
 *  - specifying the fields used
 *
 * A traditional struct table looks like this:
 *    // class      role      instance  title  wintype  opacity   flags   floatpos   scratchkey   workspace
 *    { "Gimp",     NULL,     NULL,     NULL,  NULL,    0,        0,      NULL,      NULL,        "4"        },
 *    { "Firefox",  NULL,     NULL,     NULL,  NULL,    0,        0,      NULL,      NULL,        "9"        },
 *
 * Alternatively you can specify the fields that are relevant to your rule, e.g.
 *
 *    { .class = "Gimp", .workspace = "5" },
 *    { .class = "Firefox", .workspace = "9" },
 *
 * Any fields that you do not specify will default to 0 or NULL.
 *
 * Refer to the Rule struct definition for the list of available fields.
 */
static const Rule clientrules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	{ .wintype = WTYPE "DIALOG", .flags = AlwaysOnTop|Centered|Floating },
	{ .class = "firefox", .workspace = "9" },
};

/* Bar settings, this defines what bars exists, their position, and what attributes they have.
 *
 *    monitor - the exact monitor number the bar should be created on
 *              (0 - primary, 1 - secondary, 2 - tertiary)
 *    idx     - the bar index, used in relation to bar rules below
 *              (bar indexes can be reused across monitors)
 *    vert    - whether the bar is horizontal (0) or vertical (1), not
 *              all bar modules will have support for being displayed
 *              in a vertical bar
 *    name    - this is just a reference that can be used for logging
 *              purposes
 *
 *    Bar positioning consists of four values, x, y, w and h which,
 *    similarly to floatpos, can have different meaning depending on
 *    the characters used. Absolute positioning (as in cross-monitor)
 *    is not supported, but exact positions relative to the monitor
 *    can be used. Percentage values are recommended for portability.
 *
 *    All values can be a percentage relative to the space available
 *    on the monitor or they can be exact values, here are some example
 *    values:
 *       x
 *                  0% - left aligned (default)
 *                100% - right aligned
 *                 50% - bar is centered on the screen
 *                  0x - exact position relative to the monitor
 *                 -1x - value < 0 means use default
 *       y
 *                  0% - top bar (default)
 *                100% - bottom bar
 *                  0y - exact position relative to the monitor
 *                 -1y - value < 0 means use default
 *       w
 *                100% - bar takes up the full width of the screen (default)
 *                 20% - small bar taking a fifth of the width of the screen
 *                500w - the bar is 500 pixels wide (including border)
 *                 -1w - value <= 0 means use default
 *       h
 *                100% - bar takes up the full height of the screen
 *                 20% - small bar taking a fifth of the height of screen
 *                 30h - the bar is 30 pixels high (including border)
 *                 -1h - value <= 0 means use the default (deduced by font size)
 *
 *    Note that vertical and horizontal side padding are controlled by the
 *    vertpad and sidepad variables towards the top of this configuration file.
 */
static const BarDef bars[] = {
	/* monitor idx  vert   x     y      w     h     name  */
	{  0,      0,   0,    "0%    0%     100% -1h ", "Primary top" },
	{  1,      0,   0,    "0%    0%     100% -1h ", "Secondary top" },
	{  2,      0,   0,    "0%    0%     100% -1h ", "Tertiary top" },
	{  3,      0,   0,    "0%    0%     100% -1h ", "Quaternary top" },
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    scheme - defines the default scheme for the bar module
 *    lpad - adds artificial spacing on the left hand side of the module
 *    rpad - adds artificial spacing on the right hand side of the module
 *    value - arbitrary value where the interpretation is module specific
 *    alignment - how the module is aligned compared to other modules
 *    sizefunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
#define PWRL PwrlNone
static const BarRule barrules[] = {
	/* monitor  bar    scheme   lpad rpad value  alignment               sizefunc                  drawfunc                 clickfunc                 hoverfunc                 name */
	{ -1,       0,     0,       0,   0,   PWRL,  BAR_ALIGN_LEFT,         size_workspaces,          draw_workspaces,         click_workspaces,         hover_workspaces,         "workspaces" },
	{ -1,       0,     0,       0,   5,   0,     BAR_ALIGN_LEFT,         size_ltsymbol,            draw_ltsymbol,           click_ltsymbol,           NULL,                     "layout" },
	{'A',       0,     0,       5,   5,   0,     BAR_ALIGN_RIGHT,        size_systray,             draw_systray,            click_systray,            NULL,                     "systray" },
	{'A',       0,     0,       5,   5,   0,     BAR_ALIGN_RIGHT,        size_status,              draw_status,             click_status,             NULL,                     "status0" },
	{'A',       0,     0,       5,   5,   1,     BAR_ALIGN_RIGHT,        size_status,              draw_status,             click_status,             NULL,                     "status1" },
	{'A',       0,     0,       5,   5,   2,     BAR_ALIGN_RIGHT,        size_status,              draw_status,             click_status,             NULL,                     "status2" },
	{'A',       0,     0,       5,   5,   3,     BAR_ALIGN_RIGHT,        size_status,              draw_status,             click_status,             NULL,                     "status3" },
	{'A',       0,     0,       5,   5,   4,     BAR_ALIGN_RIGHT,        size_status,              draw_status,             click_status,             NULL,                     "status4" },
	{'A',       0,     0,       5,   5,   5,     BAR_ALIGN_RIGHT,        size_status,              draw_status,             click_status,             NULL,                     "status5" },
	{'A',       0,     0,       5,   5,   6,     BAR_ALIGN_RIGHT,        size_status,              draw_status,             click_status,             NULL,                     "status6" },
	{'A',       0,     0,       5,   5,   7,     BAR_ALIGN_LEFT,         size_status,              draw_status,             click_status,             NULL,                     "status7" },
	{'A',       0,     0,       5,   5,   8,     BAR_ALIGN_RIGHT,        size_status,              draw_status,             click_status,             NULL,                     "status8" },
	{'A',       0,     0,       5,   5,   9,     BAR_ALIGN_RIGHT,        size_status,              draw_status,             click_status,             NULL,                     "status9" },
	{ -1,       0,     0,       5,   0,   0,     BAR_ALIGN_NONE,         size_wintitle_sticky,     draw_wintitle_sticky,    click_wintitle_sticky,    NULL,                     "wintitle_sticky" },
	{ -1,       0,     0,       5,   0,   PWRL,  BAR_ALIGN_NONE,         size_wintitle_single,     draw_wintitle_single,    click_wintitle_single,    NULL,                     "wintitle" },
};

/* Workspace rules define what workspaces are available and their properties.
 *
 *    name     - the name of the workspace, this is a reference used for keybindings - see WSKEYS
 *    monitor  - the monitor number the workspace starts on by default, -1 means assign freely
 *    pinned   - whether the workspace is pinned on the assigned monitor
 *    layout   - the layout index the workspace should start with, refer to the layouts array
 *    mfact    - factor of master area size, -1 means use global config
 *    nmaster  - number of clients in master area, -1 means use global config
 *    nstack   - number of clients in primary stack area, -1 means use global config
 *    gaps     - whether gaps are enabled for the workspace, -1 means use global config
 *
 *    icons:
 *       def   - the default icon shown for the workspace, if empty string then the workspace is
 *               hidden by default, if NULL then the workspace name is used for the icon
 *       vac   - the vacant icon shows if the workspace is selected, the default icon is an empty
 *               string (hidden by default) and the workspace has no clients
 *       occ   - the occupied icon shows if the workspace has clients
 *
 */
static const WorkspaceRule wsrules[] = {
	/*                                                                     ------------------------------- schemes ------------------------------- ------ icons ------
	   name,  monitor,  pinned,  layout,  mfact,  nmaster,  nstack,  gaps, default,          visible,          selected,         occupied,         def,   vac,  occ,  */
	{  "11",   0,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "1",   "",   "1",  },
	{  "12",   0,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "2",   "",   "2",  },
	{  "13",   0,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "3",   "",   "3",  },
	{  "14",   0,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "4",   "",   "4",  },
	{  "15",   0,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "5",   "",   "5",  },
	{  "16",   0,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "6",   "",   "6",  },
	{  "17",   0,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "7",   "",   "7",  },
	{  "18",   0,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "8",   "",   "8",  },
	{  "19",   0,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "9",   "",   "9",  },
	{  "21",   1,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "1",   "",   "1",  },
	{  "22",   1,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "2",   "",   "2",  },
	{  "23",   1,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "3",   "",   "3",  },
	{  "24",   1,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "4",   "",   "4",  },
	{  "25",   1,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "5",   "",   "5",  },
	{  "26",   1,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "6",   "",   "6",  },
	{  "27",   1,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "7",   "",   "7",  },
	{  "28",   1,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "8",   "",   "8",  },
	{  "29",   1,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "9",   "",   "9",  },
	{  "31",   2,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "1",   "",   "1",  },
	{  "32",   2,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "2",   "",   "2",  },
	{  "33",   2,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "3",   "",   "3",  },
	{  "34",   2,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "4",   "",   "4",  },
	{  "35",   2,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "5",   "",   "5",  },
	{  "36",   2,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "6",   "",   "6",  },
	{  "37",   2,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "7",   "",   "7",  },
	{  "38",   2,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "8",   "",   "8",  },
	{  "39",   2,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "9",   "",   "9",  },
	{  "41",   3,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "1",   "",   "1",  },
	{  "42",   3,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "2",   "",   "2",  },
	{  "43",   3,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "3",   "",   "3",  },
	{  "44",   3,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "4",   "",   "4",  },
	{  "45",   3,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "5",   "",   "5",  },
	{  "46",   3,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "6",   "",   "6",  },
	{  "47",   3,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "7",   "",   "7",  },
	{  "48",   3,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "8",   "",   "8",  },
	{  "49",   3,       1,       0,       -1,    -1,       -1,      -1,    SchemeWsNorm,     SchemeWsVisible,  SchemeWsSel,      SchemeWsOcc,      "9",   "",   "9",  },
};

static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int nstack      = 0;    /* number of clients in primary stack area */
static const int enablegaps  = 0;    /* whether gaps are enabled by default or not */

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function, { nmaster, nstack, layout, master axis, stack axis, secondary stack axis, symbol func }, name */
	{ "[]=",      flextile,         { -1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, TOP_TO_BOTTOM, 0, NULL }, "tile" },
	{ "[M]",      flextile,         { -1, -1, NO_SPLIT, MONOCLE, MONOCLE, 0, NULL }, "monocle" },
 	{ "><>",      NULL,             { -1, -1 }, "floating" }, /* no layout function means floating behavior */
};

#define Shift ShiftMask
#define Ctrl ControlMask
#define Alt Mod1Mask
#define AltGr Mod3Mask
#define Super Mod4Mask
#define ShiftGr Mod5Mask

/* key definitions */
#define MODKEY Alt

#define SCRATCHKEYS(MOD,KEY,CMD) \
	{ KeyPress,   MOD,                      KEY,      togglescratch,       {.v = CMD } }, \
	{ KeyPress,   MOD|Ctrl,                 KEY,      setscratch,          {.v = CMD } }, \
	{ KeyPress,   MOD|Ctrl|Shift,           KEY,      removescratch,       {.v = CMD } }, \

#define WSKEYS(MOD,KEY,INDEX) \
	{ KeyPress,   MOD,                      KEY,      viewwsbyindex,        {.i = INDEX} }, \
	{ KeyPress,   MOD|Ctrl,                 KEY,      enablewsbyindex,      {.i = INDEX} }, \

#define STACKKEYS(MOD,ACTION) \
	{ KeyPress,   MOD, XK_j, ACTION, {.i = INC(+1) } }, \
	{ KeyPress,   MOD, XK_k, ACTION, {.i = INC(-1) } }, \
	{ KeyPress,   MOD, XK_s, ACTION, {.i = PREVSEL } }, \
	{ KeyPress,   MOD, XK_w, ACTION, {.i = 1 } }, \
	{ KeyPress,   MOD, XK_e, ACTION, {.i = 2 } }, \
	{ KeyPress,   MOD, XK_a, ACTION, {.i = 3 } }, \
	{ KeyPress,   MOD, XK_z, ACTION, {.i = LASTTILED } },

/* This relates to the StackerIcons functionality and should mirror the STACKKEYS list above. */
static const StackerIcon stackericons[] = {
	{ "[j]", {.i = INC(+1) } },
	{ "[k]", {.i = INC(-1) } },
	{ "[s]", {.i = PREVSEL } },
	{ "[w]", {.i = 1 } },
	{ "[e]", {.i = 2 } },
	{ "[a]", {.i = 3 } },
	{ "[z]", {.i = LASTTILED } },
};

/* Helper macros for spawning commands */
#define SHCMD(cmd) { .v = (const char*[]){ NULL, "/bin/sh", "-c", cmd, NULL } }
#define CMD(...)   { .v = (const char*[]){ NULL, __VA_ARGS__, NULL } }

/* Scratch/Spawn commands:        NULL (scratchkey), command, argument, argument, ..., NULL */
static const char *termcmd[]  = { "st", NULL };
static const char *dmenucmd[] = {
	"dmenu_run",
	"-fn", dmenufont,
	"-nb", dmenunormbgcolor,
	"-nf", dmenunormfgcolor,
	"-sb", dmenuselbgcolor,
	"-sf", dmenuselfgcolor,
//	"-bb", dmenubordercolor,
	NULL
};

static const char *statusclickcmd[] = { "~/bin/statusbar/statusclick.sh", NULL };

static Key keys[] = {
	/* type       modifier                      key              function                argument */
	{ KeyPress,   MODKEY,                       XK_p,            spawn,                  {.v = dmenucmd } }, // spawn dmenu for launching other programs
	{ KeyPress,   MODKEY|Shift,                 XK_Return,       spawn,                  {.v = termcmd } }, // spawn a terminal
	{ KeyPress,   MODKEY,                       XK_b,            togglebar,              {0} }, // toggles the display of the bar(s) on the current monitor
	{ KeyPress,   MODKEY,                       XK_j,            focusstack,             {.i = +1 } }, // focus on the next client in the stack
	{ KeyPress,   MODKEY,                       XK_k,            focusstack,             {.i = -1 } }, // focus on the previous client in the stack
	{ KeyPress,   MODKEY,                       XK_i,            incnmaster,             {.i = +1 } }, // increase the number of clients in the master area
	{ KeyPress,   MODKEY,                       XK_d,            incnmaster,             {.i = -1 } }, // decrease the number of clients in the master area
	{ KeyPress,   MODKEY,                       XK_h,            setmfact,               {.f = -0.05} }, // decrease the size of the master area compared to the stack area(s)
	{ KeyPress,   MODKEY,                       XK_l,            setmfact,               {.f = +0.05} }, // increase the size of the master area compared to the stack area(s)
	{ KeyPress,   MODKEY,                       XK_Return,       zoom,                   {0} }, // moves the currently focused window to/from the master area (for tiled layouts)
	{ KeyPress,   MODKEY,                       XK_Return,       zoom,                   {0} }, // moves the currently focused window to/from the master area (for tiled layouts)
//	{ KeyPress,   MODKEY,                       XK_Tab,          togglewsmask,           {0} }, // revert to previous view
	{ KeyPress,   MODKEY,                       XK_c,            killclient,             {0} }, // close the currently focused window
	{ KeyPress,   MODKEY,                       XK_t,            setlayout,              {0} }, // set the tile layout
	{ KeyPress,   MODKEY,                       XK_f,            setlayout,              {1} }, // set the monocle layout
	{ KeyPress,   MODKEY,                       XK_m,            setlayout,              {2} }, // set the floating layout
	{ KeyPress,   MODKEY,                       XK_space,        setlayout,              {-1} }, // toggles between current and previous layout
	{ KeyPress,   MODKEY|ShiftMask,             XK_space,        togglefloating,         {0} }, // toggles between tiled and floating arrangement for the currently focused client
	{ KeyPress,   MODKEY,                       XK_0,            viewallwsonmon,         {0} }, // view all workspaces on the current monitor
	{ KeyPress,   MODKEY,                       XK_comma,        focusmon,               {.i = -1 } }, // focus on the previous monitor, if any
	{ KeyPress,   MODKEY,                       XK_period,       focusmon,               {.i = +1 } }, // focus on the next monitor, if any
	{ KeyPress,   MODKEY|Shift,                 XK_comma,        clienttomon,            {.i = -1 } }, // sends the current client to an adjacent monitor
	{ KeyPress,   MODKEY|Shift,                 XK_period,       clienttomon,            {.i = +1 } }, // sends the current client to an adjacent monitor
	WSKEYS(MODKEY,                              XK_1,  1)
	WSKEYS(MODKEY,                              XK_2,  2)
	WSKEYS(MODKEY,                              XK_3,  3)
	WSKEYS(MODKEY,                              XK_4,  4)
	WSKEYS(MODKEY,                              XK_5,  5)
	WSKEYS(MODKEY,                              XK_6,  6)
	WSKEYS(MODKEY,                              XK_7,  7)
	WSKEYS(MODKEY,                              XK_8,  8)
	WSKEYS(MODKEY,                              XK_9,  9)
	{ KeyPress,   MODKEY|Shift,                 XK_q,            quit,                   {0} }, // exit dusk
	{ KeyPress,   MODKEY|Ctrl|Shift,            XK_q,            restart,                {0} }, // restart dusk
};

/* button definitions */
/* click can be ClkWorkspaceBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                     event mask               button          function          argument */
	{ ClkLtSymbol,               0,                       Button1,        setlayout,        {-1} }, // toggles between current and previous layout
	{ ClkLtSymbol,               0,                       Button3,        setlayout,        {2} },  // change to floating layout
	{ ClkWinTitle,               0,                       Button1,        focuswin,         {0} }, // focus on the given client
	{ ClkWinTitle,               0,                       Button2,        zoom,             {0} }, // moves the currently focused window to/from the master area (for tiled layouts)
//	{ ClkStatusText,             0,                       Button1,        statusclick,      {.i = 1 } }, // sends mouse button presses to statusclick script when clicking on status modules
//	{ ClkStatusText,             0,                       Button2,        statusclick,      {.i = 2 } },
//	{ ClkStatusText,             0,                       Button3,        statusclick,      {.i = 3 } },
//	{ ClkStatusText,             0,                       Button4,        statusclick,      {.i = 4 } },
//	{ ClkStatusText,             0,                       Button5,        statusclick,      {.i = 5 } },
//	{ ClkStatusText,             0,                       Button6,        statusclick,      {.i = 6 } },
//	{ ClkStatusText,             0,                       Button7,        statusclick,      {.i = 7 } },
//	{ ClkStatusText,             0,                       Button8,        statusclick,      {.i = 8 } },
//	{ ClkStatusText,             0,                       Button9,        statusclick,      {.i = 9 } },
	{ ClkStatusText,             Shift,                   Button1,        statusclick,      {.i = 10 } },
	{ ClkStatusText,             Shift,                   Button2,        statusclick,      {.i = 11 } },
	{ ClkStatusText,             Shift,                   Button3,        statusclick,      {.i = 12 } },
	{ ClkStatusText,             0,                       Button1,        spawn,            {.v = termcmd } }, // spawn a terminal
	{ ClkStatusText,             0,                       Button2,        spawn,            {.v = termcmd } }, // spawn a terminal
	{ ClkStatusText,             0,                       Button3,        spawn,            {.v = termcmd } }, // spawn a terminal
	{ ClkStatusText,             0,                       Button4,        spawn,            {.v = termcmd } }, // spawn a terminal
	{ ClkStatusText,             0,                       Button5,        spawn,            {.v = termcmd } }, // spawn a terminal
	{ ClkStatusText,             0,                       Button6,        spawn,            {.v = termcmd } }, // spawn a terminal
	{ ClkStatusText,             0,                       Button7,        spawn,            {.v = termcmd } }, // spawn a terminal
	{ ClkStatusText,             0,                       Button8,        spawn,            {.v = termcmd } }, // spawn a terminal
	{ ClkStatusText,             0,                       Button9,        spawn,            {.v = termcmd } }, // spawn a terminal
	{ ClkClientWin,              MODKEY,                  Button1,        movemouse,        {0} }, // moves a client window into a floating or tiled position depending on floating state
	{ ClkClientWin,              MODKEY,                  Button2,        togglefloating,   {0} }, // toggles between tiled and floating arrangement for given client
	{ ClkClientWin,              MODKEY,                  Button3,        resizemouse,      {0} }, // change the size of a floating client window
	{ ClkWorkspaceBar,           0,                       Button1,        viewws,           {0} }, // view the workspace by clicking on workspace icon
	{ ClkWorkspaceBar,           0,                       Button3,        enablews,         {0} }, // enables the workspace in addition to other workspaces
};

static const char *ipcsockpath = "/tmp/dusk.sock";
static IPCCommand ipccommands[] = {
	IPCCOMMANDS( customlayout, 8, ARG_TYPE_SINT, ARG_TYPE_STR, ARG_TYPE_SINT, ARG_TYPE_SINT, ARG_TYPE_SINT, ARG_TYPE_SINT, ARG_TYPE_SINT, ARG_TYPE_SINT ),
	IPCCOMMAND( changeopacity, ARG_TYPE_FLOAT ),
	IPCCOMMAND( clienttomon, ARG_TYPE_SINT ),
	IPCCOMMAND( clientstomon, ARG_TYPE_SINT ),
	IPCCOMMAND( cyclelayout, ARG_TYPE_SINT ),
	IPCCOMMAND( enable, ARG_TYPE_STR ),
	IPCCOMMAND( enablewsbyindex, ARG_TYPE_SINT ),
	IPCCOMMAND( enablewsbyname, ARG_TYPE_STR ),
	IPCCOMMAND( defaultgaps, ARG_TYPE_NONE ),
	IPCCOMMAND( disable, ARG_TYPE_STR ),
	IPCCOMMAND( floatpos, ARG_TYPE_STR ),
	IPCCOMMAND( focusdir, ARG_TYPE_SINT ),
	IPCCOMMAND( focusmaster, ARG_TYPE_NONE ),
	IPCCOMMAND( focusmon, ARG_TYPE_SINT ),
	IPCCOMMAND( focusstack, ARG_TYPE_SINT ),
	IPCCOMMAND( focusurgent, ARG_TYPE_NONE ),
	IPCCOMMAND( hidebar, ARG_TYPE_NONE ),
	IPCCOMMAND( incrgaps, ARG_TYPE_SINT ),
	IPCCOMMAND( incrigaps, ARG_TYPE_SINT ),
	IPCCOMMAND( incrogaps, ARG_TYPE_SINT ),
	IPCCOMMAND( incrihgaps, ARG_TYPE_SINT ),
	IPCCOMMAND( incrivgaps, ARG_TYPE_SINT ),
	IPCCOMMAND( incrohgaps, ARG_TYPE_SINT ),
	IPCCOMMAND( incrovgaps, ARG_TYPE_SINT ),
	IPCCOMMAND( incnmaster, ARG_TYPE_SINT ),
	IPCCOMMAND( incnstack, ARG_TYPE_SINT ),
	IPCCOMMAND( inplacerotate, ARG_TYPE_SINT ),
	IPCCOMMAND( killclient, ARG_TYPE_NONE ),
	IPCCOMMAND( killunsel, ARG_TYPE_NONE ),
	IPCCOMMAND( layoutconvert, ARG_TYPE_NONE ),
	IPCCOMMAND( mark, ARG_TYPE_NONE ),
	IPCCOMMAND( markall, ARG_TYPE_SINT ), // 0 = mark all, 1 = mark floating, 2 = mark hidden
	IPCCOMMAND( maximize, ARG_TYPE_NONE ),
	IPCCOMMAND( maximizevert, ARG_TYPE_NONE ),
	IPCCOMMAND( maximizehorz, ARG_TYPE_NONE ),
	IPCCOMMAND( mirrorlayout, ARG_TYPE_NONE ),
	IPCCOMMAND( movetowsbyindex, ARG_TYPE_SINT ),
	IPCCOMMAND( movetowsbyname, ARG_TYPE_STR ),
	IPCCOMMAND( sendtowsbyindex, ARG_TYPE_SINT ),
	IPCCOMMAND( sendtowsbyname, ARG_TYPE_STR ),
	IPCCOMMAND( movealltowsbyindex, ARG_TYPE_SINT ),
	IPCCOMMAND( movealltowsbyname, ARG_TYPE_STR ),
	IPCCOMMAND( moveallfromwsbyindex, ARG_TYPE_SINT ),
	IPCCOMMAND( moveallfromwsbyname, ARG_TYPE_STR ),
	IPCCOMMAND( movewsdir, ARG_TYPE_SINT ),
	IPCCOMMAND( rotatelayoutaxis, ARG_TYPE_SINT ),
	IPCCOMMAND( rotatestack, ARG_TYPE_SINT ),
	IPCCOMMAND( placedir, ARG_TYPE_SINT ),
	IPCCOMMAND( pushdown, ARG_TYPE_NONE ),
	IPCCOMMAND( pushup, ARG_TYPE_NONE ),
	IPCCOMMAND( quit, ARG_TYPE_NONE ),
	IPCCOMMAND( restart, ARG_TYPE_NONE ),
	IPCCOMMAND( rioresize, ARG_TYPE_NONE ),
	IPCCOMMAND( setattachdefault, ARG_TYPE_STR),
	IPCCOMMAND( setborderpx, ARG_TYPE_SINT ),
	IPCCOMMAND( setclientborderpx, ARG_TYPE_SINT ),
	IPCCOMMAND( setlayoutaxisex, ARG_TYPE_SINT ),
	IPCCOMMAND( setlayout, ARG_TYPE_SINT ),
	IPCCOMMAND( setcfact, ARG_TYPE_FLOAT ),
	IPCCOMMAND( setmfact, ARG_TYPE_FLOAT ),
	IPCCOMMAND( setwfact, ARG_TYPE_FLOAT ),
	IPCCOMMAND( setgapsex, ARG_TYPE_SINT ),
	IPCCOMMANDS( setstatus, 2, ARG_TYPE_UINT, ARG_TYPE_STR ),
	IPCCOMMAND( settitle, ARG_TYPE_STR ),
	IPCCOMMANDS( setwintitle, 2, ARG_TYPE_UINT, ARG_TYPE_STR ),
	IPCCOMMAND( showbar, ARG_TYPE_NONE ),
	IPCCOMMAND( showhideclient, ARG_TYPE_NONE ),
	IPCCOMMAND( stackfocus, ARG_TYPE_SINT ),
	IPCCOMMAND( stackpush, ARG_TYPE_SINT ),
	IPCCOMMAND( stackswap, ARG_TYPE_SINT ),
	IPCCOMMAND( swallow, ARG_TYPE_NONE ),
	IPCCOMMAND( switchcol, ARG_TYPE_NONE ),
	IPCCOMMAND( swapwsbyindex, ARG_TYPE_SINT ),
	IPCCOMMAND( swapwsbyname, ARG_TYPE_STR ),
	IPCCOMMAND( toggle, ARG_TYPE_STR ), // toggle functionality on and off
	IPCCOMMAND( togglebar, ARG_TYPE_NONE ),
	IPCCOMMAND( togglebarpadding, ARG_TYPE_NONE ),
	IPCCOMMAND( togglecompact, ARG_TYPE_NONE ),
	IPCCOMMAND( toggleclientflag, ARG_TYPE_STR ),
	IPCCOMMAND( togglefakefullscreen, ARG_TYPE_NONE ),
	IPCCOMMAND( togglefloating, ARG_TYPE_NONE ),
	IPCCOMMAND( togglefullscreen, ARG_TYPE_NONE ),
	IPCCOMMAND( togglegaps, ARG_TYPE_NONE ),
	IPCCOMMAND( togglekeybindings, ARG_TYPE_NONE ),
	IPCCOMMAND( togglemark, ARG_TYPE_NONE ),
	IPCCOMMAND( togglenomodbuttons, ARG_TYPE_NONE ),
	IPCCOMMAND( togglepinnedws, ARG_TYPE_NONE ),
	IPCCOMMAND( togglesticky, ARG_TYPE_NONE ),
	IPCCOMMAND( togglews, ARG_TYPE_NONE ),
	IPCCOMMAND( transfer, ARG_TYPE_NONE ),
	IPCCOMMAND( transferall, ARG_TYPE_NONE ),
	IPCCOMMAND( unfloatvisible, ARG_TYPE_NONE ),
	IPCCOMMAND( unmark, ARG_TYPE_NONE ),
	IPCCOMMAND( unmarkall, ARG_TYPE_NONE ),
	IPCCOMMAND( unswallow, ARG_TYPE_NONE ),
	IPCCOMMAND( viewallwsonmon, ARG_TYPE_NONE ),
	IPCCOMMAND( viewalloccwsonmon, ARG_TYPE_NONE ),
	IPCCOMMAND( viewselws, ARG_TYPE_NONE ),
	IPCCOMMAND( viewwsbyindex, ARG_TYPE_SINT ),
	IPCCOMMAND( viewwsbyname, ARG_TYPE_STR ),
	IPCCOMMAND( viewwsdir, ARG_TYPE_SINT ),
	IPCCOMMAND( xrdb, ARG_TYPE_NONE ), // reload xrdb / Xresources
	IPCCOMMAND( zoom, ARG_TYPE_NONE ),
};
