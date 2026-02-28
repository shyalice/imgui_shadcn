//
// Created by Kai Tears on 27/02/2026.
//

#ifndef SHADCN_IMGUI_FONTS_HPP
#define SHADCN_IMGUI_FONTS_HPP

#include "imgui.h"

#include <unordered_map>
#include <utility>
#include <string>

namespace shadcn
{
    struct Font
    {
        std::pair< ImFont*, int > data;

        ImVec2 calculateSize( const std::string& text ) const;
        void renderText( ImDrawList* draw, const ImVec2& pos, const ImVec2& pad, const ImColor& color, const std::string& value ) const;
    };

    class CFonts
    {
        struct TempFontData
        {
            int sizePixels;
            ImFontConfig* fontConfig;
            const ImWchar* glyphRanges;
        };

        std::unordered_map< std::string, Font > m_list;

    public:
        CFonts( );
        ~CFonts( );

        static constexpr float kMaxScale = 2.5f;

        Font& get( const std::string& key );
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_FONTS_HPP
