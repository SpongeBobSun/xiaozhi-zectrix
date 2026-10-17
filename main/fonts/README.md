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

> 表情不再使用自带字体：改为由 `BUILTIN_EMOJI_FONT` 指定项目自带的
> `font_noto_emoji_30_1`（1 bpp 单色线条 emoji），显示时放大 2 倍。
