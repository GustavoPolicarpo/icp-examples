# Protocol Buffer Examples

## Dependencies

* Google Protocol Buffers 3.8.0
* CMake 3.14.4+

### Compile

```bash
$ mkdir -p build
$ cd build
$ cmake ..
$ make
```

All the executable files would be generated in `build/bin` directory.

### Run Examples

#### Send message

```bash
$ ./bin/sender  # send a message
Write the message: ("end" to finish)
icp
Write the type: (must be an integer) 
42
Write the message: ("end" to finish)
testing
Write the type: (must be an integer) 
0
Write the message: ("end" to finish)
end
```

#### List People

```bash
$ ./bin/receiver # receive a message
Received string: "icp" and string length is 3 and your type is 42
Received string: "testing" and string length is 7 and your type is 0
Received string: "end" and string length is 3 and your type is -1
```
