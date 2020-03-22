/* See LICENSE file for copyright and license details. */

/*
 * appearance
 *
 * font: see http://freedesktop.org/software/fontconfig/fontconfig-user.html
 */
static char *font = "UbuntuMono Nerd Font:size=20";
static int borderpx = 2;

/*
 * What program is execed by st depends of these precedence rules:
 * 1: program passed with -e
 * 2: utmp option
 * 3: SHELL environment variable
 * 4: value of shell in /etc/passwd
 * 5: value of shell in config.h
 */
static char *shell = "/bin/sh";
char *utmp = NULL;
char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400 -ixon -ixoff";

/* identification sequence returned in DA and DECID */
char *vtiden = "\033[?6c";

/* Kerning / character bounding-box multipliers */
static float cwscale = 1.0;
static float chscale = 1.0;

/*
 * word delimiter string
 *
 * More advanced example: L" `'\"()[]{}"
 */
wchar_t *worddelimiters = L" ";

/* selection timeouts (in milliseconds) */
static unsigned int doubleclicktimeout = 300;
static unsigned int tripleclicktimeout = 600;

/* alt screens */
int allowaltscreen = 1;

/* frames per second st should at maximum draw to the screen */
static unsigned int xfps = 120;
static unsigned int actionfps = 30;

/*
 * blinking timeout (set to 0 to disable blinking) for the terminal blinking
 * attribute.
 */
static unsigned int blinktimeout = 800;

/*
 * thickness of underline and bar cursors
 */
static unsigned int cursorthickness = 2;
/*
 * 1: render most of the lines/blocks characters without using the font for
 *    perfect alignment between cells (U2500 - U259F except dashes/diagonals).
 *    Bold affects lines thickness if boxdraw_bold is not 0. Italic is ignored.
 * 0: disable (render all U25XX glyphs normally from the font).
 */
const int boxdraw = 0;
const int boxdraw_bold = 0;

/* braille (U28XX):  1: render as adjacent "pixels",  0: use font */
const int boxdraw_braille = 0;

/*
 * bell volume. It must be a value between -100 and 100. Use 0 for disabling
 * it
 */
static int bellvolume = 0;

/* default TERM value */
char *termname = "xterm-256color";

/*
 * spaces per tab
 *
 * When you are changing this value, don't forget to adapt the »it« value in
 * the st.info and appropriately install the st.info in the environment where
 * you use this st version.
 *
 *	it#$tabspaces,
 *
 * Secondly make sure your kernel is not expanding tabs. When running `stty
 * -a` »tab0« should appear. You can tell the terminal to not expand tabs by
 *  running following command:
 *
 *	stty tabs
 */
unsigned int tabspaces = 8;

