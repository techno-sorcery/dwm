# dwm
My personal build of DWM, customized with a set of "common sense", spectrwm-esque patches and keybinds.


## Setup

```bash
git clone https://github.com/techno-sorcery/dwm
cd dwm
sudo make install
```

Refer to suckless' documentation for configuration and patching info. Some things, like modifying brightness and volume,
are specific to my machine and might not work out-of-the-box for you.


## Patches

- accessnthmon - Arranges monitors by physical placement instead of initialization order
- [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/) - Adds keybind to toggle fullscreen for dwm windows
- [staticstatus](https://dwm.suckless.org/patches/staticstatus/) - Ties the status bar to a single monitor
- [adjacenttag-skipvacant](https://dwm.suckless.org/patches/adjacenttag/) - Adds keybinds to move the view/windows between adjacent tags
- [fixborders](https://dwm.suckless.org/patches/alpha/) - Fixes transparent borders when using a compositor like Picom
- [attachbottom](https://dwm.suckless.org/patches/attachbottom/) - Adds new windows to the bottom of the stack, instead of the top
- [bar height](https://dwm.suckless.org/patches/bar_height/) - Allows the default bar height to manually be set
- [cyclelayouts](https://dwm.suckless.org/patches/cyclelayouts/) - Adds keybinds to cycle between window layouts
- [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/) - Hides tags with no assigned windows from bar
- [pertag](https://dwm.suckless.org/patches/pertag/) - Layouts are assigned to specific tags, instead of every single one
- [push](https://dwm.suckless.org/patches/push/) - Adds keybinds to move windows up/down the stack
- [restartsig](https://dwm.suckless.org/patches/restartsig/) - Adds a keybind and signal handler to restart DWM 
- [scratchpad](https://dwm.suckless.org/patches/scratchpad/) - Lets you spawn a floating "scratchpad" terminal
- [sticky](https://dwm.suckless.org/patches/sticky/) - Adds a keybind to make "sticky" windows appear across all tags
- [stickyindicator](https://dwm.suckless.org/patches/stickyindicator/) - Indicates whether a window is sticky or not
- [swallow](https://dwm.suckless.org/patches/swallow/) - Terminal windows "swallow" child processes
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/) - Adjustable inner gaps between windows
- [warp](https://dwm.suckless.org/patches/warp/) - Moves mouse cursor to the center of newly focused screens or windows
- [xresources](https://dwm.suckless.org/patches/xresources/) - Uses Xresources to handle certain settings


## Keybinds
### Window movement
- alt + j               - Move to next window
- alt + k               - Move to previous window
- alt + enter           - Move window to/from stack
- alt + x               - Kill window


### Stack
- alt + i               - Increment number of windows in stack
- alt + d               - Decrement number of windows in stack


### Sizing
- alt + h               - Enlarge window horizontally
- alt + l               - Decrease window horizontally
- alt + shift + u       - Enlarge window vertically
- alt + shift + d       - Decrease window vertically
- alt + shift + r       - Reset vertical window sizing


### Tags
- alt + tab             - Move to last viewed tag
- alt + \<num\>         - Move to selected tag
- alt + shift + \<num\> - Move window to selected tag
- alt + shift + h       - Move to previous tag
- alt + shift + l       - Move to next tag

- alt + shift + space   - Toggle window floating
- alt + s               - Toggle window sticky

### Monitors
- alt + .               - Move to next monitor
- alt + ,               - Move to previous monitor
- alt + shift + .       - Move window (and view) to next monitor
- alt + shift + ,       - Move window (and view) to previous monitor

### Layouts
- alt + space           - Toggle current and last layout
- alt + ctrl + h        - Previous layout
- alt + ctrl + l        - Next layout
- alt + shift + j       - Move window up stack
- alt + shift + k       - Move window down stack

- alt + t               - Use tiled layout
- alt + v               - Use vertical stacked layout
- alt + g               - Use grid layout
- alt + m               - Use monocle layout


### Misc 
- alt + shift + q       - Restart dwm session
- alt + ctrl + shift + q- Exit dwm to tty
- alt + b               - Toggles bar

### Programs
- alt + p               - Opens rofi
- alt + shift + enter   - Spawns terminal (st)
- alt + \`              - Toggles scratchpad
- alt + r               - Restart dwmblocks
- PrintScreen           - Take screenshot with scrot
