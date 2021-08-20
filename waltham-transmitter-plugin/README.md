# Waltham Transmitter #

Waltham transmitter is a weston plugin which uses waltham IPC library to
connect to remote and transmit input events from the remote client back
to the compositor.

Transmitter plugin provides the API to create remote connections and push
surfaces over the network and handles remote input. The remote output creation
and handling is being done by the remoting plug-in.


### Architecture

````
				ECU 1                                                                     ECU 2
              +-----------------------------------------------------+                    +----------------------------------------------+
              |        +-----------------+                          |                    |                                              |
              |        | IVI-Application |                          |                    |               +-----------+-----------+      |
              |        +-----------------+                          |                    |               | Gstreamer |           |      |
              |                 ^                                   |    Buffer   -----------------------> (Decode)  |           |      |
              |        wayland  |                         +----------------------/       |               +-----------+           |      |
              |                 v                         |         |    (Ethernet)      |               |     Waltham-receiver  |      |
              |   +----+---------------------+            |         |        ---------------------------->                       |      |
              |   |    |  Transmitter Plugin |<-----------------------------/            |               +-----------------------+      |
              |   |    |                     |            |         |  Waltham-Protocol  |                             ^                |
              |   |    |---------------------+            |         |                    |                     wayland |                |
              |   |    |  Remoting plug-in   |------------+         |                    |                             v                |
              |   |    |                     |                      |                    |                 +---------------------+      |
              |   |    +-+-------------------+                      |                    |                 |                     |      |
              |   |                          |                      |                    |                 |       compositor    |      |
              |   |        compositor        |                      |                    |                 |                     |      |
              |   +------+-------------------+                      |                    |                 +----------------+----+      |
              |          |                                          |                    |                                  |           |
              |          v                                          |                    |                                  v           |
              |   +------------+                                    |                    |                            +----------+      |
              |   |  Display   |                                    |                    |                            |  Display |      |
              |   |            |                                    |                    |                            |          |      |
              |   +------------+                                    |                    |                            +----------+      |
              +-----------------------------------------------------+                    +----------------------------------------------+

````

### How to build

1. Prerequisite before building

	weston, wayland, gstreamer plugins and waltham should be built and
	available.

2. Get the source code from the repository.

	$ git clone https://gerrit.automotivelinux.org/gerrit/src/waltham-transmitter

3. Create build folder

	$ cd waltham-transmitter
	$ meson -Dprefix=$PREFIX_PATH build/

4. Run ninja

	$ ninja -C build/ install

5. waltham-transmitter.so should be available in the
   $PREFIX_PATH/lib/x86_64-linux-gnu/libweston-$MAJOR

### How to configure the compositor and gstreamer pipeline

1. weston.ini:

The transmitter plugin will be loaded automatically is found in the plug-ins 
directory of weston.

The destination of remoting output is configured in weston.ini and it matches
the key entries from the remoting plug-in -- the output being actually created
by the remoting plug-in.  Add output name, server address, mode ini entries
under '[transmitter-output]'. You can specify multiple [transmitter-output].

You can specify which application to be started/placed on the remote output
by adding agl-shell-app-id=app_id_name.

2. gstreamer pipeline:

You can customize the gstreamer pipeline as you want by configuring the
pipeline entry.

Some pipeline gstreamer examples are in the following files:

- pipeline_example_general.cfg : Does not use any HW encoder.
- pipeline_example_intel.cfg   : Use Intel's HW encoder.
- pipeline_example_rcar.cfg    : Use Rcar's HW encoder.

### Connection Establishment

1. Connect two board over ethernet.

2. Assign IP to both the boards and check if the simple ping works.

	For example: if transmitter IP: 192.168.2.51 and Waltham-Receiver IP:
	192.168.2.52 then

    $ ping 192.168.2.52 (you can also ping vice versa)

3. Make sure that IP address specified in the weston.ini under
   [transmitter-output] matches the Waltham-Receiver IP. The section is
   identical to that of the remoting plug-in, only the name of the section is
   different.

### How to test

Start the compositor with modified weston.ini mention above.  You can confirm
the transmitter is loaded properly from weston log as below.

````
[07:14:23.032] Transmitter weston_seat 0xaaaad0079e50
[07:14:23.032] Transmitter created pointer=0xaaaad00977c0 for seat 0xaaaad0079e50
[07:14:23.032] Transmitter created keyboard=0xaaaad0079fe0 for seat 0xaaaad0079e50
[07:14:23.032] Transmitter created touch=0xaaaacffe1010 for seat 0xaaaad0079e50
````

Start remoting:

- Start the remote compositor and start the receiver application.
- Start the compositor on the transmitter side and the application mentioned in
'[transmitter-output]' section, under agl-shell-app-id in order to 'forward'
the application to that output.
