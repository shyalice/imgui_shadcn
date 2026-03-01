//
// Created by Kai Tears on 01/03/2026.
//

#ifndef SHADCN_IMGUI_SLIDER_HPP
#define SHADCN_IMGUI_SLIDER_HPP

#include "imgui.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <variant>

namespace shadcn
{
    enum class SliderStyle
    {
        Standard,
        Simple,
        Filled
    };

    struct Slider
    {
        struct SliderState
        {
            bool grabHovered = false;
            float offset = 0.0f;

            // I guess we'll use it only for Filled style for now
            ImVec2 heldOffset;
            float heldSizeMult;

            ImVec4 hover;
        };

        struct SliderData
        {
            ImVec2 size = { 16, 16 };
            int rounding = 10;
            SliderStyle style = SliderStyle::Standard;
            std::function< void( ) > onValueChanged = nullptr;
        };

        static std::unordered_map< std::string, SliderState > state;

        bool exScalar( const SliderData& data, const std::string& id, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags );

        Slider( const std::string& id, int* v, int v_min, int v_max, const SliderData& data );
        Slider( const std::string& id, float* v, float v_min, float v_max, const SliderData& data );
        ~Slider( );
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_SLIDER_HPP
