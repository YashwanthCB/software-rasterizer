//
// Created by yashwanth on 3/18/26.
//

#include "DisplayWindow.h"
#include "TGAImage.h"

#include <X11/Xutil.h>
#include <cassert>

DisplayWindow::DisplayWindow(int width, int height):
width(width), height(height), close_message_received(false) {
    display = XOpenDisplay(nullptr);
    assert(display);

    int     screen = DefaultScreen(display);
    Window  root   = RootWindow(display, screen);
    vis    = DefaultVisual(display, screen);
    depth  = DefaultDepth(display, screen);

    XSetWindowAttributes swa{};
    swa.event_mask = ExposureMask | KeyPressMask;

    window = XCreateWindow(display, root, 0, 0, width, height, 0, depth, InputOutput, vis, CWEventMask, &swa);
    XStoreName(display, window, "TGA Viewer");
    XMapWindow(display, window);

    wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDelete, 1);

    gc = XCreateGC(display, window, 0, nullptr);
}

DisplayWindow::~DisplayWindow() {
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

void DisplayWindow::present(struct TGAImage &img) {

    std::vector<std::uint8_t> xData(width * height * 4);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            TGAColor c = img.get(x, y);
            int idx = (y * width + x) * 4;
            xData[idx + 0] = c[0];
            xData[idx + 1] = c[1];
            xData[idx + 2] = c[2];
            xData[idx + 3] = 0xFF;
        }
    }
    XImage* ximg = XCreateImage(display, vis, depth, ZPixmap, 0, reinterpret_cast<char*>(xData.data()), width, height, 32,width * 4);
    XPutImage(display, window, gc, ximg, 0, 0, 0, 0, width, height);

    ximg->data = nullptr;
    XDestroyImage(ximg);

}

void DisplayWindow::update() {
    XEvent ev;
    while (XPending(display)) {
        XNextEvent(display, &ev);
        switch (ev.type) {
            case Expose:
                printf("exposing\n");
                break;

            case KeyPress:
                //running = false;
                break;

            case ClientMessage:
                if ((Atom)ev.xclient.data.l[0] == wmDelete)
                    close_message_received = true;
                break;
        }
    }
}
