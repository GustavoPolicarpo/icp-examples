# Shared memory Examples

## Dependencies

* C++
* Linux

### Compile

```bash
$ mkdir -p build
$ cd build
$ g++ -o shm_receiver ../shm_receiver.cpp
$ g++ -o shm_sender ../shm_sender.cpp
```

All the executable files would be generated in `build` directory.

### Run Examples

#### Receive a message

```bash
$ ./shm_receiver  # start the receiver in a terminal
Read string: "icp" and length is 3 
Read string: "testing" and length is 7
Read string: "end" and length is 3
```

#### Send a message
```bash
$ ./shm_sender  # start the sender in another terminal
Write the message ("end" to finish): icp
Sent string: "icp" and string length is 3
Write the message ("end" to finish): testing
Sent string: "testing" and string length is 7
Write the message ("end" to finish): end
Sent string: "end" and string length is 3
```

