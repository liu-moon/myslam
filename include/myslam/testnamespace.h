#pragma once
#include <memory>

namespace myslam
{
    class Liu
    {
    public:
        typedef std::shared_ptr<Liu> Ptr;
        int a = 0;

    public:
        Liu() {};
        void printa();
    };
}