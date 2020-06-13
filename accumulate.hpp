#pragma once

namespace itertools
{
    //template <typename T>
    //auto sum = [](T x, T y) { return x + y; }
    typedef struct
    {
        template <typename S>
        S operator()(S x, S y) const
        {
            return x + y;
        }
    } _sum;

    template <typename C, typename F = _sum>
    class accumulate
    {
    protected:
        C container;
        F function;

    public:
        accumulate(C c, F f = _sum())
            : container(c), function(f) {}

        class iterator
        {
        protected:
            F function;
            typename C::iterator it;
            typename C::iterator last;
            decltype(*(container.begin())) sum;

        public:
            iterator(typename C::iterator first, typename C::iterator l, F fun)
                : it(first), last(l), function(fun), sum(*first) {}

            // ++i;
            iterator &operator++()
            {
                ++it;
                if (it != last)
                    sum = function(sum, *it);
                return *this;
            }
            // i++;
            iterator operator++(int)
            {
                iterator i = *this;
                ++it;
                if (it != last)
                    sum = function(sum, *it);
                return i;
            }
            bool operator==(const iterator &other) const
            {
                return it == other.it;
            }
            bool operator!=(const iterator &other) const
            {
                return it != other.it;
            }
            auto operator*() const
            {
                return sum;
            }

            iterator &operator=(const iterator &other)
            {
                if (*this != other)
                {
                    this->it = other.it;
                    this->last = other.last;
                    this->sum = other.sum;
                    this->function = other.function;
                }
                return *this;
            }
        };
        iterator begin()
        {
            return iterator(container.begin(), container.end(), function);
        }

        iterator end()
        {
            return iterator(container.end(), container.end(), function);
        }
    };
} // namespace itertools