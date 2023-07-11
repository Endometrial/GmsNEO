<!DOCTYPE html>
<html>
	<div>
		<img align="right" src="https://github.com/Endometrial/baphomet/blob/main/assets/images/baphomet.png">
		<h1>Baphomet</h1>
		<h3>A simple C game engine with features heavily informed by GMS2</h3>
	</div>
	<h2>Depends:</h2>
	<ul>
		<li>GLFW</li>
		<li>cglm</li>
		<li>portaudio</li>
		<li>libxml2</li>
		<li>libpng</li>
		<li>libogg</li>
		<li>libvorbis</li>
	</ul>
	<body>
		<h2>Objectives:</h2>
		<ul>
			<li>Impliment a basic synth for sound effects and things</li>
			<li>Add support extended room features</li>
			<li>Add support for additions to object scripts @ runtime (ex setting x,y,z variables for room purposes) </li>
				<p>	perhaps arguments could be added to the create event??? like create(int x, int y, int z, ...);
					maybe a struct or similar containing everything from the room xml could be passed?
					if all else fails rely on dlfcn.h
					additionally an initial event could be set up by the program and appended to whatever script is used however most options feel like a bandaid to a larger issue</p>
			<li>Consider creating a gui for project management</li>
			<li>Assure the final packet of ogg files is actually used b/c it currently isnt ;w;</li>
			<li>Figure out how too ignore video and other non vorbis streams in ogg files</li>
		</ul>
	</body>
</html>
