#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <stdexcept>
using namespace std;

template<typename T>
class my_future;

template<typename T>
class my_promise{
    public:
        my_promise(){
            cv = make_shared<condition_variable>();
            m = make_shared<mutex>();
            val = make_shared<T>();
            is_set = make_shared<bool>(false);
        }
        my_future<T> get_future(){
            return my_future<T>(cv, m, val, is_set);
        }
        void set_value(T value){
            *val = value;
            *is_set = true;
            cv->notify_all();
        }
    private:
        shared_ptr<T> val;
        shared_ptr<mutex> m;
        shared_ptr<condition_variable> cv;
        shared_ptr<bool> is_set;
};

template<typename T>
class my_future {
    public:
        my_future(shared_ptr<condition_variable> &cv, shared_ptr<mutex> &m, shared_ptr<T> &val, shared_ptr<bool> &is_set){
            this->cv = cv;
            this->m = m;
            this->val = val;
            this->is_set = is_set;
        };
        T get(){
            unique_lock<mutex> lock(*m);
            cv->wait(lock, [this] {  return *is_set; });
            
            return *val;
        }
        void wait(){
            unique_lock<mutex> lock(*m);
            cv->wait(lock, [this] {  return *is_set; });
        }
    private:
        shared_ptr<T> val;
        shared_ptr<mutex> m;
        shared_ptr<condition_variable> cv;
        shared_ptr<bool> is_set;
};

void take_5_seconds_and_print_and_double_n(int n, my_promise<int> &p){
    this_thread::sleep_for(5s);
    ostringstream oss;
    oss << "I'm: a promising printing n: " << n  << "\n";
    string s = oss.str();
    cout << s;
    p.set_value(n * 2);
}

int main(){
    my_promise<int> p;
    my_future<int> ftr = p.get_future();
    thread(take_5_seconds_and_print_and_double_n, 5, ref(p)).detach();
 
    std::cout << "Waiting..." << std::flush;
    ftr.wait();
    std::cout << "Done!" << std::endl;
    std::cout << "Result is " << ftr.get() << std::endl;
    return 0;
}
/*Output
nicholaslee@Nicholass-MacBook-Pro-2 build % ./hw7-4 
Waiting...I'm: a promising printing n: 5
Done!
Result is 10
*/