/* Terminal colors (16 first used in escape sequence) */
static const char *colorname[] = {
    [0] = "#000000",
    [1] = "#cd0000",
    [2] = "#00cd00",
    [3] = "#cdcd00",
    [4] = "#1E90FF",
    [5] = "#cd00cd",
    [6] = "#00cdcd",
    [7] = "#c0c0c0",

    [8] = "#666666",
    [9] = "#ff0000",
    [10] = "#00ff00",
    [11] = "#ffff00",
    [12] = "#0000ff",
    [13] = "#ff00ff",
    [14] = "#00ffff",
    [15] = "#ffffff",

    [16] = "#000000",
    [17] = "#00005f",
    [18] = "#000087",
    [19] = "#0000af",
    [20] = "#0000d7",
    [21] = "#0000ff",
    [22] = "#005f00",
    [23] = "#005f5f",
    [24] = "#005f87",
    [25] = "#005faf",
    [26] = "#005fd7",
    [27] = "#005fff",
    [28] = "#008700",
    [29] = "#00875f",
    [30] = "#008787",
    [31] = "#0087af",
    [32] = "#0087d7",
    [33] = "#0087ff",
    [34] = "#00af00",
    [35] = "#00af5f",
    [36] = "#00af87",
    [37] = "#00afaf",
    [38] = "#00afd7",
    [39] = "#00afff",
    [40] = "#00d700",
    [41] = "#00d75f",
    [42] = "#00d787",
    [43] = "#00d7af",
    [44] = "#00d7d7",
    [45] = "#00d7ff",
    [46] = "#00ff00",
    [47] = "#00ff5f",
    [48] = "#00ff87",
    [49] = "#00ffaf",
    [50] = "#00ffd7",
    [51] = "#00ffff",
    [52] = "#5f0000",
    [53] = "#5f005f",
    [54] = "#5f0087",
    [55] = "#5f00af",
    [56] = "#5f00d7",
    [57] = "#5f00ff",
    [58] = "#5f5f00",
    [59] = "#5f5f5f",
    [60] = "#5f5f87",
    [61] = "#5f5faf",
    [62] = "#5f5fd7",
    [63] = "#5f5fff",
    [64] = "#5f8700",
    [65] = "#5f875f",
    [66] = "#5f8787",
    [67] = "#5f87af",
    [68] = "#5f87d7",
    [69] = "#5f87ff",
    [70] = "#5faf00",
    [71] = "#5faf5f",
    [72] = "#5faf87",
    [73] = "#5fafaf",
    [74] = "#5fafd7",
    [75] = "#5fafff",
    [76] = "#5fd700",
    [77] = "#5fd75f",
    [78] = "#5fd787",
    [79] = "#5fd7af",
    [80] = "#5fd7d7",
    [81] = "#5fd7ff",
    [82] = "#5fff00",
    [83] = "#5fff5f",
    [84] = "#5fff87",
    [85] = "#5fffaf",
    [86] = "#5fffd7",
    [87] = "#5fffff",
    [88] = "#870000",
    [89] = "#87005f",
    [90] = "#870087",
    [91] = "#8700af",
    [92] = "#8700d7",
    [93] = "#8700ff",
    [94] = "#875f00",
    [95] = "#875f5f",
    [96] = "#875f87",
    [97] = "#875faf",
    [98] = "#875fd7",
    [99] = "#875fff",
    [100] = "#878700",
    [101] = "#87875f",
    [102] = "#878787",
    [103] = "#8787af",
    [104] = "#8787d7",
    [105] = "#8787ff",
    [106] = "#87af00",
    [107] = "#87af5f",
    [108] = "#87af87",
    [109] = "#87afaf",
    [110] = "#87afd7",
    [111] = "#87afff",
    [112] = "#87d700",
    [113] = "#87d75f",
    [114] = "#87d787",
    [115] = "#87d7af",
    [116] = "#87d7d7",
    [117] = "#87d7ff",
    [118] = "#87ff00",
    [119] = "#87ff5f",
    [120] = "#87ff87",
    [121] = "#87ffaf",
    [122] = "#87ffd7",
    [123] = "#87ffff",
    [124] = "#af0000",
    [125] = "#af005f",
    [126] = "#af0087",
    [127] = "#af00af",
    [128] = "#af00d7",
    [129] = "#af00ff",
    [130] = "#af5f00",
    [131] = "#af5f5f",
    [132] = "#af5f87",
    [133] = "#af5faf",
    [134] = "#af5fd7",
    [135] = "#af5fff",
    [136] = "#af8700",
    [137] = "#af875f",
    [138] = "#af8787",
    [139] = "#af87af",
    [140] = "#af87d7",
    [141] = "#af87ff",
    [142] = "#afaf00",
    [143] = "#afaf5f",
    [144] = "#afaf87",
    [145] = "#afafaf",
    [146] = "#afafd7",
    [147] = "#afafff",
    [148] = "#afd700",
    [149] = "#afd75f",
    [150] = "#afd787",
    [151] = "#afd7af",
    [152] = "#afd7d7",
    [153] = "#afd7ff",
    [154] = "#afff00",
    [155] = "#afff5f",
    [156] = "#afff87",
    [157] = "#afffaf",
    [158] = "#afffd7",
    [159] = "#afffff",
    [160] = "#d70000",
    [161] = "#d7005f",
    [162] = "#d70087",
    [163] = "#d700af",
    [164] = "#d700d7",
    [165] = "#d700ff",
    [166] = "#d75f00",
    [167] = "#d75f5f",
    [168] = "#d75f87",
    [169] = "#d75faf",
    [170] = "#d75fd7",
    [171] = "#d75fff",
    [172] = "#d78700",
    [173] = "#d7875f",
    [174] = "#d78787",
    [175] = "#d787af",
    [176] = "#d787d7",
    [177] = "#d787ff",
    [178] = "#d7af00",
    [179] = "#d7af5f",
    [180] = "#d7af87",
    [181] = "#d7afaf",
    [182] = "#d7afd7",
    [183] = "#d7afff",
    [184] = "#d7d700",
    [185] = "#d7d75f",
    [186] = "#d7d787",
    [187] = "#d7d7af",
    [188] = "#d7d7d7",
    [189] = "#d7d7ff",
    [190] = "#d7ff00",
    [191] = "#d7ff5f",
    [192] = "#d7ff87",
    [193] = "#d7ffaf",
    [194] = "#d7ffd7",
    [195] = "#d7ffff",
    [196] = "#ff0000",
    [197] = "#ff005f",
    [198] = "#ff0087",
    [199] = "#ff00af",
    [200] = "#ff00d7",
    [201] = "#ff00ff",
    [202] = "#ff5f00",
    [203] = "#ff5f5f",
    [204] = "#ff5f87",
    [205] = "#ff5faf",
    [206] = "#ff5fd7",
    [207] = "#ff5fff",
    [208] = "#ff8700",
    [209] = "#ff875f",
    [210] = "#ff8787",
    [211] = "#ff87af",
    [212] = "#ff87d7",
    [213] = "#ff87ff",
    [214] = "#ffaf00",
    [215] = "#ffaf5f",
    [216] = "#ffaf87",
    [217] = "#ffafaf",
    [218] = "#ffafd7",
    [219] = "#ffafff",
    [220] = "#ffd700",
    [221] = "#ffd75f",
    [222] = "#ffd787",
    [223] = "#ffd7af",
    [224] = "#ffd7d7",
    [225] = "#ffd7ff",
    [226] = "#ffff00",
    [227] = "#ffff5f",
    [228] = "#ffff87",
    [229] = "#ffffaf",
    [230] = "#ffffd7",
    [231] = "#ffffff",
    [232] = "#080808",
    [233] = "#121212",
    [234] = "#1c1c1c",
    [235] = "#262626",
    [236] = "#303030",
    [237] = "#3a3a3a",
    [238] = "#444444",
    [239] = "#4e4e4e",
    [240] = "#585858",
    [241] = "#626262",
    [242] = "#6c6c6c",
    [243] = "#767676",
    [244] = "#808080",
    [245] = "#8a8a8a",
    [246] = "#949494",
    [247] = "#9e9e9e",
    [248] = "#a8a8a8",
    [249] = "#b2b2b2",
    [250] = "#bcbcbc",
    [251] = "#c6c6c6",
    [252] = "#d0d0d0",
    [253] = "#dadada",
    [254] = "#e4e4e4",
    [255] = "#eeeeee",
    [256] = "#101010"
};


