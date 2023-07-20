#ifndef BAPHOMET_INPUT_H
#define BAPHOMET_INPUT_H

/*
	Input.h
	Created: xxxx-xx-xx
	Description:
		Input.h is a catchall for input grabbing
*/


#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ctype.h>

#include <baphomet/window.h>

#define VK_UNKNOWN -1
#define VK_SPACE 32
#define VK_APOSTROPHE 39
#define VK_COMMA 44
#define VK_MINUS 45
#define VK_PERIOD 46
#define VK_SLASH 47
#define VK_0 48
#define VK_1 49
#define VK_2 50
#define VK_3 51
#define VK_4 52
#define VK_5 53
#define VK_6 54
#define VK_7 55
#define VK_8 56
#define VK_9 57
#define VK_SEMICOLON 58 
#define VK_EQUAL 61
#define VK_L_BRACKET 91
#define VK_BACKSLASH 92
#define VK_R_BRACKET 93
#define VK_GRAVE_ACCENT 96
#define VK_ESCAPE 256
#define VK_ENTER 257
#define VK_TAB 258
#define VK_BACKSPACE 259
#define VK_INSERT 260
#define VK_DELETE 261
#define VK_RIGHT 262
#define VK_LEFT 263
#define VK_DOWN 264
#define VK_UP 265
#define VK_PAGE_UP 266
#define VK_PAGE_DOWN 267
#define VK_HOME 268
#define VK_END 269
#define VK_CAPS_LOCK 280
#define VK_SCROLL_LOCK 281
#define VK_NUM_LOCK 282
#define VK_PRINT_SCREEN 283
#define VK_PAUSE 284
#define VK_F1 290
#define VK_F2 291
#define VK_F3 292
#define VK_F4 293
#define VK_F5 294
#define VK_F6 295
#define VK_F7 296
#define VK_F8 297
#define VK_F9 298
#define VK_F10 299
#define VK_F11 300
#define VK_F12 301
#define VK_F13 302
#define VK_F14 303
#define VK_F15 304
#define VK_F16 305
#define VK_F17 306
#define VK_F18 307
#define VK_F19 308
#define VK_F20 309
#define VK_F21 310
#define VK_F22 311
#define VK_F23 312
#define VK_F24 313
#define VK_F25 314
#define VK_KP_0 320
#define VK_KP_1 321
#define VK_KP_2 322
#define VK_KP_3 323
#define VK_KP_4 324
#define VK_KP_5 325
#define VK_KP_6 326
#define VK_KP_7 327
#define VK_KP_8 328
#define VK_KP_9 329
#define VK_KP_DECIMAL 330
#define VK_KP_DIVIDE 331
#define VK_KP_MULTIPLY 332
#define VK_KP_SUBTRACT 333
#define VK_KP_ADD 334
#define VK_KP_ENTER 335
#define VK_KP_EQUAL 336
#define VK_L_SHIFT 340
#define VK_L_CONTROL 341
#define VK_L_ALT 342
#define VK_L_SUPER 343
#define VK_R_SHIFT 344
#define VK_R_CONTROL 345
#define VK_R_ALT 346
#define VK_R_SUPER 347
#define VK_MENU 348

int key_press(int key);
int ord(char key);

#endif