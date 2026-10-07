FROM fedora:44 AS builder

RUN dnf config-manager disable fedora-cisco-openh264

RUN dnf install -y \
    qt6-qtbase-devel \
    qt6-qtpdf-devel \
    qt6-qtmultimedia-devel \
    qt6-qtsvg-devel \
    qt6-qttools-devel \
    qt6-qtwayland-devel \
    gcc-c++ \
    make \
    && dnf clean all

WORKDIR /src
COPY . .

RUN qmake6 GraphicsEditor.pro && make -j$(nproc)

FROM fedora:44

RUN dnf config-manager disable fedora-cisco-openh264

RUN dnf install -y \
    qt6-qtbase \
    qt6-qtbase-gui \
    qt6-qtpdf \
    qt6-qtmultimedia \
    qt6-qtsvg \
    qt6-qtwayland \
    mesa-libGL \
    mesa-libEGL \
    libxkbcommon-x11 \
    xcb-util-cursor \
    && dnf clean all

COPY --from=builder /src/GraphicsEditor /usr/bin/GraphicsEditor
COPY --from=builder /src/packaging/rpm/graphics-editor.desktop /usr/share/applications/
COPY --from=builder /src/packaging/rpm/graphics-editor-256.png /usr/share/icons/hicolor/256x256/apps/

ENTRYPOINT ["/usr/bin/GraphicsEditor"]
