# protocol-ezmq-plus-cpp

protocol-ezmq-plus-cpp is a library which provides a messaging interface with AutomationML(AML) data model.

## Prerequisites ##
 - You must install basic prerequisites for build
   - Make sure that libtool, pkg-config, build-essential, autoconf, and automake are installed.
   ```
   $ sudo apt-get install libtool pkg-config build-essential autoconf automake
   ```

- Python
  - Version : 2.4 to 3.0
  - [How to install](https://wiki.python.org/moin/BeginnersGuide/Download)

- SCons
  - Version : 2.3.0 or above
  - [How to install](http://scons.org/doc/2.3.0/HTML/scons-user/c95.html)

## How to build ##
1. Goto: ~/protocol-ezmq-plus-cpp/</br>
2. Following are the scripts for building ezmq plus library:</br>
   **(a) build.sh**      : Native build for x86_64</br>
   **(b) build_arm.sh**  : Native build for armhf [Raspberry pi board]</br>

**Notes** </br>
(a) For getting help about script [ build.sh ] : **$ ./build.sh --help** </br>
(b) For getting help about script [ build_arm.sh ] : **$ ./build_arm.sh --help** </br>

**Example**
```
Usage: ./build.sh <option>
Options:
  --with_dependencies=(default: false)                               :  Build with dependencies
  --build_mode=[release|debug](default: release)                     :  Build ezmq plus library and samples in release or debug mode
  -h / --help                                                        :  Display help and exit
Examples:
build:-
  $ ./build.sh
  $ ./build.sh --with_dependencies=true
  $ ./build.sh --with_dependencies=false --build_mode=release
  $ ./build.sh --with_dependencies=false --build_mode=debug
help:-
  $ ./build.sh -h
```

## How to run ##

### Prerequisites ###
 Built ezmq plus library

### Publisher sample ###
1. Goto: ~/protocol-ezmq-plus-cpp/out/linux/{ARCH}/{MODE}/samples/
2. export LD_LIBRARY_PATH=../
3. Run the sample:
    ```
     ./publisher
    ```
    - **It will give list of options for running the sample.** </br>

### Subscriber sample ###
1. Goto: ~/protocol-ezmq-plus-cpp/out/linux/{ARCH}/{MODE}/samples/
2. export LD_LIBRARY_PATH=../
3. Run the sample:
    ```
     ./AmlSubscriber
     ./XmlSubscriber
    ```
    - **It will give list of options for running the sample.** </br>

### Discovery sample ###
1. Goto: ~/protocol-ezmq-plus-cpp/out/linux/{ARCH}/{MODE}/samples/
2. export LD_LIBRARY_PATH=../
3. Run the sample:
    ```
     ./TopicDiscovery
    ```
    - **It will give list of options for running the sample.** </br>

## Docker Build sample ##
1. Reference [Dockerfile_arm](Dockerfile_arm) on repository.

## Usage guide for ezmq library (for microservices)

1. The microservice which wants to use ezmq plus APIs has to link following libraries:</br></br>
   **(A) If microservice wants to link ezmq plus dynamically following are the libraries it needs to link:**</br>
        - libezmq_plus.so</br>
        - libezmq.so</br>
        - libaml.so</br>
        - libcurl.so</br>
        - libjsoncpp.so</br>
        - libprotobuf.so</br>
        - libzmq.so </br>
   **(B) If microservice wants to link ezmq plus statically following are the libraries it needs to link:**</br>
        - libezmq_plus.a</br>
        - libezmq.a</br>
        - libaml.a</br>
        - libcurl.a</br>
        - libjsoncpp.a</br>
        - libprotobuf.a</br>
        - libzmq.a </br>
2. Reference ezmq plus library APIs : [doc/doxygen/docs/html/index.html](doc/doxygen/docs/html/index.html)
