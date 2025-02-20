# Exercise 7.1
See hw7-1.cpp and LockFreeStack.h for the implementation of the lock-free stack.
## Output without compare and exchange
```cpp
// NOTE THAT THIS IS BAD CODE
void
Stack::push(int val)
{
    StackItem *newItem = new StackItem(val);
    newItem->next = head.load().link;
    StackHead newHead = StackHead{newItem, head.load().count + 1};
    
    head = newHead;
}
```
```bash
nicholaslee@Nicholass-MacBook-Pro-2 build % ./hw7-1
Thread 0x700004c72000 inserting 0
Thread 0x700004c72000 inserting 1
Thread 0x700004c72000 inserting 2
Thread 0x700004e7e000 inserting 0
Thread 0x700004b6c000 inserting 0
...
Thread 0x700004c72000 got 37
hw7-1(38124,0x700004e7e000) malloc: Double free of object 0x7f8640c04100
Thread 0x700004dfb000 got 36
Thread 0x700004bef000 inserting 44
Thread 0x700004bef000 inserting 45
Thread 0x700004bef000 inserting 46
Thread 0x700004ae9000 got 34
Thread 0x700004f01000 got 43
Thread 0x700004f01000 got 45
Thread 0x700004f01000 got 0
Thread 0x700004c72000 got 0
Thread 0x700004cf5000 got 35
hw7-1(38124,0x700004e7e000) malloc: *** set a breakpoint in malloc_error_break to debug
Thread 0x700004bef000 inserting 47
Thread 0x700004cf5000 got 0
Thread 0x700004bef000 inserting 48
Thread 0x700004bef000 inserting 49
zsh: abort      ./hw7-1
```
## Output with compare and exchange
```bash
nicholaslee@Nicholass-MacBook-Pro-2 build % ./hw7-1
Thread 0x700007bcb000 inserting 0
Thread 0x700007fe3000 inserting 0
Thread 0x700007bcb000 inserting 1
Thread 0x700007fe3000 inserting 1
Thread 0x700007dd7000 inserting 0
...
Thread 0x700007c4e000 got 0
Thread 0x700007f60000 got 0
Thread 0x700007e5a000 got 1
Thread 0x700007e5a000 got 1
Thread 0x700007e5a000 got 1
Thread 0x700007e5a000 got 0
Thread 0x700008066000 got 2
Thread 0x700007e5a000 got 0
```

# Exercise 7.2
See hw7-2.cpp 

```bash
nicholaslee@Nicholass-MacBook-Pro-2 build % ./hw7-2 
async's have been deployed
I'm async: my_async printing 5
I'm async: async printing 5
```

# Exercise 7.3
See hw7-3.cpp
```bash
nicholaslee@Nicholass-MacBook-Pro-2 build % ./hw7-3
Tasks have been deployed
I'm: task printing 5
I'm: my_task printing 5
my_task returned: 10
task returned: 10
```
# Exercise 7.4
See hw7-4.cpp
```bash
nicholaslee@Nicholass-MacBook-Pro-2 build % ./hw7-4 
Waiting...I'm: a promising printing n: 5
Done!
Result is 10
```
# References
- https://stackoverflow.com/questions/18815221/what-is-decltype-and-how-is-it-used
    - Getting the return type of a function.
- https://en.cppreference.com/w/cpp/thread/packaged_task
    - Packaged task
- https://en.cppreference.com/w/cpp/thread/async
    - Async
- https://en.cppreference.com/w/cpp/thread/promise
    - Promise
- https://en.cppreference.com/w/cpp/thread/future
    - Future
- https://en.cppreference.com/w/cpp/memory/shared_ptr   
    - Shared pointer