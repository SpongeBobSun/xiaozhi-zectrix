# Built-in fonts for the Zectrix board

## font_noto_sans_basic_18_1.c

- 内容：18 px、1 bpp（无抗锯齿）中文位图字体，覆盖 5985 个常用汉字与标点。
- 来源：由 [Noto Sans SC](https://fonts.google.com/noto/specimen/Noto+Sans+SC) 生成
  （Regular / wght=400，用 fontTools 从可变字体实例化）。
- 许可证：Noto Sans SC 采用 SIL Open Font License 1.1（OFL-1.1）。
  本文件是其位图渲染结果，同样按 OFL-1.1 使用与再分发；
  原始字体版权归 Google LLC 所有。
- 重新生成（需要 Node.js）：

  ```bash
  # 1) 从 NotoSansSC-VF.ttf 实例化 Regular
  python -m pip install fonttools
  python - <<'PY'
  from fontTools.ttLib import TTFont
  from fontTools.varLib import instancer
  f = TTFont("NotoSansSC-VF.ttf")
  instancer.instantiateVariableFont(f, {"wght": 400}).save("NotoSansSC-Regular.ttf")
  PY

  # 2) 生成 1bpp LVGL 字体（字符集取自 78__xiaozhi-fonts/charsets/common.json）
  npx --yes lv_font_conv@1.5.3 --no-compress --no-prefilter \
    --force-fast-kern-format \
    --font NotoSansSC-Regular.ttf --autohint-off \
    --symbols "<common.json 与字体 cmap 的交集字符>" \
    --format lvgl --bpp 1 --size 18 \
    --lv-font-name font_noto_sans_basic_18_1 -o font_noto_sans_basic_18_1.c
  ```

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
