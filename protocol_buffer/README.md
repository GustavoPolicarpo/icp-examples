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
Write the message ("end" to finish): icp
Write the type (must be an integer): 42
Sent string: "icp" and string length is 3 and type is 42
Write the message ("end" to finish): testing
Write the type (must be an integer): 0
Sent string: "testing" and string length is 7 and type is 0
Write the message: ("end" to finish) end
Sent string: "end" and string length is 3 and type is -1
```

#### Receive message

```bash
$ ./bin/receiver # receive a message
Received string: "icp" and string length is 3 and type is 42
Received string: "testing" and string length is 7 and type is 0
Received string: "end" and string length is 3 and type is -1
```
