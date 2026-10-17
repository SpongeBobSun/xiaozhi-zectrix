# Built-in fonts for the Zectrix board

## font_ark_pixel_24_1.c

- 内容：24 px、1 bpp（无抗锯齿）中文位图字体，覆盖 5709 个常用汉字与标点。
- 来源：[Ark Pixel Font（方舟像素字体）](https://github.com/TakWolf/ark-pixel-font)
  的 12 px 简体中文设计（`zh_hans`），以 **2 倍整数放大**渲染到 24 px。
- 为什么用像素字体：本面板是 1 bpp，矢量字体（Noto Sans SC 等）经过二值化后
  笔画会断裂或粘连；像素字体每个字形都按整数像素网格设计，整数倍渲染后完全锐利。
- 许可证：SIL Open Font License 1.1（OFL-1.1，见 release 内的 `OFL.txt`）。
- 重新生成（需要 Node.js）：

  ```bash
  # 1) 从 release 取 12px zh_hans 的 woff2，转成 ttf
  python -m pip install fonttools brotli
  python - <<'PY2'
  from fontTools.ttLib import TTFont
  f = TTFont("ark-pixel-12px-proportional-zh_hans.ttf.woff2")
  f.flavor = None
  f.save("ArkPixel-12px-zh_hans.ttf")
  PY2

  # 2) 生成 1bpp LVGL 字体（size 必须是 12 的整数倍）
  npx --yes lv_font_conv@1.5.3 --no-compress --no-prefilter     --force-fast-kern-format --font ArkPixel-12px-zh_hans.ttf --autohint-off     --symbols "<common.json 与字体 cmap 的交集字符>"     --format lvgl --bpp 1 --size 24     --lv-font-name font_ark_pixel_24_1 -o font_ark_pixel_24_1.c
  ```

> 字体名格式为 `font_<family>_<size>_<bpp>`，`main/CMakeLists.txt` 会从中解析
> 字号和 bpp，所以新增字体族不需要改 CMake 逻辑。

## font_noto_emoji_96_1.c

- 内容：96 px、1 bpp（无抗锯齿）单色线条表情位图，覆盖 21 个情绪表情。
- 来源：由 [Noto Emoji](https://fonts.google.com/noto/specimen/Noto+Emoji)
  生成（单色 glyf 轮廓，**非**彩色版本）。
- 许可证：SIL Open Font License 1.1（OFL-1.1），与原字体一致；
  原始字体版权归 Google LLC 所有。
- 重新生成：

  ```bash
  # Noto Emoji 的 woff2 可从 @fontsource/noto-emoji 获取，先转成 ttf：
  python -m pip install fonttools brotli
  python - <<'PY'
  from fontTools.ttLib import TTFont
  f = TTFont("noto-emoji-emoji-400-normal.woff2"); f.flavor = None
  f.save("NotoEmoji-Regular.ttf")
  PY

  npx --yes lv_font_conv@1.5.3 --no-compress --no-prefilter     --force-fast-kern-format --font NotoEmoji-Regular.ttf     --range 0x1f602,0x1f606,...     --format lvgl --bpp 1 --size 96     --lv-font-name font_noto_emoji_96_1 -o font_noto_emoji_96_1.c
  ```

> 表情字体通过 `BUILTIN_EMOJI_FONT` 按板卡选择（默认 `font_noto_emoji_30_4`，
> 与上游一致）；本板卡用 `font_noto_emoji_96_1`。
