# Pipe Examples

## Dependencies

* C++
* Linux

### Compile

```bash
$ mkdir -p build
$ cd build
$ g++ -o pipe ../pipe.cpp
```

All the executable files would be generated in `build` directory.

### Run Examples

#### Send and receive a message

```bash
$ ./pipe  # run
Write the message ("end" to finish):
icp
Written message = icp and Read message = icp 
Write the message ("end" to finish):
testing
Written message = testing and Read message = testing
Write the message ("end" to finish):
end
Written message = end and Read message = end
```

