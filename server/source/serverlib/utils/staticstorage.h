#pragma once

#include <memory>

template<typename stored>
class StaticStorage
{
public:
    static stored& instance()
    {
        return *s_model;
    }

    template<typename... parameter>
    static void reset(parameter&&... parameters)
    {
        s_model = std::make_unique<stored>(std::forward<parameter>(parameters)...);
    }

protected:
    static std::unique_ptr<stored> s_model;
};
