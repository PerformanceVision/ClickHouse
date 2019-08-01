#include <Functions/FunctionFactory.h>
#include <Functions/FunctionStringToString.h>
#include "FunctionsURL.h"
#include "domain.h"
#include <common/find_symbols.h>

namespace DB
{

struct ExtractPathFull
{
    static size_t getReserveLengthForElement() { return 30; }

    static void execute(const Pos data, const size_t size, Pos & res_data, size_t & res_size)
    {
        res_data = data;
        res_size = 0;

        Pos pos = data;
        Pos end = pos + size;

        StringRef host = getURLHost(data, size);

        if (host.size && end != (pos = find_first_symbols<'/'>(host.data + host.size, end)))
        {
            res_data = pos;
            res_size = end - res_data;
        }
    }
};

struct NamePathFull { static constexpr auto name = "pathFull"; };
using FunctionPathFull = FunctionStringToString<ExtractSubstringImpl<ExtractPathFull>, NamePathFull>;

void registerFunctionPathFull(FunctionFactory & factory)
{
    factory.registerFunction<FunctionPathFull>();
}

}
