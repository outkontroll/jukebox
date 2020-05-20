#include "RectangleMatcher.h"

namespace juce {

void PrintTo(const Rectangle<float>& r, std::ostream* os)
{
    *os << "[" << r.getX() << ", " << r.getY() << "] - [" << r.getRight() << ", " << r.getBottom() << "], w:" << r.getWidth() << ", h" << r.getHeight() << "\n";
}

}
