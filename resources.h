#ifdef DZEN_XRESOURCES

/* if no args is given and no resources found */
static String fallbackResources[] = {
  "*fontSet: -*-fixed-*-*-*-*-*-*-*-*-*-*-*-*",
  "*background: #111111",
  "*foreground: grey70",

  "*title.title: dzen title",
  "*title.width: 0",
  "*title.justify: center",
  /* if this default is changed, change also
     the warning about dzen.title_win.expand in main.c */
  "*title.expand-dir: center",
  "*title.y: 0",

  "*slave.title: dzen slave",
  "*slave.width: 0",
  "*slave.justify: left",
  "*slave.ismenu: False",
  "*slave.ishmenu: False",
  "*slave.x: 0",
  /*
    Xmu XtJustify are ONLY 0:left,1:center,2:right
    So another boolean resource is needed (as a temporary
    variable in _myinit struct)
  */
  "*expand: False",

  "*lines: 0",
  "*update: False",

  "*persistent: False",
  "*timeout: 0",

  "*height: 0",
  "*geometry: 0x0+0+0",

  "*dock: False",
  /*
    no defaut action_string,
    maybe event.per-{event} subresources later ?
    "*event: defaultEvent",
  */
  0
};

/*
  the last field of a XtResource is the default used
   in the case the libXt autoconversion of option value
   failed
*/
#define offset(field) XtOffsetOf(SWIN, field)
static XtResource      slaveResList[] = {
  { XtNtitle, XtCTitle, XtRString, sizeof(String),
    offset(name), XtRImmediate, NULL},
  { XtNjustify, XtCJustify, XtRJustify, sizeof(XtJustify),
    offset(alignment), XtRImmediate, (XtPointer)XtJustifyLeft},
  { XtNwidth, XtCWidth, XtRDimension, sizeof (Dimension),
    offset(width), XtRImmediate, 0},
  { "lines", "Lines", XtRInt, sizeof(int),
    offset(max_lines), XtRImmediate, 0},
  { "ismenu", "IsMenu", XtRBoolean, sizeof(Boolean),
    offset(ismenu), XtRImmediate, False},
  { "ishmenu", "IsHorizontalMenu", XtRBoolean, sizeof(Boolean),
    offset(ishmenu), XtRImmediate, False},
  { XtNx, XtCX, XtRInt, sizeof(int),
    offset(x), XtRImmediate, 0},
};
#undef offset

#define offset(field) XtOffsetOf(TWIN, field)
static XtResource      titleResList[] = {
  { XtNtitle, XtCTitle, XtRString, sizeof(String),
    offset(name), XtRImmediate, NULL},
  { XtNjustify, XtCJustify, XtRJustify, sizeof(XtJustify),
    offset(alignment), XtRImmediate, (XtPointer)XtJustifyLeft},
  { XtNwidth, XtCWidth, XtRDimension, sizeof (Dimension),
    offset(width), XtRImmediate, 0},
  { XtNy, XtCY, XtRInt, sizeof(int),
    offset(y), XtRImmediate, 0},
  { "expand-dir", "expand-dir", XtRJustify, sizeof(XtJustify),
    offset(expand), XtRImmediate, (XtPointer)XtJustifyCenter},
};
#undef offset

#define offset(field) XtOffsetOf(Dzen, field)
  static XtResource      dzenResList[] = {
  /* TODO: use XtDefaultFontSet ? */
  /* WARNING : it parse a fontSet ! not a font !
     so be sure to put at least one * (wildcard) in the fontset string
     passed to -fn or given in .Xresources */
  { XtNfontSet, XtCFontSet, XtRFontSet, sizeof(XFontSet),
    offset(font.set), XtRString, "-*-fixed-*-*-*-*-*-*-*-*-*-*-*-*"},
  { XtNforeground, XtCForeground, XtRPixel, sizeof(Pixel),
    offset(fg), XtRImmediate, XtDefaultForeground},
  { XtNbackground, XtCBackground, XtRPixel, sizeof(Pixel),
    offset(bg), XtRImmediate, XtDefaultBackground},
  { "timeout", "timeout", XtRLong, sizeof(long),
    offset(timeout), XtRImmediate, (XtPointer)0},
  { "persistent", "persistent", XtRBoolean, sizeof(Boolean),
    offset(ispersistent), XtRImmediate, (XtPointer)False},

  { "update", "Update", XtRBoolean, sizeof(Boolean),
    offset(tsupdate), XtRImmediate, False},
  { XtNheight, XtCHeight, XtRDimension, sizeof (Dimension),
    offset(line_height), XtRDimension, 0},
  { "xinescreen", "xinescreen", XtRInt, sizeof(int),
    offset(xinescreen), XtRImmediate, 0},
  };
