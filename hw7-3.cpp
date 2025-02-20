#include <future>
#include <iostream>

using namespace std; 
template<class R>
class my_packaged_task;

template<class R, class ...ArgTypes>
class my_packaged_task <R(ArgTypes...)> {
    public:
        my_packaged_task(R(*task_function)(ArgTypes...)){
            p = promise<R>();
            func = task_function;
        }
        
        future<R> get_future(){
            return p.get_future();
        }
        void operator()(ArgTypes... args){
            p.set_value(func(args...));
        }
    private:
        promise<R> p;
        R(*func)(ArgTypes...);
};

int take_5_seconds_and_print_and_double_n(int n, string which_task){
    this_thread::sleep_for(5s);
    ostringstream oss;
    oss << "I'm: " << which_task << " printing " << n  << "\n";
    string s = oss.str();
    cout << s;
    return n * 2;
}

int main() {
    my_packaged_task<int(int, string)> my_task(take_5_seconds_and_print_and_double_n);
    packaged_task<int(int, string)> task(take_5_seconds_and_print_and_double_n);
    
    future<int> my_future = my_task.get_future();
    future<int> future = task.get_future();
    thread my_task_thread(std::move(my_task), 5, "my_task");
    thread task_td(std::move(task), 5, "task");

    cout << "Tasks have been deployed" << endl;
    my_task_thread.join();
    task_td.join();

    cout << "my_task returned: " << my_future.get() << endl;
    cout << "task returned: " << future.get() << endl;
    return 0;
}
/* Output
nicholaslee@Nicholass-MacBook-Pro-2 build % ./hw7-3
Tasks have been deployed
I'm: task printing 5
I'm: my_task printing 5
my_task returned: 10
task returned: 10
*/