#!/bin/bash
set -e

NAME=GraphicsEditor
PKG_NAME=graphics-editor
VERSION=1.0
ARCH=amd64

cd "$(dirname "$0")/../.."

qmake6 GraphicsEditor.pro
make -j$(nproc)

rm -rf /tmp/deb
mkdir -p /tmp/deb/DEBIAN
mkdir -p /tmp/deb/usr/bin
mkdir -p /tmp/deb/usr/share/applications
mkdir -p /tmp/deb/usr/share/icons/hicolor/256x256/apps

cp GraphicsEditor /tmp/deb/usr/bin/
cp packaging/deb/graphics-editor.desktop /tmp/deb/usr/share/applications/
cp packaging/deb/graphics-editor.png /tmp/deb/usr/share/icons/hicolor/256x256/apps/

chmod 755 /tmp/deb/usr/bin/GraphicsEditor
chmod 644 /tmp/deb/usr/share/applications/graphics-editor.desktop
chmod 644 /tmp/deb/usr/share/icons/hicolor/256x256/apps/graphics-editor.png

cat > /tmp/deb/DEBIAN/control << EOF
Package: $PKG_NAME
Version: $VERSION
Architecture: $ARCH
Maintainer: Твоё Имя <твой_email@example.com>
Section: graphics
Priority: optional
Depends: libqt6core6, libqt6gui6, libqt6widgets6, libqt6pdf6, libqt6multimedia6, libqt6svg6, libqt6sql6, libqt6network6, libqt6printsupport6
Description: Графический редактор для создания и редактирования изображений
 Полноценный редактор с поддержкой векторных объектов,
 текста, пользовательских путей и экспорта в PDF.
EOF

dpkg-deb --build /tmp/deb ~/${PKG_NAME}_${VERSION}-1_${ARCH}.deb

ls -lh ~/${PKG_NAME}_${VERSION}-1_${ARCH}.deb