#undef offset

#define offset(field) XtOffsetOf(_myinit, field)
static XtResource      appResList[] = {
  /* TODO: use XtRGeometry */
  { XtNgeometry, XtCGeometry, XtRString, sizeof (String),
    offset(geometry), XtRImmediate, "0x0+0+0"},
  { "dock", "Dock", XtRBoolean, sizeof(Boolean),
    offset(dock), XtRImmediate, False},
  { "event", "Event", XtRString, sizeof(String),
    offset(event), XtRString, NULL},
  { "fn-preload", "Font-Preload", XtRString, sizeof(String),
    offset(fnpre), XtRImmediate, NULL},
  /* temporary stored in the _myinit struct, then
     dzen.title_win.expand is initialised */
  { "expand", "expand", XtRBoolean, sizeof(Boolean),
    offset(expand), XtRBoolean, False},
};


static XrmOptionDescRec optionsSpec[] =
  {
    { "-fn", XtCFontSet, XrmoptionSepArg, 0 },
    { "-fg", XtCForeground, XrmoptionSepArg, 0 },
    { "-bg", XtCBackground, XrmoptionSepArg, 0 },

    /*
      too special options to be used as a XrmOptionDescRec,
      they all add a boolean meaning to their value 
      { "-p", "timeout", XrmoptionSepArg, 0 }, // ispersistent
      { "-m", "ishmenu", XrmoptionSepArg, 0 }, // ismenu
      { "-expand", "expand", XrmoptionSepArg, 0 },
    */

    { "-title-name", "title.name", XrmoptionSepArg, 0 },
    { "-ta", "title.justify", XrmoptionSepArg, 0 },
    { "-tw", "title.width", XrmoptionSepArg, 0 },
    { "-y", "title.y", XrmoptionSepArg, 0 },

    { "-slave-name", "slave.name", XrmoptionSepArg, 0 },
    { "-sa", "slave.justify", XrmoptionSepArg, 0 },
    { "-w", "slave.width", XrmoptionSepArg, 0 },
    { "-x", "slave.x", XrmoptionSepArg, 0 },


    { "-h", XtCHeight, XrmoptionSepArg, 0 },
    { "-geometry", XtCGeometry, XrmoptionSepArg, 0 },

    { "-u", "update", XrmoptionIsArg, 0 },
    { "-dock", "dock", XrmoptionIsArg, 0 },

    { "-e", "event", XrmoptionSepArg, 0 },
    { "-l", "slave.lines", XrmoptionSepArg, 0 },

    { "-fn-preload", "fn-preload", XrmoptionSepArg, 0 },
#ifdef DZEN_XINERAMA
    { "-xs", "xinescreen", XrmoptionSepArg, 0 },
#endif
  };

#endif

static char *help_list[] = {
  "[--help ]",
  "[--version ]",
  "[-p [seconds]]",
  "[-m [h[orizontal]]",
  "[-ta <l|c|r>]",
  "[-sa <l|c|r>]",
  "[-x <pixel>]",
  "[-y <pixel>]",
  "[-w <pixel>]",
  "[-h <pixel>]",
  "[-tw <pixel>]",
  "[-e <string>]",
  "[-l <lines>]",
  "[-fn <font>]",
  "[-bg <color>]",
  "[-fg <color>]",
  "[-geometry <geometry string>]",
  "[-expand <l[eft]|r[ight]|<b[oth]|c[enter]>>]",
  "[-dock]",
  "[-u]",
  "[-title-name <string>]",
  "[-slave-name <string>]",
  "[--profile <string>]",
  "[-fn-preload <string>]",
#ifdef DZEN_XINERAMA
  "[-xs <screen>]",
#endif
#ifdef DZEN_XRESOURCES
  "[-profile <classname>]",
#endif
  NULL
};
