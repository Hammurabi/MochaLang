class Clock
    public:
        long millis()
            return 0
        long nano()
            return 0

class Console
    public:
        void write(string out)
            print out
        void read(string& in)
            read in

class System
    private:
    public:
        Clock clock = new Clock()
        Console console = new Console()

class array<T>
    public:
        protected ulong length //can only be read from outside of class but never changed.
        T operator[] (ulong at)
            return _array[at]

        constructor(ulong size = 1)
            _array = new T(size)
            length = size
        destructor()
            delete _array

        void resize(ulong size)
            if size == length
                return
            x64_ptr<T> n = new T(size)
            if size < length
                memcpy(n, _array, size * sizeof(T))
            else
                memcpy(n, _array, length * sizeof(T))
            length = size
    private:
        x64_ptr<T> _array
        

class stack<T>
    private:
        array<T> _stack = 1
        uint     _index = 0
        uint     _size  = 1

        void push_element(T t)
            _stack.resize(++_size)
            _stack[_index++] = t

        T pop_element()
            if size - _index > 10
                _stack.resize(size - 10)
            return _stack[--_index]
    public:
        constructor()
        destructor()
            delete _stack
        void push(T element)
            push_element(element)
        T    pop()
            pop_element()
        T    top()
            return _stack[_index - 1]