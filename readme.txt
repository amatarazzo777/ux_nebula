



T
 @note: on linux, xcb the following dependencies are needed. These require
 administrator privilege and use the 'sudo' on ubuntu style.
 
  # apt-get install libx11-dev libxcb-keysyms1-dev libx11-xcb-dev
 
  documentation:

 
 currently this is the only one implemented.

pkg-config --cflags X11 X11-xcb xcb xcb-image xcb-keysyms xcb-shm
	
pkg-config --libs xcb-image xcb-keysyms xcb-shm
		


X11
X11-xcb
xcb
xcb-image
xcb-keysyms
xcb-shm




