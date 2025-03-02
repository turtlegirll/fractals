#include "pch.h"
#include "fractal.h"
#if __has_include("fractal.g.cpp")
#include "fractal.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::fractals::implementation
{
    int32_t fractal::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void fractal::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void fractal::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
