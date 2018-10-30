# CLort

An experimental prototype of Snort++ that offloads pattern matching to the GPU.
Designed with Odroid devides as the main targets in mind, that support OpenCL 1.2
Based on https://github.com/snort3/snort3

# LIMITATIONS
In its current version, CLort does not evaluate rule options after a match is found in the fast-pattern matching engine. Thus, it will not properly report packets that match the full rules. Instead, it only reports the total number of matches reported by the fast-pattern matching engine.


# DEPENDENCIES

* OpenCL 1.2
* autotools or cmake to build from source
* daq from http://www.snort.org for packet IO
* dnet from https://github.com/dugsong/libdnet.git for network utility functions
* g++ >= 4.8 or other C++11 compiler
* hwloc from https://www.open-mpi.org/projects/hwloc/ for CPU affinity management
* LuaJIT from http://luajit.org for configuration and scripting
* OpenSSL from https://www.openssl.org/source/ for SHA and MD5 file signatures,
  the protected_content rule option, and SSL service detection
* pcap from http://www.tcpdump.org for tcpdump style logging
* pcre from http://www.pcre.org for regular expression pattern matching
* pkgconfig from https://www.freedesktop.org/wiki/Software/pkg-config/ to locate build dependencies
* zlib from http://www.zlib.net for decompression



# BUILD SNORT 

(mostly taken from Snort++)

Follow these steps:

1.  Make sure src/search_engines/acsmx2.cc:1163 points to the correct path for findMatches.cl 
   
1.  Setup install path:

    ```shell
    export my_path=/path/to/snorty
    ```

1.  Compile and install:

    
  * To build with cmake and make, run configure_cmake.sh.  It will automatically create and populate a new subdirectory named 'build'.

    ```shell
    ./configure_cmake.sh --prefix=$my_path
    cd build
    make -j 8 install
    ```

# RUN SNORT

(taken from Snort++)

First set up the environment:

```shell
export LUA_PATH=$my_path/include/snort/lua/\?.lua\;\;
export SNORT_LUA_PATH=$my_path/etc/snort
```

Then give it a go:

* Snort++ provides lots of help from the command line.  Here are some examples:

    ```shell
    $my_path/bin/snort --help
    $my_path/bin/snort --help-module suppress
    $my_path/bin/snort --help-config | grep thread
    ```

* Examine and dump a pcap.  In the following, replace a.pcap with your
  favorite:

    ```shell
    $my_path/bin/snort -r a.pcap
    $my_path/bin/snort -L dump -d -e -q -r a.pcap
    ```

* Verify a config, with or w/o rules:

    ```shell
    $my_path/bin/snort -c $my_path/etc/snort/snort.lua
    $my_path/bin/snort -c $my_path/etc/snort/snort.lua -R $my_path/etc/snort/sample.rules
    ```

* Run IDS mode.  In the following, replace pcaps/ with a path to a directory
  with one or more *.pcap files:

    ```shell
    $my_path/bin/snort -c $my_path/etc/snort/snort.lua -R $my_path/etc/snort/sample.rules \
        -r a.pcap -A alert_test -n 100000
    ```

* Let's suppress 1:2123.  We could edit the conf or just do this:

    ```shell
    $my_path/bin/snort -c $my_path/etc/snort/snort.lua -R $my_path/etc/snort/sample.rules \
        -r a.pcap -A alert_test -n 100000 --lua "suppress = { { gid = 1, sid = 2123 } }"
    ```

* Go whole hog on a directory with multiple packet threads:

    ```shell
    $my_path/bin/snort -c $my_path/etc/snort/snort.lua -R $my_path/etc/snort/sample.rules \
        --pcap-filter \*.pcap --pcap-dir pcaps/ -A alert_fast --max-packet-threads 8
    ```


