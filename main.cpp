#include <iostream>
#include <coroutine>


struct Task{
    struct promise_type{
        void return_void() {}
        auto initial_suspend(){ return std::suspend_never{};}
        auto final_suspend() noexcept { return std::suspend_always{};}
        Task get_return_object(){ return Task();}
        void unhandled_exception(){ std::abort();}
    };
};

Task f(){
    co_return;
}

int main(){

    f();
    return 0;
}