== CutyCapt ==

CutyCapt is a small cross-platform command-line utility to capture WebKit's
rendering of a web page into a variety of vector and bitmap formats, including
SVG, PDF, PS, PNG, JPEG, TIFF, GIF, and BMP. See [IECapt][1] for a similar tool
based on Internet Explorer.

=== Note from Sam Stelfox ===

I am not the original author of CutyCapt. This distinction is reserved for
[Bjoern Hoehrmann][2], and [github][3].

This fork introduces SOCKS5 proxy support as I had need of it for a particular
project I was working on. This fork is the result of those efforts.

I particularily wanted to run this on Fedora which I couldn't find good
instructions for and thus I've also added a section in here to document how I
compiled this from source.

=== Samples ===

Here are some samples of CutyCapt generated renderings:

* [PNG Snapshot][4] of [http://digg.com][5]
* [PNG Snapshot][6] of [http://csszengarden.com/?cssfile=/209/209.css&page=0][7]
* [SVG Snapshot][8] of [http://silverlight.net][9]
* [PDF Snapshot][10] of [http://silverlight.net][9]

=== Status ===

CutyCapt has a number of known quirks, most of which are caused by problems
with Qt and/or WebKit. For example, while plugin support can be enabled, and
the plugins execute properly, their rendering cannot be captured on some
platforms. Use of with caution.

=== Requirements ===

CutyCapt depends on [Qt 4.4.0+][11].

=== Download ===

A linux binary of this file will be made available for 64 bit platforms when I
get compilation working.

=== Usage ===

Open a command prompt and ask for help:

>  % CutyCapt --help
>  -----------------------------------------------------------------------------
>  Usage: CutyCapt --url=http://www.example.org/ --out=localfile.png
>  -----------------------------------------------------------------------------
>   --help                         Print this help page and exit
>   --url=<url>                    The URL to capture (http:...|file:...|...)
>   --out=<path>                   The target file (.png|pdf|ps|svg|jpeg|...)
>   --out-format=<f>               Like extension in --out, overrides heuristic
>   --min-width=<int>              Minimal width for the image (default: 800)
>   --min-height=<int>             Minimal height for the image (default: 600)
>   --max-wait=<ms>                Don't wait more than (default: 90000, inf: 0)
>   --delay=<ms>                   After successful load, wait (default: 0)
>   --user-styles=<url>            Location of user style sheet, if any
>   --header=<name>:<value>        request header; repeatable; some can't be set
>   --method=<get|post|put>        Specifies the request method (default: get)
>   --body-string=<string>         Unencoded request body (default: none)
>   --body-base64=<base64>         Base64-encoded request body (default: none)
>   --app-name=<name>              appName used in User-Agent; default is none
>   --app-version=<version>        appVers used in User-Agent; default is none
>   --user-agent=<string>          Override the User-Agent header Qt would set
>   --javascript=<on|off>          JavaScript execution (default: on)
>   --java=<on|off>                Java execution (default: unknown)
>   --plugins=<on|off>             Plugin execution (default: unknown)
>   --private-browsing=<on|off>    Private browsing (default: unknown)
>   --auto-load-images=<on|off>    Automatic image loading (default: on)
>   --js-can-open-windows=<on|off> Script can open windows? (default: unknown)
>   --js-can-access-clipboard=<on|off> Script clipboard privs (default: unknown)
>   --print-backgrounds=<on|off>   Backgrounds in PDF/PS output (default: off)
>  -----------------------------------------------------------------------------
>   <f> is svg,ps,pdf,itext,html,rtree,png,jpeg,mng,tiff,gif,bmp,ppm,xbm,xpm
>  -----------------------------------------------------------------------------
>  http://cutycapt.sf.net - (c) 2003-2010 Bjoern Hoehrmann - bjoern@hoehrmann.de

=== Using CutyCapt without an X server ===

You cannot use CutyCapt without an X server, but you can use e.g. Xvfb as
light-weight server if you are not running an interactive graphical desktop
environment. For example, you could use:

```
$ xvfb-run --server-args="-screen 0, 1024x768x24" ./CutyCapt --url=http://www.example.org --out=example.png
```

=== Compilation in Fedora ===

```
yum install qt-devel qtwebkit-devel -y
/usr/lib64/qt4/bin/qmake
make
```

Currently I'm getting the following error when I try to compile (unrelated to my changes):

> g++ -c -pipe -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fstack-protector --param=ssp-buffer-size=4 -m64 -mtune=generic -O2 -D_REENTRANT -Wall -W -DQT_NO_DEBUG -DQT_WEBKIT_LIB -DQT_SVG_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED -I/usr/lib64/qt4/mkspecs/linux-g++ -I. -I/usr/include/QtCore -I/usr/include/QtNetwork -I/usr/include/QtGui -I/usr/include/QtSvg -I/usr/include/QtWebKit -I/usr/include -I. -o CutyCapt.o CutyCapt.cpp
> CutyCapt.cpp: In member function ‘void CutyCapt::handleSslErrors(QNetworkReply*, QList<QSslError>)’:
> CutyCapt.cpp:243:10: error: invalid use of incomplete type ‘class QNetworkReply’
> In file included from /usr/include/QtWebKit/qgraphicswebview.h:24:0,
>                  from /usr/include/QtWebKit/QtWebKit:3,
>                  from CutyCapt.cpp:27:
> /usr/include/QtWebKit/qwebpage.h:40:7: error: forward declaration of ‘class QNetworkReply’
> CutyCapt.cpp: At global scope:
> CutyCapt.cpp:241:1: warning: unused parameter ‘errors’ [-Wunused-parameter]
> CutyCapt.cpp: In member function ‘void CutyCapt::saveSnapshot()’:
> CutyCapt.cpp:270:10: warning: enumeration value ‘InnerTextFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:270:10: warning: enumeration value ‘HtmlFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:270:10: warning: enumeration value ‘PngFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:270:10: warning: enumeration value ‘JpegFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:270:10: warning: enumeration value ‘MngFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:270:10: warning: enumeration value ‘TiffFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:270:10: warning: enumeration value ‘GifFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:270:10: warning: enumeration value ‘BmpFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:270:10: warning: enumeration value ‘PpmFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:270:10: warning: enumeration value ‘XbmFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:270:10: warning: enumeration value ‘XpmFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:270:10: warning: enumeration value ‘OtherFormat’ not handled in switch [-Wswitch]
> CutyCapt.cpp:299:5: error: case label ‘(CutyCapt::OutputFormat)3u’ not within a switch statement
> CutyCapt.cpp:300:5: error: case label ‘(CutyCapt::OutputFormat)4u’ not within a switch statement
> CutyCapt.cpp:308:7: error: break statement not within loop or switch
> CutyCapt.cpp:310:5: error: case label not within a switch statement
> CutyCapt.cpp: At global scope:
> CutyCapt.cpp:319:1: error: expected declaration before ‘}’ token
> make: *** [CutyCapt.o] Error 1

[1]: http://iecapt.sourceforge.net/
[2]: mailto:bjoern@hoehrmann.de
[3]: https://github.com/hoehrmann
[4]: http://cutycapt.sourceforge.net/digg.png
[5]: http://digg.com
[6]: http://cutycapt.sourceforge.net/css-co-ltd.png
[7]: http://csszengarden.com/?cssfile=/209/209.css&page=0
[8]: http://cutycapt.sourceforge.net/silverlight.net.svgz
[9]: http://silverlight.net
[10]: http://cutycapt.sourceforge.net/silverlight.net.pdf
[11]: http://qt-project.org/
