**Table of Content**

1. TOC
{:toc}

## Information

## How to build waltham-transmitter-plugin

1. Go to AGL build folder and configure your environment. Add
'agl-weston-waltham-remoting' as distro feature.

```
       $ cd $AGL_TOP
       $ source meta-agl/scripts/aglsetup.sh -f -b ${MACHINE_TYPE} [additional_distro_features] agl-weston-waltham-remoting
```

2. Build agl-demo-platform by using bitbake.

3. Clone/download the waltham-transmitter-plugin on your own and build
locally using the build system provided. See README.md file for more
information.

## How to configure weston.ini and GStreamer pipeline

### weston.ini

Add output name, host IP address, port number, and mode key under
'[transmitter-output]' section. 
You can speficy multiple [transmitter-output] with different output-name.

```
/* Example_weston.ini - single transmitter-output */
	[transmitter-output]
	name=transmitter-1
	mode=640x720@30
	host=192.168.20.99
	port=5005
	agl-shell-app-id=<APP_ID>
```

### GStreamer pipeline

You can use GStreamer pipeline as you want. Here are some examples.

```

/* General pipeline which does not use any HW encoder */
	appsrc name=src ! videoconvert ! video/x-raw,format=I420 ! jpegenc ! \
		rtpjpegpay ! udpsink name=sink host=YOUR_RECIEVER_IP \
		port=YOUR_RECIEVER_PORT sync=false async=false

/* pipeline to use Intel's HW encoder */
	appsrc name=src ! videoconvert ! video/x-raw,format=I420 ! \
			mfxh264enc bitrate=3000000 rate-control=1 ! rtph264pay config-interval=1 ! \
			udpsink name=sink host=YOUR_RECIEVER_IP port=YOUR_RECIEVER_PORT \
			sync=false async=false

/* pipeline to use Rcar's HW encoder */
	appsrc name=src ! videoconvert ! video/x-raw,format=I420 ! \
				omxh264enc bitrate=3000000 control-rate=2 ! rtph264pay ! \
				udpsink name=sink host=YOUR_RECIEVER_IP port=YOUR_RECIEVER_PORT \
				sync=false async=false

```

## Connection Establishment

1. Connect two boards over ethernet.
2. Assign IP to both boards.
```Example:
	transmitter IP: 192.168.2.51
	waltham-receiver IP: 192.168.2.52
```
3. Check if the simple ping works
```
        $ ping 192.168.2.52 (you can also ping vice versa)
```

## Typical issues & Tips

### help functions
You can find the help information of LayerManagerControl command by using

```
$ LayerManagerControl help
```

### waltham-transmitter and waltham-receiver doesn't not communicate

1. Please check ethernet connection. If you assign 192.168.2.51 and
   192.168.2.52 for waltham-transmitter and waltham-receiver, you shall ping
   vice versa.

```
/* At waltham-transmitter side */
	$ ping 192.168.2.52

/* At waltham-receiver side */
	$ ping 192.168.2.51
```

2. Make sure that IP address specified in the weston.ini under
   [transmitter-output] matches the waltham-receiver IP address.

3. Make sure that IP address in pipeline.cfg on the transmitter side match the
   waltham-receiver's IP address.

