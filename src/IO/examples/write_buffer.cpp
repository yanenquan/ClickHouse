#include <string>

#include <iostream>
#include <sstream>

#include <base/types.h>
#include <IO/WriteHelpers.h>
#include <IO/WriteBufferFromOStream.h>


int main(int, char **)
{
    try
    {
        Int64 a = -123456;
        Float64 b = 123.456;
        String c = "вася pe\ttya";
        String d = "'xyz\\";

        std::stringstream s;    // STYLE_CHECK_ALLOW_STD_STRING_STREAM
        s.exceptions(std::ios::failbit);

        {
            DB::WriteBufferFromOStream out(s);

            DB::writeIntText(a, out);
            DB::writeChar(' ', out);

            DB::writeFloatText(b, out);
            DB::writeChar(' ', out);

            DB::writeEscapedString(c, out);
            DB::writeChar('\t', out);

            DB::writeQuotedString(d, out);
            DB::writeChar('\n', out);
        }

        std::cout << s.str();
    }
    catch (const DB::Exception & e)
    {
        std::cerr << e.what() << ", " << e.displayText() << std::endl;
        return 1;
    }

    return 0;
}