/*
 * Default colors (colorname index)
 * foreground, background, cursor, reverse cursor
 */
unsigned int defaultfg = 15;
unsigned int defaultbg = 0;
static unsigned int defaultcs = 231;
static unsigned int defaultrcs = 2;

/*
 * Default shape of cursor
 * 2: Block ("█")
 * 4: Underline ("_")
 * 6: Bar ("|")
 * 7: Snowman ("☃")
 */
static unsigned int cursorshape = 2;

/*
 * Default columns and rows numbers
 */

static unsigned int cols = 80;
static unsigned int rows = 24;

/*
 * Default colour and shape of the mouse cursor
 */
static unsigned int mouseshape = XC_xterm;
static unsigned int mousefg = 7;
static unsigned int mousebg = 0;

/*
 * Color used to display font attributes when fontconfig selected a font which
 * doesn't match the ones requested.
 */
static unsigned int defaultattr = 11;

/*
 * Internal mouse shortcuts.
 * Beware that overloading Button1 will disable the selection.
 */
static MouseShortcut mshortcuts[] = {
    /* button               mask            string */
    // { Button4,              XK_NO_MOD,      "\031" },
    // { Button5,              XK_NO_MOD,      "\005" },
};

MouseKey mkeys[] = {
    /* button               mask            function        argument */
    { Button4,              XK_NO_MOD,      kscrollup,      {.i =  1} },
    { Button5,              XK_NO_MOD,      kscrolldown,    {.i =  1} },
    { Button4,              ShiftMask,      zoom,           {.f =  1} },
    { Button5,              ShiftMask,      zoom,           {.f = -1} },
};

/* Internal keyboard shortcuts. */
#define MODKEY Mod1Mask
#define TERMMOD (ControlMask|Mod1Mask)

