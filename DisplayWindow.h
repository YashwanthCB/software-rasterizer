//
// Created by yashwanth on 3/18/26.
//

#pragma once

#include <X11/Xlib.h>
#include <vector>
#include <cstdint>


class DisplayWindow {
public:
    DisplayWindow(int width, int height);
    ~DisplayWindow();
    void present(struct TGAImage& img);
    void update();
    bool should_close(){return close_message_received;}

private:
    Display* display;
    Window window;
    GC gc;
    Atom wmDelete;
    int width, height;
    Visual* vis;
    int depth;
    bool close_message_received;
    std::vector<std::uint8_t> xData;
};

