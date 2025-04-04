/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 3;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static unsigned int gappih    = 0;       /* horiz inner gap between windows */
static unsigned int gappiv    = 0;       /* vert inner gap between windows */
static unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static int horizpadbar        = 0;        /* horizontal padding for statusbar */
static int vertpadbar         = 4;        /* vertical padding for statusbar */
static const char *fonts[]          = { "Terminus:size=10", "Noto Color Emoji:size=9"};
static char dmenufont[]       = "Terminus 10";
/* static const char col_gray1[]       = "#222222"; */
/* static const char col_gray2[]       = "#444444"; */
/* static const char col_gray3[]       = "#bbbbbb"; */
/* static const char col_gray4[]       = "#eeeeee"; */
/* static consconst t char col_cyan[]        = "#005577"; */
static const unsigned int baralpha = 0xc0;
static const unsigned int borderalpha = OPAQUE;

static char norm_fg[]               = "#dadada";
static char norm_bg[]               = "#0a0a0a";
static char norm_border[]            = "#555555";

static char sel_fg[]                = "#dadada";
static char sel_bg[]                = "#cc0700";
static char sel_border[]            = "#a8a8a8";

static char roficonfig[]            = "~/.config/rofi/dmenu.rasi";

/* static const char *colors[][3]      = { */
/* 	/1*               fg         bg         border   *1/ */
/* 	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 }, */
/* 	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  }, */
/* }; */

static char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { norm_fg, norm_bg, norm_border },
    [SchemeSel]  = { sel_fg,  sel_bg,  sel_border},
};

static unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

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
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    /* { "[@]",      spiral }, */
    /* { "[\\]",     dwindle }, */
    /* { "H[]",      deck }, */
    { "TTT",      bstack },
    { "===",      bstackhoriz },
    /* { "HHH",      grid }, */
    /* { "###",      nrowgrid }, */
    /* { "---",      horizgrid }, */
    { ":::",      gaplessgrid },
    /* { "|M|",      centeredmaster }, */
    /* { ">M>",      centeredfloatingmaster }, */
    { "[M]",      monocle },
    { "><>",      NULL },    /* no layout function means floating behavior */
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define ALTMOD Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; */
static const char *dmenucmd[] = { "rofi", "-show", "drun", "-theme", roficonfig, "-drun-display-format", "{name}", NULL };
static const char *termcmd[]  = { "st", NULL };


/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    /* { "baralpha",           INTEGER, &baralpha }, */
    /* { "borderalpha",        INTEGER, &borderalpha }, */
    { "roficonfig",         STRING,  &roficonfig },
    { "norm_bg",            STRING,  &norm_bg },
    { "norm_border",        STRING,  &norm_border },
    { "norm_fg",            STRING,  &norm_fg },
    { "sel_bg",             STRING,  &sel_bg },
    { "sel_border",         STRING,  &sel_border },
    { "sel_fg",             STRING,  &sel_fg },
    { "borderpx",          	INTEGER, &borderpx },
    { "snap",          		INTEGER, &snap },
    { "showbar",          	INTEGER, &showbar },
    { "topbar",          	INTEGER, &topbar },
    { "nmaster",          	INTEGER, &nmaster },
    { "resizehints",       	INTEGER, &resizehints },
    { "mfact",      	 	FLOAT,   &mfact },
};


#include <X11/XF86keysym.h>
static const Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },

    { MODKEY,                       XK_b,      togglebar,      {0} },

    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    /* { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} }, */
    /* { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} }, */
    /* { MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} }, */

    { MODKEY,                       XK_Return, zoom,           {0} },

    /* { MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */

    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_x,      killclient,     {0} },

    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_v,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[5]} },
    { MODKEY|ControlMask,		    XK_h,      cyclelayout,    {.i = -1 } },
    { MODKEY|ControlMask,           XK_l,      cyclelayout,    {.i = +1 } },

    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

    { MODKEY,                       XK_f,      togglefullscr,  {0} },

    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    { MODKEY|ShiftMask,             XK_l,      viewnext,       {0} },
    { MODKEY|ShiftMask,             XK_h,      viewprev,       {0} },
    /* { MODKEY|ControlMask|ShiftMask, XK_Right,  tagtonext,      {0} }, */
    /* { MODKEY|ControlMask|ShiftMask, XK_Left,   tagtoprev,      {0} }, */

    TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)

        { MODKEY|ShiftMask,             XK_q,      quit,           {1} },
        { MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} }, 

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
        { ALTMOD,                       XK_s,      spawn,          SHCMD("flatpak run org.signal.Signal") },
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

