#include <bitcoin/error.hpp>

namespace libbitcoin {

const char* error_category_impl::name() const
{
    return "bitcoin";
}

std::string error_category_impl::message(int ev) const
{
    error ec = static_cast<error>(ev);
    switch (ec)
    {
    case error::object_doesnt_exist:
        return "Object does not exist";
    case error::object_already_exists:
        return "Matching previous object found";
    default:
        return "Unknown error";
    }
}

const std::error_category& error_category()
{
    static error_category_impl instance;
    return instance;
}

std::error_code make_error_code(error e)
{
    return std::error_code(static_cast<int>(e), error_category());
}

std::error_condition make_error_condition(error e)
{
    return std::error_condition(static_cast<int>(e), error_category());
}

} // libbitcoin