static Shortcut shortcuts[] = {
    /* mask                 keysym          function        argument */
    { XK_ANY_MOD,           XK_Break,       sendbreak,      {.i =  0} },
    { ControlMask,          XK_Print,       toggleprinter,  {.i =  0} },
    { ShiftMask,            XK_Print,       printscreen,    {.i =  0} },
    { XK_ANY_MOD,           XK_Print,       printsel,       {.i =  0} },
    { ControlMask | ShiftMask, XK_J,        zoom,           {.f = +1} },
    { ControlMask | ShiftMask, XK_K,        zoom,           {.f = -1} },
    { ControlMask | ShiftMask, XK_space,    zoomreset,      {.f =  0} },
    { TERMMOD,              XK_j,           kscrolldown,    {.i =  1} },
    { TERMMOD,              XK_k,           kscrollup,      {.i =  1} },
    { ShiftMask | TERMMOD,  XK_J,           kscrolldown,    {.i =  5} },
    { ShiftMask | TERMMOD,  XK_K,           kscrollup,      {.i =  5} },
    { TERMMOD,              XK_c,           clipcopy,       {.i =  0} },
    { TERMMOD,              XK_v,           clippaste,      {.i =  0} },
    { TERMMOD,              XK_y,           selpaste,       {.i =  0} },
    { TERMMOD,              XK_Escape,      keyboard_select, { 0 }     },
    { ShiftMask,            XK_Insert,      selpaste,       {.i =  0} },
    { TERMMOD,              XK_Num_Lock,    numlock,        {.i =  0} },

 { Mod1Mask,             XK_q,           input,          {.v = "גּq"} },
 { Mod1Mask,             XK_w,           input,          {.v = "גּw"} },
 { Mod1Mask,             XK_e,           input,          {.v = "גּe"} },
 { Mod1Mask,             XK_r,           input,          {.v = "גּr"} },
 { Mod1Mask,             XK_t,           input,          {.v = "גּt"} },
 { Mod1Mask,             XK_y,           input,          {.v = "גּy"} },
 { Mod1Mask,             XK_u,           input,          {.v = "גּu"} },
 { Mod1Mask,             XK_i,           input,          {.v = "גּi"} },
 { Mod1Mask,             XK_o,           input,          {.v = "גּo"} },
 { Mod1Mask,             XK_i,           input,          {.v = "גּi"} },
 { Mod1Mask,             XK_p,           input,          {.v = "גּp"} },
 { Mod1Mask,             XK_a,           input,          {.v = "גּa"} },
 { Mod1Mask,             XK_s,           input,          {.v = "גּs"} },
 { Mod1Mask,             XK_d,           input,          {.v = "גּd"} },
 { Mod1Mask,             XK_f,           input,          {.v = "גּf"} },
 { Mod1Mask,             XK_g,           input,          {.v = "גּg"} },
 { Mod1Mask,             XK_h,           input,          {.v = "גּh"} },
 { Mod1Mask,             XK_j,           input,          {.v = "גּj"} },
 { Mod1Mask,             XK_k,           input,          {.v = "גּk"} },
 { Mod1Mask,             XK_l,           input,          {.v = "גּl"} },
 { Mod1Mask,             XK_z,           input,          {.v = "גּz"} },
 { Mod1Mask,             XK_x,           input,          {.v = "גּx"} },
 { Mod1Mask,             XK_c,           clipcopy,       {.i = 0 } },
 { Mod1Mask,             XK_v,           clippaste,      {.i = 0 } },
 { Mod1Mask,             XK_b,           input,          {.v = "גּb"} },
 { Mod1Mask,             XK_n,           input,          {.v = "גּn"} },
 { Mod1Mask,             XK_m,           input,          {.v = "גּm"} },
 { Mod1Mask,             XK_1,           input,          {.v = "גּ1"} },
 { Mod1Mask,             XK_2,           input,          {.v = "גּ2"} },
 { Mod1Mask,             XK_3,           input,          {.v = "גּ3"} },
 { Mod1Mask,             XK_4,           input,          {.v = "גּ4"} },
 { Mod1Mask,             XK_5,           input,          {.v = "גּ5"} },
 { Mod1Mask,             XK_6,           input,          {.v = "גּ6"} },
 { Mod1Mask,             XK_7,           input,          {.v = "גּ7"} },
 { Mod1Mask,             XK_8,           input,          {.v = "גּ8"} },
 { Mod1Mask,             XK_9,           input,          {.v = "גּ9"} },
 { Mod1Mask,             XK_0,           input,          {.v = "גּ0"} },
 { Mod1Mask,             XK_Q,           input,          {.v = "גּQ"} },
 { Mod1Mask,             XK_W,           input,          {.v = "גּW"} },
 { Mod1Mask,             XK_E,           input,          {.v = "גּE"} },
 { Mod1Mask,             XK_R,           input,          {.v = "גּR"} },
 { Mod1Mask,             XK_T,           input,          {.v = "גּT"} },
 { Mod1Mask,             XK_Y,           input,          {.v = "גּY"} },
 { Mod1Mask,             XK_U,           input,          {.v = "גּU"} },
 { Mod1Mask,             XK_I,           input,          {.v = "גּI"} },
 { Mod1Mask,             XK_O,           input,          {.v = "גּO"} },
 { Mod1Mask,             XK_P,           input,          {.v = "גּP"} },
 { Mod1Mask,             XK_A,           input,          {.v = "גּA"} },
 { Mod1Mask,             XK_S,           input,          {.v = "גּS"} },
 { Mod1Mask,             XK_D,           input,          {.v = "גּD"} },
 { Mod1Mask,             XK_F,           input,          {.v = "גּF"} },
 { Mod1Mask,             XK_G,           input,          {.v = "גּG"} },
 { Mod1Mask,             XK_H,           input,          {.v = "גּH"} },
 { Mod1Mask,             XK_J,           input,          {.v = "גּJ"} },
 { Mod1Mask,             XK_K,           input,          {.v = "גּK"} },
 { Mod1Mask,             XK_L,           input,          {.v = "גּL"} },
 { Mod1Mask,             XK_Z,           input,          {.v = "גּZ"} },
 { Mod1Mask,             XK_X,           input,          {.v = "גּX"} },
 { Mod1Mask,             XK_C,           input,          {.v = "גּC"} },
 { Mod1Mask,             XK_V,           input,          {.v = "גּV"} },
 { Mod1Mask,             XK_B,           input,          {.v = "גּB"} },
 { Mod1Mask,             XK_N,           input,          {.v = "גּN"} },
 { Mod1Mask,             XK_M,           input,          {.v = "גּM"} },
 { Mod1Mask,             XK_space,       input,          {.v = "גּ "} },
};

/*
 * Special keys (change & recompile st.info accordingly)
 *
 * Mask value:
 * * Use XK_ANY_MOD to match the key no matter modifiers state
 * * Use XK_NO_MOD to match the key alone (no modifiers)
 * appkey value:
 * * 0: no value
 * * > 0: keypad application mode enabled
 * *   = 2: term.numlock = 1
 * * < 0: keypad application mode disabled
 * appcursor value:
 * * 0: no value
 * * > 0: cursor application mode enabled
 * * < 0: cursor application mode disabled
 * crlf value
 * * 0: no value
 * * > 0: crlf mode is enabled
 * * < 0: crlf mode is disabled
 *
 * Be careful with the order of the definitions because st searches in
 * this table sequentially, so any XK_ANY_MOD must be in the last
 * position for a key.
 */

/*
 * If you want keys other than the X11 function keys (0xFD00 - 0xFFFF)
 * to be mapped below, add them to this array.
 */
