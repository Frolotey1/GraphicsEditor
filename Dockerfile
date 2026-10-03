FROM fedora:44

RUN dnf install -y \
    qt6-qtbase \
    qt6-qtbase-gui \
    qt6-qtpdf \
    qt6-qtmultimedia \
    qt6-qtsvg \
    mesa-libGL \
    mesa-libEGL \
    libxkbcommon-x11 \
    xcb-util-cursor \
    xcb-util-wm \
    xcb-util-image \
    xcb-util-keysyms \
    xcb-util-renderutil \
    libxcb \
    && dnf clean all

COPY GraphicsEditor /usr/bin/GraphicsEditor
COPY graphics-editor.desktop /usr/share/applications/
COPY graphics-editor.png /usr/share/icons/hicolor/256x256/apps/

ENTRYPOINT ["/usr/bin/GraphicsEditor"]
