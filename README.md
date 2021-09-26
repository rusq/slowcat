# slowcat.c - slow down the display of a file
```
copyright (c) 2001,2002,2007  dave w capella   All Rights Reserved

distributed under the terms of the GNU Public license

There is NO WARRANTY, and NO SUPPORT WHATSOEVER.

building: make slowcat && mv slowcat $HOME/bin
(assuming that you have a personal bin directory)

usage: slowcat [-d usecs] filename
where usecs is the number of micro-seconds to delay.

feedback welcome. enjoy!
...dave


09/24/07 - modifications to include nanosleep, brian at landsberger.com
09/26/21 - include string.h and usage function, support for Darwin. github:rusq
```
