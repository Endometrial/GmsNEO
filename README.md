<!DOCTYPE html>
<html>
	<img style="float: right;" src="https://github.com/Endometrial/baphomet/blob/main/assets/images/baphomet.png">
	<h1># Baphomet</h1>
	<h3>A simple C game engine with features heavily informed by GMS2</h3>
	<h2>Depends:</h2>
	<ol>
		<li>GLFW</li>
		<li>cglm</li>
		<li>portaudio</li>
		<li>libxml2</li>
		<li>libpng</li>
		<li>libogg</li>
		<li>libvorbis</li>
	</ol>
	<body>
		<h2>Objectives:</h2>
		<ol>
			<li>Set defaults in some sort of config file or simply main.h</li>
			<li>Port to Linux, Win64, & BSD</li>
			<li>Improve styling & predicatability of function names generally </li>
			<li>Optimize typing generally</li>
			<li>Add support for converting types to the ones used ex .exr to .png</li>
			<li>Consider using a different image format than png ex bitmap </li>
			<li>Add support for loading & playing .ogg (vorbis) via portaudio</li>
			<li>Consider support for playing arbitrary audio callbacks or a set of custom callbacks </li>
				<p>ex audio_play_chip(long freq, int msecs, int type); 
with a potential note_get_freq(char* note); 
where note is "D" "A#"... and type is CHIP_SQUARE or similar</p>
			<li>Add support for loading backgrounds with rooms</li>
			<li>Add support for additions to object scripts @ runtime (ex setting x,y,z variables for room purposes) </li>
				<p>perhaps arguments could be added to the create event??? like create(int x, int y, int z, ...);
maybe a struct or similar containing everything from the room xml could be passed?
if all else fails rely on dlfcn.h
additionally an initial event could be set up by the program and appended to whatever script is used however most options feel like a bandaid to a larger issue</p>
			<li>Consider creating a gui for project management</li>
		</ol>
	</body>
</html>
