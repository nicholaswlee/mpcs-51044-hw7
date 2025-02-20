#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std; 

template<typename Func, typename ...Args>
auto my_async(Func f, Args... args) {
    packaged_task<decltype(f(args...))(Args...)> task(f);
    future<decltype(f(args...))> task_result = task.get_future();
    thread t(std::move(task), args...);
    t.detach();
    return task_result;
}

void take_5_seconds_and_print_n(int n, string which_async){
    this_thread::sleep_for(5s);
    cout << "I'm async: "<< which_async << " printing " << n << endl;
}

int main() {
    auto f_myasync = my_async(take_5_seconds_and_print_n, 5, "my_async");
    auto f_async = async(take_5_seconds_and_print_n, 5, "async");
    cout << "async's have been deployed" << endl;
    f_myasync.get();
    f_async.get();
    return 0;
}
/* Output
nicholaslee@Nicholass-MacBook-Pro-2 build % ./hw7-2 
async's have been deployed
I'm async: my_async printing 5
I'm async: async printing 5
*/