arch=$(uname -m)
if [ "$arch" = "arm64" ]; then
    export CFLAGS="-mmacosx-version-min=14.0 -target arm64-apple-macos14.0"
    export CXXFLAGS="-mmacosx-version-min=14.0 -target arm64-apple-macos14.0"
    export LDFLAGS="-L/opt/homebrew/opt/ffmpeg@6/lib"
    export CPPFLAGS="-I/opt/homebrew/opt/ffmpeg@6/include"
    export PKG_CONFIG_PATH="/opt/homebrew/opt/ffmpeg@6/lib/pkgconfig"
    export MACOS_SDK=""
    swift_flags="-target arm64-apple-macos14.0"
elif [ "$arch" = "x86_64" ]; then
    export CFLAGS="-mmacosx-version-min=11.0 -target x86_64-apple-macos11.0"
    export CXXFLAGS="-mmacosx-version-min=11.0 -target x86_64-apple-macos11.0"
    export TOOLCHAINS="org.swift.5101202406041a"
    export MACOS_SDK="/Users/wg/Downloads/MacOSX12.0.sdk"
    export LDFLAGS="-L/usr/local/opt/ffmpeg@5/lib"
    export CPPFLAGS="-I/usr/local/opt/ffmpeg@5/include"
    export PKG_CONFIG_PATH="/usr/local/opt/ffmpeg@5/lib/pkgconfig"
    swift_flags="-target x86_64-apple-macos11.0"
fi


meson setup build -Dlibmpv=true -Dswift-flags="$swift_flags" --wipe
meson compile -C build -v -j8