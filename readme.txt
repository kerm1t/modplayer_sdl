10/3/2022
Dt.Einheit, Talia+Wolli


project Mod player
------------------
well, using pocketmod, which is a 1 header library.
an example with SDL2 is given


- pocketmod - https://github.com/rombankzero/pocketmod
- SDL - https://github.com/libsdl-org/SDL/releases/tag/release-2.24.0

How to build
mkdir build
cd build
cmake .. -A x64
cmake --build .

features:
- text output
- drag & drop mod files to be played

- create an SDL window, instead of the GDI
 ... this went pretty smooth, had this after a couple of minutes
 // https://stackoverflow.com/questions/49539717/how-to-render-a-point-in-sdl2
- nettes SDL drawing tut: https://thenumb.at/cpp-course/sdl2/04/04.html
- for text output I was thinking of using ttf (nice tutorial here: https://thenumb.at/cpp-course/sdl2/07/07.html), then quickly decided for a bmp-font look solution


2do:
- 4 scopes like in fasttrackerII
+ graphics output via (a) GDI or >>> (b) SDL <<<
+ drag & drop mod files onto window
- merge text.cpp and .h into single header file
- make textX2 and textX4 to output for seniors :-)
- rename text.hpp to text_sdl.hpp? or use #define to differentiate between SDL and tinyPTC :-)
- tonhoehe, um (a) boxen zu faerben (b) spectrum analyzer zu zeichnen
- play a sample, e.g. when hitting keys 1-10
- stop playback, e.g. upon LMB click
- 4 scopes: gradient bars // https://discourse.libsdl.org/t/sdl2-color-gradient/25408
- improve visualization of sample being played, i.e. use either channel or pattern? // https://wiki.multimedia.cx/index.php/Protracker_Module

problems
--------
(1) error LNK2019: unresolved external symbol SDL_main referenced in function main_getcmdline
-> int main() to int main(int argc, char **argv), i.e. add argc and argv
(2) loading file put into a function, to load when drag & drop, char* mod_data passed to the function -> Run-Time Check Failure #3 - The variable 'mod_data' is being used without being initialized -> solution: initialize mod_data : char *mod_data = NULL;
