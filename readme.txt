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

- create an SDL window, instead of the GDI
 ... this went pretty smooth, had this after a couple of minutes
 // https://stackoverflow.com/questions/49539717/how-to-render-a-point-in-sdl2
- nettes SDL drawing tut: https://thenumb.at/cpp-course/sdl2/04/04.html


2do:
- 4 scopes like in fasttrackerII
+ graphics output via (a) GDI or >>> (b) SDL <<<
- drag & drop mod files onto window
- merge text.cpp and .h into single header file
- make textX2 and textX4 to output for seniors :-)
- rename text.hpp to text_sdl.hpp? or use #define to differentiate between SDL and tinyPTC :-)
- tonhoehe, um (a) boxen zu faerben (b) spectrum analyzer zu zeichnen
- play a sample, e.g. when hitting keys 1-10
- stop playback, e.g. upon LMB click

problems
--------
(1) error LNK2019: unresolved external symbol SDL_main referenced in function main_getcmdline
-> int main() to int main(int argc, char **argv), i.e. add argc and argv
