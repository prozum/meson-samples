# Cool emscripten demos
- https://blog.fazibear.me/definitive-guide-to-rust-sdl-2-and-emscripten-93d707b22bbb
- https://win95.ajf.me/
- http://boxedwine.sourceforge.net/b4/games.html
- https://tbfleming.github.io/em-shell/
- http://game.prozum.dk/randsim/

# Dependencies
- glibc
- python 3
- flatpak (Gnome Builder)

# Install emscripten
wget https://s3.amazonaws.com/mozilla-games/emscripten/releases/emsdk-portable.tar.gz
sudo tar -xf emsdk-portable.tar.gz -C /opt/

source /opt/emsdk-portable/emsdk_env.sh
emsdk update
emsdk install latest
emsdk activate latest

# Install git, ninja & flatpak
sudo dnf install git ninja-build flatpak
sudo apt install git ninja flatpak

# Install meson
sudo dnf install python3-pip
sudo apt install python3-pip

# Install meson
sudo pip3 install meson

# Install and run Gnome Builder flatpak
flatpak install --from https://git.gnome.org/browse/gnome-apps-nightly/plain/gnome-builder.flatpakref?h=stable

flatpak run org.gnome.Builder
