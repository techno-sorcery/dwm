/* See LICENSE file for copyright and license details. */
#include <string.h>

/* appearance */
static unsigned int borderpx        = 5;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih          = 5;       /* horiz inner gap between windows */
static unsigned int gappiv          = 5;       /* vert inner gap between windows */
static unsigned int gappoh          = 0;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov          = 0;       /* vert outer gap between windows and screen edge */
static int smartgaps                = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static int user_bh                  = 1; /* 2 is the default spacing around the bar's font */
static char font[]                  = "Terminess Nerd Font:size=12";
static char rofifont[]              = "Terminus 10";
static const char *fonts[]          = { "Terminus:size=10", "Noto Color Emoji:size=9"};

static char norm_fg[]               = "#dadada";
static char norm_bg[]               = "#0a0a0a";
static char norm_border[]            = "#555555";

static char sel_fg[]                = "#dadada";
static char sel_bg[]                = "#005577";
static char sel_border[]            = "#a8a8a8";

static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { norm_fg, norm_bg, norm_border },
    [SchemeSel]  = { sel_fg,  sel_bg,  sel_border},
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "st-256color",      NULL,     NULL,           0,         0,          1,           0,        -1 },
    { NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */

    { "TTT",      bstack },
    { "===",      bstackhoriz },
    { ":::",      gaplessgrid },

    { "H[]",      deck },
    { "[M]",      monocle },

    { "><>",      NULL },    /* no layout function means floating behavior */

    { NULL,       NULL },
};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		/* { "dmenufont",          STRING,  &dmenufont }, */
        {"rofifont",            STRING,  &rofifont },
        {"user_bh",             INTEGER, &user_bh },
		{ "norm_bg",            STRING,  &norm_bg },
		{ "norm_border",        STRING,  &norm_border },
		{ "norm_fg",            STRING,  &norm_fg },
		{ "sel_bg",             STRING,  &sel_bg },
		{ "sel_border",         STRING,  &sel_border },
		{ "sel_fg",             STRING,  &sel_fg },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "gappih",          	INTEGER, &gappih },
		{ "gappiv",          	INTEGER, &gappiv },
		{ "gappoh",          	INTEGER, &gappoh },
		{ "gappov",          	INTEGER, &gappov },
		{ "statmonval",         INTEGER, &statmonval },
};

/* key definitions */
#define MODKEY Mod1Mask
#define ALTMOD Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
{ ALTMOD,                       KEY,      focusnthmon,    {.i  = TAG } }, \
{ ALTMOD|ShiftMask,             KEY,      tagnthmon,      {.i  = TAG } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "rofi", "-show", "drun", "-theme", "~/.config/rofi/dmenu.rasi", "-font", rofifont, "-drun-display-format", "{name}", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include <X11/XF86keysym.h>
static const Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_x,      killclient,     {0} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_f,      togglefullscr,  {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_v,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[5]} },

    { MODKEY|ShiftMask,             XK_q,      quit,           {1} },
    { MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} }, 
    { MODKEY|ControlMask,           XK_h,      cyclelayout,    {.i = -1 } },
    { MODKEY|ControlMask,           XK_l,      cyclelayout,    {.i = +1 } },
    { MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
    { MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
    { MODKEY,                       XK_s,      togglesticky,   {0} },

	{ MODKEY|ShiftMask,             XK_l,      viewnext,       {0} },
	{ MODKEY|ShiftMask,             XK_h,      viewprev,       {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  tagtonext,      {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   tagtoprev,      {0} },

    { MODKEY|ShiftMask,             XK_u,      setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_d,      setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,             XK_r,      setcfact,       {.f =  0.00} },
    
    { MODKEY,                       XK_r,      spawn,          SHCMD("for i in $(seq 1 25); do pkill -RTMIN+$i dwmblocks; done") },
    { 0,                            XK_Print,  spawn,          SHCMD("scrot -s -f /home/$USER/Photos/screenshots/%Y-%m-%d_%H:%M:%S.png") },
    { ShiftMask,                    XK_Print,  spawn,          SHCMD("scrot /home/$USER/Photos/screenshots/%Y-%m-%d_%H:%M:%S.png") },
    { 0,          XF86XK_MonBrightnessUp,      spawn,          SHCMD("light -A 10; pkill -RTMIN+2 dwmblocks") },
    { 0,          XF86XK_MonBrightnessDown,    spawn,          SHCMD("light -U 10; pkill -RTMIN+2 dwmblocks") },
    { 0,          XF86XK_AudioRaiseVolume,     spawn,          SHCMD("pulsemixer --change-volume +5; pkill -RTMIN+2 dwmblocks") },
    { 0,          XF86XK_AudioLowerVolume,     spawn,          SHCMD("pulsemixer --change-volume -5; pkill -RTMIN+2 dwmblocks") },
    { 0,          XF86XK_AudioMute,            spawn,          SHCMD("pulsemixer --toggle-mute; pkill -RTMIN+2 dwmblocks") },
    { 0,          XF86XK_AudioMicMute,         spawn,          SHCMD("amixer set Capture toggle") },

    // Execute programs
    { ALTMOD,                       XK_c,      spawn,          SHCMD("st -T orpie -e orpie") },
    { ALTMOD,                       XK_m,      spawn,          SHCMD("st -T ncmpcpp -e ncmpcpp") },
    { ALTMOD,                       XK_n,      spawn,          SHCMD("st -T newsboat -e newsboat") },
    { ALTMOD,                       XK_b,      spawn,          SHCMD("flatpak run com.vivaldi.Vivaldi") },

    TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
