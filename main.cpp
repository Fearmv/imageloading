#include <iostream>
#include <fstream>
#include <stdio.h>
#include "frame.h"
#include "image.h"

typedef unsigned char byte;

using namespace std;

const double frames_per_sec = 20;
const int dur_in_sec = 5;

frame frame(720, 480);

int main() {
    // Construct the ffmpeg command to run.
    const char * cmd =
    "ffmpeg              "
    "-y                  "
    "-hide_banner        "
    "-f rawvideo         " // input to be raw video data
    "-pixel_format rgb24 "
    "-video_size 720x480 "
    "-r 60               " // frames per second
    "-i -                " // read data from the standard input stream
    "-pix_fmt yuv420p    " // to render with Quicktime
    "-vcodec mpeg4       "
    "-an                 " // no audio
    "-q:v 5              "// quality level; 1 <= q <= 32
    "output.mp4          ";
    
    // Run the ffmpeg command and get pipe to write into its standard input stream.
#ifdef _WIN32
    FILE * pipe = _popen(cmd, "wb");
#else
    FILE * pipe = popen(cmd, "w");
#endif
    if (pipe == 0) {
        cout << "error: " << strerror(errno) << endl;
        return 1;
    }
    
    //determines size of images
    Image quack;
    quack.load("ducky.bmp", 150, 150);
    Image doggo;
    doggo.load("doggo.bmp", 150, 150);
    
    int num_frames = dur_in_sec * frames_per_sec;
    int a = 0;
    int b = 0;
    int x = 100;
    int y = 100;
    for (int i = 0; i < num_frames; ++i) {
        frame.clear();
        quack.draw(a, b);
        doggo.draw(x, y);
        frame.write(pipe);
        a+=3;
        x+=2;
        y+=2;
    }
    
    fflush(pipe);
#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif
    
    cout << "num_frames: " << num_frames << endl;
    cout << "Done." << endl;
    
    return 0;
}
