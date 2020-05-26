# Named pipe Examples

## Dependencies

* C++
* Linux

### Compile

```bash
$ mkdir -p build
$ cd build
$ g++ -o named_pipe_receiver ../named_pipe_receiver.cpp
$ g++ -o named_pipe_sender ../named_pipe_sender.cpp
```

All the executable files would be generated in `build` directory.

### Run Examples

#### Receive a message

```bash
$ ./named_pipe_receiver  # start the receiver in a terminal
Received string: "icp" and length is 3 
Received string: "testing" and length is 7
Received string: "end" and length is 3
```

#### Send a message
```bash
$ ./named_pipe_sender  # start the sender in another terminal
Write the message ("end" to finish): icp
Sent string: "icp" and string length is 3
Write the message ("end" to finish): testing
Sent string: "testing" and string length is 7
Write the message ("end" to finish): end
Sent string: "end" and string length is 3
```

