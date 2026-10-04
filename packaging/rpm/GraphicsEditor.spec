Name:           GraphicsEditor
Version:        1.0
Release:        1%{?dist}
Summary:        Приложение для создания и редактирования графических фигур.

License:        MIT
URL:            https://github.com/Frolotey1/GraphicsEditor
Source0:        %{name}-%{version}.tar.gz
Source1:        graphics-editor.desktop
Source2:        graphics-editor-256.png

BuildRequires:  qt6-qtbase-devel
BuildRequires:  qt6-qtbase
BuildRequires:  gcc-c++
BuildRequires:  make

Requires:       qt6-qtbase
Requires:       qt6-qtbase-gui

%global debug_package %{nil}

%description
Приложение для создания и редактирования графических фигур.

%prep
%autosetup -n %{name}-%{version}

%build
%{_qt6_qmake} GraphicsEditor.pro
%make_build

%install
%make_install INSTALL_ROOT=%{buildroot}

install -Dm0644 %{SOURCE1} %{buildroot}%{_datadir}/applications/graphics-editor.desktop
install -Dm0644 %{SOURCE2} %{buildroot}%{_datadir}/icons/hicolor/256x256/apps/graphics-editor-256.png

%files
%{_bindir}/GraphicsEditor
%{_datadir}/applications/graphics-editor.desktop
%{_datadir}/icons/hicolor/256x256/apps/graphics-editor-256.png

%changelog
* Fri Oct 03 2025 Name Lastname <frolotey@gmail.com> - 1.0-1
- Initial package
