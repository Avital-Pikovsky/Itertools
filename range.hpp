#pragma once

namespace itertools
{
    class range
    {
    protected:
        int first, last;

    public:

        //Constructor range:
        range(int f, int l) : first(f), last(l)
        {
        }

        class iterator
        {

        private:
            int current;

        public:
            //Constructor iterator:
            iterator(int c = 0)
                : current(c)
            {
            }
            // ++i;
            iterator &operator++()
            {
                current += 1;
                return *this;
            }
            // i++;
            const iterator operator++(int)
            {
                iterator temp = *this;
                current += 1;
                return temp;
            }

            bool operator==(const iterator &other) const
            {
                return current == other.current;
            }

            bool operator!=(const iterator &other) const
            {
                return current != other.current;
            }

            int operator*()
            {
                return current;
            }
            iterator &operator=(const iterator &other)
            {
                if (*this != other)
                {
                    this->current = other.current;
                }
                return *this;
            }
        };

        iterator begin() const
        {
            return iterator(first);
        }

        iterator end() const
        {
            return iterator(last);
        }
    };

} // namespace itertools
