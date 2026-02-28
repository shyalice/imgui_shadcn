import json
import re
import sys
from pathlib import Path

def to_macro_name(s: str) -> str:
    s = re.sub(r"[^0-9a-zA-Z]+", "_", s).strip("_")
    return s.upper()

def parse_codepoint(icon_obj: dict) -> int:
    enc = icon_obj.get("encodedCode") or ""
    if enc:
        if enc[0] == "\\":
            hexpart = enc[1:]
            if re.fullmatch(r"[0-9a-fA-F]{3,6}", hexpart):
                return int(hexpart, 16)

        if len(enc) == 1:
            return ord(enc)

    uni = icon_obj.get("unicode") or ""
    m = re.search(r"&#(\d+);", uni)
    if m:
        return int(m.group(1), 10)

    raise ValueError(f"Cannot parse codepoint from: {icon_obj}")

def utf8_define_str(cp: int) -> str:
    b = chr(cp).encode("utf-8")
    return "".join(f"\\x{byte:02x}" for byte in b)

def compress_ranges(codepoints: list[int]) -> list[tuple[int, int]]:
    cps = sorted(set(codepoints))
    if not cps:
        return []
    ranges = []
    start = prev = cps[0]
    for cp in cps[1:]:
        if cp == prev + 1:
            prev = cp
            continue
        ranges.append((start, prev))
        start = prev = cp
    ranges.append((start, prev))
    return ranges

def main():
    if len(sys.argv) < 3:
        print("Usage: gen_lucide_header.py <lucide.json> <out_header.h> [PREFIX]")
        print("Example: gen_lucide_header.py lucide.json lucide_icons.h LUCIDE")
        sys.exit(1)

    in_path = Path(sys.argv[1])
    out_path = Path(sys.argv[2])
    prefix = sys.argv[3] if len(sys.argv) >= 4 else "LUCIDE"

    data = json.loads(in_path.read_text(encoding="utf-8"))

    items = []
    codepoints = []
    for name, obj in data.items():
        cp = parse_codepoint(obj)
        items.append((name, cp))
        codepoints.append(cp)

    items.sort(key=lambda x: x[0].lower())
    cp_min = min(codepoints)
    cp_max = max(codepoints)
    ranges = compress_ranges(codepoints)

    guard = f"{prefix}_ICONS_H".upper()
    lines = []
    lines.append("// Auto-generated. Do not edit by hand.\n")
    lines.append(f"#ifndef {guard}\n#define {guard}\n\n")
    lines.append("#include <stdint.h>\n\n")
    lines.append(f"#define ICON_MIN_{prefix} 0x{cp_min:04X}\n")
    lines.append(f"#define ICON_MAX_{prefix} 0x{cp_max:04X}\n\n")

    lines.append("// ImGui glyph ranges (use with AddFontFromFileTTF(..., ranges))\n")
    lines.append("// Example:\n")
    lines.append("//   ImFontConfig cfg; cfg.MergeMode = true;\n")
    lines.append(f"//   io.Fonts->AddFontFromFileTTF(\"lucide.ttf\", size, &cfg, ICON_{prefix}_RANGES);\n\n")
    lines.append("#ifdef __cplusplus\n")
    lines.append("#include \"imgui.h\"\n")
    lines.append(f"static const ImWchar ICON_{prefix}_RANGES[] = {{\n")
    for a, b in ranges:
        lines.append(f"    0x{a:04X}, 0x{b:04X},\n")
    lines.append("    0\n};\n")
    lines.append("#endif\n\n")

    for name, cp in items:
        macro = f"ICON_{prefix}_{to_macro_name(name)}"
        u8 = utf8_define_str(cp)
        lines.append(f"#define {macro} \"{u8}\"  // U+{cp:04X}\n")

    lines.append(f"\n#endif // {guard}\n")
    out_path.write_text("".join(lines), encoding="utf-8")

if __name__ == "__main__":
    main()