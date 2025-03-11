SuperAwesomeCool DWM Configuration
============================

This is my personal DWM config, which I've been using (with occasional changes) for the past couple of years. Some keybindings are different, but I don't feel like enumerating them so just check config.def.h if you're interested.  

Status bar not included (dwmblocks and all my bash status bar widgets are in my [Dotfiles](https://github.com/techno-sorcery/Dotfiles) repo)  

Patch List
---
- actualfullscreen - Adds keybind to make windows fill the whole screen, without any borders  
- adjacenttag - Adds keybinds to switch to adjacent tags
- alpha - Adds transparency to the status bar
- attachbottom - Causes new windows to be attached to the stack bottom
- vanitygaps - Useless gap plugin I used for a while but disabled
- cyclelayouts - Adds keybinds to cycle between enabled layouts
- hide_vacant_tags - hides... vacant tags! *gasp!*
- pertag - Layouts are now assigned per-tag, rather than being universally applied
- push_no_master - Adds keybinds to move windows within the stack
- removeborder - Doesn't draw borders if a single window is on-screen
- restartsig - Adds keybind to restart dwm
- statuspadding - Adds padding to the status bar
- swallow - Terminal windows now swallow applications launched from them
- warp - Cursor is automatically "warped" between selected windows/screens
