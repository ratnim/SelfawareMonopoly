#pragma once

#include <memory>

template <typename BaseState>
class Budhist
{
public:
    template <typename State, typename... args>
    void stateChange(args&&... parameters)
    {
        m_state = std::make_unique<State>(std::forward<args>(parameters)...);
    }

protected:
    std::unique_ptr<BaseState> m_state;
};
