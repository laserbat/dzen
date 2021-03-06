/*
 * (C)opyright MMVI-MMVII Anselm R. Garbe <garbeam at gmail dot com>
 * (C)opyright MMVII Robert Manea <rob dot manea  at gmail dot com>
 * See LICENSE file for license details.
 *
 */

#include "dzen.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define ONEMASK ((size_t)(-1) / 0xFF)

void *
emalloc(unsigned int size) {
    void *res = malloc(size);

    if(!res)
        eprint("fatal: could not malloc() %u bytes\n", size);
    return res;
}

void
eprint(const char *errstr, ...) {
    va_list ap;

    va_start(ap, errstr);
    vfprintf(stderr, errstr, ap);
    va_end(ap);
    exit(EXIT_FAILURE);
}

char *
estrdup(const char *str) {
    void *res = strdup(str);

    if(!res)
        eprint("fatal: could not malloc() %u bytes\n", strlen(str));
    return res;
}
void
spawn(const char *arg) {
    static const char *shell = NULL;

    if(!shell && !(shell = getenv("SHELL")))
        shell = "/bin/sh";
    if(!arg)
        return;
    /* The double-fork construct avoids zombie processes and keeps the code
    * clean from stupid signal handlers. */
    if(fork() == 0) {
        if(fork() == 0) {
            setsid();
            execl(shell, shell, "-c", arg, (char *)NULL);
            fprintf(stderr, "dzen: execl '%s -c %s'", shell, arg);
            perror(" failed");
        }
        exit(0);
    }
    wait(0);
}

// convert XColor to XftColor
#ifdef DZEN_XFT
void
XColorToXRenderColor(XColor xcol, XRenderColor *rendcol) {
    rendcol->red = xcol.red;
    rendcol->green = xcol.green;
    rendcol->blue = xcol.blue;
    rendcol->alpha = 0xFFFF;
}
#endif

#ifdef DZEN_XRESOURCES
Boolean
CvtStringToXColor(Display *dpy, XrmValue *args, Cardinal *num_args, XrmValue *fromVal, XrmValue *toVal, XtPointer *converter_data ) {
    XrmValue *pixelVal = XtNew(XrmValue);
    // needed by the donestr macro of libXt
    pixelVal->size = sizeof(Pixel);
    Status st = False;
    if (XtCallConverter(dpy, XtCvtStringToPixel, args, *num_args, fromVal, pixelVal, NULL) == True)
        st = XtCallConverter(dpy, XtCvtPixelToColor, args, *num_args, pixelVal, toVal, NULL);
    XtFree((char *)pixelVal);
    return st;
}
#endif

