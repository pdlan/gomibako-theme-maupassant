[maupassant](https://github.com/pagecho/maupassant) for [Gomibako](https://github.com/pdlan/gomibako)

## How to Install

Supposing the path to Gomibako is /path/to/gomibako

```
git clone https://github.com/pdlan/gomibako-theme-maupassant.git
cd gomibako-theme-maupassant
mkdir build
cd build
cmake -DGOMIBAKO_DIRECTORY=/path/to/gomibako ..
make
make install
```

Then edit the configuration file of Gomibako and change theme to libtheme_maupassant.so (Linux) / libtheme_maupassant.dylib (macOS) / theme_maupassant.dll (Windows).

You can edit /path/to/gomibako/custom_sidebar.html to customize the sidebar
and /path/to/gomibako/comment.html to add code of commentary system (e.g. Disqus).