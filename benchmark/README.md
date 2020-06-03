# Benchmark - IPC

Here you can find the codes used to run a benchmark for some IPC mechanism. 

For each test, a process (sender) sends a group of [1e5, 1000, 10] random messages to another process (receiver). For each message, the sender waits for feedback from the receiver, going to the next message.
