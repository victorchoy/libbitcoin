#ifndef LIBBITCOIN_STORAGE_ERRORS_H
#define LIBBITCOIN_STORAGE_ERRORS_H

#include <system_error>

namespace libbitcoin {

enum class error
{
    // storage errors
    object_doesnt_exist = 1,
    object_already_exists,
    // network errors
    system_network_error
};

class error_category_impl
  : public std::error_category
{
public:
    virtual const char* name() const;
    virtual std::string message(int ev) const;
};

const std::error_category& error_category();

std::error_code make_error_code(error e);
std::error_condition make_error_condition(error e);

} // libbitcoin

namespace std
{
    template <>
    struct is_error_code_enum<libbitcoin::error>
      : public true_type {};
}

#endif

