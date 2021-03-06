//
// Copyright (C) 2019 Rian Quinn <user@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// -----------------------------------------------------------------------------
#ifdef EXAMPLE01

#include <thread>
#include <iostream>
#include <future>

void foo(std::promise<int> promise)
{
    promise.set_value(42);
}

int main(void)
{
    std::promise<int> promise;
    auto future = promise.get_future();

    std::thread t{foo, std::move(promise)};
    t.join();

    std::cout << "The answer is: " << future.get() << '\n';

    return 0;
}

// The answer is: 42

#endif

// -----------------------------------------------------------------------------
#ifdef EXAMPLE02

#include <thread>
#include <iostream>
#include <future>

void foo(std::promise<int> promise)
{
    promise.set_value(42);
    while (true);
}

int main(void)
{
    std::promise<int> promise;
    auto future = promise.get_future();

    std::thread t{foo, std::move(promise)};

    future.wait();
    std::cout << "The answer is: " << future.get() << '\n';

    t.join();

    // Never reached
    return 0;
}

// The answer is: 42

#endif
