//
// Created by Kai Tears on 27/02/2026.
//

#include "shadcn.hpp"

#include "fonts/fonts.hpp"
#include "styles/styles.hpp"

using shadcn::Entry;
using shadcn::GlobalContext;

Entry::Entry( )
{
    g = std::make_unique< GlobalContext >( );
    initialized = true;
}

Entry::~Entry( ) = default;

GlobalContext::GlobalContext( )
{
    auto& style = ImGui::GetStyle( );
    style.CurveTessellationTol = 0.1f;
    style.ItemSpacing = { 10, 10 };

    fonts = std::make_unique< CFonts >( );
    styles = std::make_unique< CStyles >( );
}

GlobalContext::~GlobalContext( ) = default;

std::unique_ptr< GlobalContext > shadcn::g;
