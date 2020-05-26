# Shared memory Examples

## Dependencies

* C++
* Linux

### Compile

```bash
$ mkdir -p build
$ cd build
$ g++ -o queue_sender ../queue_sender.cpp
$ g++ -o queue_receiver_1 ../queue_receiver_1.cpp
$ g++ -o queue_receiver_2 ../queue_receiver_2.cpp
```

All the executable files would be generated in `build` directory.

### Run Examples

#### Send a message
```bash
$ ./queue_sender  # start the sender in a terminal
Write the message ("end" to finish): icp
Write the type (must be an integer [1 or 2]): 1
Sent string: "icp" and string length is 3 and type is 1
Write the message ("end" to finish): testing
Write the type (must be an integer [1 or 2]): 2
Sent string: "testing" and string length is 7 and type is 2
Write the message ("end" to finish): end
Sent string: "end" and string length is 3 and type is 1
Sent string: "end" and string length is 3 and type is 2
```

#### Receive a message in receiver 1

```bash
$ ./queue_receiver_1  # start the receiver in a second terminal
Received string: "icp" and string length is 3 and type is 1
Received string: "end" and string length is 3 and type is 1
```

#### Receive a message in receiver 2

```bash
$ ./queue_receiver_2  # start the receiver in a third terminal
Received string: "testing" and string length is 7 and type is 2
Received string: "end" and string length is 3 and type is 1
```



