/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Roboto Medium:size=8", "FontAwesome:size=8" };
/* static const char *fonts[]          = { "Roboto Medium:size="}; */
static const char dmenufont[]       = "monospace:size=10";
static const char normbgcolor[]     = "#222222";
/* static const char normfgcolor[]     = "#bbbbbb"; */
static const char normfgcolor[]     = "#aaaaaa";
/* static const char normbordercolor[] = "#444444"; */
static const char normbordercolor[] = "#000000";
static const char selbgcolor[]      = "#535d6c";
static const char selfgcolor[]      = "#ffffff";
static const char selbordercolor[]	= "#8581a0";
static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1.", "2.", "3.", "4.", "5.", "6.", "7.", "8.", "9." , "0." };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class							instance    title       tags mask		isfloating   monitor */
	{ "Gimp",							NULL,       NULL,       0,				1,           -1 },
	{ "Firefox",						NULL,       NULL,       1 << 3,			0,           -1 },
	{ "Librewolf",						NULL,       NULL,       1 << 3,			0,           -1 },
	{ "firefox",						NULL,       NULL,       1 << 3,			0,           -1 },
	{ "Brave-browser",						NULL,       NULL,       1 << 3,			0,           -1 },
	{ "Tor Browser",					NULL,       NULL,       1 << 3,			1,           -1 },
	{ "Qutebrowser",					NULL,       NULL,       1 << 3,			0,           -1 },
	{ "qutebrowser",					NULL,       NULL,       1 << 3,			0,           -1 },
	{ "speedcrunch",					NULL,		NULL,		0,				1,			 -1 },
	{ "SpeedCrunch",					NULL,		NULL,		0,				1,			 -1 },
	{ "TelegramDesktop",				NULL,		NULL,		0,				1,			 -1 },
	{ "Skype",							NULL,		NULL,		0,				1,			 -1 },
	{ "Arandr",							NULL,		NULL,		0,				1,			 -1 },
	{ "Pcmanfm",						NULL,		NULL,		1 << 5,			0,			 -1 },
	{ "Remmina",						NULL,		NULL,		1 << 7,			0,			 -1 },
	{ "mpv",							NULL,		NULL,		0,				1,			 -1 },
	{ "vlc",							NULL,		NULL,		0,				1,			 -1 },
	{ "Xfce4-appfinder",				NULL,		NULL,		0,				1,			 -1 },
	{ "Microsoft Teams - Preview",				NULL,		NULL,		1 << 6,				0,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
#define LAYOUT_TILE		0
#define LAYOUT_BOTTOM	1
#define LAYOUT_FLOAT	2
#define LAYOUT_MONOCLE	3
#define LAYOUT_DECK		5
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	/* { "===",      bstackhoriz }, */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ "[D]",      deck },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TERMINAL	"default-terminal"
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { TERMINAL, "-t", scratchpadname, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,			            XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,			            XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_n,	   togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_backslash, setmfact,    {.f = 1.50} },
	{ AltMask,                      XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_z,		view,		   {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,			            XK_F1,     setlayout,      {.v = &layouts[LAYOUT_TILE]} },
	{ MODKEY,			            XK_F2,     setlayout,      {.v = &layouts[LAYOUT_BOTTOM]} },
	{ MODKEY,						XK_F3,     setlayout,      {.v = &layouts[LAYOUT_MONOCLE]} },
	{ MODKEY|AltMask,               XK_f,      setlayout,      {.v = &layouts[LAYOUT_FLOAT]} },
	/* { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} }, */
	/* { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} }, */
	{ MODKEY|AltMask,               XK_d,      setlayout,      {.v = &layouts[LAYOUT_DECK]} },
	/* { MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} }, */
	{ MODKEY|ShiftMask,				XK_space,  cyclelayout,    {.i = -1 } },
	{ MODKEY,						XK_space,  cyclelayout,    {.i = +1 } },
	/* { MODKEY,                       XK_z,			 setlayout,      {0} }, */
	{ MODKEY|ControlMask,           XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	/* { MODKEY,                       XK_0,      view,           {.ui = ~0 } }, */
	{ MODKEY|ShiftMask,             XK_s,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask|ControlMask,	XK_r,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
};
