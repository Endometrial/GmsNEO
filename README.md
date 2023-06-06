![alt text](https://github.com/Endometrial/baphomet/blob/main/assets/images/baphomet.png)
# Baphomet
A simple C game engine with features heavily informed by GMS2

Depends:
GLFW
cglm
portaudio
libxml2
libpng
libogg
libvorbis

Objectives:
* Set defaults in some sort of config file or simply main.h
* Port to Linux, Win64, & BSD
* Improve styling & predicatability of function names generally 
* Optimize typing generally
* Add support for converting types to the ones used ex .exr to .png
* Consider using a different image format than png ex bitmap 
* Add support for loading & playing .ogg (vorbis) via portaudio
* Consider support for playing arbitrary audio callbacks or a set of custom callbacks 
ex audio_play_chip(long freq, int msecs, int type); 
with a potential note_get_freq(char* note); 
where note is "D" "A#"... and type is CHIP_SQUARE or similar
* Add support for loading backgrounds with rooms
* Add support for additions to object scripts @ runtime (ex setting x,y,z variables for room purposes) 
perhaps arguments could be added to the create event??? like create(int x, int y, int z, ...);
maybe a struct or similar containing everything from the room xml could be passed?
if all else fails rely on dlfcn.h
additionally an initial event could be set up by the program and appended to whatever script is used however most options feel like a bandaid to a larger issue
* Consider creating a gui for project management
