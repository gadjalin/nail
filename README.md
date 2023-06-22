# Nail

&nbsp;&nbsp; *"Because all you have is a hammer."*

---

## The Story

I regularly found myself thinking

&nbsp;&nbsp; *"Would be useful if I had these little pieces of code in this
project..."*

So I decided to put them all in a library I could easily include in my
projects, and that would be small enough not to bloat it too much.

I still don't really know if anyone else would find it useful though, and I
think that is what the name reflects : nails are essential to building
anything, really, but some people just prefer to use screws, if that makes any
sense.

## The Project

Nail is a utility library. It aims at providing all these little things you
wish you had during development and that does not need to be that complicated, but can always be extended when necessary.

## Features

Nail currently features the following:

 - Debugging Utilities
	- An extensive implementation of **Assertions** inspired by [this article](https://www.foonathan.net/2016/09/assertions/)
	- An implementation of **Tee**, when you don't want to put std::cout everywhere while debugging, inspired by [this article](https://www.fluentcpp.com/2017/09/29/tee-getting-precious-debug-info-easily/)
	- A **TODO_BEFORE** macro, when you want to fix yourself a deadline, inspired by [this other article](https://www.fluentcpp.com/2019/01/01/todo_before-clean-codebase-2019/)
	- A **__FILENAME__** macro, without the full path, and **SourceLocation** type (soon to be replace by c++20's [std::source_location](https://en.cppreference.com/w/cpp/utility/source_location))
	- A **crash()** method, for difficult times.
 - A Customisable Event System
	- An **EventQueue**, when a time will come to **process()**
	- An **EventDispatcher**, because you can handle it better
	- A **Signal/Listener** system, when it really can't wait
 - Strong Types [for strong interfaces](https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/)
    - Additionaly, **Ranged** Numerical values, when you only accept values in a specific range
 - **Shared Library** management
 - **System Info** Utilities (Memory, OS, Architecture...)

## Coming Soon

 - A **Console** interface
 - A **Logging** system
 - Custom **Memory Management**
 - **Time/Date/Chrono** Utilities
 - **Math** Utilities
 - **Random Number Generator** Utility
 - Probably more uninteresting stuff...

## Installation

I'll be working on this, otherwise it's just cmake

## Credits

Developer: [Gaétan "Gad" Jalin](https://github.com/AarnoldGad/) (hello)

Licence: zlib (See LICENCE file)


