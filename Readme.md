# Requirements
- Python 3

# Install Emscripten
```bash
wget https://s3.amazonaws.com/mozilla-games/emscripten/releases/emsdk-portable.tar.gz
sudo tar -xf emsdk-portable.tar.gz -C /opt/

source /opt/emsdk-portable/emsdk_env.sh
emsdk update
emsdk install latest
emsdk activate latest
```

# Install Git, Ninja & Flatpak
```bash
# Fedora
sudo dnf install git ninja-build flatpak
# Ubuntu
sudo add-apt-repository ppa:alexlarsson/flatpak
sudo apt update
sudo apt install flatpak
```

# Install Meson
```bash
# Fedora
sudo dnf install python3-pip
# Ubuntu
sudo apt install python3-pip

sudo pip3 install meson
```

# Build from CLI
```bash
git clone git@github.com:prozum/samples.git && cd samples
meson --cross-file=emscripten.txt . build
ninja -C build
```

# Install and run Gnome Builder flatpak (Optional)
```bash
flatpak install --from https://git.gnome.org/browse/gnome-apps-nightly/plain/gnome-builder.flatpakref?h=stable

flatpak run org.gnome.Builder
```

# Cool Emscripten Demos
- [Rust + Emscripten + SDL2](https://blog.fazibear.me/definitive-guide-to-rust-sdl-2-and-emscripten-93d707b22bbb)
- [Windows 95](https://win95.ajf.me/)
- [Wine](http://boxedwine.sourceforge.net/b4/games.html)
- [Busybox](https://tbfleming.github.io/em-shell/)
- [Drone Simulator](http://game.prozum.dk/randsim/)


