//
// Created by Kai Tears on 27/02/2026.
//

#include "fonts/fonts.hpp"

#include "fonts/geist/geist_400.hpp"
#include "fonts/geist/geist_500.hpp"
#include "fonts/geist/geist_600.hpp"
#include "fonts/geist/geist_700.hpp"

#include "fonts/lucide/lucide.hpp"
#include "fonts/lucide/lucide_defines.hpp"

#include <vector>

using shadcn::CFonts;
using shadcn::Font;

ImVec2 Font::calculateSize( const std::string& text ) const
{
    auto size = data.first->CalcTextSizeA( data.second, FLT_MAX, -1, text.c_str( ) );
    size.x -= 1;
    return size;
}

void Font::renderText( ImDrawList* draw, const ImVec2& pos, const ImVec2& pad, const ImColor& color, const std::string& value ) const
{
    auto const text_size = calculateSize( value );
    draw->AddText( data.first, data.second, pos - ImVec2( text_size.x * pad.x, text_size.y * pad.y ), color, value.c_str( ) );
}

CFonts::CFonts( )
{
    auto* fonts = ImGui::GetIO( ).Fonts;

    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.FontDataOwnedByAtlas = false;

    ImFontConfig config;
    config.FontDataOwnedByAtlas = false;

    static auto const merge_icons = [ & ]( int size ) -> void {
        icons_config.GlyphOffset.y = size / 2;
        fonts->AddFontFromMemoryTTF( fonts::kLucideIconsTTF, sizeof fonts::kLucideIconsTTF, static_cast< float >( size ) * kMaxScale, &icons_config, ICON_LUCIDE_RANGES );
    };

    static auto const add_font = [ & ]( void* font_data, int font_data_size, const TempFontData& data ) -> Font {
        auto const result = Font { .data = std::make_pair( fonts->AddFontFromMemoryTTF( font_data, font_data_size, static_cast< float >( data.sizePixels ) * kMaxScale, data.fontConfig, data.glyphRanges ), data.sizePixels ) };
        merge_icons( data.sizePixels );
        return result;
    };

    static std::vector< int > const font_sizes = {
        14, 16, 18, 20 };

    for ( auto const size : font_sizes )
    {
        m_list[ "geist_400_" + std::to_string( size ) ] = add_font( fonts::kGeist400TTF, sizeof fonts::kGeist400TTF, TempFontData { .sizePixels = size, .fontConfig = &config, .glyphRanges = fonts->GetGlyphRangesCyrillic( ) } );
        m_list[ "geist_500_" + std::to_string( size ) ] = add_font( fonts::kGeist500TTF, sizeof fonts::kGeist500TTF, TempFontData { .sizePixels = size, .fontConfig = &config, .glyphRanges = fonts->GetGlyphRangesCyrillic( ) } );
        m_list[ "geist_600_" + std::to_string( size ) ] = add_font( fonts::kGeist600TTF, sizeof fonts::kGeist600TTF, TempFontData { .sizePixels = size, .fontConfig = &config, .glyphRanges = fonts->GetGlyphRangesCyrillic( ) } );
        m_list[ "geist_700_" + std::to_string( size ) ] = add_font( fonts::kGeist700TTF, sizeof fonts::kGeist700TTF, TempFontData { .sizePixels = size, .fontConfig = &config, .glyphRanges = fonts->GetGlyphRangesCyrillic( ) } );
    }

    ImGui::GetIO( ).FontGlobalScale = 1.f / kMaxScale;
}

CFonts::~CFonts( ) = default;

Font& CFonts::get( const std::string& key )
{
    return m_list[ key ];
}