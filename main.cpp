#include <iostream>
#include <coroutine>


struct Task{
    struct promise_type{
        void return_value(int value) {returned_value = value;}
        auto initial_suspend(){ return std::suspend_never{};}
        auto final_suspend() noexcept { return std::suspend_always{};}
        Task get_return_object(){ 
            return Task{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }
        void unhandled_exception(){ std::abort();}

        int returned_value;
    };

    std::coroutine_handle<promise_type> handle;

    ~Task(){
        std::cout<<"inside destructor of task"<<std::endl;
        if(handle){
            handle.destroy();
        }
    }


    int get_returned_value(){
        return handle.promise().returned_value;
    }
};

Task f(){
    std::cout<<"inside f"<<std::endl;
    co_return 42;
}

int main(){
    
    auto task = f();
    std::cout<<task.get_returned_value()<<std::endl;
    return 0;
}