static KeySym mappedkeys[] = { -1 };

/*
 * State bits to ignore when matching key or button events.  By default,
 * numlock (Mod2Mask) and keyboard layout (XK_SWITCH_MOD) are ignored.
 */
static uint ignoremod = Mod2Mask | XK_SWITCH_MOD;

/*
 * Override mouse-select while mask is active (when MODE_MOUSE is set).
 * Note that if you want to use ShiftMask with selmasks, set this to an other
 * modifier, set to 0 to not use it.
 */
static uint forceselmod = ShiftMask;

/*
 * This is the huge key array which defines all compatibility to the Linux
 * world. Please decide about changes wisely.
 */
static Key key[] = {
    /* keysym          mask            string     appkey appcursor */
    { XK_KP_Home,       ShiftMask,      "\033[2J",       0,   -1},
    { XK_KP_Home,       ShiftMask,      "\033[1;2H",     0,   +1},
    { XK_KP_Home,       XK_ANY_MOD,     "\033[H",        0,   -1},
    { XK_KP_Home,       XK_ANY_MOD,     "\033[1~",       0,   +1},
    { XK_KP_Up,         XK_ANY_MOD,     "\033Ox",       +1,    0},
    { XK_KP_Up,         XK_ANY_MOD,     "\033[A",        0,   -1},
    { XK_KP_Up,         XK_ANY_MOD,     "\033OA",        0,   +1},
    { XK_KP_Down,       XK_ANY_MOD,     "\033Or",       +1,    0},
    { XK_KP_Down,       XK_ANY_MOD,     "\033[B",        0,   -1},
    { XK_KP_Down,       XK_ANY_MOD,     "\033OB",        0,   +1},
    { XK_KP_Left,       XK_ANY_MOD,     "\033Ot",       +1,    0},
    { XK_KP_Left,       XK_ANY_MOD,     "\033[D",        0,   -1},
    { XK_KP_Left,       XK_ANY_MOD,     "\033OD",        0,   +1},
    { XK_KP_Right,      XK_ANY_MOD,     "\033Ov",       +1,    0},
    { XK_KP_Right,      XK_ANY_MOD,     "\033[C",        0,   -1},
    { XK_KP_Right,      XK_ANY_MOD,     "\033OC",        0,   +1},
    { XK_KP_Prior,      ShiftMask,      "\033[5;2~",     0,    0},
    { XK_KP_Prior,      XK_ANY_MOD,     "\033[5~",       0,    0},
    { XK_KP_Begin,      XK_ANY_MOD,     "\033[E",        0,    0},
    { XK_KP_End,        ControlMask,    "\033[J",       -1,    0},
    { XK_KP_End,        ControlMask,    "\033[1;5F",    +1,    0},
    { XK_KP_End,        ShiftMask,      "\033[K",       -1,    0},
    { XK_KP_End,        ShiftMask,      "\033[1;2F",    +1,    0},
    { XK_KP_End,        XK_ANY_MOD,     "\033[4~",       0,    0},
    { XK_KP_Next,       ShiftMask,      "\033[6;2~",     0,    0},
    { XK_KP_Next,       XK_ANY_MOD,     "\033[6~",       0,    0},
    { XK_KP_Insert,     ShiftMask,      "\033[2;2~",    +1,    0},
    { XK_KP_Insert,     ShiftMask,      "\033[4l",      -1,    0},
    { XK_KP_Insert,     ControlMask,    "\033[L",       -1,    0},
    { XK_KP_Insert,     ControlMask,    "\033[2;5~",    +1,    0},
    { XK_KP_Insert,     XK_ANY_MOD,     "\033[4h",      -1,    0},
    { XK_KP_Insert,     XK_ANY_MOD,     "\033[2~",      +1,    0},
    { XK_KP_Delete,     ControlMask,    "\033[M",       -1,    0},
    { XK_KP_Delete,     ControlMask,    "\033[3;5~",    +1,    0},
    { XK_KP_Delete,     ShiftMask,      "\033[2K",      -1,    0},
    { XK_KP_Delete,     ShiftMask,      "\033[3;2~",    +1,    0},
    { XK_KP_Delete,     XK_ANY_MOD,     "\033[P",       -1,    0},
    { XK_KP_Delete,     XK_ANY_MOD,     "\033[3~",      +1,    0},
    { XK_KP_Multiply,   XK_ANY_MOD,     "\033Oj",       +2,    0},
    { XK_KP_Add,        XK_ANY_MOD,     "\033Ok",       +2,    0},
    { XK_KP_Enter,      XK_ANY_MOD,     "\033OM",       +2,    0},
    { XK_KP_Enter,      XK_ANY_MOD,     "\r",           -1,    0},
    { XK_KP_Subtract,   XK_ANY_MOD,     "\033Om",       +2,    0},
    { XK_KP_Decimal,    XK_ANY_MOD,     "\033On",       +2,    0},
    { XK_KP_Divide,     XK_ANY_MOD,     "\033Oo",       +2,    0},
    { XK_KP_0,          XK_ANY_MOD,     "\033Op",       +2,    0},
    { XK_KP_1,          XK_ANY_MOD,     "\033Oq",       +2,    0},
    { XK_KP_2,          XK_ANY_MOD,     "\033Or",       +2,    0},
    { XK_KP_3,          XK_ANY_MOD,     "\033Os",       +2,    0},
    { XK_KP_4,          XK_ANY_MOD,     "\033Ot",       +2,    0},
    { XK_KP_5,          XK_ANY_MOD,     "\033Ou",       +2,    0},
    { XK_KP_6,          XK_ANY_MOD,     "\033Ov",       +2,    0},
    { XK_KP_7,          XK_ANY_MOD,     "\033Ow",       +2,    0},
    { XK_KP_8,          XK_ANY_MOD,     "\033Ox",       +2,    0},
    { XK_KP_9,          XK_ANY_MOD,     "\033Oy",       +2,    0},
    { XK_Up,            ShiftMask,      "\033[1;2A",     0,    0},
    { XK_Up,            Mod1Mask,       "\033[1;3A",     0,    0},
    { XK_Up,         ShiftMask | Mod1Mask, "\033[1;4A",     0,    0},
    { XK_Up,            ControlMask,    "\033[1;5A",     0,    0},
    { XK_Up,      ShiftMask | ControlMask, "\033[1;6A",     0,    0},
    { XK_Up,       ControlMask | Mod1Mask, "\033[1;7A",     0,    0},
    { XK_Up, ShiftMask | ControlMask | Mod1Mask, "\033[1;8A",  0,    0},
    { XK_Up,            XK_ANY_MOD,     "\033[A",        0,   -1},
    { XK_Up,            XK_ANY_MOD,     "\033OA",        0,   +1},
    { XK_Down,          ShiftMask,      "\033[1;2B",     0,    0},
    { XK_Down,          Mod1Mask,       "\033[1;3B",     0,    0},
    { XK_Down,       ShiftMask | Mod1Mask, "\033[1;4B",     0,    0},
    { XK_Down,          ControlMask,    "\033[1;5B",     0,    0},
    { XK_Down,    ShiftMask | ControlMask, "\033[1;6B",     0,    0},
    { XK_Down,     ControlMask | Mod1Mask, "\033[1;7B",     0,    0},
    { XK_Down, ShiftMask | ControlMask | Mod1Mask, "\033[1;8B", 0,    0},
    { XK_Down,          XK_ANY_MOD,     "\033[B",        0,   -1},
    { XK_Down,          XK_ANY_MOD,     "\033OB",        0,   +1},
    { XK_Left,          ShiftMask,      "\033[1;2D",     0,    0},
    { XK_Left,          Mod1Mask,       "\033[1;3D",     0,    0},
    { XK_Left,       ShiftMask | Mod1Mask, "\033[1;4D",     0,    0},
    { XK_Left,          ControlMask,    "\033[1;5D",     0,    0},
    { XK_Left,    ShiftMask | ControlMask, "\033[1;6D",     0,    0},
    { XK_Left,     ControlMask | Mod1Mask, "\033[1;7D",     0,    0},
    { XK_Left, ShiftMask | ControlMask | Mod1Mask, "\033[1;8D", 0,    0},
    { XK_Left,          XK_ANY_MOD,     "\033[D",        0,   -1},
    { XK_Left,          XK_ANY_MOD,     "\033OD",        0,   +1},
    { XK_Right,         ShiftMask,      "\033[1;2C",     0,    0},
    { XK_Right,         Mod1Mask,       "\033[1;3C",     0,    0},
    { XK_Right,      ShiftMask | Mod1Mask, "\033[1;4C",     0,    0},
    { XK_Right,         ControlMask,    "\033[1;5C",     0,    0},
    { XK_Right,   ShiftMask | ControlMask, "\033[1;6C",     0,    0},
    { XK_Right,    ControlMask | Mod1Mask, "\033[1;7C",     0,    0},
    { XK_Right, ShiftMask | ControlMask | Mod1Mask, "\033[1;8C", 0,   0},
    { XK_Right,         XK_ANY_MOD,     "\033[C",        0,   -1},
    { XK_Right,         XK_ANY_MOD,     "\033OC",        0,   +1},
    { XK_ISO_Left_Tab,  ShiftMask,      "\033[Z",        0,    0},
    { XK_Return,        Mod1Mask,       "\033\r",        0,    0},
    { XK_Return,        XK_ANY_MOD,     "\r",            0,    0},
    { XK_Insert,        ShiftMask,      "\033[4l",      -1,    0},
    { XK_Insert,        ShiftMask,      "\033[2;2~",    +1,    0},
    { XK_Insert,        ControlMask,    "\033[L",       -1,    0},
    { XK_Insert,        ControlMask,    "\033[2;5~",    +1,    0},
    { XK_Insert,        XK_ANY_MOD,     "\033[4h",      -1,    0},
    { XK_Insert,        XK_ANY_MOD,     "\033[2~",      +1,    0},
    { XK_Delete,        ControlMask,    "\033[M",       -1,    0},
    { XK_Delete,        ControlMask,    "\033[3;5~",    +1,    0},
    { XK_Delete,        ShiftMask,      "\033[2K",      -1,    0},
    { XK_Delete,        ShiftMask,      "\033[3;2~",    +1,    0},
    { XK_Delete,        XK_ANY_MOD,     "\033[P",       -1,    0},
    { XK_Delete,        XK_ANY_MOD,     "\033[3~",      +1,    0},
    { XK_BackSpace,     XK_NO_MOD,      "\177",          0,    0},
    { XK_BackSpace,     Mod1Mask,       "\033\177",      0,    0},
    { XK_Home,          ShiftMask,      "\033[2J",       0,   -1},
    { XK_Home,          ShiftMask,      "\033[1;2H",     0,   +1},
    { XK_Home,          XK_ANY_MOD,     "\033[H",        0,   -1},
    { XK_Home,          XK_ANY_MOD,     "\033[1~",       0,   +1},
    { XK_End,           ControlMask,    "\033[J",       -1,    0},
    { XK_End,           ControlMask,    "\033[1;5F",    +1,    0},
    { XK_End,           ShiftMask,      "\033[K",       -1,    0},
    { XK_End,           ShiftMask,      "\033[1;2F",    +1,    0},
    { XK_End,           XK_ANY_MOD,     "\033[4~",       0,    0},
    { XK_Prior,         ControlMask,    "\033[5;5~",     0,    0},
    { XK_Prior,         ShiftMask,      "\033[5;2~",     0,    0},
    { XK_Prior,         XK_ANY_MOD,     "\033[5~",       0,    0},
    { XK_Next,          ControlMask,    "\033[6;5~",     0,    0},
    { XK_Next,          ShiftMask,      "\033[6;2~",     0,    0},
    { XK_Next,          XK_ANY_MOD,     "\033[6~",       0,    0},
    { XK_F1,            XK_NO_MOD,      "\033OP",       0,    0},
    { XK_F1, /* F13 */  ShiftMask,      "\033[1;2P",     0,    0},
    { XK_F1, /* F25 */  ControlMask,    "\033[1;5P",     0,    0},
    { XK_F1, /* F37 */  Mod4Mask,       "\033[1;6P",     0,    0},
    { XK_F1, /* F49 */  Mod1Mask,       "\033[1;3P",     0,    0},
    { XK_F1, /* F61 */  Mod3Mask,       "\033[1;4P",     0,    0},
    { XK_F2,            XK_NO_MOD,      "\033OQ",       0,    0},
    { XK_F2, /* F14 */  ShiftMask,      "\033[1;2Q",     0,    0},
    { XK_F2, /* F26 */  ControlMask,    "\033[1;5Q",     0,    0},
    { XK_F2, /* F38 */  Mod4Mask,       "\033[1;6Q",     0,    0},
    { XK_F2, /* F50 */  Mod1Mask,       "\033[1;3Q",     0,    0},
    { XK_F2, /* F62 */  Mod3Mask,       "\033[1;4Q",     0,    0},
    { XK_F3,            XK_NO_MOD,      "\033OR",       0,    0},
    { XK_F3, /* F15 */  ShiftMask,      "\033[1;2R",     0,    0},
    { XK_F3, /* F27 */  ControlMask,    "\033[1;5R",     0,    0},
    { XK_F3, /* F39 */  Mod4Mask,       "\033[1;6R",     0,    0},
    { XK_F3, /* F51 */  Mod1Mask,       "\033[1;3R",     0,    0},
    { XK_F3, /* F63 */  Mod3Mask,       "\033[1;4R",     0,    0},
    { XK_F4,            XK_NO_MOD,      "\033OS",       0,    0},
    { XK_F4, /* F16 */  ShiftMask,      "\033[1;2S",     0,    0},
    { XK_F4, /* F28 */  ControlMask,    "\033[1;5S",     0,    0},
    { XK_F4, /* F40 */  Mod4Mask,       "\033[1;6S",     0,    0},
    { XK_F4, /* F52 */  Mod1Mask,       "\033[1;3S",     0,    0},
    { XK_F5,            XK_NO_MOD,      "\033[15~",      0,    0},
    { XK_F5, /* F17 */  ShiftMask,      "\033[15;2~",    0,    0},
    { XK_F5, /* F29 */  ControlMask,    "\033[15;5~",    0,    0},
    { XK_F5, /* F41 */  Mod4Mask,       "\033[15;6~",    0,    0},
    { XK_F5, /* F53 */  Mod1Mask,       "\033[15;3~",    0,    0},
    { XK_F6,            XK_NO_MOD,      "\033[17~",      0,    0},
    { XK_F6, /* F18 */  ShiftMask,      "\033[17;2~",    0,    0},
    { XK_F6, /* F30 */  ControlMask,    "\033[17;5~",    0,    0},
    { XK_F6, /* F42 */  Mod4Mask,       "\033[17;6~",    0,    0},
    { XK_F6, /* F54 */  Mod1Mask,       "\033[17;3~",    0,    0},
    { XK_F7,            XK_NO_MOD,      "\033[18~",      0,    0},
    { XK_F7, /* F19 */  ShiftMask,      "\033[18;2~",    0,    0},
    { XK_F7, /* F31 */  ControlMask,    "\033[18;5~",    0,    0},
    { XK_F7, /* F43 */  Mod4Mask,       "\033[18;6~",    0,    0},
    { XK_F7, /* F55 */  Mod1Mask,       "\033[18;3~",    0,    0},
    { XK_F8,            XK_NO_MOD,      "\033[19~",      0,    0},
    { XK_F8, /* F20 */  ShiftMask,      "\033[19;2~",    0,    0},
    { XK_F8, /* F32 */  ControlMask,    "\033[19;5~",    0,    0},
    { XK_F8, /* F44 */  Mod4Mask,       "\033[19;6~",    0,    0},
    { XK_F8, /* F56 */  Mod1Mask,       "\033[19;3~",    0,    0},
    { XK_F9,            XK_NO_MOD,      "\033[20~",      0,    0},
    { XK_F9, /* F21 */  ShiftMask,      "\033[20;2~",    0,    0},
    { XK_F9, /* F33 */  ControlMask,    "\033[20;5~",    0,    0},
    { XK_F9, /* F45 */  Mod4Mask,       "\033[20;6~",    0,    0},
    { XK_F9, /* F57 */  Mod1Mask,       "\033[20;3~",    0,    0},
    { XK_F10,           XK_NO_MOD,      "\033[21~",      0,    0},
    { XK_F10, /* F22 */ ShiftMask,      "\033[21;2~",    0,    0},
    { XK_F10, /* F34 */ ControlMask,    "\033[21;5~",    0,    0},
    { XK_F10, /* F46 */ Mod4Mask,       "\033[21;6~",    0,    0},
    { XK_F10, /* F58 */ Mod1Mask,       "\033[21;3~",    0,    0},
    { XK_F11,           XK_NO_MOD,      "\033[23~",      0,    0},
    { XK_F11, /* F23 */ ShiftMask,      "\033[23;2~",    0,    0},
    { XK_F11, /* F35 */ ControlMask,    "\033[23;5~",    0,    0},
    { XK_F11, /* F47 */ Mod4Mask,       "\033[23;6~",    0,    0},
    { XK_F11, /* F59 */ Mod1Mask,       "\033[23;3~",    0,    0},
    { XK_F12,           XK_NO_MOD,      "\033[24~",      0,    0},
    { XK_F12, /* F24 */ ShiftMask,      "\033[24;2~",    0,    0},
    { XK_F12, /* F36 */ ControlMask,    "\033[24;5~",    0,    0},
    { XK_F12, /* F48 */ Mod4Mask,       "\033[24;6~",    0,    0},
    { XK_F12, /* F60 */ Mod1Mask,       "\033[24;3~",    0,    0},
    { XK_F13,           XK_NO_MOD,      "\033[1;2P",     0,    0},
    { XK_F14,           XK_NO_MOD,      "\033[1;2Q",     0,    0},
    { XK_F15,           XK_NO_MOD,      "\033[1;2R",     0,    0},
    { XK_F16,           XK_NO_MOD,      "\033[1;2S",     0,    0},
    { XK_F17,           XK_NO_MOD,      "\033[15;2~",    0,    0},
    { XK_F18,           XK_NO_MOD,      "\033[17;2~",    0,    0},
    { XK_F19,           XK_NO_MOD,      "\033[18;2~",    0,    0},
    { XK_F20,           XK_NO_MOD,      "\033[19;2~",    0,    0},
    { XK_F21,           XK_NO_MOD,      "\033[20;2~",    0,    0},
    { XK_F22,           XK_NO_MOD,      "\033[21;2~",    0,    0},
    { XK_F23,           XK_NO_MOD,      "\033[23;2~",    0,    0},
    { XK_F24,           XK_NO_MOD,      "\033[24;2~",    0,    0},
    { XK_F25,           XK_NO_MOD,      "\033[1;5P",     0,    0},
    { XK_F26,           XK_NO_MOD,      "\033[1;5Q",     0,    0},
    { XK_F27,           XK_NO_MOD,      "\033[1;5R",     0,    0},
    { XK_F28,           XK_NO_MOD,      "\033[1;5S",     0,    0},
    { XK_F29,           XK_NO_MOD,      "\033[15;5~",    0,    0},
    { XK_F30,           XK_NO_MOD,      "\033[17;5~",    0,    0},
    { XK_F31,           XK_NO_MOD,      "\033[18;5~",    0,    0},
    { XK_F32,           XK_NO_MOD,      "\033[19;5~",    0,    0},
    { XK_F33,           XK_NO_MOD,      "\033[20;5~",    0,    0},
    { XK_F34,           XK_NO_MOD,      "\033[21;5~",    0,    0},
    { XK_F35,           XK_NO_MOD,      "\033[23;5~",    0,    0},
};

/*
 * Selection types' masks.
 * Use the same masks as usual.
 * Button1Mask is always unset, to make masks match between ButtonPress.
 * ButtonRelease and MotionNotify.
 * If no match is found, regular selection is used.
 */
static uint selmasks[] = {
    [SEL_RECTANGULAR] = Mod1Mask,
};

/*
 * Printable characters in ASCII, used to estimate the advance width
 * of single wide characters.
 */
static char ascii_printable[] =
    " !\"#$%&'()*+,-./0123456789:;<=>?"
    "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
    "`abcdefghijklmnopqrstuvwxyz{|}~";
