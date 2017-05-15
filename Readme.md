# Install dependencies

## Install Emscripten
```bash
wget https://s3.amazonaws.com/mozilla-games/emscripten/releases/emsdk-portable.tar.gz
sudo tar -xf emsdk-portable.tar.gz -C /opt/

source /opt/emsdk-portable/emsdk_env.sh
emsdk update
emsdk install latest
emsdk activate latest
```

## Install Git, Ninja & Meson
```bash
# Fedora
sudo dnf install git ninja-build python3-pip
# Ubuntu
sudo apt install git ninja-build python3-pip

# Shared
sudo pip3 install meson
```

# Build from CLI
```bash
git clone https://github.com/prozum/meson-samples.git && cd meson-samples
meson --cross-file=emscripten.txt . build
ninja -C build
```

# Run from CLI
```bash
python -m SimpleHTTPServer &
xdg-open http://localhost:8000/build
# Select a sample folder
```

# Install and run Gnome Builder flatpak (Optional)
```bash
# Fedora
sudo dnf install flatpak
# Ubuntu
sudo dnf install flatpak
sudo add-apt-repository ppa:alexlarsson/flatpak
sudo apt update
sudo apt install flatpak

# Shared
flatpak install --from https://git.gnome.org/browse/gnome-apps-nightly/plain/gnome-builder.flatpakref?h=stable
flatpak run org.gnome.Builder
```

# Cool Emscripten Demos
- [LLVM](https://kripken.github.io/llvm.js/demo.html)
- [Busybox](https://tbfleming.github.io/em-shell/)
- [Windows 95](https://win95.ajf.me/)
- [Wine](http://boxedwine.sourceforge.net/b4/games.html)
- [Drone Simulator](http://game.prozum.dk/randsim/)
- [Rust + Emscripten + SDL2](https://blog.fazibear.me/definitive-guide-to-rust-sdl-2-and-emscripten-93d707b22bbb)
