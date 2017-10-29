#include "computor.hpp"

int main(int argc, char *argv[])
{
   Computor math = Computor((string)argv[1]);

    math.solve();
    return (0);
}