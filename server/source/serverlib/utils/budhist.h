#pragma once

#include <memory>
#include <type_traits>

template <typename BaseState>
class Budhist
{
public:
    template <typename State, typename... args>
    std::enable_if_t<std::is_constructible_v<State, args...>> stateChange(args&&... parameters)
    {
        m_state = std::make_unique<State>(std::forward<args>(parameters)...);
    }

    template <typename State, typename... args>
    std::enable_if_t<std::is_constructible_v<State, BaseState*, args...>> stateChange(args&&... parameters)
    {
        m_state = std::make_unique<State>(m_state.get(), std::forward<args>(parameters)...);
    }

protected:
    std::unique_ptr<BaseState> m_state;
};
