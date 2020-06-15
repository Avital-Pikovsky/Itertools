#pragma once

namespace itertools
{

    template <typename F, typename C>
    class filterfalse
    {
    protected:
        C container;
        F filter;

    public:
        filterfalse(F f, C c)
            : filter(f), container(c) {}

        class iterator
        {
        protected:
            F filter;
            typename C::iterator it;
            typename C::iterator last;

        public:
            iterator(F fil, typename C::iterator first, typename C::iterator l)
                : filter(fil), it(first), last(l) {
                    while (it != last && filter(*it))
                    ++it;
                }

            // ++i;
            iterator &operator++()
            {
                ++it;
                while (it != last && filter(*it))
                    ++it;
                return *this;
            }
            // i++;
            iterator operator++(int)
            {
                iterator i = *this;
                ++(*this);
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
            auto operator*()
            {
                return *it;
            }

            iterator &operator=(const iterator &other)
            {
                if (*this != other)
                {
                    this->it = other.it;
                    this->last = other.last;
                    this->filter = other.filter;
                }
                return *this;
            }
        };
        iterator begin()
        {
            return iterator(filter, container.begin(), container.end());
        }

        iterator end()
        {
            return iterator(filter, container.end(), container.end());
        }
    };
} // namespace itertools