## cockroutine

- A function is `coroutine` _iff_ it has one of the following:

    __co_yield__, __co_return__ or __co_await__

- _initial_suspend_ should usually return `std::suspend_always` or `std::suspend_never`

- _final_suspend_ should almost always return `std::suspend_always`

- Task has a nested type `promise_type`

- An instance of promise_type is created for us, and is tied to the lifetime of the coroutine


## exposition only
```cpp
Task f(){
    struct CoroutineFrame{
        Task::promise_type promise;

        auto initial_block{
            co_return 42;
        }
    };

    auto frame = new CoroutineFrame();
    return frame->promise.get_return_object();
}

auto task = f();
```