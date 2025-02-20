#include "LockFreeStack.h"
#include <iostream>
#include <thread>
#include <vector>

using namespace mpcs51044;
using namespace std;
void insert_and_pop(Stack &stack, int n)
{
    auto thread_id = this_thread::get_id();
    for(int i = 0; i < n; i++) {
        ostringstream oss;
        oss << "Thread " << thread_id << " inserting " << i << "\n";
        string s = oss.str();
        cout << s;
        stack.push(i);
    }
    for(int i = 0; i < n; i++) {
        int val = stack.pop();
        ostringstream oss;
        oss << "Thread " << thread_id << " got " << val << "\n";
        string s = oss.str();
        cout << s;
    }
}

int main(){
    Stack stack;
    vector<thread> threads = vector<thread>();
    for(int i = 0; i < 10; i++) {
        threads.push_back(thread(insert_and_pop, ref(stack), 50));
    }
    for(thread &t : threads) {
        t.join();
    }
    return 0;
}
 
/* Output with compare and exchange (good) 
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

*/

/* Output without compare and exchange (bad)
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
*/